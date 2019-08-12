import threading

global on
global threadlock
global log_on

threadlock = threading.Lock()
on = True
log_count = 0
