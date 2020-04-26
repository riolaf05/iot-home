### Rotate camera from MQTT queue

### Installation

1. Follow this istructions to plug the servo motor:

![image](https://github.com/riolaf05/cv-follow-camera/blob/master/images/servo.png)

2. Launch build_container.sh to build Docker.

3. Run: 

```console
docker run -it --rm -d --privileged -p 1883:1883 -e TOPIC=camera --device /dev/gpiomem rio05docker/raspberry_container_generic:camera
```

