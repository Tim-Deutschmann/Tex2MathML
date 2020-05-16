#include "fileio.h"
#include "generic/error.h"
#include "stringio.h"

int numberOfRows(char *filename, bool robust_behaviour)
{
	FILE *fptr=fopen(filename,"r");
	if(!fptr) return -1;
	int rows=numberOfRows(fptr, robust_behaviour);
	fclose(fptr);
	return rows;	
}

int numberOfRows(FILE *fptr, bool robust_behaviour)
{
	int rows=0, c;
	char line_buffer[100];
	long filepos=ftell(fptr);
	fseek(fptr,SEEK_SET,0);
	bool is_new_line=true;
	while((c=fgetc(fptr))!=EOF)
	{
		switch(c)
		{
			case '\n':
				rows++;
				is_new_line=true;
				break;
			case '#':
				if(is_new_line && robust_behaviour)
					fgets(line_buffer, 100, fptr);	// eat comment line
				is_new_line=false;
				break;
			default:
				is_new_line=false;
		}	
	}
	fseek(fptr, SEEK_SET, filepos);
	return rows;	
}

int numberOfColumns(char *filename, bool robust_behaviour)
{
	FILE *fptr=fopen(filename, "r");
	if(!fptr) return -1;
	int ntabs=numberOfColumns(fptr, robust_behaviour);
	fclose(fptr);
	return ntabs;
}

int numberOfColumns(FILE *fptr, bool robust_behaviour)
{
	long filepos=ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	int ntabs=0;
	if(robust_behaviour)
	{
		fseek(fptr, 0, SEEK_END);
		long file_size=ftell(fptr);

		fseek(fptr, 0, SEEK_SET);
		char *line_buffer=new char[int(file_size)];
		if(!line_buffer)
		{
			errorIn(__FILE__, __LINE__, __func__);
			return -1;
		}
		fgets(line_buffer, file_size, fptr);
		condenseLine(line_buffer);
		ntabs=numberOf('\t', line_buffer)+1;
		delete [] line_buffer;
		/*
		int character;
		while(1)
		{
			character=fgetc(fptr);
			fseek(fptr, -1, SEEK_CUR);	// rewind file ptr by one character
			if(character=='#')
				fgets(line_buffer, 100, fptr);	// eat comment line
			else break;
		}
		bool last_character_is_a_spacer=true;
		do
		{
			character=fgetc(fptr);
			switch(character)
			{
				case ' ':
				case '\t':
					last_character_is_a_spacer=true;
					break;

				case EOF:
				case '\n':
					break;

				default:
					if(last_character_is_a_spacer)
					{
						ntabs++;
						last_character_is_a_spacer=false;
					}
			}
		}
		while(character!=EOF && character!='\n');*/
	}
	else
	{
		int c;
		while((c=fgetc(fptr))!='\n' && c!=EOF) if(c=='\t') ntabs++;
		ntabs++;
	}
	fseek(fptr,filepos, SEEK_SET);
	return ntabs;
}

bool readTable(FILE *fptr, int rows, int columns, int element_size, char *format_string, void *data)
{
	int row, column, fields_read;
	if(rows>1)
	{
		char irf[20], ref[20];	// in-row-format and row-end-format
		sprintf(irf,"%%%s\t",format_string);
		sprintf(ref,"%%%s\n",format_string);
		for(row=0;row<rows;row++)
			for(column=0;column<columns;column++)
			{
				if(column<columns-1)
					fields_read=fscanf(fptr,irf,data);
				else
					fields_read=fscanf(fptr,ref,data);
				if(fields_read!=1)
				{
					fprintf(stderr,"error in column %d, row %d!\n",column+1,row+1);
					fprintf(stderr,"read %d field(s)!\n",fields_read);
					return false;
				}
				data=(void *)((char *)data+element_size);
			}
	}
	else
	{
		char format[20];	// in-row-format and row-end-format
		sprintf(format,"%%%s\\n",format_string);
		for(row=0;row<rows;row++)
		{
			fields_read=fscanf(fptr,format_string,data);
			if(fields_read!=1)
			{
				fprintf(stderr,"error in row %d!\n",row+1);
				fprintf(stderr,"read %d field(s)!\n",fields_read);
				return false;
			}
			data=(void *)((char *)data+element_size);
		}
	}
	return true;
}

bool doesFileExist(char *filename)
{
	FILE *fptr=fopen(filename,"r");
	if(!fptr)
		return false;
	fclose(fptr);
	return true;
}

bool loadFileContentBinary(char *filename, char **pbuffer, int *pfilesize)
{
	int filesize;
	char *buffer;
	FILE *fptr=fopen(filename, "rb");
	*pbuffer = 0;
	*pfilesize = 0;
	if(!fptr)
	{
		*pfilesize=0;
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "file \"%s\" does not exist or can not be read\n", filename);
		return false;
	}
	fseek(fptr, 0, SEEK_END);
	filesize = ftell(fptr);
	// buffer = malloc (sizeof(char) * (filesize+1));
	buffer = new char [ filesize + 1 ];
	if(!buffer)
	{
		fclose(fptr);
		*pfilesize = 0;
		*pbuffer = 0;
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "file \"%s\": could not allocate %d bytes\n", filename, filesize);
		return false;
	}
	// read content
	fseek(fptr, 0, SEEK_SET);
	fread(buffer, sizeof(char) * filesize, 1, fptr);
	*pfilesize = filesize;
	*pbuffer = buffer;
	fclose(fptr);
	return true;
}


