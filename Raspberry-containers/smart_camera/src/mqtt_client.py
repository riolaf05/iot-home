import paho.mqtt.client as paho
import sys
import time
import datetime
from time import sleep
from on_messages import on_message
from servo_driver import get_pwm, move_servo


def on_subscribe(client, userdata, mid, granted_qos):
    print "Subscribed: "+str(mid)+" "+str(granted_qos)

def on_message(client, userdata, msg):
        try:
                payload = float(msg.payload)
                move_servo(payload)
                
        except Exception as e:
                print "connessione persa!"
                print e

'''
This script is used to listen on MQTT port 1883 and trigger the "on_message_xxx" methods
which actually publishes on ThingSpeak or other front end objects.  
'''

#client = paho.Client("Python1",False)
client = paho.Client()
client.username_pw_set("rio", "onslario89")
client.on_subscribe = on_subscribe
client.on_message = on_message
try:
        print "connecting.."
        client.connect("192.168.1.0", 1883) 
        client.subscribe("camera", qos=1)
        client.loop_forever()
        
except Exception as e:
        print e
