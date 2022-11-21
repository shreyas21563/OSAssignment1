#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdbool.h>
#include<string.h>

void _rm(const char* filename, bool i, bool v){
    if(i){
        FILE *file;
        if(file = fopen(filename, "r")){
            fclose(file);
            printf("rm: Do you want to remove '%s' ? ", filename);
            char c;
            scanf("%c", &c);
            if(c!='y'){
                return;
            }
        }
        else{
            perror("rm: file do not exists");
            exit(EXIT_FAILURE);
        }
    }
	int ret = remove(filename);
    if(ret){
        perror("rm: cannot remove ");
        exit(EXIT_FAILURE);
    }
    if(v){
        printf("removed '%s' \n", filename);
    }
}
int main(int argc, const char *argv[]){
	if(argc==2){
        _rm(argv[1], false, false);
    }
    else if(argc==3){
        if(strcmp(argv[1], "-i")==0){
            _rm(argv[2], true, false);
        }
        else if(strcmp(argv[1], "-v")==0){
            _rm(argv[2], false, true);
        }
    }
	return 0;
}
