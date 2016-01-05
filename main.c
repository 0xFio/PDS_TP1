/* ------------------------------------------
 * Project: Unix interpreter
 * Authors: Rejas C. & Poroli F.
 * Version: 1.0, 2016-01-04
 * ------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "sheel.h"



#define BUFFER_SIZE 1000



int main(int argc, char** argv) {

	char* input = malloc(sizeof(char) * BUFFER_SIZE);

	char** args = malloc(sizeof(char*) * 100);

	read_profile_file();


	printf("Hello world\n");


	while(true) { //true


		fgets(input, BUFFER_SIZE, stdin); // Read the input command
		remove_cr(input);

		if (strchr(input,'=') != NULL) {

			add_env(input);
		}
		else if (strncmp(input, "$", 1) == 0) {

			printf("  %s \n", read_env(input));
		}
		else if (strcmp(input, "pwd") == 0) {

			printf("  pwd = %s \n", pwd());
		}
		else if (strncmp(input, "cd", 2) == 0) {

			args = strxpld(input, " ");
			cd(args[1]);
		}
		else if (strncmp(input, "alias", 5) == 0) {

		}
		else if (strcmp(input, "exit") == 0) {

			break;
		}
	}

	return EXIT_SUCCESS;

}
