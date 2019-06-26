FROM arm32v7/ubuntu:16.04

RUN mkdir mqtt_client
RUN pip install paho-mqtt

WORKDIR mqtt_client

COPY ./Arduino-Raspberry_MQTT/MQTT_Client.py mqtt_client/

CMD [ "python", "mqtt_client/MQTT_Client.py" ]