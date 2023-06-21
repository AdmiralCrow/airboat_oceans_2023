#TERMINAL COMMAND
#nc -p 31336 -w 5 192.168.0.50 8001

import socket, sys, time

HOST = '192.168.0.50'
PORT = 8001

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

msg = '$PSEAG'
msg= "$PSEAC,L,0,0,0,*14\n"
#msg= '$PSEAC,R,,,,*3A\n'
#s.send(msg.encode())

data = s.recv(1024)
s.close()
print('Received:' , data)


#EXAMPLE MSG RECIEVED FROM TERMINAL COMMAND
#$GPGGA,,,,,,0,,,,M,,M,,*66
#$VCGLL,,,,,,V*04
#$PSEAA,-2.2,0.7,222.6,,47.8,-0.04,-0.01,-1.00,-0.01*7A
#$PSEAB,28.2,49742,0.8,23.9,7858,,,28.3,,0.8,0.0,0.0,,,6*76
#$PSEAD,L,0.0,0.0,0.0,LIDAR_OFF,,1,1*63
#$PSEAE,0.53,11.9,0.76,11.9,,0,0,0,0,0,1,0,1,0,0,1,00000000,0,0,0,,,*68
#$PSEAF,T,2*27
#$PSEAG,M*21
#$PSEAJ,1,0,,,,,,*4C
#$PTQM0,2041,00,00,,00,0.0,,,0,,0.0,,0.0,0.0,,,,0,0*33
#$PTQM1,2041,00,00,,00,0.0,,,0,,0.0,,0.0,0.0,,,,0,0*32
#$DEBUG,,,,,,,,,,,,,,,,,*7D
