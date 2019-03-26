FROM python:2.7

RUN mkdir mqtt_client
RUN pip install paho-mqtt

WORKDIR mqtt_client

COPY ./Arduino-Raspberry MQTT/MQTT_Client.py mqtt_client/

EXPOSE 1883

CMD [ "python", "./MQTT_Client.py" ]