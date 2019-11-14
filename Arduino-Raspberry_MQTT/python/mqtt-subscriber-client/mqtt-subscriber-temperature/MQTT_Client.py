import paho.mqtt.client as paho
import sys
import urllib2
import time
import datetime
from time import sleep
from on_messages import on_message
#import Adafruit_DHT as dht

# Enter Your ThingSpeak API key here
myAPI = 'JHTAY1BANPFEPCW0'
# URL where we will send the data, Don't change it
baseURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: "+str(mid)+" "+str(granted_qos))

def on_message(client, userdata, msg):
        try:
                temperature = float(msg.payload)
                # If Reading is valid
                if isinstance(temperature, float):
                        # Formatting to two decimal places
                        temperature = '%.2f' % temperature                                    
                        # Sending the data to ThingSpeak
                        conn = urllib2.urlopen(baseURL + '&field1=%s' % (temperature))
                        ts = time.time()
                        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
                        print str(st) + ": temperature " + str(temperature) + "° C"
                        # Closing the connection
                        conn.close()
                else:
                        print 'Error'
                # Sesnor (e.g. DHT22) requires 2 seconds to give a reading, so make sure to add delay of above 2 seconds.
                sleep(20)
        except:
                print "connessione persa!"

'''
This script is used to listen on MQTT port 1883 and trigger the "on_message_xxx" methods
which actually publishes on ThingSpeak or other front end objects.  
'''

client = paho.Client()
#client.username_pw_set("rio", "onslario89")
client.on_subscribe = on_subscribe
client.on_message = on_message
try:
        client.connect("192.168.1.10", 30050) #TODO: fix hard coded endpoint IP #old ip 10.44.0.5?
        client.subscribe("temperature", qos=1)
        print "connecting.."

        client.loop_forever()
except Exception:
        print "no MQTT broker found!"
