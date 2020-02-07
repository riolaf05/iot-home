#!/bin/bash

export GITHUB_SHA=$1

#Installing Mosquitto
mkdir /mosquitto
mkdir /mosquitto/data
mkdir /mosquitto/log

kubectl apply -f kubernetes/mosquitto/persistentVolume.yaml
kubectl apply -f kubernetes/mosquitto/persistentVolumeClaim.yaml
#kubectl apply -f kubernetes/mosquitto/service.yaml
kubectl apply -f kubernetes/mosquitto/deployment.yaml
kubectl expose deployment rpi-mosquitto --type=LoadBalancer --name=rpi-mosquitto

#Install MQTT subscriber pods

kubectl apply -f kubernetes/mqtt-subscriber-client/mqtt-subscriber-moisture/deployment.yaml
kubectl apply -f kubernetes/mqtt-subscriber-client/mqtt-subscriber-moisture/service.yaml
kubectl apply -f kubernetes/mqtt-subscriber-client/mqtt-subscriber-temperature/deployment.yaml
kubectl apply -f kubernetes/mqtt-subscriber-client/mqtt-subscriber-temperature/service.yaml


