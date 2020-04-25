FROM rio05docker/obj_detection_cd:rpi3_rt_tflite_tpu

RUN apt-get install rpi.gpio

COPY smart_camera.py /home/scripts/object_detections/smart_camera.py
COPY servo_driver.py /home/scripts/object_detections/servo_driver.py

CMD ["python3", "smart_camera.py", "--model", "/tmp/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite", "--label", "/tmp/coco_labels.txt"]


