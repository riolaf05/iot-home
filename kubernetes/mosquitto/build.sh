#!/bin/bash

#Deploy step, applying k8s resources
kubectl apply -f persistentVolume.yaml
kubectl apply -f persistentVolumeClaim.yaml
kubectl apply -f service.yaml
kubectl apply -f deployment.yaml
