/* ------------------------------------------
 * Project: Unix interpreter
 * Authors: Rejas C. & Poroli F.
 * Version: 1.0 provisoire, 2016-04-17
 * ------------------------------------------*/

#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdio.h> 
#include <stdlib.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>


#define MAX_ALIAS 100


/**
 * Structure alias
 */
typedef struct alias alias_t;
struct alias
{
	char* name;
	char* value;
};

int nbr_alias; // nombre totale des alias existant


void read_profile_file ();
int write_on_file(const int fd_file, const char* str);
char* creat_str_home(const char* pw_dir);
char* creat_str_path();

int add_env(const char* name_value);
char* read_env(const char* name);

int cd(const char* directory);
char* pwd();

void remove_char(char* str, const char char_remove);


void remove_cr(char* str);
char** strxpld(char* str, const char* delim);
const int count_delim(const char* str, const char* c);


void add_alias(alias_t* alias, const char* name_value);
void view_all_alias(alias_t* alias);
int find_alias_value(alias_t* alias, const char* name);
void view_alias(alias_t* alias, const char* name);



#endif
