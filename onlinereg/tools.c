#include <stdio.h>
#include <stdlib.h>
void unbuffered(){
	return;
}
void showflag(){
	char FLAG[1024];
	FILE *input = fopen("FLAG", "r");
	fgets(FLAG, 1024, input);
	printf("%s\n", FLAG);
}
