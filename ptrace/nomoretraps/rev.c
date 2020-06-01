#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

void errquit(const char *msg) {
	perror(msg);
	exit(-1);
}

int
main(int argc, char *argv[]) {
	pid_t child;
	FILE *input = fopen("nomoretraps.txt", "r");
	char secret[6281 * 2];
	for(int i=0;fscanf(input, "%c%c", &secret[i], &secret[i+1])!=EOF;i+=2){
		
	}
	
	if(argc < 2) {
		fprintf(stderr, "usage: %s program [args ...]\n", argv[0]);
		return -1;
	}
	if((child = fork()) < 0) errquit("fork");
	if(child == 0) {
		if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) errquit("ptrace@child");
		execvp(argv[1], argv+1);
		errquit("execvp");
	} else {
		long long counter = 0LL;
		int wait_status;
		if(waitpid(child, &wait_status, 0) < 0) errquit("waitpid");
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_EXITKILL);
		ptrace(PTRACE_CONT, child, 0, 0);
                if(waitpid(child, &wait_status, 0) < 0) errquit("waitpid");
		while (WIFSTOPPED(wait_status)) {
			struct user_regs_struct regs;
			if(ptrace(PTRACE_GETREGS, child, 0, &regs)==0){
				long long rip = regs.rip - 1;
				long long value = ptrace(PTRACE_PEEKTEXT, child, rip, 0);

				value &= 0xFFFFFFFFFFFFFF00;

				char tmp[3];
                        	tmp[0] = secret[counter*2];
                	        tmp[1] = secret[counter*2+1];
        	                tmp[2] = '\0';

	                        long long hexvalue = strtol(tmp, NULL, 16);

                	        value |= hexvalue;
	
                        	ptrace(PTRACE_POKETEXT, child, rip, value);
                	        counter++;
        	                regs.rip = rip;
	                        ptrace(PTRACE_SETREGS, child, 0, &regs);
			}

			if(ptrace(PTRACE_CONT, child, 0, 0) < 0) errquit("ptrace@parent");
			if(waitpid(child, &wait_status, 0) < 0) errquit("waitpid");
		}
		fprintf(stderr, "## %lld instruction(s) executed\n", counter);
	}
	return 0;
}


