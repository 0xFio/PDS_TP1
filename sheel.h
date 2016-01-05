/* ------------------------------------------
 * Project: Unix interpreter
 * Authors: Rejas C. & Poroli F.
 * Version: 1.0, 2016-04-01
 * ------------------------------------------*/

#ifndef __SHEEL_H__
#define __SHEEL_H__

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


void read_profile_file ();
void write_on_file(int fd_file, const char* str);
char* creat_str_home(const char* pw_dir);
char* creat_str_path();

int add_env(char* name_value);
char* read_env(char* name);

int cd(char* directory);
char* pwd();

void remove_char(char* str, char char_remove);


void remove_cr(char* str);
char** strxpld(char* str, const char* delim);
const int count_delim(const char* str, const char* c);


#endif
