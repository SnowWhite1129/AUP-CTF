#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern char buf[8192];
void envvar(int id){
	if(id){
                write(1, "checkenv", 8);
                char tmp[1024];
                read(0, tmp, 1024);
                return;
        }

	char secret[1024]="SECRET=";
	strcat(secret, buf);
	
	char process[1024];
	FILE* file = fopen("/proc/self/cmdline", "r");
	fgets(process, 1024, file);	
		
	char *args[] = {process, NULL};
	char *env[] = {"SHORTCUT=YES", secret, NULL};

	execve(args[0], args, env);
}
//EOF
