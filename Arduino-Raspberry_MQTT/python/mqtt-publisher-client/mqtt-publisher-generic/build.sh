#!/bin/bash

DAY=$(date -d "$D" '+%d')
MONTH=$(date -d "$D" '+%m')
DOCKER_TAG='rpi3_test_'$DAY'_'$MONTH

echo "Build and push subscriber container"
docker build -t "rio05docker/mqtt_publisher_generic:"$DOCKER_TAG .
docker push rio05docker/mqtt_publisher_generic:$DOCKER_TAG