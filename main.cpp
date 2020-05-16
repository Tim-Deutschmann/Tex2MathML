#include "Tex2MathMLConverter.h"
#include "generic/error.h"

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("usage: Tex2MathML [HTML file] tex2mathml.conf");
		return 0;
	}
	Tex2MathMLConverter converter;
	if(!converter.read(argv[2]) ||\
		!converter.loadUserTexSymbols())
	{
		errorIn(__FILE__, __LINE__, __func__);
		return -1;
	}
	if(!converter.load(argv[1]))
	{
		errorIn(__FILE__, __LINE__, __func__);
		return 0;
	}
	if(!converter.analyzeContent())
	{
		errorIn(__FILE__, __LINE__, __func__);
		return 0;
	}
	converter.print(stdout);
	return 0;
}

