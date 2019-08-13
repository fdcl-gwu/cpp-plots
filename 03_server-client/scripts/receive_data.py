'''
MIT License

Copyright (c) 2019 Flight Dynamics and Control Lab

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
'''


import global_variables as SYS

import numpy as np
import socket
import threading
import time


class Client(threading.Thread):
    def __init__(self, thread_id):
        threading.Thread.__init__(self)
        self.thread_id = thread_id
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def run(self):
        print('CLIENT: opening client ..')
        self.client.connect(('localhost', 9999))

        while SYS.on:
            try:
                # bytes_sent = client.send('12345')
                # if bytes_sent > 0:
                #     print('Bytes sent: {}'.format(bytes_sent))

                data_received = self.client.recv(1024)
                if len(data_received) > 0:
                    # print(data_received)

                    SYS.threadlock.acquire()
                    self.parse_received_data(data_received)
                    SYS.threadlock.release()
                else:
                    time.sleep(0.2)

                if data_received == 'exit':
                    SYS.on = False
                    print('CLIENT: received exit signal from the server ..')
                    print('CLIENT: exiting program ..')
                    break
            except:
                SYS.on = False
                print('CLIENT: server closed unexpectedly!')
                print('CLIENT: exiting program ..')
                break

            print('CLIENT: end of program.')
        
    def parse_received_data(self, data_received):

        try:
            split_line = data_received.split(',')
            SYS.data_from_server = np.array(
                [float(split_line[0]),  \
                float(split_line[1]),  \
                float(split_line[2])])
        except:
            pass
