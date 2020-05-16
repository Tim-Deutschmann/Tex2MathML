#ifndef _File_h
#define _File_h

#include "fileio.h"

class File
{

	protected:

		FILE *fptr;
		char *file_content;
		char *file_name;
		int file_size;

		bool load(FILE *fptr);

	public:

		File();
		~File();

		inline FILE *getFILEPtr(){return fptr;}

		bool open(char *filename, const char *mode);

		bool load(char *file_name);
		inline bool load(){return load(fptr);}
		
		void close();

		inline int numberOfRows(){return ::numberOfRows(fptr);}
		inline int numberOfColumns(bool robust_behaviour=false){return ::numberOfColumns(fptr,robust_behaviour);}
		inline bool readTable(int rows, int columns, int element_size, char *format_string, void *data){return ::readTable(fptr, rows, columns, element_size, format_string, data);}
};

#endif

