import paho.mqtt.client as paho
#see: http://www.steves-internet-guide.com/publishing-messages-mqtt-client/
broker="rpi-mosquitto"
port=1883

def on_publish(client,userdata,result):             #create function for callback. The mid value is the message id and can 
													#be used with the mid value returned from the publish method to check that 
													#a particular message has been published.
    print("data published \n")
    pass

def on_disconnect(client, userdata, rc):
   print("client disconnected ok")

def on_log(client, userdata, level, buf):
    print("log: ",buf)

client1= paho.Client("control1")                    #create client object
client1.on_log=on_log
client1.on_publish = on_publish                     #assign function to callback

#client.tls_set('c:/python34/steve/MQTT-demos/certs/ca.crt') #to set SSL certificate

print("connectiong to broker..")
client1.connect(broker,port)                        #establish connection
ret= client1.publish("test","10")
print("message published..")            		#publish

client1.on_disconnect = on_disconnect
client1.disconnect()