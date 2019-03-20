FROM python:3

ADD MQTT_Client.py /

RUN pip3 install paho-mqtt

RUN pip3 install urllib.request

CMD [ "python", "./MQTT_Client.py" ]