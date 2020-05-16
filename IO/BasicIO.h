#ifndef _BasicIO_h
#define _BasicIO_h

#include "stringio.h"
#include "IO/BasicIO.h"

#include <stdio.h>

#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <string>

#define BasicIO_string_size	2048

using namespace std;

class BasicIO
{
	typedef void (BasicIO::*writeFunctionPtr)(FILE *);
	bool write(char *file_name, writeFunctionPtr pWriteFunction);

	public:

		enum Type_e
		{
			type_bool,
			type_int,
			type_uint,
			type_float,
			type_double,
			type_angle,
			type_string,
			type_file,
			type_configuration,
			type_directory,
#ifdef McArtim
			type_profile,
#endif
			type_enum
		};

		struct Parameter_s
		{
			// ~Parameter_s(){ cout << "destroying " << name_list.front() << '\n';}
			void *ptr;

			enum Type_e type;

			list<string> name_list;

			list< pair<int, string> > enum_map;

			const char *description;
			const char *enum_name_list_string;
			const char *name_list_string;
		};

	protected:

		const char *IOName;

		list<struct Parameter_s> ParameterList;

		void formatFilePath(char *file_path, char *file_name);

		char dir_base[BasicIO_string_size];
		char conf_file_name[BasicIO_string_size];

		void addParameter(void *ptr, const enum Type_e& t, const char *names, const char *enum_names, const char *description);

	public:

		BasicIO();

		inline const char *getIOName(){return IOName;}
		inline char *getConfFileName(){return conf_file_name;}

		static int getSizeof(enum Type_e t);

		bool read(char *file_name, bool cancel_on_errors=true);
		inline bool reload(){return read(conf_file_name);}

		void write(FILE *fptr);
		inline bool write(char *file_name){return write(file_name, &BasicIO::write);}

		void writeTemplate(FILE *fptr);
		inline bool writeTemplate(char *file_name){return write(file_name, &BasicIO::writeTemplate);}

		struct Parameter_s *findParameter(void *ptr);
		struct Parameter_s *findParameter(const string& name);

		bool O2I(const char *name, const char *value_string);
		bool I2O(struct Parameter_s *p, const char *value_string);
		bool I2O(void *ptr, const char *value_string);

		const char *getIOName(void *ptr);
		const char *getDescription(void *ptr);
		inline char *getBaseDirectory(){return dir_base;}
		inline void getBaseDirectoryFromFilename(char *file_name){extractPathFromFilename(file_name, dir_base);}
		
		virtual bool loadFiles(){return true;}
		bool readAndLoadFiles(char *conf_file_name);

};

#endif// _BasicIO_h


