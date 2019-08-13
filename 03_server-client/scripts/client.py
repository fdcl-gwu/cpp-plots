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
