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
                    # print(bytes_received)

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
                # a = 1
                SYS.on = False
                print('CLIENT: server closed unexpectedly!')
                print('CLIENT: exiting program ..')
                break

            # print('CLIENT: end of program.')
        
    def parse_received_data(self, data_received):

        try:
            split_line = data_received.split(',')
            SYS.data_from_server = np.array(
                [float(split_line[0]),  \
                float(split_line[1]),  \
                float(split_line[2])])
        except:
            pass
