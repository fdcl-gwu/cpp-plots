import global_variables as SYS

import socket, time
import threading

from receive_data import Client


print('MAIN: starting program ..')
thread_client = Client(1)

thread_client.run()

print('MAIN: end of program.')
