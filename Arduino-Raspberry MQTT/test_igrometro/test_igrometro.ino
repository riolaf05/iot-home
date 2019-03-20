void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0); //Legge il valore analogico
  //float percentage_value = (100 * sensorValue)/950;
  Serial.println(sensorValue); //Stampa a schermo il valore
    
}
