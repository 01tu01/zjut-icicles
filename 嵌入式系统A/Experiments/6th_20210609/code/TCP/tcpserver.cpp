
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>

#include <netinet/in.h>

#include <errno.h>

#define PORT 7777

main ()

{

struct sockaddr_in client, server;// �ͻ��˵�ַ��Ϣ ������ַ��Ϣ
socklen_t namelen;
int s, ns,  pktlen;//s������socket ns�����ݴ���socket namelen:client�ĵ�ַ���� pktlen:�������ݵ��ֽ���

char buf[400];

char buf3[200];

s=socket(AF_INET, SOCK_STREAM, 0); //�������ӵ�SOCKET,sΪsocket������

// ��ʼ����������ַ

memset ((char *)&server, sizeof(server), 0); //���ѿ����ڴ�ռ� server ��ȫ���ֽڵ�ֵ��Ϊֵ0.������bzero

server.sin_family = AF_INET;

server.sin_port = htons(PORT);//�˿ں�

server.sin_addr.s_addr = INADDR_ANY;//���������ַ,INADDR_ANY��ʾ������IP��ַ

//server��Ҫ��listen֮ǰ��һ����Ҷ�֪���ĵ�ַ,���Ǹոճ�ʼ���õ�ip+�˿ں� 
bind(s, (struct sockaddr *)&server, sizeof(server));

listen(s,1);//�����ͻ�������,iΪsocket�����Ŷ����ӵ�������

/*����client����,sΪserver��������(������socket������),�ڶ���������ָ��client��Э���ַ,���������������ַ����

����ֵns��һ��ȫ�µ�������,�����ݴ���socket,�����뷵�ؿͻ���tcp����*/

namelen = sizeof (client);

ns = accept (s, (struct sockaddr *)&client, &namelen);

//��ʼ��������I/O

for (;;) {

/*recv����client���͵�����,recv����������copy���ݣ������Ľ���������Э������ɵģ��� ��һ������ָ�����ն��׽������������ڶ�������ָ��һ�����������û������������recv�������յ������ݣ�����������ָ��buf�ĳ���

recv����������ʵ��copy���ֽ���*/

pktlen = recv (ns, buf, sizeof (buf), 0);

if (pktlen == 0)

break;

printf ("Received line: %s\n", buf);

printf ("Enter a line: ");

gets(buf3);

/*������send��ns�ķ��ͻ����е����ݴ������ӵ���һ�˵ģ�����Э�鴫�ģ�send�����ǰ�buf�е�����copy��ns�ķ��ͻ�������ʣ��ռ���

����ʵ��copy���ֽ���*/

send (ns, buf3,sizeof(buf3), 0);

}

close(ns);

close(s);

}
