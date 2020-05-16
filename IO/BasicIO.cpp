#include "BasicIO.h"
#include <stdlib.h>

#include <math.h>
#include "Math/trigonometry.h"

#define BASICIO_FILE_UNDEFINED	"undefined"
#define BASICIO_STRING_UNDEFINED	"none"

#ifdef McArtim
	#include "../current/atmosphere/profile/Profile.h"
#endif 

#include "generic/error.h"

BasicIO::BasicIO()
{
	IOName="BasicIO";
	addParameter(dir_base, type_directory, "dir_base|dir_base_directory", 0, "base directory in which all subordinated files can be found");
}

bool BasicIO::O2I(const char *name_string, const char *value_string)
{
	struct Parameter_s *p;

#ifdef McArtim
	// investigate if there are braces
	class Profile *pProfile;
	int cluster_index=-1, data_index=-1;
	const char *test_name_string=name_string;
	char modified_name_string[100];
	if(numberOf('[', name_string)==1 && numberOf(']', name_string)==1)
	{
		char pair_buffer[50], buffer[30];
		if(!extractBracketExpression(name_string, '[', ']', pair_buffer))
		{
			errorIn(__FILE__, __LINE__, __func__);
			fprintf(stderr, "could not extract bracket expression from \"%s\"!\n", name_string);
			return false;
		}
		if(numberOf(',', pair_buffer)!=1)
		{
			errorIn(__FILE__, __LINE__, __func__);
			fprintf(stderr, "wrong bracket expression format \"%s\", allowed is only \"[abc,xyz]\"!\n", name_string);
			return false;
		}

		extractWordFromList(pair_buffer, 0, ',', buffer);
		cluster_index=atoi(buffer)-1;

		extractWordFromList(pair_buffer, 1, ',', buffer);
		data_index=atoi(buffer)-1;

		// terminate name_string after profile name, at '['
		strcpy(modified_name_string, name_string);
		char *char_ptr=modified_name_string;
		while(*char_ptr!='\0' && *char_ptr!='[')
			char_ptr++;
		*char_ptr='\0';
		test_name_string=modified_name_string;
		// printf("%s %d %d\n", name_string, length, strlen(name_string));
	}
#else
	const char *test_name_string=name_string;
#endif
	list<struct BasicIO::Parameter_s>::iterator it_p;
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{
		p=&(*it_p);
		list<string>::iterator it_name;
		for(it_name=p->name_list.begin();it_name!=p->name_list.end();it_name++)
		{
			if(!it_name->compare(0, it_name->length(), test_name_string))
			{
				switch(p->type)
				{
					case type_bool:
						if(!extractBool((char *)value_string, (bool *)p->ptr))
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "wrong boolean flag syntax: \"%s\". Allowed is yes|true|1 or no|false|0!\n", value_string);
							return false;
						}
						break;
					case type_uint:
						*((unsigned int *)p->ptr)=(unsigned int)atoi(value_string);
						break;

					case type_int:
						*((int *)p->ptr)=atoi(value_string);
						break;

					case type_float:
						*((float *)p->ptr)=(float) atof(value_string);
						break;

					case type_double:
						*((double *)p->ptr)=atof(value_string);
						break;

					case type_angle:
						*((double *)p->ptr)=Rad(atof(value_string));
						break;
#ifdef McArtim
					case type_profile:
						pProfile=(class Profile *)p->ptr;
						if(cluster_index<0 || cluster_index>=pProfile->getNOClusters())
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "invalid cluster index %d in \"%s\"!\n", cluster_index+1, name_string);
							return false;
						}
						else if(data_index<0 || data_index>=pProfile->getClusterDimension())
						{
							errorIn(__FILE__, __LINE__, __func__);
							fprintf(stderr, "invalid data index %d in \"%s\"!\n", data_index+1, name_string);
							return false;
						}
						else
						{
							struct Profile::Cluster_s *pCluster=pProfile->getClusterPtr()+cluster_index;
							pCluster->input_data[data_index]=atof(value_string);
							pProfile->invalidateCluster(cluster_index);
						}
						break;
#endif
					case type_configuration:
					case type_file:
					case type_directory:
					case type_string:
						strcpy((char *)p->ptr, value_string);
						break;

					case type_enum:
						{
							list< pair<int, string> >::iterator it_enum;
							for(it_enum=p->enum_map.begin();it_enum!=p->enum_map.end();it_enum++)
								if(!strcmp(it_enum->second.c_str(), value_string))
								{
									*((int *)p->ptr)=it_enum->first;
									return true;
								}
							fprintf(stderr, "unknown enum lvalue \"%s\" for parameter \"%s\"!\n", value_string, name_string);
							return false;
						}
						break;

					default:
						errorIn(__FILE__, __LINE__, __func__);
						fprintf(stderr, "parameter with name \"%s\" found but with undefined type!\n", name_string);
						return false;
				}
				return true;
			}
		}
	}
	return false;
}

struct BasicIO::Parameter_s *BasicIO::findParameter(void *ptr)
{
	list<struct BasicIO::Parameter_s>::iterator it_p;
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
		if(it_p->ptr==ptr)
			return (struct Parameter_s *)&(*it_p);
	return (struct Parameter_s *)0;
}

struct BasicIO::Parameter_s *BasicIO::findParameter(const string& name)
{
	int n;
	struct Parameter_s *p;
	list<struct BasicIO::Parameter_s>::iterator it_p;
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{
		p=&(*it_p);
		list<string>::iterator it_name;
		for(it_name=p->name_list.begin();it_name!=p->name_list.end();it_name++)
		{
			n=it_name->length();
			if(!name.compare(0, n, *it_name))
				return p;
		}
	}
	/*//int n;
	list<struct BasicIO::Parameter_s>::iterator it_p;
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{
		list<string>::iterator pName=it_p->name_list.begin();
		n=pName->length();
		for(;pName!=it_p->name_list.end();pName++)
			if(!name.compare(0, n, *pName))	//if(!pName->compare(0, n, name))
				return (struct Parameter_s *)&(*it_p);
	}*/
	return (struct Parameter_s *)0;
}

const char *BasicIO::getIOName(void *ptr)
{
	struct Parameter_s *p=findParameter(ptr);
	return p ? (p->name_list.begin())->c_str() : 0;
}

const char *BasicIO::getDescription(void *ptr)
{
	struct Parameter_s *p=findParameter(ptr);
	return p ? p->description : 0;
}

bool BasicIO::write(char *file_name, BasicIO::writeFunctionPtr pWriteFunction)
{
	FILE *fptr=fopen(file_name, "w");
	if(!fptr)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "could not write to file \"%s\"\n", file_name);
		return false;
	}
	(this->*pWriteFunction)(fptr);
	fclose(fptr);
	return true;
}

void BasicIO::writeTemplate(FILE *fptr)
{
	/*struct Parameter_s *p;
	char value_string[100];

	list<struct BasicIO::Parameter_s>::iterator it_p;
	int maximum_width=0, width;
	// determine maximum width
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{
		p=(struct BasicIO::Parameter_s *)&(*it_p);
		I2O(p, (const char *)value_string);
		width=strlen(value_string);

		list<string>::iterator it_name=p->name_list.begin();
		width+=it_name->length();
		it_name++;
		for(;it_name!=p->name_list.end();it_name++)
			width+=1+it_name->length();
		if(width>maximum_width)
			maximum_width=width;
	}
	maximum_width+=5;
	// output with comments on same position
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{	
		p=(struct BasicIO::Parameter_s *)&(*it_p);
		I2O(p, (const char *)value_string);
		width=strlen(value_string);

		list<string>::iterator it_name=p->name_list.begin();
		width+=it_name->length();
		fprintf(fptr, "%s", it_name->c_str());
		it_name++;
		for(;it_name!=p->name_list.end();it_name++)
		{
			fprintf(fptr, "|%s", it_name->c_str());
			width+=1+it_name->length();
		}
		fprintf(fptr, "=%s",  value_string);
		for(;width<maximum_width;width++)
			fputc(' ', fptr);
		fprintf(fptr, "# %s\n",  p->description);
	}*/
	struct Parameter_s *p;
	list<struct BasicIO::Parameter_s>::iterator it_p;
	char value_string[100];
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{	
		p=(struct BasicIO::Parameter_s *)&(*it_p);
		I2O(p, (const char *)value_string);
		fprintf(fptr, "%s=%s\t", p->name_list_string, value_string);
		if(p->type==type_enum)
			fprintf(fptr, "# selection: %s :%s\n", p->enum_name_list_string, p->description);
		else
			fprintf(fptr, "# %s\n", p->description);
	}
}

void BasicIO::write(FILE *fptr)
{
	struct Parameter_s *p;
	char value_string[100];
	list<struct BasicIO::Parameter_s>::iterator it_p;
	for(it_p=ParameterList.begin();it_p!=ParameterList.end();it_p++)
	{
		p=(struct BasicIO::Parameter_s *)&(*it_p);
		I2O(p, (const char *)value_string);

		list<string>::iterator it_name=p->name_list.begin();
		fprintf(fptr, "%s", it_name->c_str());
		/*it_name++;
		for(;it_name!=p->name_list.end();it_name++)
			fprintf(fptr, "|%s", it_name->c_str());*/
		fprintf(fptr, "=%s\n",  value_string);
	}
}

bool BasicIO::read(char *file_name, bool cancel_on_errors)
{
	FILE *fptr=fopen(file_name,"r");
	if(!fptr)
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "could not read %s conf file\n", IOName);
		return false;
	}
	int line_number=0;
	bool continue_search;
	char name_buffer[100], value_buffer[100];
	char line_buffer[300], *source_ptr, *destination_ptr;
	while(fgets(line_buffer, 300, fptr))
	{
		line_number++;
		// strip comments after #
		source_ptr=line_buffer;
		continue_search=true;
		do
		{
			switch(*source_ptr)
			{
				case '#':
				case '\n':
				case '\0':
					*source_ptr='\0';
					continue_search=false;
					break;
			}
			source_ptr++;
		}while(continue_search);
		// separate  name = value
		if(numberOf('=', line_buffer)!=1)
			continue;
			/*fprintf(stderr, "file \"%s\" line %d: no equation sign found!\n", file_name, line_number);
			fclose(fptr);
			return false;
			fprintf(stderr, "skipping file \"%s\" line %d: no equation sign found\n", file_name, line_number);*/
		source_ptr=line_buffer;
		destination_ptr=name_buffer;
		continue_search=true;
		do
		{
			switch(*source_ptr)
			{
				case ' ':
				case '\t':
					break;
				case '=':
					*destination_ptr='\0';
					continue_search=false;
					break;
				case '\0':
					continue_search=false;
					break;
				default:
					*destination_ptr++=*source_ptr;
			}
			source_ptr++;
		}while(continue_search);
		continue_search=true;
		strcpy(value_buffer, source_ptr);
		condenseLine(value_buffer);
		if(!O2I(name_buffer, value_buffer) && cancel_on_errors)
		{
			fprintf(stderr, "\nfile \"%s\" line %d: name (\"%s\") value (\"%s\") pair not accepted!\n\n", \
				file_name, line_number, name_buffer, value_buffer);
			fclose(fptr);
			writeTemplate(stderr);
			fputc('\n', stderr);
			return false;
		}
	}
	fclose(fptr);
	strcpy(conf_file_name, file_name);
	return true;
}

bool BasicIO::I2O(struct Parameter_s *p, const char *value_string)
{
	switch(p->type)
	{
		case type_bool:
			strcpy((char *)value_string, *((bool *)p->ptr)?"yes":"no");
			break;

		case type_int:
			sprintf((char *)value_string, "%d", *((int *)p->ptr));
			break;

		case type_uint:
			sprintf((char *)value_string, "%u", *((unsigned int *)p->ptr));
			break;

		case type_float:
			sprintf((char *)value_string, "%f", *((float *)p->ptr));
			break;

		case type_double:
			sprintf((char *)value_string, "%lf", *((double *)p->ptr));
			break;

		case type_angle:
			sprintf((char *)value_string, "%lf", Degree(*((double *)p->ptr)));
			break;

		case type_file:
		case type_configuration:
		case type_directory:
		case type_string:
			strcpy((char *)value_string, (const char *)p->ptr);
			break;

		case type_enum:
		{
			list< pair<int, string> >::iterator it_enum;
			for(it_enum=p->enum_map.begin(); it_enum!=p->enum_map.end(); it_enum++)
				if(it_enum->first==*((int *)p->ptr))
				{
					strcpy((char *)value_string, it_enum->second.c_str());
					return true;
				}
			strcpy((char *)value_string, "(undefined)");
			break;
		}
#ifdef McArtim
		case type_profile:
			break;
#endif

		default:
			errorIn(__FILE__, __LINE__, __func__);
			fprintf(stderr, "parameter \"%s\" not associated with certain type!\n", p->name_list.begin()->c_str());
			return false;
	}
	return true;	
}

bool BasicIO::I2O(void *ptr, const char *value_string)
{
	struct Parameter_s *p=findParameter(ptr);
	return p ? I2O(p, value_string) : false;
}

void BasicIO::formatFilePath(char *filepath, char *file_name)
{
	if(!strcmp(file_name, BASICIO_FILE_UNDEFINED))
	{
		errorIn(__FILE__, __LINE__, __func__);
		fprintf(stderr, "found undefined file name!\n");
	}
	else
		sprintf(filepath, "%s%s", dir_base, file_name);
}

bool BasicIO::readAndLoadFiles(char *conf_file_name)
{
	getBaseDirectoryFromFilename(conf_file_name); // note: base directory set by this call might be overwritten!
	return read(conf_file_name) && loadFiles();
}

int BasicIO::getSizeof(enum Type_e t)
{
	switch(t)
	{
		case type_bool:
			return sizeof(bool);

		case type_uint:
		case type_int:
		case type_enum:
			return sizeof(int);

		case type_float:
			return sizeof(float);

		case type_double:
		case type_angle:
			return sizeof(double);

		case type_string:
		case type_configuration:
		case type_file:
		case type_directory:
		default:;
	}
	return 0;
}

void BasicIO::addParameter(void *ptr, const BasicIO::Type_e& t, const char *names, const char *enum_names, const char *description)
{
	int i=0, n;
	char buffer[1000];

	struct Parameter_s p;

	p.ptr=ptr;
	p.type=t;
	p.name_list.clear();
	n=numberOf('|', names);
	if(n)
		for(i=0;i<=n;i++)
		{
			extractWordFromList(names, i, '|', buffer);
			p.name_list.push_back(string(buffer));
		}
	else
		p.name_list.push_back(string(names));
	p.name_list_string=names;
	p.enum_map.clear();
	if(enum_names)
	{
		n=numberOf('|', enum_names);
		if(n)
			for(i=0;i<=n;i++)
			{
				extractWordFromList(enum_names, i, '|', buffer);
				p.enum_map.push_back(pair<int, string>(i, string(buffer)));
			}
		p.enum_map.push_back(pair<int, string>(i, string(enum_names)));
		p.enum_name_list_string=enum_names;
	}
	else
		p.enum_name_list_string=0;
	p.description=description;
	switch(t)
	{
		case type_string:
			strcpy((char *) ptr, BASICIO_STRING_UNDEFINED );
			break;

		case type_file:
			strcpy((char *) ptr, BASICIO_FILE_UNDEFINED);
			break;

		case type_directory:
			// strcpy((char *) ptr, "directory");
			*((char *)ptr)='\0';
			break;
		default:;
	}

	ParameterList.push_back(p);
}













