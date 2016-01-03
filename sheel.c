#include <stdio.h> 
#include <stdlib.h>      
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include <fcntl.h>

#define BUFFER_SIZE 1000


void write_HOME (int fd_profile, char *str_home) {

	const char HOME[] ="HOME=";
	str_home = strcat(str_home,"\n");

	if (write(fd_profile, HOME, strlen(HOME)) != strlen(HOME)) {
		printf("erreur : écriture du HOME dans profile\n");
    }

	if (write(fd_profile, str_home, strlen(str_home)) != strlen(str_home)) {
		printf("erreur : écriture du HOME dans profile\n");
    }


}


void write_PATH (int fd_profile) {

	const char str_path[] = "PATH=/bin:/usr/bin:/usr/local/bin\n";

	if (write(fd_profile, str_path, strlen(str_path)) != strlen(str_path)) {
		printf("erreur : écriture du PATH dans profile\n");
    }

}




void read_profile_file () {

	bool creat_HOME = true;
	bool creat_PATH = true;

	char str[128];



	char *token;

	//char *str_home;

	struct passwd *p = getpwuid(getuid());

	char str_home[strlen(p->pw_dir)];

	strcpy(str_home,p->pw_dir);


	int fd_profile = open(strcat(p->pw_dir,"/profile"), O_RDWR | O_CREAT, S_IRWXU);

	if (fd_profile < 0) {
		printf("erreur sur l'ouverture du fichier profile");
    }

	read(fd_profile, str, 127);

	token = strtok(str,"\n");
	if (token == NULL) {

		printf("creer les deux machin ... ");
	}
	else {

		while (token != NULL) {

			if (strstr(token,"PATH") != NULL) {
				creat_PATH = false;
			}
			else if (strstr(token,"HOME") != NULL) {
				creat_HOME = false;
			}

			printf("  %s\n", token );
			token = strtok(NULL, "\n");
		}

	}

	if (creat_HOME == true) 
		write_HOME(fd_profile, str_home);

	if (creat_PATH == true) 
		write_PATH (fd_profile);
	


}






void main()
{
	int test = 0;

	char* input = malloc(sizeof(char) * BUFFER_SIZE);

	//char *putenv

	read_profile_file();


	printf("Hello world\n");

	while(true) {
		fgets(input, BUFFER_SIZE, stdin); // Read the input command

		printf("%d : \n",strlen(input));


			if (strrchr(input,'=') != NULL) {

				printf("le fatal test :%d et  %s",strlen(input),input);
				printf("le fatal2 test2 :%d et  %s",strlen("A=10"),"A=10");

				if (putenv("A=50") == 0)
					printf("succes put env\n");
				
			//	if (putenv(input) == 0)
				//	printf("succes put env\n");

			}
			else if (strrchr(input,'$') != NULL) {


			//	printf("le testtt : %s", strtok(input,"$"));
			//	printf("get env : %s \n", getenv(strtok(input,"$"))); // sa ne marche pas !
				printf("get env : %s \n", getenv("A")); // sa ne marche pas !
			}
		
	

	}


	



}
