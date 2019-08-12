import global_variables as SYS

import matplotlib.pyplot as plt
import socket, time
import threading

from receive_data import Client
from plot_funcs import plot_data

plt.style.use('seaborn')
SYS.on = True

print('MAIN: starting program ..')

thread_client = Client(1)
thread_client.start()

fig = plt.figure(figsize=plt.figaspect(0.5))
ax_1 = fig.add_subplot(1, 2, 1)
ax_2 = fig.add_subplot(1, 2, 2)

while SYS.on:
    try:
        time.sleep(0.001)

        SYS.threadlock.acquire()
        x = SYS.data_from_server
        SYS.threadlock.release()

        plot_data(ax_1, ax_2, x)
        plt.draw()
        plt.pause(0.001)

    except KeyboardInterrupt:
        SYS.on = False
        print('MAIN: exiting program ..')
        break

print('MAIN: end of program.')
