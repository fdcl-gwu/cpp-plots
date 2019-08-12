#ifndef PLOTTING_SERVER_H
#define PLOTTING_SERVER_H

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define MSG_NOSIGNAL 0x0
#define MAXBUF 1024

namespace fdcl 
{

namespace plot 
{
    
class server
{
public:
    server(void);
    ~server(void);

    void init(void);
    void close(void);
    int receive(char (&buffer)[MAXBUF], int len);
    int send(char (&buffer)[MAXBUF], int len);
    int send_non_blocking(char (&buffer)[MAXBUF], int len);

private:
    struct sockaddr_in serv_addr;
    int port = 9999;
    int sockfd;
    int bytes_received;
    int bytes_sent;
    bool is_closed = false;


};  // end of class server
}  // end of namesapce plot
}  // end of namespace fdcl


#endif