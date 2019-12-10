#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 8000 
#define BUFSIZE 4096

int main(void)
{
	struct sockaddr_in saddr, caddr;
	int                len, fd1, fd2, ret,i,j;
	char               buf[BUFSIZE],filename[BUFSIZE],str[BUFSIZE],slen[100];
	FILE *fp;
	i=4;
	j=0;
	/* make server's socket */
	if ((fd1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		return -1;
	}


	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family      = AF_INET;
	saddr.sin_port        = htons(PORTNUM);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(fd1, (struct sockaddr*)&saddr, sizeof(saddr))) {
		perror("bind");
		return -1;
	}

	if(listen(fd1, 5)) {
		perror("listen");
		return -1;
	}

	if((fd2 = accept(fd1, (struct sockaddr*) &caddr, &len)) < 0) {
		perror("accept");
		exit(1);
	}
	while(1){
	if ((ret = recv(fd2, buf, BUFSIZE, 0)) > 0) {
		write(1,buf,ret);
		printf("\n");
	}else{
	  break;
	}
	//	printf("point %c\n",buf[0]);
	if(buf[0]=='G' && buf[1]=='E'&& buf[2]=='T' ){
	  while(buf[i]!='>'){
	    filename[i-4]=buf[i];
	    i++;
	  }
	  printf("%s\n",filename);
	  fp=fopen(filename,"r");
	if(fp == NULL){
	  printf("NOT FOUND\n");
	  return -1;
	}
	while((str[j]= fgetc(fp))!=EOF){
	  j++;
	}
	sprintf(slen,"FILE(%d):",strlen(str));
	strcat(slen,str);
	//printf("%s\n",slen);
	}//ifget
	send(fd2,slen,strlen(slen),0);

	}//while
	close(fd2);
	
	close(fd1);
	
	return 0;
}
