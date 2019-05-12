#include <Bounce2.h> // Used for "debouncing" the pushbutton
#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed
const int buttonPin = 13; // Connect your button to pin #13

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "Vodafone-A41502247";
const char* wifi_password = "s3wv93bx9pkwd3m5";

// MQTT
// Make sure to update this for your own MQTT Broker!
// TODO: externalize parameters!!!
const char* mqtt_server = "192.168.1.9";
const char* mqtt_topic = "test";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "Client ID";

// Time to sleep (in seconds):
const int sleepTimeS =300;

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker


void setup() {
  // Begin Serial on 115200
  // Remember to choose the correct Baudrate on the Serial monitor!
  // This is just for debugging purposes
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }

  //BEGIN OF "ONCE-WAS-LOOP" FUNCTION (PUT IT HERE DUE TO DEEP-SLEEP MODE ////////////
  // The "loop" function has been moved here because, shoarting the 
  // "D0" pin to ground, the NodeMCU will be restarted every time
  // the "begin" function has finished. 
  // This allows to put the NodeMCU to sleep for a given time!
  
  // PUBLISH to the MQTT Broker (topic = mqtt_topic, defined at the beginning)
  // TODO: CHANGE the function according to the sensor you want to use! <<< HERE
  float output_value = moistureSensor(A0);
  char cstr[16];
  if (client.publish(mqtt_topic, itoa(output_value, cstr, 10))) {
    Serial.println("message sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_topic, itoa(output_value, cstr, 10));
  }
     delay(5000);
  //END OF "ONCE-WAS-LOOP" FUNCTION //////////////////////////////////////////////////
  
  Serial.println("Deep sleep mode for sleepTimeS * microseconds");
  ESP.deepSleep(sleepTimeS * 1000000); 
}

void loop() {
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

int relayInput(char inputPin){
  //TODO
}

int genericSensor(char inputPin){
  //TODO
}

