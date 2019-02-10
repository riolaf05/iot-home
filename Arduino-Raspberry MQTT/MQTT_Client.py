import paho.mqtt.client as paho
import sys
import urllib2
import time
import datetime
from time import sleep
import Adafruit_DHT as dht

# Enter Your API key here
myAPI = 'CTPSMGYK3QGWKV8T'
# URL where we will send the data, Don't change it
baseURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: "+str(mid)+" "+str(granted_qos))

def on_message(client, userdata, msg):
        try:
                humi = float(msg.payload)
                # If Reading is valid
                if isinstance(humi, float):
                        # Formatting to two decimal places
                        humi = '%.2f' % humi                                    
                        # Sending the data to ThingSpeak
                        conn = urllib2.urlopen(baseURL + '&field1=%s' % (humi))
                        ts = time.time()
                        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')
                        print str(st) + ": humidity " + str(humi) + "%"
                        # Closing the connection
                        conn.close()
                else:
                        print 'Error'
                # Sesnor (e.g. DHT22) requires 2 seconds to give a reading, so make sure to add delay of above 2 seconds.
                sleep(20)
        except:
                print "connessione persa!"

client = paho.Client()
client.username_pw_set("pi", "raspberry")
client.on_subscribe = on_subscribe
client.on_message = on_message
client.connect("localhost", 1883)
client.subscribe("test", qos=1)

print "connecting.."

client.loop_forever()