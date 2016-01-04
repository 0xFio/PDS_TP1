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

	read_profile_file();


	printf("Hello world\n");



	while(true) { // true
		fgets(input, BUFFER_SIZE, stdin); // Read the input command

		//printf("%d : \n",strlen(input));


			if (strrchr(input,'=') != NULL) {

				add_env(input);

			}
			else if (strrchr(input,'$') != NULL) {


				printf("resultat de read_env : %s", read_env(input));

			}

	}

	return EXIT_SUCCESS;

}
