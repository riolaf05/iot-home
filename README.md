# iot-home
it containts scripts from my home iot platform

# MQTT Server
## Deploy 
### Run as a Docker
docker build -t python-mqtt . (only first time)

docker run -p localhost:1883:1883 python-mqtt
