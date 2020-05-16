#ifndef _Tex2MathMLConverter_h
#define _Tex2MathMLConverter_h

#include "IO/BasicIO.h"
#include "IO/File.h"

#include <vector>
#include <string>

#include "tex2mml_data_types.h"

using namespace std;

class Tex2MathMLConverter: public File, public BasicIO
{

public:

	struct MathSection_s
	{
		int index; 		// index into content array
		int length;		// length of section

		int environment_index;	// index of first character of math environment
		int environment_length; // total length of math environment

		string text;		// the expression, e.g. a(t) or \frac{1}{2}
		string mml;		// result

		enum EquationType_e equation_type;
	
	};

	struct TexElement_s
	{
		int length;		// length of text
		string expression;
		
		enum SubSupType_e ss_type;
		enum TexElementType_e type;

		union
		{
			int tex_command_index;
			int tex_symbol_index;
		};

		inline bool isUnpairedBracket(){return type == TET_brace || type == TET_parameter_brace;}
	};

public:

	Tex2MathMLConverter();
	~Tex2MathMLConverter();
	
	inline bool loadUserTexSymbols(){return loadUserTexSymbols(fn_tex_symbols);}
	inline void printContent(FILE *fptr){fprintf(fptr, "%s\n", file_content);}

	bool analyzeContent(bool convert_immedeatly = true);
	void print(FILE *fptr);

protected:

	// internal variables

	vector<struct MathSection_s> MathSection;

	// tex symbols 
	char fn_tex_symbols[BasicIO_string_size];

	struct TexSymbol_s *UserTexSymbol;
	char *tex_symbol_data;
	int no_user_tex_symbols;
	bool b_matrices_in_displaystyle;

	string line_feed_string;

	// functions
	bool loadUserTexSymbols(const char *file_name);
	bool findSymbol(const char *expression, int *pindex);

	bool convert(struct MathSection_s *pms, bool is_eqnarray);
	bool slurpSingleTexExpression(char *text, struct TexElement_s *pTE, bool text_mode);
	void addMMLSymbol(string& mml, int index);

	bool collectEmbracedElements(vector<struct TexElement_s>& lote, int index, vector<struct TexElement_s>& sub_list);
	bool collectAndConvert(string& mml, vector<struct TexElement_s> lote, int index, int *pno_processed_tex_elements);

	bool processCommand(string& mml, vector<struct TexElement_s> lote, int index, int *pno_processed_tex_elements);
	bool processArray(string& mml, vector<struct TexElement_s>& lote, int index, vector<struct TexElement_s>& array_format, int *pno_processed_tex_elements);

	bool atomic_mml_convert(string& mml, vector<struct TexElement_s>& list_of_elements, bool b_test_complexity = true);

	bool putSymbol(string& mml, const char *symbol_buffer);
	// bool processSubSup(string& mml, const string& sub_sup_base, bool b_use_under_over, char *text, char **pp_next_char);

};

#endif // _Tex2MathMLConverter_h



