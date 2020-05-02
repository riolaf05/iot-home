FROM arm32v7/python:3.7.7-alpine3.10

RUN apt-get update && apt-get install -y rpi.gpio
RUN pip3 install paho-mqtt

#COPY smart_camera.py /home/scripts/object_detections/smart_camera.py
COPY servo_driver.py /home/scripts/object_detections/servo_driver.py
COPY mqtt_client.py /home/scripts/object_detections/mqtt_client.py
COPY on_messages.py /home/scripts/object_detections/on_messages.py

#CMD ["python3", "smart_camera.py", "--model", "/tmp/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite", "--label", "/tmp/coco_labels.txt"]
CMD ["/scripts/python", "mqtt_client.py"]


