#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
void _mkdir(const char* filename, bool v, bool p){
    int ret = mkdir(filename, 0777);
    if(ret && !p){
        perror("mkdir: cannot create directory");
        exit(EXIT_FAILURE);
    }
    if(v){
        printf("mkdir: created directory '%s' \n", filename);
    }

}
int main(int argc, const char *argv[]){
    if(argc==2){
        _mkdir(argv[1], false, false);
    }
    else if(argc==3){
        if(strcmp(argv[1], "-v")==0){
            _mkdir(argv[2], true, false);
        }
        else if(strcmp(argv[1], "-p")==0){
            _mkdir(argv[2], false, true);
        }   
    }
    return 0;
}
