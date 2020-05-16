include settings.mk

objects=\
IO/File.o \
IO/stringio.o \
IO/BasicIO.o \
Tex2MathMLConverter.o


include generic/standard_rules.mk

Tex2MathML: ${objects}
	${CC} main.cpp ${INCLUDE} ${LDFLAGS} ${DEBUG} ${objects} -o Tex2MathML

symbol_structs:
	echo -e "#ifndef _tex_symbols_h\n#define _tex_symbols_h\n"> tex_symbols.h
	echo -e "#include \"tex2mml_data_types.h\"\n\nstruct TexSymbol_s GlobalTexSymbol[] =\n{" >> tex_symbols.h
	cat tex_symbols.txt | sed -f symbols2struct.sed >> tex_symbols.h
	echo -e "};\n\n#endif // _tex_symbols_h\n" >> tex_symbols.h

