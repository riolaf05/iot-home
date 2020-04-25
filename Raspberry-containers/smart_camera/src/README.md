### Computer Vision camera with Edge TPU 

Object detection inference docker image with Edge TPU device runtime

Based on Raspbian Stretch, it contains:

* Python 3.5.3
* Tensorflow Lite
* Picamera module
* Edge TPU runtime

It must run on RaspberryPi with Edge TPU Coral device

### Installation

1. Follow this istructions to plug the servo motor:

![image](https://github.com/riolaf05/cv-follow-camera/blob/master/images/servo.png)

2. Use CI/CD pipeline to build Docker.

3. To run with Raspberry Camera and Edge TPU usb device:

```console
docker run -it --rm --privileged -p 8000:8000 -v /dev/bus/usb:/dev/bus/usb --device=/dev/vchiq --device /dev/gpiomem rio05docker/ai_obj_detection_camera:rpi3_rt_tflite_tpu_${GITHUB_SHA}
```

4. exec the container and run: 

```console
python3 demo_real_time_obj_detection_server.py --model /tmp/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite --label /tmp/coco_labels.txt
```

5. Log in on browser from `<rpi3_ip>:8000`, use:

* user: pi
* camera picamera

### TODO: 
* ~~Test real time predictions~~
* ~~Add multi-direction movements~~
* Improve performance
