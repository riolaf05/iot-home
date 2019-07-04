# IoT-home
it containts scripts from my home iot platform

# MQTT broker

docker run eclipse-mosquitto

## Deploy MQTT client 
### Run as a Docker

```console
docker build -t python-mqtt-rio-client:rpi3_latest ./Arduino-Raspberry_MQTT/client/ (only first time)

docker push python-mqtt-rio-client:rpi3_latest

docker run --net=host --restart unless-stopped -d python-mqtt-rio-client (launch MQTT broker on 1883 first)
```
or run on Kubernetes.

### TODO: add external configuration file!

