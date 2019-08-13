/* 
 * Copyright (c) 2019 Flight Dynamics and Control Lab
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
#include <unistd.h> //close
#include <arpa/inet.h> //close
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