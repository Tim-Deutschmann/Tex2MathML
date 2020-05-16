#ifndef _fileio_h
#define _fileio_h

#include <stdio.h>

int numberOfRows(char *filename, bool robust_behaviour=false);
int numberOfRows(FILE *fptr, bool robust_behaviour=false);
int numberOfColumns(char *filename, bool robust_behaviour=false);
int numberOfColumns(FILE *fptr, bool robust_behaviour=false);

bool doesFileExist(char *filename);

bool readTable(FILE *fptr, int rows, int columns, int element_size, char *format_string, void *data);
bool loadFileContentBinary(char *filename, char **pbuffer, int *pfilesize);

#endif //_fileio_h

