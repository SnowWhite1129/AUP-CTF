#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
void orw(){
	char localflag[]="/home/misp/AUP-CTF/orw/FLAG";
	char flag[]="/home/orw/FLAG";
	char buf[1024]={0};
	int fd = open(localflag, O_RDONLY);
	read(fd, buf, 1024);
	write(1, buf, 1024);
}
//EOF
