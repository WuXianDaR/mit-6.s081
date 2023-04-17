#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void prime(int *lo_p){
	int n;
	int hi_p[2];
	if(read(lo_p[0],&n,4) == 0){
		exit(0);	
	}
	else{
		printf("prime %d\n",n);	
	}
	
	pipe(hi_p);
	if(fork() == 0){
		close(hi_p[1])	;
		prime(hi_p);
		close(hi_p[0]);	
	}
	else{
		close(hi_p[0]);
		int num;
		while(read(lo_p[0],&num,4)){
			if(num % n != 0){
				write(hi_p[1],&num,4);	
			}		
		}
			close(hi_p[1]);
			wait(0);
			exit(0);	
	}
}
int main(){
	int p[2];
	pipe(p);
	if(fork() == 0){
		close(p[1]);
		prime(p);
		exit(0);	
	}
	else{
		close(p[0]);
		int i;
		for(i = 2;i <= 35;++i){
			write(p[1],&i,sizeof(i));
		}	
		close(p[1]);
		wait(0);
	exit(0);
	}
}
