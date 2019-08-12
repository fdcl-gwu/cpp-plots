import socket, time

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 9999))

while True:

    try:
        # bytes_sent = client.send('12345')
        # if bytes_sent > 0:
        #     print('Bytes sent: {}'.format(bytes_sent))
            
        bytes_received = client.recv(1024);
        if len(bytes_received) > 0:
            print(bytes_received)
        else:
            time.sleep(0.2)
        
        if bytes_received == 'exit':
            print('Received exit signal from the server ..')
            print('Exiting program ..')
            break
    
    except KeyboardInterrupt:
        print('Exiting program ..')
        break
    except:
        print('Server closed!')
        print('Exiting program ..')
        break

print('End of program.')
