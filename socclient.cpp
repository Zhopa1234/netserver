#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
     
#define TRUE   1 
#define FALSE  0 
#define PORT 54321 
#define HORN_ON		1
#define HORN_OFF	2
#define HORN_AZIMUTH	3
#define HORN_ZERO	4


struct 
{
short message_number  ;
char azimuth[96];
char extra_data[12] ;   //for future use
}horn_msg_req;

struct 
{
short message_number;
short reply_code;
}horn_msg_reply;



int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    char sndBuff[1024];
    struct sockaddr_in serv_addr; 
    
    short msg_type;



    if(argc < 2 )
    {
        printf("\n Usage: %s <ip of server> <message number> <azimuth> optional\n",argv[0] );
        return 1;
    } 

    memset(&horn_msg_reply, 0,sizeof(horn_msg_reply));
    memset(&horn_msg_req, 0,sizeof(horn_msg_req)); 
    

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 
     

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 

    //if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    if(inet_pton(AF_INET, /*"192.168.1.4"*/ argv[1],  &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    msg_type =   (int)*argv[2] - (int)('0');
    if (( (int)*argv[2] - (int)('0') ) == HORN_AZIMUTH )
	{
    	strcpy ( horn_msg_req.azimuth, argv[3]);
    	
	}
    horn_msg_req.message_number  = (int)*argv[2] - (int)('0')  ;
     
    n = write (sockfd , &horn_msg_req , sizeof (horn_msg_req ));
    printf ( "wrote bytes sent n=%d %d\n", n,sizeof (horn_msg_req ) );
    memset (&horn_msg_reply , 0 , sizeof(horn_msg_reply));
    memset ( recvBuff, 0 , sizeof ( recvBuff ) );	
    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff))) > 0)
    {
	printf ( "received %d bytes \n", n );
        memcpy ( &horn_msg_reply , recvBuff , sizeof ( horn_msg_reply ) );
        printf ( "horn_msg_reply.message_number %d , horn_msg_reply.reply_code=%d\n", 
	horn_msg_reply.message_number, horn_msg_reply.reply_code );

        printf ( "\ndsconnecting \n");
		close ( sockfd );
		return 0;
#if 0
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
#endif
    } 
    if ( n == 0)
	{
		printf ( "\ndsconnecting \n");
		close ( sockfd );
		return 0;
	}

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}