import threading
import numpy as np

global on
global threadlock
global log_on
global data_from_server

threadlock = threading.Lock()
on = True
log_count = 0
data_from_server = np.array([0.0, 0.0, 0.0])