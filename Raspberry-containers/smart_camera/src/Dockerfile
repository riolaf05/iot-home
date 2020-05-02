FROM raspbian/stretch

RUN apt-get update 
RUN apt-get install -y build-essential cmake pkg-config 
RUN apt-get install -y libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev 
RUN apt-get install -y libavcodec-dev libavformat-dev libswscale-dev libv4l-dev 
RUN apt-get install -y libxvidcore-dev libx264-dev 
RUN apt-get install -y libgtk2.0-dev libgtk-3-dev 
RUN apt-get install -y libatlas-base-dev gfortran 
RUN apt-get install -y python3-dev 
RUN apt-get install -y python3-pip
#RUN apt-get install -y curl zip

RUN pip3 install opencv-python

RUN apt-get install -y rpi.gpio
RUN pip3 install paho-mqtt

#COPY smart_camera.py /home/scripts/object_detections/smart_camera.py
COPY servo_driver.py /home/scripts/object_detections/servo_driver.py
COPY mqtt_client.py /home/scripts/object_detections/mqtt_client.py
COPY on_messages.py /home/scripts/object_detections/on_messages.py

#CMD ["python3", "smart_camera.py", "--model", "/tmp/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite", "--label", "/tmp/coco_labels.txt"]
CMD ["/scripts/python", "mqtt_client.py"]


