# IoT-home
it containts scripts from my home iot platform

## Installation 

* Add /mosquitto/data and /mosquitto/log folders 

* Install Mosquitto Broker and IoT clients to communicate with Arduino devices

## MQTT broker

### Run with Kubernetes

Clone this repo on a Raspberry Pi with Kubernetes installed and run:

```console
install.sh <github_sha>
```

Where `<github_sha>` is the latest GitHub sha code used on the last GitHub Actions continuous delivery pipeline and can be found on Docker Hub.

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

See MQTT Broker Kubernetes installation.

### Run as a Docker

```console
iot-home/Arduino-Raspberry_MQTT/python/mqtt-subscriber-client/mqtt-subscriber-moisture/build.sh
iot-home/Arduino-Raspberry_MQTT/python/mqtt-subscriber-client/mqtt-subscriber-temperature/build.sh

docker run --restart=unless-stopped -it -d --network host rio05docker/mqtt_subscriber_moisture_sensor:rpi3_test_<day>_<month>
docker run --restart=unless-stopped -it -d --network host rio05docker/mqtt_subscriber_temperature_sensor:rpi3_test_<day>_<month>
```

*TODO: add external configuration file!*

