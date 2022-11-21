#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
void _date(const char* filename, bool u, bool r){
    time_t t = time(NULL);
	if(!u && !r){
        printf("%s", ctime(&t));
    }
	else if(u && !r){
		printf("%s", asctime(gmtime(&t)));
	}
	else if(!u && r){
		FILE *file;
		if(file = fopen(filename, "r")){
            fclose(file);
			struct stat info;
			stat(filename, &info);
			printf("%s", ctime(&info.st_mtime));
		}
		else{
			printf("File or Directory do not exists\n");
			exit(EXIT_FAILURE);
		}
	}
}
int main(int argc, const char *argv[]){
	if (argc == 1){
		_date(NULL, false, false);
	}
	else if(argc==2){
		if(strcmp(argv[1], "-u")==0){
			_date(NULL, true, false);
		}
	}
	else if(argc==3){
		if(strcmp(argv[1], "-r")==0){
			_date(argv[2], false, true);
		}
	}
	// else if (argc == 2){
	// 	if (argv[1][0] == '-'){
	// 		if(argv[1][1]=='a'){
	// 			_ls(".", true, false);
	// 		}else{
	// 			perror("Incorrect flag");
	// 			exit(EXIT_FAILURE);
	// 		}
	// 	}else{
	// 		perror("Incorrect Command"); 
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// else if(argc ==3){
	// 	if(argv[1][0]=='-' && argv[1][1]=='d' && argv[2][0]=='*' && argv[2][1]=='/'){
	// 		_ls(".", false, true);
	// 	}
	// }else{
	// 		perror("Incorrect Command"); 
	// 		exit(EXIT_FAILURE);
	// }
	return 0;
}
