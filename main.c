/* ------------------------------------------
 * Project: Unix interpreter
 * Authors: Rejas C. & Poroli F.
 * Version: 1.0 provisoire, 2016-01-17
 * ------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

#define BUFFER_SIZE 1000

int main(int argc, char** argv) {

	char* input = malloc(sizeof(char) * BUFFER_SIZE);

	char** args = malloc(sizeof(char*) * 100);

	struct alias all_alias[MAX_ALIAS];
	nbr_alias = 0;

	read_profile_file();

	while(true) { //true

		fgets(input, BUFFER_SIZE, stdin); // Read the input command
		remove_cr(input);

		if (strncmp(input, "alias ", 6) == 0) {

			args = strxpld(input, " ");

			if (strcmp(args[1], "-p") == 0) {
				view_all_alias(all_alias);
			}
			else if (strchr(args[1], '=') != NULL)
				add_alias(all_alias, args[1]);
			else
				view_alias(all_alias, args[1]);
		}		
		else if (strncmp(input, "$", 1) == 0) {

			printf("  %s \n", read_env(input));
		}
		else if (strchr(input,'=') != NULL) {

			add_env(input);
		}
		else if (strcmp(input, "pwd") == 0) {

			printf("  pwd = %s \n", pwd());
		}
		else if (strncmp(input, "cd", 2) == 0) {
			args = strxpld(input, " ");
			cd(args[1]);
		}
		else if (strcmp(input, "exit") == 0) {

			break;
		}
	}

	return EXIT_SUCCESS;

}
