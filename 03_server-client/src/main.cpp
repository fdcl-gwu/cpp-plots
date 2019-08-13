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

#include "plotting_server.h"

#include <pthread.h>
#include <iostream>
#include <util.h>

#define NUM_THREADS 3


int getch(void);
void *thread_plot_server(void *thread_id);
void *thread_update_data(void *thread_id);
void *thread_key(void *thread_id);
void string_to_char_buffer(char (&buffer)[MAXBUF], int &num_bytes, \
    std::string &data_string);


bool system_on = true;
pthread_mutex_t data_mutex;
std::string data_to_send = "hello client";

int main(void)
{
    printf("SERVER: starting program ..\n");

    // Define pthread variables.
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    struct sched_param param;
    int fifo_max_prio, fifo_min_prio;

    // Initialize mutex and condition variables.
    pthread_mutex_init(&data_mutex, NULL);

    // Set thread attributes.
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    fifo_max_prio = sched_get_priority_max(SCHED_FIFO);
    fifo_min_prio = sched_get_priority_min(SCHED_FIFO);

    param.sched_priority = fifo_max_prio / NUM_THREADS;
    pthread_attr_setschedparam(&attr, &param);


    printf("SERVER: creating threads ..\n");
    pthread_create(&threads[0], &attr, thread_plot_server, 0);
    pthread_create(&threads[1], &attr, thread_update_data, 0);
    pthread_create(&threads[2], &attr, thread_key, 0);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("SERVER: program closed!\n");
    return 0;
}


void *thread_plot_server(void *thread_id)
{
    printf("PLOT: thread starting ..\n");

    fdcl::plot::server server;
    char buffer[MAXBUF];
    int num_bytes;

    // int bytes_received = 0;
    int bytes_sent = 0;

    server.init();
    while (system_on)
    {
        // bytes_received = server.receive(buffer, num_bytes);
        // if (bytes_received > 0) printf("Received: %i\t", bytes_received);
        // if (!system_on) break;

        pthread_mutex_lock(&data_mutex);
        string_to_char_buffer(buffer, num_bytes, data_to_send);
        pthread_mutex_unlock(&data_mutex);

        bytes_sent = server.send(buffer, num_bytes);
        // if(bytes_sent > 0) printf("Sent: %i\n", bytes_sent);

        usleep(100000); // 10 Hz
    }

    printf("PLOT: sending exit signal to client ..\n");
    usleep(1000000); // 1 second

    std::string exit_string = "exit";
    string_to_char_buffer(buffer, num_bytes, exit_string);
    bytes_sent = server.send_non_blocking(buffer, num_bytes);

    server.close();

    printf("PLOT: thread closed!\n");
    pthread_exit(NULL);
}


void string_to_char_buffer(char (&buffer)[MAXBUF], int &num_bytes, \
    std::string &data_string)
{
    num_bytes = data_string.length();
    strncpy(buffer, data_string.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = 0;
}


void *thread_update_data(void *thread_id)
{
    printf("DATA: thread starting ..\n");

    int i = 0;
    while(system_on)
    {
        i++;
        pthread_mutex_lock(&data_mutex);
        data_to_send = "12,23," + std::to_string(i);
        pthread_mutex_unlock(&data_mutex);

        usleep(200000); // 50 Hz
    }

    printf("DATA: thread closed!\n");
    pthread_exit(NULL);
}


void *thread_key(void *thread_id)
{
    printf("KEY: thread initialized ..\n");

    char c;
    while (system_on)
    {
        c = getch();
        if (c == 'q') system_on = false;
        usleep(100000); // 10 Hz
    }

    printf("KEY: thread closed!\n");
    pthread_exit(NULL);
}


int getch(void)
{
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}