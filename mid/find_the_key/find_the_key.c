#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void orw(char flag[]){
	char buf[1024]={0};
	int fd = open(flag, O_RDONLY);
	read(fd, buf, 1024);
	write(1, buf, 1024);
}
void find(char path[]){
	DIR *dirp = opendir(path);
        struct dirent *dir;
	while( (dir = readdir(dirp)) != NULL){
		char cur[1024];
	        strcpy(cur, path);
	        strcat(cur, "/");
                strcat(cur, dir->d_name);		
		
		if (dir->d_type == DT_DIR){
			if ((strcmp(dir->d_name, ".")==0) || (strcmp(dir->d_name, "..")==0) ){
	                        continue;
        	        } else{
				find(cur);
			}
		} else{
			if(strcmp(dir->d_name, "FLAG")==0){
				orw(cur);
				return;
			}
		}
	}
	closedir(dirp);
}
void find_the_key(){
//	find("/usr/share/tree");
	find("/home/misp/AUP-CTF/find_the_key");
}
//EOF
