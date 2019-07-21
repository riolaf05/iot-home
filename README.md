# IoT-home
it containts scripts from my home iot platform

## Installation 

* Add /mosquitto/data and /mosquitto/log folders 

* Install Mosquitto Broker and IoT clients to communicate with Arduino devices

## MQTT broker

### Run with Kubernetes

```console
kubernetes/mosquitto/build.sh
```

### Run as a Docker

```console
docker run eclipse-mosquitto
```

To expose MQTT to external clients use: 

```console
kubectl expose deployment rpi-mosquitto --type=LoadBalancer --name=rpi-mosquitto
```

then retrieve broker ip address with 

```console
kubectl get svc | grep rpi-mosquitto
```

TODO: change hard-coded broker IP address

## Deploy MQTT client (Python scripts)

### Run with Kubernetes

```console
kubernetes/<script>/build.sh
```

### Run as a Docker

```console
docker build -t python-mqtt-rio-client:rpi3_latest ./Arduino-Raspberry_MQTT/client/ (only first time)

docker push python-mqtt-rio-client:rpi3_latest

docker run --net=host --restart unless-stopped -d python-mqtt-rio-client (launch MQTT broker on 1883 first)
```
or run on Kubernetes.

*TODO: add external configuration file!*

