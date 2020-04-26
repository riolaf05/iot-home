## Installation with Docker

To run Raspberry Pi Dockers with GPIO access launch:
```console
docker run -it --device /dev/gpiomem -d --restart=unless-stopped <container_name>:<tag>
```