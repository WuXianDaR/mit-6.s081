#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"
int compare(char * file1,char * file2){
	char *p;
	for(p = file1+strlen(file1);p >= file1&&*p != '/';--p){
			;
	}	
	++p;
	return strcmp(p,file2);
}
void find(char *path,char * fileName){
	char buf[512],*p;
	int fd;
	struct dirent de;
	struct stat st;	

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
 	switch(st.type){
		case T_FILE:
			if(compare(path,fileName) == 0){
				printf("%s\n",path);}
				break;	

		case T_DIR:
		if(strlen(path)+1+DIRSIZ + 1 > sizeof(buf)){
			printf("find:path too long\n")	;
			break;
		}
		strcpy(buf,path);
		p = buf+strlen(buf);
		*p++ = '/';
		while(read(fd,&de,sizeof(de)) == sizeof(de)){
			if(de.inum == 0)continue;
			memmove(p,de.name,DIRSIZ);
			if(strcmp(de.name,".") == 0|| strcmp(de.name,"..") == 0){
				continue;	
			}
			p[DIRSIZ] = 0;
			find(buf,fileName);	
		}

	} 
	close(fd);
}
int main(int argc,char * argv[]){
	if(argc < 3){
		switch(argc){
			case 0:
			case 1:fprintf(2,"lack arguments\n");exit(1);
			case 2:find(".",argv[0]);exit(0);
		}
	}	
	find(argv[1],argv[2]);
	exit(0);
}
