import global_variables as SYS

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

                bytes_received = self.client.recv(1024)
                if len(bytes_received) > 0:
                    print(bytes_received)
                else:
                    time.sleep(0.2)

                if bytes_received == 'exit':
                    SYS.on = False
                    print('CLIENT: received exit signal from the server ..')
                    print('CLIENT: exiting program ..')
                    break

            except KeyboardInterrupt:
                SYS.on = False
                print('Exiting program ..')
                break
            except:
                SYS.on = False
                print('CLIENT: server closed unexpectedly!')
                print('CLIENT: exiting program ..')
                break

        print('CLIENT: End of program.')
