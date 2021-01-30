w pir se#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

//topics
#define MQTT_PUB_PIR "pir/alert"

/*Put your SSID & Password*/
const char* ssid = "FASTWEB-D82B93";  // Enter SSID here
const char* password = "W1JA3M3R2A";  //Enter Password here

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "192.168.1.12";
const char* mqtt_username = "rio";
const char* mqtt_password = "onslario89";
const char* clientID = "Client ID";

// DHT Sensor
int sensor = 13;  // Digital pin D7 

// Tempo di calibrazione del sensore
int calibrationTime = 30;

//Il tempo in cui l'uscita sia bassa
long unsigned int lowIn;

// valore di millisecondi, per cui si ritiene che ci sia "quiete"
long unsigned int pause = 5000;

boolean lockLow = true;
boolean takeLowTime;

// Impostazione del sensore
void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);

  Serial.println("Connessione..");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connesso..!");
  Serial.print("IP: ");  Serial.println(WiFi.localIP());

  // Initialise the WiFi and MQTT Client objects
  WiFiClient wifiClient;
  PubSubClient client(mqtt_server, 31085, wifiClient); // 1883 is the listener port for the Broker

  //Fase di calibrazione
  Serial.print("Calibrazione del sensore ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" Fatto");
  Serial.println("SENSORE ATTIVO");
  delay(50);
}

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connesso al broker MQTT!");
  }
  else {
    Serial.println("Connessione al broker MQTT fallita...");
  }

void loop() {
  

  // Questo IF permette di stabilre se il sensore rileva un oggetto in movimento
  if (digitalRead(sensor) == HIGH) {

    if (client.publish(MQTT_PUB_PIR, "ON") {
        Serial.println("Intrusione rilevata!");
      }
  
    if (lockLow) {

      lockLow = false;
      Serial.println("---");
      Serial.print("Movimento rilevato a ");
      Serial.print(millis() / 1000);
      Serial.println(" sec");
      delay(50);
    }
    takeLowTime = true;
  }
  
  // Questo IF permette di stabilire se non c'è più nessun movimento
  if (digitalRead(sensor) == LOW) {

    if (takeLowTime) {
      lowIn = millis();
      takeLowTime = false;
    }

    if (!lockLow && millis() - lowIn > pause) {

      lockLow = true;
      Serial.print("Movimento terminato a ");      //output
      Serial.print((millis() - pause) / 1000);
      Serial.println(" sec");
      delay(50);
    }
  }
}
