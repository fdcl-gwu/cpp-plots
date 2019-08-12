import socket, time

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 9999))

while True:

    try:
        bytes_sent = client.send('12345')
        if bytes_sent > 0:
            print('Bytes sent: {}'.format(bytes_sent))
            
        bytes_recev = client.recv(1024);
        if bytes_recev > 0:
            print('Bytes eceived: {}'.format(bytes_recev))
                
        time.sleep(0.2)
    
    except KeyboardInterrupt:
        print('Exiting program ..')
        break
    except:
        print('Server closed!')
        print('Exiting program ..')
        break

print('End of program.')
