#include <stdio.h>
#include <stdlib.h>
void unbuffered(){
	setbuf(stdout, NULL);
}
void showflag(){
	char FLAG[1024];
	FILE *input = fopen("FLAG", "r");
	fgets(FLAG, 1024, input);
	printf("%s\n", FLAG);
}
