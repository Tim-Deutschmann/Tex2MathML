#ifndef _tex2mml_data_types_h
#define _tex2mml_data_types_h

enum EquationType_e
{
	ET_none,
	ET_math,
	ET_displaymath,
	ET_equation,
	ET_eqnarray
};

enum TexCommandType_e
{
	TC_none,
	TC_frac,
	TC_sqrt,
	TC_stackrel,
	TC_mathop,
	TC_limits,
	TC_environment,
	TC_decoration,
	TC_accent,
	TC_text_box,
	TC_font_modifier
};

enum SubSupType_e
{
	SST_none,
	SST_sub,
	SST_sup,
	SST_sub_sup,
	SST_sup_sub
};

enum TexElementType_e
{
	TET_none,
	TET_backslash_symbol,
	TET_command,
	TET_alpha,
	TET_text,
	TET_number,
	TET_subsup, // '_' or '^'
	TET_parameter_brace, // e.g. '{' or '}'
	TET_brace, // e.g. "()[]{}" optional \left \right
	TET_space,
	TET_eol,	// \\\\ (end of line)
	TET_other
};

struct TexSymbol_s
{
	const char *keyword;

	bool b_is_operator;
	bool b_translate_by_copy;
	bool b_is_html_smybol;

	const char *mml_name;
	const char *tag_parameter;
};

struct TexCommand_s
{
	const char *keyword;

	enum TexCommandType_e type;
	int no_optional_parameters;
	int no_parameters;

	union
	{
		const char *mml_tag;
		const char *mml_name;
		const char *tag_parameter;
	};
};

#endif // _tex2mml_data_types_h


