#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 7777

int main (int argc, char *argv[])

{

struct sockaddr_in server;

int s, ns;

int pktlen, buflen;

char buf1[256], buf2[256];

if (argc!=2)
{
  fprintf(stderr,"Usage:%s hostname\a\n",argv[0]);
  exit(1);
}

s=socket(AF_INET, SOCK_STREAM, 0);

server.sin_family = AF_INET;

server.sin_port = htons(PORT);

server.sin_addr.s_addr = inet_addr (argv[1]);

//connect��һ��������client��socket������,�ڶ���������server��socket��ַ,������Ϊ��ַ����

if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)

{

perror("connect()");

exit(1);

}

//��������I/O

for (;;) {

printf ("Enter a line: ");

gets (buf1);//��stdin���ж�ȡ�ַ�����ֱ�����ܵ����з�

buflen = strlen (buf1);

if (buflen == 0)

break;

send(s, buf1, buflen + 1, 0);

recv(s, buf2, sizeof (buf2), 0);

printf("Received line: %s\n", buf2);

}

close(s);

return 0;

}
