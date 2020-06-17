
# Node Red installation and configuration

## Features:

* Smart garden status led: allows to read from 
`smart_garden_status` topic (which is updated by MQTT device, e.g. ESP8266) and store informations about device status (on, off). 

## Installation

### Install and configure MySQL

* With Kubernetes:

Install MySQL pod from [pannello_controllo](https://github.com/riolaf05/pannello-server) repo.

* With docker:

```console
docker run --name=mysql --network=host -e MYSQL_ROOT_PASSWORD=<password> -d hypriot/rpi-mysql (if not already present)

docker exec -it mysql mysql -uroot -p

create database SmartGarden;

use SmartGarden;

CREATE TABLE Smart_Garden_Status
(
ID int NOT NULL AUTO_INCREMENT,
Name varchar(255) NOT NULL,
Timestamp varchar(255),
Status varchar(255),
PRIMARY KEY (ID)
);

```

### Configure Node Red docker:

```console

mkdir ~/volume/nodered

docker run -d -it --restart=unless-stopped -p 1880:1880 -v /home/pi/volume/nodered:/data --name mynodered nodered/node-red:1.0.2-10-arm32v7

```

### Cofigure Node Red:

* Install packages:

1. Open <node_ip>:1883, then go to:
```console
Settings -> Palette -> Install tab
```
and install packages listed in requirements.txt

2. Import flow.json from the UI tool.

3. Authentication: 
Open `/volume/nodered/setting.js` and uncomment the following lines: 
```console
adminAuth: {
        type: "credentials",
        users: [{
            username: "<USER>",
            password: "<PASSWORD>",
            permissions: "*"
        }]
    },
```
replacing <USER> and <PASSWORD> (with base64 encoded password). Finally restart Nodered Docker image:
```console
docker restart mynodered
```

