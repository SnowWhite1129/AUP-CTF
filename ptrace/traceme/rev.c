#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

void errquit(const char *msg) {
	perror(msg);
	exit(-1);
}

int main(int argc, char *argv[]) {
	pid_t child;
	setbuf(stdout, NULL);
	if(argc < 2) {
		fprintf(stderr, "usage: %s program\n", argv[0]);
		return -1;
	}
	if((child = fork()) < 0) errquit("fork");
	if(child == 0) {
		if(ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) errquit("ptrace");
		execvp(argv[1], argv+1);
		errquit("execvp");
	} else {
		int status;
		if(waitpid(child, &status, 0) < 0) errquit("waitpid");
		ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_EXITKILL);

		struct user_regs_struct regs;
		unsigned long long rip;
		
		unsigned long long addr = 0x201b80;
		long long int data;
		unsigned long long answer[5];
		while (WIFSTOPPED(status)){
			if(ptrace(PTRACE_GETREGS, child, NULL, &regs)==0){
                                rip = regs.rip;
                                unsigned long long tmp = rip >> 40;
                                if(tmp != 0x7f){
					rip &= 0xFFFFFFFFF000;
					rip += addr;
					for(int i=0; i<5; ++i){
						answer[i] = ptrace(PTRACE_PEEKTEXT, child, rip + i*8, 0);
					}
				} 
                         }


			if(ptrace(PTRACE_SINGLESTEP, child, 0, 0) < 0){
				perror("ptrace");
			}
			if(waitpid(child, &status, 0) < 0) errquit("waitpid");
		}
		printf("Flag: ");
		char buf[1005] = "python3 rev.py";
		for(int i=0; i<5; ++i){
                        sprintf(buf, "%s %llx ", buf, answer[i]);
                }
		system(buf);
		perror("done")	;
	}
	return 0;
}


