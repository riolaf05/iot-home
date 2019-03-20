# iot-home
it containts scripts from my home iot platform

# MQTT broker

docker run eclipse-mosquitto

## Deploy MQTT client 
### Run as a Docker
docker build -t python-mqtt . (only first time)

docker run -p localhost:1883:1883 python-mqtt (TODO: is is right??)
