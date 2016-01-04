/* ------------------------------------------
 * Project: Unix interpreter
 * Authors: Rejas C. & Poroli F.
 * Version: 1.0, 2016-01-04
 * ------------------------------------------*/


#include "sheel.h"



/**
 *	@brief Function to read and configure the profile file and setenv PUTH and HOME 
 *	@param --
 *	@return const int ...
 */
void read_profile_file () {

	#define BUFFER_STR 128

	bool creat_HOME = true;
	bool creat_PATH = true;

	char buffer_str[BUFFER_STR];
	char *token;

	struct passwd *p = getpwuid(getuid());

	char str_home[strlen(p->pw_dir)];
	strcpy(str_home,p->pw_dir);


	int fd_profile = open(strcat(p->pw_dir,"/profile"), O_RDWR | O_CREAT, S_IRWXU);
		// Open the file profile, Read&Write, if is onexcisting creat it.

	if (fd_profile < 0) {
		printf("erreur sur l'ouverture du fichier profile");
		// peut etre utiliser errno !!!!
    }

	read(fd_profile, buffer_str, BUFFER_STR);

	token = strtok(buffer_str,"\n");	// find PATH or HOME in the file profile

	while (token != NULL) {

		if (strstr(token,"PATH") != NULL) {
			creat_PATH = false;	// if PATH find do not creat a line PATH
			// ajouter ici pour le setenv !!
		}
		else if (strstr(token,"HOME") != NULL) {
			creat_HOME = false; // if HOME find do not creat a line HOME
			// ajouter ici pour le setenv !!
		}

		printf("  %s\n", token );
		token = strtok(NULL, "\n");
	}

	if (creat_HOME == true)
		write_on_file(fd_profile, creat_str_home(str_home));

	if (creat_PATH == true)
		write_on_file(fd_profile, creat_str_path());

}


void write_on_file(int fd_file, const char* str) {

	if (write(fd_file, str, strlen(str)) != strlen(str)) {
		printf("erreur : écriture dans le fichier\n");
    }

}

char* creat_str_home(const char* pw_dir) {

	const char HOME[] = "HOME=";

	size_t len1 = strlen(pw_dir);
	size_t len2 = strlen(HOME);
	char* home = malloc(sizeof(char) *(len1 + len2 + 1));

	strcpy(home, HOME);
	strcat(home, pw_dir);
	strcat(home, "\n");

	return home;
}

char* creat_str_path() {

	char* str_path = malloc(sizeof(char) *strlen("PATH=/bin:/usr/bin:/usr/local/bin\n"));
	strcpy(str_path, "PATH=/bin:/usr/bin:/usr/local/bin\n");
	return str_path;

}



void add_env(char* name_value) {

	char* name;
	char* value;

	name = strtok(name_value, "=");
	value = strtok(NULL,"=");

	if (setenv(name, value, 1) == 0)
		printf("succes add env\n");

}

char* read_env(char* name) {

	remove_cr(name);
	remove_char(name, '$');

	printf("read env : %s=%s",name, getenv(name));

	return getenv(name);

}



void remove_char(char *str, char char_remove) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != char_remove) dst++;
    }
    *dst = '\0';
}































/**
 * @brief Function to remove the carriage return value on a string
 * @param char* str - String value
 */
void remove_cr(char* str) {
	size_t last = strlen(str) - 1;
	if (str[last] == '\n') str[last] = '\0'; // To remove the '\n'
}




const int strindxof(const char* str, const char* c) {
	bool found = false;
	int i = 0;
	size_t len = strlen(str);

	for(i = 0; i < len; i++) {
		if(str[i] == *c) {
			found = true;
			break;
		}
	}

	return found ? i : -1; // -1 means the character wasn't found
}




char* parse_value(const char* str, const char* delim) {
	const int delim_index = strindxof(str, delim);
	char* cpy_str = malloc(sizeof(char) * 1000);

	strcpy(cpy_str, str);
	for(int i = 0; i <= delim_index; i++, cpy_str++);

	return cpy_str;
}



















