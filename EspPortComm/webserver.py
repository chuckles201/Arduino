import os
import time

'''Commands to send to esp32 over wifi!

- Simply send the command over wifi with the socket..
'''

ip_addr_esp32 = "10.0.0.13"
port = 5001

import socket
global sock 
sock = socket.socket()
sock.connect((ip_addr_esp32,port))

# reconnect to host if lost
def reconnect():
    global sock
    while True:
        try:
            # Close existing socket first
            sock.close()
            
            # Create new socket
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((ip_addr_esp32, port))
            print("Successfully reconnected")
            break
            
        except socket.error as e:
            print(f"Reconnection failed: {e}")
            time.sleep(2)  # Longer delay between attempts


def move_servo(action):
    global sock
    try:
        sock.send(action.encode())
    # only if specific error    
    except OSError:
        reconnect()
    



def toggle_laser(action):
    global sock
    try:
        sock.send(action.encode())
    # only if specific error    
    except OSError:
        reconnect()


'''Setting up Webserver and taking inputs.

We can simply set up the server with flask, and
run commands
'''
from flask import Flask, render_template, request

# create our flask object
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def handle_request():
    if request.method == 'POST':
        if request.method == 'POST':
            if 'laser' in request.form:
                # Handle laser toggle
                laser_state = request.form['laser']
                # Do something with laser_state
                toggle_laser(laser_state)
            elif 'direction' in request.form:
                # Handle direction
                direction = request.form['direction']
                move_servo(direction)
        
    
    # render index.html
    return render_template('index.html')




'''Communicating with ESP'''
app.run(host="0.0.0.0",port=5000)[7]