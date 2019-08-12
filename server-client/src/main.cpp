#include "plotting_server.h"

int main(void)
{
    fdcl::plot::server server;
    char buffer[MAXBUF];
    int num_bytes = 5;

    int bytes_received = 0, bytes_sent = 0;

    server.init();
    while (true)
    {
        bytes_received = server.receive(buffer, num_bytes);
        if (bytes_received > 0) printf("Received: %i\t", bytes_received);

        bytes_sent = server.send(buffer, num_bytes);
        if(bytes_sent > 0) printf("Sent: %i\n", bytes_sent);
    }

    return 0;
}