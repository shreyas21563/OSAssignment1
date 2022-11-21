#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void _cat(const char* filename, bool n, bool E){
    FILE* pointer = fopen(filename, "r");
    char c;
    int count = 1;
    if(pointer==NULL){
        perror(filename);
        exit(EXIT_FAILURE);
    }
    if(n){
        printf("%d  ", count);
        count++;
    }
    while(true){
        c = fgetc(pointer);
        if(c==EOF){
            break;
        }
        if(c=='\n' && E){
            printf("$");
        }
        printf("%c", c);
        if(c=='\n' && n){
            printf("%d  ", count);
            count++;
        }
    } 
    
}
int main(int argc, const char *argv[]){
	if (argc == 2){
		_cat(argv[1], false, false);
	}else if(argc==3){
        if(strcmp(argv[1],"-n")==0){
            _cat(argv[2], true, false);
        }else if(strcmp(argv[1], "-E")==0){
            _cat(argv[2], false, true);
        }
    }                                                                                            
	return 0;
}
