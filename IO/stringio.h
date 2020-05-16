#ifndef _stringio_h
#define _stringio_h

#include <string.h>
#include <time.h>
#include <list>
#include <string>

using namespace std;

int numberOf(const char& character, const char *text);

template<class T> bool isIn(const T&, const T *text); 

bool isMultiByteCode(const char& character);
bool isSpecialGermanCharacter(const char& character);

bool isAlphaNumeric(const char& character); 
bool isAlphaNumeric(const wchar_t& character);

bool isAlpha(const char& character); 
bool isNumeric(const char& character); 

bool extractWordFromList(const char *text, int index, char separation_character, char *buffer);
bool extractPathFromFilename(const char *filename, char *path_buffer, char *name=0);

void remove(char character, char *text);
void replace(char character_A, char character_B, char *text);

bool extractBracketExpression(const char *text, char b1, char b2, char *buffer);

bool extractBool(const char *value_string, bool *aboolptr);
inline const char *getBoolString(bool abool){return abool?"yes":"no";}

char *strncpyz(char *destination, const char *source, size_t n);

void condenseLine(char *line_buffer);	// removes space/tab/extra character polutions between the columns and replace them by one TAB character
bool calculateSecondsInEpoche(int *pSiE, char *date_string, char *time_string);
void formatTimeFromSecondsInEpoche(time_t SiE, char *time_string);

void createListOfStrings(char *x_separated_list, char x, class list<string>& list_of_strings, const char *empty_list_string="none");

#endif //_stringio_h

