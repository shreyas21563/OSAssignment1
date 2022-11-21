#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main(){
	char directory[1000];
	char str[1000];
	char s[1000];
	char *p_directory = calloc(1000, sizeof(char));
	pid_t pid;
	while(1){
		printf("%s >>> ", getcwd(s, sizeof(s)));
		scanf("%[^\n]%*c", directory);
		char *argv[1000];
		char * token = strtok(directory, " ");
		int count = 0;
   		while( token != NULL ) {
      		argv[count] = token;
      		token = strtok(NULL, " ");
			count++;
   		}
		if(strcmp(argv[0],"cd")==0){
			char *temp = calloc(1000, sizeof(char));
			getcwd(temp, 1000);
			bool nothing = true;
			if(count == 2){
				if(chdir(argv[1])!=0){
					nothing = false;
					perror(argv[1]);
				}
			}
			else if(count==3){
				if(strcmp("-m", argv[1])==0){
					if(chdir(argv[2])!=0){
						mkdir(argv[2], 0777);
						chdir(argv[2]);
					}
				}
				else if(strcmp("-v", argv[1])==0){
					if(chdir(argv[2])!=0){
						nothing = false;
						perror(argv[2]);
					}
					else{
						printf("\nDirectory changed to %s\n\n", getcwd(s, sizeof(s)));
					}
				}
				else{
					printf("No such Command Option\n");
				}
			}
			else{
				printf("Incorrect Command\n");
			}
			if(nothing){
				p_directory = temp;
			}
		}
		else if(strcmp(argv[0],"echo")==0){
			if(count==1){
				continue;
			}
			else if(strcmp(argv[1], "-n")==0){
				for(int i = 2; i<count; i++){
					printf("%s ", argv[i]);
				}
			}
			else if(strcmp(argv[1], "-b")==0){
				int *arr = calloc(128, sizeof(int));
				for(int j = 2; j<count; j++){
					for(int i = 0; i<strlen(argv[j]); i++){
						int a = argv[j][i];
						arr[a]++;
					}
				}
				for(int i = 0; i<128; i++){
					if(arr[i]!=0){
						printf("%c -> %d\n", i, arr[i]);
					}
				}
			}
			else{
				for(int i = 1; i<count; i++){
					printf("%s ", argv[i]);
				}
				printf("\n");
			}
		}
		else if(strcmp(argv[0], "pwd")==0){
			if(count==1){
				printf("%s\n", getcwd(s, 1000));
			}
			else if(count==2){
				if(strcmp(argv[1], "-t")==0){
					getcwd(s, sizeof(s));
					int integer = 3;
					printf("|->");
					for(int i = 1; i<strlen(s); i++){
						if(s[i]=='/'){
							printf("\n");
							for(int j = 0; j<integer; j++){
								printf(" ");
							}
							printf("|->");
							integer += 3;
						}
						else{
							printf("%c", s[i]);
						}
					}
					printf("\n");
				}
				else if(strcmp(argv[1], "-s")==0){
					printf("%s\n", p_directory);
				}
				else{
					printf("No such Command Option\n");
				}
			}
			else{
				printf("Incorrect Command\n");
			}
		}
		else if(strcmp(argv[0], "exit")==0){
			break;
		}
		else if(strcmp(argv[0], "ls")==0){
			pid = fork();
			if(pid==0){
				if(count==1){
					execl("ls", "ls", NULL);
					exit (1);
				}else if(count==2 && strcmp(argv[1], "-a")==0){
					execl("ls", "ls", "-a", NULL);
					exit(1);
				}else if(count==2 && strcmp(argv[1], "-A")==0){
					execl("ls", "ls", "-A", NULL);
					exit(1);
				}else if(count==2 && argv[1][0]=='-'){
					printf("Incorrect flag\n");
					exit(1);
				}
				else{
					printf("Incorrect Command\n");
					exit(1);
				}
			}else{
				wait(NULL);
			}
		}else if(strcmp(argv[0], "date")==0){
			pid = fork();
			if(pid==0){
				if(count==1){
					execl("date", "date", NULL);
				}
				else if(count==2){
					if(strcmp(argv[1], "-u")==0){
						execl("date", "date", "-u", NULL);
					}
					else if(argv[1][0]=='-'){
						printf("Incorrect flag\n");
					}
					else{
						printf("Incorrect Command\n");
					}
				}
				else if(count==3){
					if(strcmp(argv[1], "-r")==0){
						execl("date", "date", "-r", argv[2], NULL);
					}
					else if(argv[1][0]=='-'){
						printf("Incorret flag\n");
					}
					else{
						printf("Incorrect Command\n");
					}
				}
				else{
					printf("Incorrect Command\n");
				}
				exit(1);
			}else{
				wait(NULL);
			}
		}
		else if(strcmp(argv[0], "cat")==0){
			pid = fork();
			if(pid==0){
				if(count==2){
					execl("cat", "cat", argv[1], NULL);
				}else if(count==3){
					if(strcmp(argv[1], "-n")==0){
						execl("cat", "cat", "-n", argv[2], NULL);
					}else if(strcmp(argv[1], "-E")==0){
						execl("cat", "cat", "-E", argv[2], NULL);
					}
					else if(argv[1][0]=='-'){
						printf("Incorrect flag\n");
					}
					else{
						printf("Incorrect Command\n");
					}
				}
				else{
					printf("Incorrect Command\n");
				}
				exit(1);
			}else{
				wait(NULL);
			}
		}
		else if(strcmp(argv[0], "rm")==0){
			pid = fork();
			if(pid==0){
				if(count==2){
					execl("rm", "rm", argv[1], NULL);
				}
				else if(count==3){
					if(strcmp(argv[1], "-i")==0){
						execl("rm", "rm", "-i", argv[2], NULL);
					}
					else if(strcmp(argv[1], "-v")==0){
						execl("rm", "rm", "-v", argv[2], NULL);
					}
					else if(argv[1][0]=='-'){
						printf("Incorrect flag\n");
					}
					else{
						printf("Incorrect Command\n");
					}
				}
				else{
					printf("Incorrect Command\n");
				}
				exit(1);
			}else{
				wait(NULL);
			}
		}
		else if(strcmp(argv[0], "mkdir")==0){
			pid = fork();
			if(pid==0){
				if(count==2){
					execl("mkdir", "mkdir", argv[1], NULL);
				}
				else if(count==3){
					if(strcmp("-v", argv[1])==0){
						execl("mkdir", "mkdir", "-v", argv[2], NULL);
					}
					else if(strcmp("-p", argv[1])==0){
						execl("mkdir", "mkdir", "-p", argv[2], NULL);
					}
					else if(argv[1][0]=='-'){
						printf("Incorrect flag\n");
					}
					else{
						printf("Incorrect Command\n");
					}
				}
				else{
					printf("Incorrect Command\n");
				}
				exit(1);
			}else{
				wait(NULL);
			}
		}
		else{
			printf("Incorrect Command\n");
		}
	}
	return 0;
}
