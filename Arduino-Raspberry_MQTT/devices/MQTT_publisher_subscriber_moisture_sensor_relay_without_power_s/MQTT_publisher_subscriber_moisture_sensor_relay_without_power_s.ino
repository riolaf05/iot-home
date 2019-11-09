#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <DHT.h>        // DHT11 temperature and humidity sensor Predefined library

#define DHTTYPE DHT11
#define dht_dpin 0

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed
const int buttonPin = 13; // Connect your button to pin #13

////////////////////////////////////////////// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "Vodafone-A41502247";
const char* wifi_password = "s3wv93bx9pkwd3m5";

////////////////////////////////////////////// MQTT
// Make sure to update this for your own MQTT Broker!
// TODO: externalize parameters!!!
const char* mqtt_server = "192.168.1.0";
const char* mqtt_topic = "moisture";
const char* mqtt_sub_topic = "pump_activation";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
const int mqtt_port = 1883; //choose K8s MQTT port
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "ClientID";
const char* ok_message = "ON";

WiFiClient espClient;
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.print("Subscribing to MQTT topic, new message arrived: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(10);
  digitalWrite(13, LOW);
 
  Serial.println();
  Serial.println("-----------------------");
 
}

float moistureSensor(char inputPin){
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
 
  Serial.begin(115200);

  DHT dht(dht_dpin, DHTTYPE);
 
  WiFi.begin(ssid, wifi_password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
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
 
  client.subscribe("pump_activation");
 
}
 
void loop() {
  //////////////////////////////////////Subscribing to MQTT topic..
  client.loop();

  ////////////////////////////////////Publishing to MQTT topic..
  //////////////////////////////// Getting moisture sensor value
  float moisture_value = moistureSensor(A0);
  char cstr[16];
  // Sending moisture value to MQTT broker
  if (client.publish(mqtt_topic, itoa(moisture_value, cstr, 10))) {
    Serial.println("Message sent to MQTT topic!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_topic, itoa(moisture_value, cstr, 10));
  }

  ///////////////////////////////////////// Getting DHT values
  t = dht.readTemperature(); //Read temperature in celcius
  // Sending temperature value to MQTT broker
  if (client.publish(mqtt_topic, itoa(t, cstr, 10))) {
    Serial.println("Message sent to MQTT topic!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_topic, itoa(t, cstr, 10));
  }

  
  delay(5000);
}
