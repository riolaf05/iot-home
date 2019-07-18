# IoT-home
it containts scripts from my home iot platform

## Installation 

* Add /mosquitto/data and /mosquitto/log folders 

* Install Mosquitto Broker and IoT devices

### Install MQTT broker

* Kubernetes: 
```console
bash iot-home/kubernetes/mosquitto/build.sh
```
* Docker:
```console
docker run eclipse-mosquitto
```

### Deploy MQTT client 

* Kubernetes
TODO

* Docker

```console
docker build -t python-mqtt-rio-client:rpi3_latest ./Arduino-Raspberry_MQTT/client/ (only first time)

docker push python-mqtt-rio-client:rpi3_latest

docker run --net=host --restart unless-stopped -d python-mqtt-rio-client (launch MQTT broker on 1883 first)
```

*TODO: add external configuration file!*

