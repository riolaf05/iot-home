FROM rio05docker/obj_detection_cd:rpi3_rt_tflite_tpu

RUN apt-get install rpi.gpio

COPY demo_real_time_obj_detection_server.py /home/scripts/object_detections/demo_real_time_obj_detection_server.py
COPY servo_driver.py /home/scripts/object_detections/servo_driver.py

CMD ["python3", "demo_real_time_obj_detection_server.py", "--model", "/tmp/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite", "--label", "/tmp/coco_labels.txt"]


