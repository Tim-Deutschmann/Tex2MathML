#include "Tex2MathMLConverter.h"

#include "IO/stringio.h"
#include "generic/error.h"

#include "tex_symbols.h"

// #include <string.h>

#define LINE_BUFFER_SIZE	100

/*
⋅  &sdot;  &#x22c5;  It is used to specify dot product
⨯  &cross;  &#x2a2f;  It is used to specify cross product
‖  &vert;  &#x2016;  It is used to specify norm (magnitude) bars
⟨  &lang;  &#x27e8;  It is used to specify left angle bracket
⟩  &rang;  &#x27e9;  It is used to specify right angle bracket
∘  &compfn;  &#x2218;  It is used to specify function composition
→  &rarr;  &#x2192;  It is used to specify general function mapping
↦  &mapsto;  &#x21a6;  It is used to specify concrete function mapping
ı  &imath;  &#x0131;  It is used to specify dotless i
ȷ  &jmath;  &#x0237;  It is used to specify dotless j 
*/

struct TexCommand_s GlobalTexCommand [] =
{
	// main commands ---------------------------------------------------------------
	{"frac",	TC_frac,		0,	2,	"mfrac"},
	{"sqrt",	TC_sqrt,		1,	1,	"mroot"},
	{"stackrel",	TC_stackrel,		0,	2,	"mover"},
	// subsup ----------------------------------------------------------------------
	{"limits",	TC_limits,		0,	0,	""},
	{"mathop",	TC_mathop,		0,	0,	""},
	// environment -----------------------------------------------------------------
	{"begin",	TC_environment,		0,	2,	""},
	{"end",		TC_environment,		0,	1,	""},
	// decorations -----------------------------------------------------------------
	{"overline",	TC_decoration,		0,	1,	"mover"},
	{"underline",	TC_decoration,		0,	1,	"munder"},
	{"overbrace",	TC_decoration,		0,	1,	"mover"},
	{"underbrace",	TC_decoration,		0,	1,	"munder"},
	// math accents ----------------------------------------------------------------
	{"hat",		TC_accent,		0,	1,	"^"},
	{"breve",	TC_accent,		0,	1,	""},
	{"grave",	TC_accent,		0,	1,	"`"},
	{"acute",	TC_accent,		0,	1,	"'"},
	{"bar",		TC_accent,		0,	1,	"&macr;"},
	{"dot",		TC_accent,		0,	1,	"."},
	{"ddot",	TC_accent,		0,	1,	".."},
	{"tilde",	TC_accent,		0,	1,	"&Tilde;"},
	{"check",	TC_accent,		0,	1,	"v"},
	{"vec",		TC_accent,		0,	1,	"&rightarrow;"},
	// text ------------------------------------------------------------------------
	{"mbox",	TC_text_box,		0,	1,	"mtext"},
	{"textrm",	TC_text_box,		0,	1,	"mtext"},
	// font modification ---------------------------------------------------------------------------
	{"mathrm",	TC_font_modifier,		0,	1,	"roman"},
	{"mathbf",	TC_font_modifier,	0,	1,	"bold"},
	{"mathit",	TC_font_modifier,	0,	1,	"italic"},
	{"mathbi",	TC_font_modifier,	0,	1,	"bold-italic"},
	{"mathsf",	TC_font_modifier,	0,	1,	"sans-serif"},
	{"mathtt",	TC_font_modifier,	0,	1,	"monospace"},
	{"mathbb",	TC_font_modifier,	0,	1,	"double-struck"},
	{"mathnormal",	TC_font_modifier,	0,	1,	"normal"}
};

bool findCommand(const char *expression, int *pindex)
{
	int i, n = sizeof(GlobalTexCommand) / sizeof(GlobalTexCommand[0]);
	for(i=0;i<n;i++)
		if(!strcmp(expression, GlobalTexCommand[i].keyword))
		{
			*pindex = i;
			return true;
		}
	return false;
}

inline bool isSubSup(const char& c){return c == '_' || c == '^';}

void addMML(string& mml, const string& what, const char *mml_tag, const char *tag_parameter = 0)
{
	char buffer[LINE_BUFFER_SIZE];
	// sprintf(buffer, "<%s%c%s>%s</%s>", mml_tag, tag_parameter?' ':'\0', tag_parameter, what.c_str(), mml_tag);
	if(tag_parameter)
		sprintf(buffer, "<%s %s>%s</%s>", mml_tag, tag_parameter, what.c_str(), mml_tag);
	else
		sprintf(buffer, "<%s>%s</%s>", mml_tag, what.c_str(), mml_tag);
		
	mml += string(buffer);
}

const char *getOppositeBracket(const char *xbrace)
{
	switch(*xbrace)
	{
		case '{': return "}";
		case '}': return "{";
		case '(': return ")";
		case ')': return "(";
		case '[': return "]";
		case ']': return "[";
		case 'l': return "right";
		case 'r': return "left";
		case '|': return "|";
		default:;
	}
	return 0;
}

Tex2MathMLConverter::Tex2MathMLConverter()
{
	UserTexSymbol = 0;
	tex_symbol_data = 0;
	no_user_tex_symbols = 0;
	b_matrices_in_displaystyle = false;
	addParameter(&b_matrices_in_displaystyle, type_bool, "b_matrices_in_displaystyle", 0, "add 'displaystyle=\"\true\"' to matrix translations?");
	addParameter(fn_tex_symbols, type_file, "fn_tex_symbols", 0, "file with 5 columns: (tex keyword) (operator?) (copy?) (is HTML symbol?) (MathML expression)");
}

Tex2MathMLConverter::~Tex2MathMLConverter()
{
	if(UserTexSymbol)
		delete [] UserTexSymbol;
	if(tex_symbol_data)
		delete [] tex_symbol_data; // free(symbol_data);
}

bool Tex2MathMLConverter::loadUserTexSymbols(const char *file_name)
{
	int i = 0, j, n, no_lines = 0, data_size = 0;
	char line_buffer[LINE_BUFFER_SIZE];
	char text_buffer[LINE_BUFFER_SIZE], *cptr;
	FILE *fptr = fopen(file_name, "r");
	if(!fptr)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "error loading file \"%s\"\n", file_name);
		return false;
	}
	while(fgets(line_buffer, LINE_BUFFER_SIZE, fptr))
	{
		if(line_buffer[0]!='#')
		{
			no_lines++;

			// overwrite '\n'
			line_buffer[strlen(line_buffer)-1] = '\0';

			// analyze line format
			if(numberOf('\t', line_buffer)!=5)
			{
				errorIn(__FILE__, __LINE__, __func__);
				fprintf(stderr, "malformatted line %d:\n--> %sin file \"%s\"\n", i+1, line_buffer, file_name);
				fclose(fptr);
				return false;
			}

			extractWordFromList(line_buffer, 0, '\t', text_buffer);
			data_size += strlen(text_buffer) + 1;

			// check Boolean flags
			for(j=0;j<3;j++)
			{
				extractWordFromList(line_buffer, 1+j, '\t', text_buffer);
				n = atoi(text_buffer);
				if( n != 0 && n != 1)
				{
					errorIn(__FILE__, __LINE__, __func__);
					fprintf(stderr, "error in column %d of line %d: \"%s\" in file \"%s\"\nboolean flag must be either 0 or 1\n", j+2, i+1, line_buffer, file_name);
					fclose(fptr);
					return false;
				}
			}
			extractWordFromList(line_buffer, 4, '\t', text_buffer);
			if(!(text_buffer[0] == '0' && text_buffer[1] == '\0'))
				data_size += strlen(text_buffer) + 1;

			extractWordFromList(line_buffer, 5, '\t', text_buffer);
			if(!(text_buffer[0] == '0' && text_buffer[1] == '\0'))
				data_size += strlen(text_buffer) + 1;
		}
		i++;
	}
	// allocate data memory
	if(tex_symbol_data)
		delete [] tex_symbol_data; // free(symbol_data);
	tex_symbol_data = new char [ data_size ] ;
	//symbol_data = (char *) malloc( sizeof(char) * data_size );

	if(!tex_symbol_data)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "allocation error while loading file \"%s\"\n", file_name);
		fclose(fptr);
		return false;
	}
	if(UserTexSymbol)
		delete [] UserTexSymbol;
	if(!(UserTexSymbol = new struct TexSymbol_s[no_lines]))
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "allocation error while loading file \"%s\"\n", file_name);
		fclose(fptr);
		return false;
	}
	// actual read-in of data
	fseek(fptr, 0, SEEK_SET);
	cptr = tex_symbol_data;
	TexSymbol_s *pUserTexSymbol;
	i=0;
	while(fgets(line_buffer, LINE_BUFFER_SIZE, fptr))
	{
		if(line_buffer[0]!='#')
		{
			pUserTexSymbol = UserTexSymbol + i;
			line_buffer[strlen(line_buffer)-1]='\0';

			// 1st column
			pUserTexSymbol->keyword = cptr;
			extractWordFromList(line_buffer, 0, '\t', cptr);
			cptr += strlen(cptr) + 1;

			// 2nd column
			extractWordFromList(line_buffer, 1, '\t', text_buffer);
			pUserTexSymbol->b_is_operator = atoi(text_buffer) == 1 ? true : false;

			// 3rd column
			extractWordFromList(line_buffer, 2, '\t', text_buffer);
			pUserTexSymbol->b_translate_by_copy = atoi(text_buffer) == 1 ? true : false;

			// 4th column
			extractWordFromList(line_buffer, 3, '\t', text_buffer);
			pUserTexSymbol->b_is_html_smybol = atoi(text_buffer) == 1 ? true : false;

			// 5th column
			extractWordFromList(line_buffer, 4, '\t', text_buffer);
			if(text_buffer[0] == '0' && text_buffer[1] == '\0')
				pUserTexSymbol->mml_name = 0;
			else
			{
				pUserTexSymbol->mml_name = cptr;
				extractWordFromList(line_buffer, 4, '\t', cptr);
				cptr += strlen(cptr) + 1;
			}

			// 6th column
			extractWordFromList(line_buffer, 5, '\t', text_buffer);
			if(text_buffer[0] == '0' && text_buffer[1] == '\0')
				pUserTexSymbol->tag_parameter = 0;
			else
			{
				pUserTexSymbol->tag_parameter = cptr;
				extractWordFromList(line_buffer, 5, '\t', cptr);
				cptr += strlen(cptr) + 1;
			}
			i++;
		}
	}
	no_user_tex_symbols = no_lines;
	fclose(fptr);
	return true;
}

bool Tex2MathMLConverter::findSymbol(const char *expression, int *pindex)
{
	for(int i=0;i<no_user_tex_symbols;i++)
		if(!strcmp(expression, UserTexSymbol[i].keyword))
		{
			*pindex = i;
			return true;
		}
	return false;
}

void Tex2MathMLConverter::print(FILE *fptr)
{
	int i, n = MathSection.size(), index, last_index = 0;
	if(n==0)
	{
		fwrite(file_content, file_size, 1, stdout);
		return;
	}
	for(i=0;i<n;i++)
	{
		index = MathSection[i].environment_index;
		fwrite(file_content + last_index, index - last_index, 1, stdout);
		fprintf(fptr, "%s", MathSection[i].mml.c_str());
		last_index = index + MathSection[i].environment_length;
	}
	fwrite(file_content + last_index, file_size - last_index, 1, stdout);
}

bool Tex2MathMLConverter::analyzeContent(bool convert_immedeatly)
{
	int i, n;
	bool found_section, is_eqnarray;
	char *cptr = file_content, *tmp_cptr;
	struct MathSection_s current_math_section;
	MathSection.clear();
	do
	{
		is_eqnarray = false;
		found_section = false;
		if(*cptr == '$')
		{
			cptr++;
			// check if it is inline math or math evironment
			if(*cptr == '$')
			{
				current_math_section.environment_index = int(cptr - file_content - 1);
				current_math_section.equation_type = ET_displaymath;
				// math evironment:
				// ....$$\nXXX\nXXX\nXXX\nXXX$$....
				cptr++;
				// cptr now points to first character after $$
				current_math_section.index = i = int(cptr - file_content);
				while(*cptr!='$')
					cptr++;
				current_math_section.length = n = int(cptr - file_content) - i;
				cptr++;
				current_math_section.environment_length = n + 4;
			}
			else
			{
				current_math_section.environment_index = int(cptr - file_content - 1);
				current_math_section.equation_type = ET_math;
				// inline math:
				// ....$XXXXX$....
				current_math_section.index = i = int(cptr - file_content);
				while(*cptr!='$')
					cptr++;
				current_math_section.length = n = int(cptr - file_content) - i;
				current_math_section.environment_length = n + 2;
			}
			found_section = true;
		}
		else if(*cptr == '\\')
		{
			if(!strncmp(cptr+1, "begin", 5))
			{
				if(!strncmp(cptr+7, "equation", 8))
				{
					current_math_section.environment_index = int(cptr - file_content);
					current_math_section.equation_type = ET_equation;
					//\begin{equation}... 1+5+1+8+1 = 16
					tmp_cptr = cptr + 16;
					current_math_section.index = i = int(tmp_cptr - file_content);
					tmp_cptr = strstr(cptr, "\\end{equation}");
					current_math_section.length = n = int(tmp_cptr - file_content) - i;
					cptr = tmp_cptr + 13;
					current_math_section.environment_length = n + 30;
				}
				else if(!strncmp(cptr+7, "eqnarray", 8))
				{
					current_math_section.environment_index = int(cptr - file_content);
					current_math_section.equation_type = ET_eqnarray;
					//\begin{equation}... 1+5+1+8+1 = 16
					tmp_cptr = cptr + 16;
					current_math_section.index = i = int(tmp_cptr - file_content);
					tmp_cptr = strstr(cptr, "\\end{eqnarray}");
					current_math_section.length = n = int(tmp_cptr - file_content) - i;
					cptr = tmp_cptr + 13;
					current_math_section.environment_length = n + 30;
					is_eqnarray = true;
				}
				found_section = true;
			}
		}
		if(found_section)
		{
			current_math_section.text = string(file_content + i, n);
			MathSection.push_back(current_math_section);
			if(convert_immedeatly && !convert(&MathSection.back(), is_eqnarray))
			{
				errorIn(__FILE__, __LINE__, __func__);
				return false;
			}
		}
		cptr++;
	}while(*cptr != '\0');
	return true;
}

enum TexCommandType_e getCommandType(struct Tex2MathMLConverter::TexElement_s& te)
{
	return te.type == TET_command ? GlobalTexCommand[te.tex_command_index].type : TC_none ;
}

bool Tex2MathMLConverter::convert(struct MathSection_s *pms, bool is_eqnarray)
{
	string& mml = pms->mml;

	// pre-analyze content
	struct TexElement_s te;
	bool text_mode = false;
	vector<struct TexElement_s> list_of_tex_elements;
	char *cptr = (char *) pms->text.c_str();
	mml += string (pms->equation_type == ET_math ? "<math>" : "<math class=\"equation\" mode=\"display\">");
	if(pms->equation_type == ET_eqnarray)
	{
		int environment_index = 0;
	
		// unknown mtable
		mml += "<mtable displaystyle=\"true\" columnalign=\"right center left\">";

		// determine number of rows
		mml += "<mtr>";
		mml += "<mtd>";
		do
		{
			if(*cptr == '\\' && *(cptr+1) == '\\' && environment_index<=0)
			{
				if(!atomic_mml_convert(mml, list_of_tex_elements, false))
				{
					errorIn(__FILE__, __LINE__, __func__);
					fprintf(stderr, "error converting math section \"%s\"\n", pms->text.c_str());
					return false;
				}
				mml += "</mtd>";
				mml += "</mtr><mtr>";
				mml += "<mtd>";
				list_of_tex_elements.clear();
				cptr += 2;
			}
			else if(*cptr == '&' && *(cptr-1) != '\\' && environment_index<=0)
			{
				if(!atomic_mml_convert(mml, list_of_tex_elements, false))
				{
					errorIn(__FILE__, __LINE__, __func__);
					fprintf(stderr, "error converting math section \"%s\"\n", pms->text.c_str());
					return false;
				}
				mml += "</mtd><mtd>";
				list_of_tex_elements.clear();
				cptr ++;
			}
			else
			{
				if(!slurpSingleTexExpression(cptr, &te, text_mode))
				{
					errorIn(__FILE__, __LINE__, __func__);
					return false;
				}
				list_of_tex_elements.push_back(te);
				if(getCommandType(te) == TC_text_box)
					text_mode = true;
				else if(text_mode && te.type == TET_parameter_brace && te.expression[0] == '}')
					text_mode = false;
				cptr += te.length;
				if( te.type == TET_command && getCommandType(te) == TC_environment )
				{
					if(!te.expression.compare("begin"))
						environment_index++;
					else if(!te.expression.compare("end"))
					{
						environment_index--;
						if(environment_index<0)
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "inconsistent environment index in math section \"%s\"\n", pms->text.c_str());
							return false;
						}
					}
				}
			}
		}while(*cptr);
		if(!atomic_mml_convert(mml, list_of_tex_elements, false))
		{
			errorIn(__FILE__, __LINE__, __func__);
			fprintf(stderr, "error converting math section \"%s\"\n", pms->text.c_str());
			return false;
		}
		list_of_tex_elements.clear();
		mml += "</mtd>";
		mml += "</mtr>";
		mml += "</mtable>";
	}
	else
	{
		text_mode = false;
		// 1. create list of tex elements
		do
		{
			if(!slurpSingleTexExpression(cptr, &te, text_mode))
			{
				errorIn(__FILE__, __LINE__, __func__);
				return false;
			}
			list_of_tex_elements.push_back(te);
			if(getCommandType(te) == TC_text_box)
				text_mode = true;
			else if(text_mode && te.type == TET_parameter_brace && te.expression[0] == '}')
				text_mode = false;
			cptr += te.length;
		}while(*cptr);

		// if(list_of_tex_elements[0].type == TET_space)
		// 	line_feed_string = list_of_tex_elements[0].expression;
		// else
			line_feed_string = "";

		// 3. format content
		// mml += string(file_content+pms->index, pms->length);
		if(!atomic_mml_convert(mml, list_of_tex_elements, false))
		{
			errorIn(__FILE__, __LINE__, __func__);
			fprintf(stderr, "error converting math section \"%s\"\n", pms->text.c_str());
			return false;
		}
	}
	mml += "</math>";
	return true;
}

bool isUmlaut(char c)
{
	switch(c)
	{
		case char(0xa4):
		case char(0xb6):
		case char(0xbc):
		case char(0x84):
		case char(0x96):
		case char(0x9c):
		case char(0x9f):
			return true;
		default:;
	}
	return false;
}

bool Tex2MathMLConverter::slurpSingleTexExpression(char *text, struct TexElement_s *pTE, bool text_mode)
{
	int length;
	bool b_c3, b_is_lb, b_is_rb;
	char *cptr = (char *) text;
	if(*cptr == '\\')
	{
		++cptr;
		if(*cptr == '{' || *cptr == '}')
		{
			pTE->type = TET_brace;
			pTE->expression = string(cptr, 1);
			length = 2;
		}
		else if(!strncmp(cptr, "cr", 2))
		{
			pTE->type = TET_eol;
			pTE->expression = string(cptr, 2);
			length = 3;
		}
		else if(*cptr == '\\' && *(cptr-1) == '\\')
		{
			pTE->type = TET_eol;
			pTE->expression = string(text, 2);
			length = 2;
		}
		else if((b_is_lb = !strncmp(cptr, "left", 4) && !isalpha(*(cptr+4))) || (b_is_rb = !strncmp(cptr, "right", 5) && !isalpha(*(cptr+5))))
		{
			pTE->type = TET_brace;
			length = 1 + ( b_is_lb ? 4 : 5 );
			pTE->expression = string(text + 1, length - 1);
		}
		else
		{
			int index;
			if(isalnum(*cptr))
				while(isalnum(*cptr))
					cptr++;
			length = int ( cptr - text ) ;
			string expression = string(text + 1, length - 1);
			pTE->expression = expression;

			// distinguish t_command and t_backslash_symbol
			if(findCommand(expression.c_str(), &index))
			{
				pTE->tex_command_index = index;
				pTE->type = TET_command;
			}
			else if(findSymbol(expression.c_str(), &index))
			{
				pTE->tex_symbol_index = index;
				pTE->type = TET_backslash_symbol;
			}
			else
			{
				errorIn(__FILE__, __LINE__, __func__);
				fprintf(stderr, "unknown backslash expression \"\\%s\"\n", expression.c_str());
				return false;
			}
		}
		pTE->length = length;
		return true;
	}
	else if(isalpha(*cptr) || (b_c3 = (*cptr == char(0xc3))) || (text_mode && isspace(*cptr)))
	{
		if(isalpha(*(cptr+1)) || (b_c3 && isUmlaut(*(cptr+1))) || (text_mode && isspace(*(cptr+1))))
		{
			cptr++;
			while(isalpha(*cptr) || (b_c3 && isUmlaut(*cptr)) || (text_mode && isspace(*cptr)))
				cptr++;
			cptr--;
			pTE->type = TET_text;
		}
		else
			pTE->type = TET_alpha;
		b_c3 = false;
	}
	else if(isdigit(*cptr))
	{
		while(isdigit(*cptr))
			cptr++;
		cptr--;
		pTE->type = TET_number;
	}
	else if(*cptr == '_' || *cptr == '^')
		pTE->type = TET_subsup;
	else if(isspace(*cptr))
	{
		while(isspace(*cptr))
			cptr++;
		cptr--;
		pTE->type = TET_space;
	}
	else
	{
		// check braces....
		switch(*cptr)
		{
			case ')':
			case '(':
			case '[':
			case ']':
				pTE->type = TET_brace;
				break;

			case '{':
			case '}':
				pTE->type = TET_parameter_brace;
				break;

			default:
				pTE->type = TET_other;
		}
	}
	length = 1 + int ( cptr - text ) ;
	pTE->expression = string (text, length) ;
	pTE->length = length;
	return true;
}

bool Tex2MathMLConverter::collectEmbracedElements(vector<struct TexElement_s> &lote, int index, vector<struct TexElement_s>& sub_list)
{
	struct TexElement_s *pTE = &(lote[index]);
	if(pTE->isUnpairedBracket())
	{
		index++;
		int level = 0, n = lote.size();
		const char *lb = pTE->expression.c_str(), *rb = getOppositeBracket(lb);
		for(;index<n;index++)
		{
			pTE = &(lote[index]);
			if(pTE->isUnpairedBracket())
			{
				if(!pTE->expression.compare(rb))
				{
					if(level == 0)
						return true;
					else
						level--;
				}
				else if(!pTE->expression.compare(lb))
					level++;
			}
			sub_list.push_back(*pTE);
		}
	}
	else
		sub_list.push_back(*pTE);
	return true;
}

void Tex2MathMLConverter::addMMLSymbol(string& mml, int index)
{
	struct TexSymbol_s *pUserTexSymbol = UserTexSymbol + index;
	char element_buffer[LINE_BUFFER_SIZE];
	sprintf(element_buffer, pUserTexSymbol->b_is_html_smybol ? "&%s;" : "%s", pUserTexSymbol->b_translate_by_copy ? pUserTexSymbol->keyword : pUserTexSymbol->mml_name);
	addMML(mml, element_buffer, pUserTexSymbol->b_is_operator ? "mo" : "mi", pUserTexSymbol->tag_parameter);
	//addMML(mml, element_buffer, pUserTexSymbol->b_is_operator ? "mo" : "mi");
}

bool Tex2MathMLConverter::collectAndConvert(string& mml, vector<struct TexElement_s> lote, int index, int *pno_processed_tex_elements)
{
	vector<struct TexElement_s> sub_list;
	if(!collectEmbracedElements(lote, index,  sub_list))
	{
		errorIn(__FILE__, __LINE__, __func__);
		return false;	
	}
	if(!atomic_mml_convert(mml, sub_list))
	{
		errorIn(__FILE__, __LINE__, __func__);
		return false;	
	}
	*pno_processed_tex_elements = 2 + sub_list.size();
	return true;
}

bool Tex2MathMLConverter::processCommand(string& mml, vector<struct TexElement_s> lote, int index, int *pno_processed_tex_elements)
{
	bool b_is_font_modifier;
	vector<struct TexElement_s> sub_list;
	struct TexElement_s &tex_element = lote[index];
	struct TexCommand_s *pGlobalTexCommand = GlobalTexCommand + tex_element.tex_command_index;
	int i, N = pGlobalTexCommand->no_parameters, no_tex_elements, no_processed_tex_elements = 1;
	string mml_tag = string(pGlobalTexCommand->mml_tag);
	if(getCommandType(tex_element) == TC_font_modifier)
	{
		b_is_font_modifier = true;
		mml += "<mo mathvariant=\"" + string(pGlobalTexCommand->tag_parameter) + "\">"; 
	}
	else
	{
		b_is_font_modifier = false;
		mml += '<' + string(mml_tag) + '>';
	}
	// go to first index after command
	index++;
	for(i=0;i<N;i++) // loop over all parameters
	{
		sub_list.clear();
		if(!collectEmbracedElements(lote, index,  sub_list))
		{
			errorIn(__FILE__, __LINE__, __func__);
			return false;	
		}
		mml += line_feed_string;
		if(!atomic_mml_convert(mml, sub_list))
		{
			errorIn(__FILE__, __LINE__, __func__);
			return false;	
		}
		no_tex_elements = 2 + sub_list.size();
		index += no_tex_elements;
		no_processed_tex_elements += no_tex_elements;
	}
	*pno_processed_tex_elements = no_processed_tex_elements;
	if(b_is_font_modifier)
		mml += "</mo>";
	else
		mml += "</" + string(mml_tag) + '>';
	return true;
}

bool Tex2MathMLConverter::processArray(string& mml, vector<struct TexElement_s>& lote, int index, vector<struct TexElement_s>& array_format, int *pno_processed_tex_elements)
{
	string column_format_string;
	int i, no_format_elements = array_format.size();
	if(no_format_elements != 1)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "array format string too complex!\n");
		return false;
	}
	// _________________
	const char *cptr = array_format[0].expression.c_str();
	do
	{
		switch(*cptr)
		{
			case 'c':
				column_format_string += "center ";
				break;

			case 'r':
				column_format_string += "right ";
				break;

			case 'l':
				column_format_string += "left ";
				break;
			default:;
		}
		cptr++;
	}while(*cptr);
	column_format_string.pop_back();

	// investigate list_of_tex_elements in lote
	int no_tex_element = lote.size();
	struct TexElement_s &te = lote[0];
	vector<struct TexElement_s> sub_list;
	
	// construct column format string
	mml += "<mtable displaystyle=\"" + string(b_matrices_in_displaystyle ? "true" : "false") + "\" columnalign=\"" + column_format_string + "\">";

	// determine number of rows
	mml += "<mtr>";
	mml += "<mtd>";
	for(i = index;i<no_tex_element;i++)
	{
		te = lote[i];
		if(te.type == TET_eol)
		{
			if(!atomic_mml_convert(mml, sub_list, false))
			{
				errorIn(__FILE__, __LINE__, __func__);
				return false;
			}
			mml += "</mtd>";
			mml += "</mtr><mtr>";
			mml += "<mtd>";
			sub_list.clear();
		}
		else if(te.type == TET_other && te.expression[0] == '&')
		{
			if(!atomic_mml_convert(mml, sub_list, false))
			{
				errorIn(__FILE__, __LINE__, __func__);
				return false;
			}
			mml += "</mtd><mtd>";
			sub_list.clear();
		}
		else if(te.type == TET_command && !te.expression.compare("end"))
			break;
		else
			sub_list.push_back(te);
	}
	*pno_processed_tex_elements = i - index;
	if(!atomic_mml_convert(mml, sub_list, false))
	{
		errorIn(__FILE__, __LINE__, __func__);
		return false;
	}
	sub_list.clear();
	mml += "</mtd>";
	mml += "</mtr>";
	mml += "</mtable>";
	return true;
}

bool Tex2MathMLConverter::atomic_mml_convert(string& mml, vector<struct TexElement_s>& list_of_tex_elements, bool b_test_complexity)
{
	int i, n = list_of_tex_elements.size(), no_processed_tex_elements;
	bool b_is_complex_expression = b_test_complexity ? ( list_of_tex_elements.size() > 1 ? true : false ) : false;
	struct TexElement_s *pNextTE;
	char first_subsup_character = 0, second_subsup_character =0 ;
	bool b_underover_subsup_scripts = false, b_processing_subsup = false;
	bool b_is_last_tex_element, b_is_subsup;
	string added_mml, first_subsup_script_mml, subsup_base_mml, base_denominator_mml_name;
	const char *subsup_tag;
	if(b_is_complex_expression)
		mml += "<mrow>";
	for(i=0;i<n;i++)
	{
		struct TexElement_s &tex_element = list_of_tex_elements[i];
		// element_text = tex_element.expression.c_str();
		switch(tex_element.type)
		{
			case TET_none:
				errorIn(__FILE__, __LINE__, __func__);
				return false;
				break;

			case TET_backslash_symbol:
				addMMLSymbol(added_mml, tex_element.tex_symbol_index);
				break;
	
			case TET_command:
				switch(getCommandType(tex_element))
				{
					case TC_frac:
						if(!processCommand(added_mml, list_of_tex_elements, i, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							return false;
						}
						break;

					case TC_sqrt:
						if(list_of_tex_elements[i+1].type == TET_brace\
						&& list_of_tex_elements[i+1].expression[0] == '['\
						&& list_of_tex_elements[i+2].type == TET_number\
						&& list_of_tex_elements[i+3].type == TET_brace\
						&& list_of_tex_elements[i+3].expression[0] == ']')
						{
							base_denominator_mml_name.clear();
							addMML(base_denominator_mml_name, list_of_tex_elements[i+2].expression, "mn");
							added_mml += "<mroot>";
							if(!collectAndConvert(added_mml, list_of_tex_elements, i+4, &no_processed_tex_elements))
							{
								errorIn(__FILE__, __LINE__, __func__);
								fprintf(stderr, "%s\n", added_mml.c_str());
								fprintf(stderr, "error parsing argument of sqrt[*]{*}!\n");
								return false;
							}
							added_mml += base_denominator_mml_name;
							added_mml += "</mroot>";
							no_processed_tex_elements += 4;
						}
						else if(!processCommand(added_mml, list_of_tex_elements, i, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							return false;
						}
						break;

					case TC_stackrel: // \stackrel{oben}{unten}
					{
						string stackrel_top, stackrel_bottom;
						if(!collectAndConvert(stackrel_top, list_of_tex_elements, i+1, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "%s\n", added_mml.c_str());
							fprintf(stderr, "error parsing argument of sqrt[*]{*}!\n");
							return false;
						}
						i += 1 + no_processed_tex_elements ;
						if(!collectAndConvert(stackrel_bottom, list_of_tex_elements, i, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "%s\n", added_mml.c_str());
							fprintf(stderr, "error parsing argument of sqrt[*]{*}!\n");
							return false;
						}
						added_mml += "<mover>" + stackrel_bottom + stackrel_top + "</mover>";
						// errorIn(__FILE__, __LINE__, __func__);
						// return false;
						break;
					}
					case TC_limits:
						b_underover_subsup_scripts = true;
						no_processed_tex_elements = 1;
						// continue;
						break;

					case TC_mathop:
						// \mathop
						if(!collectAndConvert(added_mml, list_of_tex_elements, i+1, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "%s\n", added_mml.c_str());
							fprintf(stderr, "error parsing argument of sqrt[*]{*}!\n");
							return false;
						}
						no_processed_tex_elements++;
						break;

					case TC_environment:
					{
						int no_items;
						vector<struct TexElement_s> sub_list;
						if(!collectEmbracedElements(list_of_tex_elements, i+1, sub_list))
						{
							errorIn(__FILE__, __LINE__, __func__);
							return false;
						}
						no_items = sub_list.size();
						if(no_items != 1 || sub_list[0].type != TET_text)
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "error identifying environment \"%s\"\n", list_of_tex_elements[i+2].expression.c_str());
							return false;
						}
						if(!sub_list[0].expression.compare("array"))
						{
							int array_format_description_length;
							vector<struct TexElement_s> array_format_description;
							if(!collectEmbracedElements(list_of_tex_elements, i + 4, array_format_description))
							{
								errorIn(__FILE__, __LINE__, __func__);
								return false;
							}
							array_format_description_length = array_format_description.size();
							if(!processArray(added_mml, list_of_tex_elements, i + 6 + array_format_description_length, array_format_description, &no_processed_tex_elements))
							{
								errorIn(__FILE__, __LINE__, __func__);
								return false;
							}
							// \begin{array}{format}...\end{array}
							no_processed_tex_elements = 10 + array_format_description_length + no_processed_tex_elements;
						}
						else
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "unknown math environment: %s\n", sub_list[1].expression.c_str());
							return false;
						}
						break;
					}
					case TC_decoration:
						// \overline, \underline, \overbrace, \underbrace
						errorIn(__FILE__, __LINE__, __func__);
						break;

					case TC_accent:
						// \hat, \breve, \grave, \bar, \dot, \ddot, \tilde, \check, \acute, \vec
						added_mml += "<mover>";
						if(!collectAndConvert(added_mml, list_of_tex_elements, i+1, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "%s\n", added_mml.c_str());
							fprintf(stderr, "error parsing argument of sqrt[*]{*}!\n");
							return false;
						}
						no_processed_tex_elements++;
						addMML(added_mml, string(GlobalTexCommand[tex_element.tex_command_index].mml_name), "mo");
						added_mml += "</mover>";
						break;
					
					case TC_font_modifier:
					case TC_text_box:
						// \mbox, \mathrm
						if(!processCommand(added_mml, list_of_tex_elements, i, &no_processed_tex_elements))
						{
							errorIn(__FILE__, __LINE__, __func__);
							return false;
						}
						break;
	
					case TC_none:
						errorIn(__FILE__, __LINE__, __func__);
						return false;

				}
				i += no_processed_tex_elements - 1;
				break;

			case TET_alpha:
				addMML(added_mml, tex_element.expression, "mi");
				break;

			case TET_text:
				// addMML(added_mml, tex_element.expression, "mtext");
				mml += tex_element.expression;
				break;

			case TET_number:
				addMML(added_mml, tex_element.expression, "mn");
				break;

			case TET_parameter_brace:
				//added_mml += "<mrow>";
				if(!collectAndConvert(added_mml, list_of_tex_elements, i, &no_processed_tex_elements))
				{
					errorIn(__FILE__, __LINE__, __func__);
					return false;
				}
				i += no_processed_tex_elements - 1;
				//added_mml += "</mrow>";
				break;

			case TET_brace:
			{
				//addMML(added_mml, tex_element.expression, "mo");
				string embraced_string;
				const char *left_bracket, *right_bracket;
				if(tex_element.expression[0] == 'l')
				{
					// \left[x].....\right[y]
					int no_items;
					vector<struct TexElement_s> sub_list;
					if(!collectEmbracedElements(list_of_tex_elements, i, sub_list))
					{
						errorIn(__FILE__, __LINE__, __func__);
						return false;
					}
					no_items = sub_list.size();
					// --------------------------------------------------------
					left_bracket = list_of_tex_elements[i+1].expression.c_str();
					right_bracket = list_of_tex_elements[i+no_items+2].expression.c_str();
					left_bracket = (*left_bracket == '.') ? 0 : left_bracket;
					right_bracket = (*right_bracket == '.') ? 0 : right_bracket;
					if(left_bracket && right_bracket)
						added_mml += "<mfenced open=\"" + string(left_bracket) + "\" close=\"" + string(right_bracket) + "\">";
					else if(right_bracket && !left_bracket)
						added_mml += "<mfenced open=\"\" close=\"" + string(right_bracket) + "\">";
					else if(left_bracket && !right_bracket)
						added_mml += "<mfenced open=\"" + string(left_bracket) + "\" close=\"\">";
					else
						added_mml += "<mfenced open=\"\" close=\"\">";
					// go -----------------------------------------------------
					sub_list.erase(sub_list.begin());	// remove x
					if(!atomic_mml_convert(embraced_string, sub_list))
					{
						errorIn(__FILE__, __LINE__, __func__);
						return false;
					}
					added_mml += embraced_string + "</mfenced>";
					no_processed_tex_elements = no_items + 3;
				}
				else
				{
					if(!collectAndConvert(embraced_string, list_of_tex_elements, i, &no_processed_tex_elements))
					{
						errorIn(__FILE__, __LINE__, __func__);
						return false;
					}
					if(tex_element.expression[0] == '(')
						added_mml += "<mfenced>" + embraced_string + "</mfenced>";
					else
					{
						left_bracket = tex_element.expression.c_str();
						right_bracket = (char *) getOppositeBracket ( left_bracket ) ;
						added_mml += "<mfenced open=\"" + string(left_bracket) + "\" close=\"" + string(right_bracket) + "\">" + embraced_string + "</mfenced>";
					}
				}
				i += no_processed_tex_elements - 1;
				break;
			}
			case TET_subsup:
				if(!b_processing_subsup)
				{
					errorIn(__FILE__, __LINE__, __func__);
					fprintf(stderr, "single subsup script character found!\n");
					return false;
				}
				if(first_subsup_character)
					second_subsup_character = tex_element.expression[0];
				else
					first_subsup_character = tex_element.expression[0];
				break;

			case TET_other:
				switch(tex_element.expression[0])
				{
					case '.':
					case ',':
					case ';':
						added_mml += tex_element.expression;
						break;
					default:
						addMML(added_mml, tex_element.expression, "mo");
				}
				break;

			case TET_space:
				mml += tex_element.expression;
				break;

			default:
				errorIn(__FILE__, __LINE__, __func__);
				return false;
		}
		b_is_last_tex_element = i+1 >= n;
		if(!b_is_last_tex_element)
		{
			pNextTE = &(list_of_tex_elements[i+1]);
			b_is_subsup = pNextTE->type == TET_subsup || ( pNextTE->type == TET_command && GlobalTexCommand[pNextTE->tex_command_index].type == TC_limits);
		}
		if(!b_is_last_tex_element && b_is_subsup)
		{
			if(b_processing_subsup)
				first_subsup_script_mml = added_mml;
			else
			{
				subsup_base_mml = added_mml;
				first_subsup_script_mml.clear();
				b_processing_subsup = true;
			}
		}
		else if(b_is_last_tex_element || (!b_is_last_tex_element && !b_is_subsup))
		{
			// the next tex element is not a subsup
			if(b_processing_subsup)
			{
				if(!added_mml.empty())
				{
					// we are processing a subsup: finish!
					if(second_subsup_character)
					{
						// already has found second subsup character
						if(first_subsup_character == second_subsup_character)
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "double sub/sup script found ^^ or __!\n");
							fprintf(stderr, "mml = \"%s\"!\n", mml.c_str());
							fprintf(stderr, "first_subsup_script_mml = \"%s\"!\n", first_subsup_script_mml.c_str());
							fprintf(stderr, "added_mml= \"%s\"!\n", added_mml.c_str());
							return false;
						}
						subsup_tag = b_underover_subsup_scripts ? "munderover" : "msubsup";
						mml += line_feed_string + '<' + string(subsup_tag) + '>' + line_feed_string;
						mml += subsup_base_mml + line_feed_string;
						if(first_subsup_character == '_')
						{
							mml += first_subsup_script_mml + line_feed_string;
							mml += added_mml + line_feed_string;
						}
						else
						{
							mml += added_mml + line_feed_string;
							mml += first_subsup_script_mml + line_feed_string;
						}
						mml += "</" + string(subsup_tag) + '>' + line_feed_string;
						first_subsup_script_mml.clear();
						first_subsup_character = second_subsup_character = 0;
						b_underover_subsup_scripts = false;
						b_processing_subsup = false;
					}
					else
					{
						if(first_subsup_character == '_')
							subsup_tag = b_underover_subsup_scripts ? "munder" : "msub";
						else
							subsup_tag = b_underover_subsup_scripts ? "mover" : "msup";
						mml += line_feed_string + '<' + string(subsup_tag) + '>' + line_feed_string;
						mml += subsup_base_mml + line_feed_string;
						mml += added_mml + line_feed_string;
						mml += "</" + string(subsup_tag) + '>' + line_feed_string;
						first_subsup_character = second_subsup_character = 0;
						b_underover_subsup_scripts = false;
						b_processing_subsup = false;
					}
				}
			}
			else
				mml += added_mml;
		}
		added_mml.clear();
	}
	if(b_is_complex_expression)
		mml += "</mrow>";
	return true;
}


