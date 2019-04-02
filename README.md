# iot-home
it containts scripts from my home iot platform

# MQTT broker

docker run eclipse-mosquitto

## Deploy MQTT client 
### Run as a Docker
docker build -t python-mqtt . (only first time)

docker run --net=host --restart unless-stopped -d python-mqtt (launch MQTT broker on 1883 first)
