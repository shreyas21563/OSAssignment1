#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdbool.h>
#include<string.h>

int isDir(const char* fileName){
    struct stat info;
    stat(fileName, &info);
    return S_ISREG(info.st_mode);
}

void _ls(const char *directory, bool a, bool A){
	DIR *dir = opendir(directory);
	struct dirent *token;
	while ((token = readdir(dir))){
		if(token==NULL){
			break;
		}else if (token->d_name[0] == '.' && !a){
			continue;
		}
		else if(A && (strcmp(token->d_name, ".")==0 || strcmp(token->d_name, "..")==0)){
			continue;
		}
		printf("%s  ", token->d_name);
	}
	printf("\n");
}
int main(int argc, const char *argv[]){
	if (argc == 1){
		_ls(".", false, false);
	}
	else if (argc == 2){
		if (argv[1][0] == '-'){
			if(argv[1][1]=='a'){
				_ls(".", true, false);
			}
			else if(argv[1][1]=='A'){
				_ls(".", false, true);
			}
			else{
				printf("Incorrect flag\n");
			}
		}
	}
	return 0;
}
