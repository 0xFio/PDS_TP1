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

	char* str_home;
	char* str_path;

	char buffer_str[BUFFER_STR];
	char* token;

	struct passwd *p = getpwuid(getuid());

	char home_arg[strlen(p->pw_dir)];
	strcpy(home_arg, p->pw_dir);

	errno = 0;

	int fd_profile = open(strcat(p->pw_dir,"/profile"), O_RDWR | O_CREAT, S_IRWXU);
		// Open the file profile, Read&Write, if is onexcisting creat it.

	if (fd_profile < 0) {
		perror("Erreur ");
    }

	// -------------------------scanf

	read(fd_profile, buffer_str, BUFFER_STR); // ----------il faut faire pour controler la fin du fichier ----------------------------------------------------------------------------------------------------------------------

	token = strtok(buffer_str,"\n");	// find PATH or HOME in the file profile

	while (token != NULL) {

		if (strncmp(token,"PATH=", 5) == 0) {
			creat_PATH = false;	// if PATH find do not creat a line PATH
			str_path = token; 
		}
		else if (strncmp(token,"HOME=", 5) == 0) {
			creat_HOME = false; // if HOME find do not creat a line HOME
			str_home = token;
		}

		printf("  %s\n", token );
		token = strtok(NULL, "\n");
	}

	if (creat_HOME == true) {
		str_home = creat_str_home(home_arg);
		write_on_file(fd_profile, str_home);
	}

	if (creat_PATH == true) {
		str_path = creat_str_path();
		write_on_file(fd_profile, str_path);
	}

	add_env(str_home);
	add_env(str_path);

}



/**
 *	@brief Function write a string on file
 *	@param const int fd_file - file descritpor
 *	@param const char* str - String value
 *	@return ..............................................................
 */
void write_on_file(const int fd_file, const char* str) {

	if (write(fd_file, str, strlen(str)) != strlen(str)) {
		printf("erreur : écriture dans le fichier\n");
    }
}


/**
 *	@brief Function to creat a string for HOME ............
 *	@param const char* pw_dir - home directory
 *	@return string value - HOME
 */
char* creat_str_home(const char* pw_dir) {

	const char HOME[] = "HOME=";

	size_t len1 = strlen(pw_dir);
	size_t len2 = strlen(HOME);
	char* home = malloc(sizeof(char) *(len1 + len2 + 100));

	strcpy(home, HOME);
	strcat(home, pw_dir);
	strcat(home, "\n");

	return home;
}

/**
 *	@brief Function to creat a string PATH
 *	@return string value - PATH
 */
char* creat_str_path() {

	char* str_path = malloc(sizeof(char) *strlen("PATH=/bin:/usr/bin:/usr/local/bin\n"));
	strcpy(str_path, "PATH=/bin:/usr/bin:/usr/local/bin\n");
	return str_path;
}


/**
 *	@brief Function to change or add an environment variable
 *	@param char* name_value - syntex : "NAME=VALUE" ------------ verifier si const !!
 *	@return integer value - errno for setenv
 */
int add_env(char* name_value) {

	char* name;
	char* value;

	errno = 0;

	name = strtok(name_value, "=");
	value = strtok(NULL, "="); // ----------- faire en sorte de lire après le = et tout

	if (setenv(name, value, 1) < 0) //overwrite = 1
		perror("Erreur ");
	return errno;
}


/**
 *	@brief Function to read an environment variable
 *	@param char* name - ------------------------------------ verfier si const !!
 *	@return integer value - errno for setenv
 */
char* read_env(char* name) {

	remove_cr(name);
	remove_char(name, '$');

	// printf("read env : %s=%s",name, getenv(name));
	return getenv(name);
}


/**
 *	@brief Function to remove a char
 *	@param char* str - string to remove a char
 *	@param const char char_remove - char to remove
 *	@return -----------------------------------------------------------------------
 */
void remove_char(char* str, const char char_remove) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != char_remove) dst++;
    }
    *dst = '\0';
}



/**
 *	@brief Function to change directoy
 *	@param char* directory - string to change directory (example : /tmp)
 *	@return integer value - errno for chdir
 */
int cd(const char* directory)  {

	errno = 0;

	if (chdir (directory) < 0)
		perror("Erreur ");
	return errno;
}


/**
 *	@brief Function to return the current working directory
 *	@return string value - the current working directory
 */
char* pwd() {

	long size;
	char *buf;
	char *ptr;

	size = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)size)) != NULL)
		ptr = getcwd(buf, (size_t)size);

	return ptr;
}




/*


0xFio: TP1 $:B=40
0xFio: TP1 $:A=30 echo $B
40

Tu as vu mongole ... tu sais meme pas écrire mongole ... enfin je sais pas ...
tu dois exploser avec les éspace ensuite tu traite le premier et etc jusqu'à la fin des espaces !!

*/















/**
 * @brief Function to remove the carriage return value on a string
 * @param char* str - String value
 */
void remove_cr(char* str) {
	size_t last = strlen(str) - 1;
	if (str[last] == '\n') str[last] = '\0'; // To remove the '\n'
}




/**
 * @brief Function to explode a string (with delimiters) into a string array
 * @param const char* str - String value
 * @param const char* delim - delimiter character
 * @return string array
 */
char** strxpld(char* str, const char* delim) {
	int size = count_delim(str, delim) + 2; // + Last value + NULL value
	char** args = malloc(sizeof(char*) * size);
	char* token;
	int i = 0;

	while((token = strsep(&str, delim)) != NULL) {
		args[i] = malloc(sizeof(char) * sizeof(token));
		strcpy(args[i], token);
		i++;
	}

	args[size - 1] = NULL; // The last argument must be NULL

	return args;
}


/**
 * @brief Function to count how many delimiter is on a string
 * @param const char* str - String value
 * @param const char* c - delimiter character
 * @return integer value - Amount of occurence founded
 */
const int count_delim(const char* str, const char* c) {
	int counter = 0;
	size_t len = strlen(str);

	for(int i = 0; i < len; i++)
		if(str[i] == *c)
			counter++;

	return counter;
}












