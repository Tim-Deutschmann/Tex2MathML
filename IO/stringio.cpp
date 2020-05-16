#include "stringio.h"
#include "generic/error.h"
#include <time.h>

#ifdef WIN32
	#include <string.h>
	#include <stdio.h>
#else
	#include <string>
#endif

int numberOf(const char& character, const char *text)
{
	int n=0;
	while(*text) if(*text++==character) n++;
	return n;
}

template<class T> bool isIn(const T& character, const T *text)
{
	T *cptr = (T *)text, c;
	do
	{
		c = *cptr++;
		if(c == character)
			return true;
	} while(c!=0);
	return false;
}

template bool isIn<char>(const char&, const char *);
template bool isIn<wchar_t>(const wchar_t&, const wchar_t*);

bool isIn(const char& character, const char *text)
{
	char *cptr = (char *)text, c;
	do
	{
		c = *cptr++;
		if(c == character)
			return true;
	} while(c!=0);
	return false;
}

bool isMultiByteCode(const char& character)
{
	switch(character)
	{
		case char(0xc2):
		case char(0xc3):
		case char(0xc4):
		case char(0xc5):
			return true;
		default:;
	}
	return false;
}

bool isAlphaNumeric(const char& character)
{
	int int_character=character;
	if((int_character >= int('a') && int_character <= int('z')) || \
		(int_character >= int('A') && int_character <= int('Z')) || \
		(int_character >= int('0') && int_character <= int('9')))
		return true;
	/*switch(character)
	{
		case char(0xa4): // ä
		case char(0xb6): // ö
		case char(0xbc): // ü
		case char(0x84): // Ä
		case char(0x96): // Ö
		case char(0x9c): // Ü
		case char(0x9f): // ß
			return true;
		default:;
	}*/
	// (int_character >= int(0xff) && int_character <= int(0x80)) ||
	return false;
}

bool isAlpha(const char& character)
{
	int int_character = character;
	if((int_character >= int('a') && int_character <= int('z')) || \
		(int_character >= int('A') && int_character <= int('Z')))
		return true;
	return false;
}

bool isNumeric(const char& character)
{
	int int_character = character;
	if(int_character >= int('0') && int_character <= int('9'))
		return true;
	return false;
}

bool isSpecialGermanCharacter(const char& character)
{
	switch(character)
	{
		case char(0xa4): // ä
		case char(0xb6): // ö
		case char(0xbc): // ü
		case char(0x84): // Ä
		case char(0x96): // Ö
		case char(0x9c): // Ü
		case char(0x9f): // ß
			return true;
		default:;
	}
	return false;
}

bool isAlphaNumeric(const wchar_t& character)
{
	if((character >= 'a' && character <= 'z') \
		|| (character >= 'A' && character <= 'Z') \
		|| (character >= 0x80 && character <= 0xff) \
		|| (character >= '0' && character <= '9'))
		return true;
	return false;
}

void remove(char character, char *text)
{
	if(!*text) return;
	size_t n=strlen(text);
	char *buffer=new char[n+1],*source_charptr=text,*destination_charptr=buffer,c;
	do
	{
		c=*source_charptr++;
		if(c!=character)
		{
			*destination_charptr=c;
			destination_charptr++;
		}
	}
	while(c!='\0');
	//*destination_charptr='\0';// terminate string
	strcpy(text,buffer);
	*(--destination_charptr)=character;
	delete [] buffer;
}

void replace(char character_A, char character_B, char *text)
{
	if(!*text || character_A=='\0') return;
	char c;
	do
	{
		c=*text;
		if(c==character_A)
			*text=character_B;
		text++;
	}
	while(c!='\0');
}

bool extractWordFromList(const char *text, int index, char separation_character, char *buffer)
{
	char character;
	while(index>0)
	{
		character=*text++;
		if(character==separation_character)
			index--;
		if(character=='\0' && index>0)
			return false;
	}
	while(1)
	{
		*buffer=*text;
		if(*text=='\0')
			return true;
		else if(*text==separation_character)
		{
			*buffer='\0';
			return true;
		}
		text++; buffer++;
	}
	return false;
}

#ifdef WIN32
	#define	DIR_CHAR	'\\'
#else
	#define DIR_CHAR	'/'
#endif	

bool extractPathFromFilename(const char *filename, char *path_buffer, char *name)
{
	const char *charptr=filename+strlen(filename)-1;
	while(*charptr--!=DIR_CHAR)
		if(charptr<filename)
			return false; // attention: this is part of the loop
	charptr++;
	int index=int(charptr-filename)+1;
	strncpy(path_buffer, filename, index);
	path_buffer[index]='\0';
	if(name)
		strcpy(name,++charptr);
	return true;
}

bool extractBracketExpression(const char *text, char b1, char b2, char *buffer)
{
	if(!numberOf(b1,text) || !numberOf(b2,text))
		return false;
	char character;
	const char *charptr=text;
	do
	{
		character=*charptr++;
		if(character=='\0')
			return false;
	}while(character!=b1);
	do
	{
		character=*charptr++;
		*buffer=character;
		buffer++;
		if(character=='\0')
			return false;
	}while(character!=b2);
	*(--buffer)='\0';
	return true;
}

bool extractBool(const char *value_string, bool *aboolptr)
{
	if(!strcmp(value_string,"yes") || !strcmp(value_string,"1") || !strcmp(value_string,"true"))
		*aboolptr=true;
	else if(!strcmp(value_string,"no") || !strcmp(value_string,"0") || !strcmp(value_string,"false"))
		*aboolptr=false;
	else
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "error extracting boolian value from %s\n", value_string);
		return false;
	}
	return true;
}

char *strncpyz(char *destination, const char *source, size_t n)
{
	char *ret=strncpy(destination,source,n);
	destination[n]='\0';
	return ret;
}

void condenseLine(char *line_buffer) // removes space/tab/extra character polutions between the columns and replace them by one TAB character
{
	char buffer[10000],*char_ptr=buffer,character,*source_ptr=line_buffer;
	bool last_character_empty=true;
	do
	{
		character=*source_ptr++;
		switch(character)
		{
			case ' ':
			case '\t':
				if(last_character_empty)
					continue;
				last_character_empty=true;
				*char_ptr++='\t';
				break;
			case 10:
				break;
			default:
				*char_ptr++=character;
				if(character!=0)
					last_character_empty=false;
		}
	}while(character);	
	if(last_character_empty)
		buffer[strlen(buffer)-1]=0;
	strcpy(line_buffer,buffer);
}

bool calculateSecondsInEpoche(int *pSiE, char *date_string, char *time_string)
{
/*
  struct tm {
               int tm_sec;	// seconds
               int tm_min;	// minutes
               int tm_hour;	// hours
               int tm_mday;	// day of the month
               int tm_mon;	// month
               int tm_year;	// year
               int tm_wday;	// day of the week
               int tm_yday;	// day in the year
               int tm_isdst;	// daylight saving time
           };
*/	
	struct tm time_struct;
	memset(&time_struct, 0, sizeof(struct tm));
#ifdef WIN32
	if(sscanf(date_string, "%d.%d.%d", &time_struct.tm_mday, &time_struct.tm_mon, &time_struct.tm_year)!=3)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "could not extract date from \"%s\"\n", date_string);
		return false;
	}
	time_struct.tm_mday--;
	time_struct.tm_mon--;
	time_struct.tm_year+=100;
	if(sscanf(date_string, "%d.%d.%d", &time_struct.tm_hour, &time_struct.tm_min, &time_struct.tm_sec)!=3)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "could not extract time from \"%s\"\n", time_string);
		return false;
	}
#else
	if(!strptime(date_string, "%d.%m.%y", &time_struct))
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "could not extract date from \"%s\"\n", date_string);
		return false;
	}
	if(!strptime(time_string, "%H:%M:%S", &time_struct))
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "could not extract time from \"%s\"\n", time_string);
		return false;
	}
#endif
	int seconds_in_epoche=mktime(&time_struct);
	if(seconds_in_epoche==-1)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "error calculating seconds in epoche for date \"%s\" and time \"%s\"\n", date_string, time_string);
		return false;
	}
	*pSiE=seconds_in_epoche;
	return true;	
}

void formatTimeFromSecondsInEpoche(time_t SiE, char *time_string)
{
	struct tm *ptm=gmtime(&SiE);
	// strftime(time_stamp, 20, "%d.%m.%y %H:%M:%S", ptm);
	sprintf(time_string, "%02d.%02d.%02d %02d:%02d:%02d", ptm->tm_mday, ptm->tm_mon+1, ptm->tm_year-100, (ptm->tm_hour+1)%24, ptm->tm_min, ptm->tm_sec); 
}

void createListOfStrings(char *x_separated_list, char x, class list<string>& list_of_strings, const char *empty_list_string)
{
	list_of_strings.clear();
	if(!x_separated_list[0] || !strcmp(x_separated_list, empty_list_string))
		return;
	char name_buffer[100];
	int i, no_separators=numberOf(x, x_separated_list);
	condenseLine(x_separated_list);
	for(i=0;i<=no_separators;i++)
	{
		extractWordFromList(x_separated_list, i, ',', name_buffer);
		list_of_strings.push_back(string(name_buffer));
	}
}






