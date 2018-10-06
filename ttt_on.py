import bluetooth
import time
import sys
import urllib2
from datetime import datetime

def is_ascii(s):
	return all(ord(c)<128 for c in s)

bd_addr = "98:D3:32:20:A9:A4"  # here need to modify. use hciconfig to get address
port = 1

sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))
print ('Connected')
#sock.settimeout(1.0)	
temp=''
print ('1. On')
print ('0. Off')
print ('3. Time')
while 1:
	tosend = raw_input()
	if tosend != '3':
		
		sock.send(tosend)
	else:
		print('open relay for how much sec?	')
		sock.send('1')
		t = raw_input()
		time.sleep( float(t) )
		sock.send('0')
	#################################
	
	while(1):
		data = sock.recv(1)
		if is_ascii(data):
			
			print(data)
			temp=''	
			break
	
	


