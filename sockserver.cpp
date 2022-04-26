//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux 
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 


     
#define TRUE   1 
#define FALSE  0 
#define PORT 54321 

#define HORN_ON		1
#define HORN_OFF	2
#define HORN_AZIMUTH	3
#define HORN_ZERO	4


struct horn_message_request
{
short message_number  ;
char azimuth[96];
char extra_data[12] ;   //for future use
}horn_msg_req ;


struct horm_message_reply
{
short message_number;
short reply_code;
}horn_msg_reply;



int Process_python_script ( horn_message_request *psReq )
{
	
char run_string[1024];
int res;
	
	switch ( psReq->message_number)
	{
	case HORN_ON:
	strcpy ( run_string , "python " );
	strcat ( run_string , "/home/pi/netserver/gpiopin.py ");
	strcat (run_string  , "6 " );
	strcat (run_string  , "1 " );
	strcat (run_string  , "1" );
	res = system ( run_string );
	printf ( "system res = %d \r\n", res );
	break;
	case HORN_OFF:
	strcpy ( run_string , "python " );
	strcat ( run_string , "/home/pi/netserver/gpiopin.py ");
	strcat (run_string  , "6 " );
	strcat (run_string  , "0 " );
	strcat (run_string  , "0" );
	res = system ( run_string );
	printf ( "system res = %d \r\n", res );
	break;
	case HORN_AZIMUTH:
        //1/65536 * 360 * 60 * 60
	//19.8 arcseconds per unit // arcsec is 1/60 of degree
	strcpy ( run_string , "python " );
	strcat ( run_string , "/home/pi/netserver/azimuth.py ");
	strcat (run_string  , psReq->azimuth );
	strcat (run_string  , "0 " );
	strcat (run_string  , "0" );
	res = system ( run_string );
	printf ( "system res = %d \r\n", res );
	break;
	case HORN_ZERO:
	strcpy ( run_string , "python " );
	strcat ( run_string , "/home/pi/netserver/zeroazimuth.py ");
	strcat (run_string  , "6 " );
	strcat (run_string  , "0 " );
	strcat (run_string  , "0" );
	res = system ( run_string );
	printf ( "system res = %d \r\n", res );
	break;
	
	break;
	default:
	res = -1;
	break;
	}
	return res;


}
     
int main(int argc , char *argv[])  
{  
    int opt = TRUE;  
    int master_socket , addrlen , new_socket , client_socket[30] , 
     max_clients = 1 , activity, i , valread , sd;  
    int max_sd;  
    struct sockaddr_in address;  
    int res;    
    char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
    fd_set readfds;  
         
        
    //initialise all client_socket[] to 0 so not checked 
    memset ( client_socket , 0 , sizeof ( client_socket )); 
    memset(&horn_msg_reply, 0,sizeof(horn_msg_reply));
    memset(&horn_msg_req, 0,sizeof(horn_msg_req)); 
    
         
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
         
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n",
                  new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
           
            
                 
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
	           printf ( "read %d bytes\n", valread );
                   memcpy ( &horn_msg_req, buffer , sizeof ( horn_msg_req ));
		   res = Process_python_script (&horn_msg_req);
                    
		   horn_msg_reply.message_number = horn_msg_req.message_number ;
		   horn_msg_reply.reply_code = res;
		   memcpy ( buffer, &horn_msg_reply, sizeof ( horn_msg_reply) );
                    
                   valread = send(sd , buffer , sizeof ( horn_msg_reply) , 0 );  
                   printf ( "sent %d bytes  %d \n", valread  , sizeof( horn_msg_reply) );
                   
                }  
            }  
        }  
    }  
         
    return 0;  
} 
