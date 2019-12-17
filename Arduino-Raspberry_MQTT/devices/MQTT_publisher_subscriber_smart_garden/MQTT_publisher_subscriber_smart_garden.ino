#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <DHT.h>        // DHT11 temperature and humidity sensor Predefined library

#define DHTTYPE DHT22
#define PUMP D7
#define dht_dpin D3

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed
const int buttonPin = 13; // Connect your button to pin #13
float t =0.0;

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "Vodafone-A41502247";
const char* wifi_password = "s3wv93bx9pkwd3m5";

// MQTT
// Make sure to update this for your own MQTT Broker!
// TODO: externalize parameters!!!
const char* mqtt_server = "192.168.1.0";
const char* mqtt_moisture_topic = "moisture";
const char* mqtt_temperature_topic = "temperature";
const char* mqtt_sub_topic = "pump_activation";
const char* status_topic = "status";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
const int mqtt_port = 1883; //choose K8s MQTT port
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "ClientID";
const char* ok_message = "ON";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(dht_dpin, DHTTYPE);

 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("New message arrived: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  digitalWrite(D7, HIGH);
  delay(5000);
  digitalWrite(D7, LOW);
  
}


float moistureSensor(char inputPin){
    //function which calculates the moisture sensor output value
    int sensorValue = analogRead(inputPin); //Read the analog value
    Serial.print("Analog value : ");
    Serial.println(sensorValue); //Print the value on serial monitor
    int percentage_value = map(sensorValue,550,10,0,100);
    Serial.print("Mositure : ");
    Serial.print(percentage_value + 87);
    Serial.println("%");
    return percentage_value+87;
}



void setup() {
  //configuring Serial, WIFI, outputs
  Serial.begin(115200);
  WiFi.begin(ssid, wifi_password);
  pinMode(PUMP, OUTPUT);       //D7 as output
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  //Configuring MQTT client
   Serial.println("Configuring MQTT client..");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqtt_username, mqtt_password )) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  
  //Subscribing to MQTT queue
  client.subscribe("pump_activation");
}



 
void loop() {
  //Subscribing to MQTT topic to check for water pump activation..
  Serial.println("Checking pump activation..");
  client.loop();



  //Publishing to MQTT topic..

  //Smart garden status
  if (client.publish(status_topic, "ON")) {
    Serial.println("Message sent to MQTT status topic!");
  }

  //Moisture
  //Getting moisture sensor value
  Serial.println("Getting moisture value..");
  float moisture_value = moistureSensor(A0);
  char cstr[16];
  // Sending moisture value to MQTT broker
  if (client.publish(mqtt_moisture_topic, itoa(moisture_value, cstr, 10))) {
    Serial.println("Message sent to MQTT moisture topic!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_moisture_topic, itoa(moisture_value, cstr, 10));
  }


  //Temperature
  //Getting DHT values
  Serial.println("Getting temperature value..");
  char cstr[16];
  t = dht.readTemperature(); //Read temperature in celcius
  Serial.print("temperature: ");
  Serial.println(t);
  //Sending temperature value to MQTT broker
  if (client.publish(mqtt_temperature_topic, itoa(t, cstr, 10))) {
    Serial.println("Message sent to MQTT temperature topic!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_temperature_topic, itoa(t, cstr, 10));
  }


  
  delay(10000);
}
