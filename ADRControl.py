import socket

clisock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )

clisock.connect( ('131.225.179.33', 2060) )

clisock.send('therm?,'.encode('UTF_8'))
print (clisock.recv(100).decode('ascii'))
print (clisock.recv(100))

clisock.close()
#setpt,x.xxx 
#COMMNADS TO CHANGE THE TEMPERATURE
#therm?, THIS ASK THE TEMPERATURE
#setpt,0.084 PUT THE VALUE AT 100MK FOR EXAMPLE.
#IF YOU WANT CHANGE THE TEMPERATURE CHANGE THE VALUE OF 0.084 LIKE OF THE TABLE.
