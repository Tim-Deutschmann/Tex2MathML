#include "File.h"
#include "generic/error.h"

#include <stdio.h>
#include <stdlib.h>

File::File()
{
	fptr = 0;
	file_content = 0;	
}

File::~File()
{
	if(file_content)
		free(file_content);
	close();
}

bool File::open(char *file_name, const char *mode)
{
	if(fptr)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "file \"%s\" still open!\n", file_name);
		close();
	}
	fptr = fopen(file_name, mode);
	if(!fptr)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "error opening file \"%s\"\n", file_name);
		return false;
	}
	this->file_name = file_name;
	return true;
}

bool File::load(FILE *fptr)
{
	// read file content
	fseek(fptr, 0, SEEK_END);
	if(file_content)
		free(file_content);
	file_size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	file_content = (char *) malloc ( file_size * sizeof(char) );
	if(!file_content)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "error allocating %d bytes for content of file \"%s\"\n", file_size, file_name);
		return false;
	}
	if(fread(file_content, file_size, 1, fptr)!=1)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "error reading %d bytes from file \"%s\"\n", file_size, file_name);
		return false;
	}
	return true;
}

bool File::load(char *file_name)
{
	if(!open(file_name, "rb"))
	{
		errorIn(__FILE__, __LINE__, __func__);
		return false;
	}
	if(!load(fptr))
	{
		errorIn(__FILE__, __LINE__, __func__);
		close();
		return false;
	}
	close();
	return true;
}

void File::close()
{
	if(fptr)
	{
		fclose(fptr);
		fptr = 0;
	}
}


