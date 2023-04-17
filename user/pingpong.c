#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc,char* argv[])
{
	int p[2];
	char mess;
	pipe(p);
	if(fork() == 0){
		read(p[0],&mess,1);
		close(p[0]);
		printf("%d: received pong\n",getpid());
		write(p[1]," ",1);
		close(p[1]);
	}
	else{
		write(p[1]," ",1);
		close(p[1]);
		wait(0);
		read(p[0],&mess,1);
		printf("%d: received ping\n",getpid());
		close(p[0]);
			
	}
	exit(0);
}

