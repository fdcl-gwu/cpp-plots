#include "plotting_server.h"


fdcl::plot::server::server(void)
{
    is_closed = false;
}


fdcl::plot::server::~server(void)
{
    if (!is_closed) close();
    is_closed = true;
}


void fdcl::plot::server::close(void)
{
    if (!is_closed) ::close(sockfd);
    is_closed = true;
    printf("PLOT: server closed!\n");
}


void fdcl::plot::server::init(void)
{
    printf("PLOT: opening socket...\n");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) printf("PLOT: ERROR: opening socket...\n");

    // reuse a port number
    int on = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        printf("PLOT: setsockopt(SO_REUSEADDR) failed\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if ( ::bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("PLOT: binding failed\n");
    }
    listen(sockfd, 5);

    unsigned int serv_len = sizeof(serv_addr);
    sockfd = ::accept(sockfd, (struct sockaddr *) &serv_addr, &serv_len);
    if (sockfd < 0) printf("PLOT: accepting failed\n");

    printf("PLOT: accepting...\n");
}


int fdcl::plot::server::receive(char (&buffer)[MAXBUF], int len)
{
    bytes_received = ::recv(sockfd, buffer, len, MSG_WAITALL);
    return bytes_received;
}


int fdcl::plot::server::send(char (&buffer)[MAXBUF], int len)
{
	bytes_sent = ::send(sockfd, buffer, len, MSG_NOSIGNAL);
    return bytes_sent;
}


int fdcl::plot::server::send_non_blocking(char (&buffer)[MAXBUF], int len)
{
    bytes_sent = ::send(sockfd, buffer, len, MSG_DONTWAIT);
    return bytes_sent;
}