
### Generic Raspberry Pi Camera on browser

This Docker Container includes: 

* Raspbian/stretch
* Picamera
* Opencv

### Istructions

1. `docker run -it --privileged -p 8000:8000 --rm --device=/dev/vchiq rio05docker/rpi_generic_camera:v1 python3 /home/scripts/camera/generic_browser_camera.py`

It can be used to perform object detection on Edge TPU from browser or as a simply browser camera