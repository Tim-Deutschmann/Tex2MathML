#ifndef _error_h
#define _error_h

#include <stdio.h>

// use with __FILE__, __LINE__ and __func__

inline void errorIn(const char *file_name, const int& line_number){fprintf(stderr, "file \"%s\" line %d\n", file_name, line_number);}
inline void errorIn(const char *file_name, const int& line_number, const char *function_name){fprintf(stderr, "file \"%s\" line %d, function %s()\n", file_name, line_number, function_name);}

#endif //_error_h

