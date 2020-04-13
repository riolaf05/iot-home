import sys
sys.path.insert(1, '/usr/lib/python3/dist-packages')
sys.path.insert(1, '/home/pi/.local/lib/python3.7/site-packages')

from flask import Flask, Response, request
import subprocess
import os
import docker


app = Flask(__name__)

client = docker.from_env()

@app.route('/camera', methods = ['GET', 'POST', 'DELETE'])
def camera():
    if request.method == 'GET':

        volume_bindings = {
                            '/dev/bus/usb': {
                                'bind': '/dev/bus/usb',
                                'mode': 'rw',
                            },
        }
        
        devices=['/dev/vchiq:rwm']

        ports = {'8000/tcp': 8000}

        container = client.containers.run(
                            image="rio05docker/obj_detection_cd:rpi3_rt_tflite_tpu",
                            name='ai-camera',
                            command=['python3', 'demo_real_time_obj_detection_server.py', '--model', '/tmp/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite', '--label /tmp/coco_labels.txt'],
                            volumes=volume_bindings,
                            devices=devices,
                            ports=ports,
                            privileged=True,
                            detach=True
                            #environment=env,
        ) 

        return Response(response=container.logs(), status=200)


@app.route('/camera_stop', methods = ['GET', 'POST', 'DELETE'])
def camera_stop():
    if request.method == 'GET':

        container = client.containers.run('ai-camera')

        return Response(response='stopped', status=200)

'''    

@app.route('/motion_sensor', methods = ['GET', 'POST', 'DELETE'])
def motion_sensor():
    if request.method == 'GET':
        """TODO"""
        return Response(response="command complete!", status=200)



@app.route('/light', methods = ['GET', 'POST', 'DELETE'])
def light():
    if request.method == 'GET':
        """TODO"""
        return Response(response="command complete!", status=200)



@app.route('/restart_minidlna', methods = ['GET', 'POST', 'DELETE'])
def restart_minidlna():
    if request.method == 'GET':
        """TODO"""
        return Response(response="command complete!", status=200)



@app.route('/ainews', methods = ['GET', 'POST', 'DELETE'])
def ainews():
    if request.method == 'GET':

        env=["TELEGRAM_BOT_TOKEN={}", "TELEGRAM_CHAT_ID={}".format(os.getenv('TELEGRAM_BOT_TOKEN'), os.getenv('TELEGRAM_CHAT_ID'))]
        
        volumes= ['/usr/bin/qemu-arm-static']
        volume_bindings = {
                            '/usr/bin/qemu-arm-static': {
                                'bind': '/usr/bin/qemu-arm-static',
                                'mode': 'rw',
                            },
        }
        host_config = client.create_host_config(
                            binds=volume_bindings
        )
        
        container = client.create_container(
                            image="rio05docker/ai_news_server:rpi3_develop_89714b6a3deaedd9672f73525ccc435cac5cd9ee",
                            name='ai-news',
                            #volumes=volumes,
                            #host_config=host_config,
                            environment=env,
        ) 

        response = client.start(container=container.get('Id'))
        client.wait(container.get('Id'))
        client.remove_container(container.get('Id'))
        return Response(response=response, status=200)



@app.route('/temperature', methods = ['GET'])
def temperature():
    if request.method == 'GET':
        stream = os.popen("/opt/vc/bin/vcgencmd measure_temp | sed 's/[^0-9|\.]*//g'")
        output = stream.read()
    return Response(response=output[:-1], status=200)



@app.route('/memory', methods = ['GET'])
def memory():
    if request.method == 'GET':
        stream = os.popen("df -h / | awk '{ print $2 }' | tail -n 1 | sed 's/[^0-9|\,]*//g'")
        output = stream.read()
    return Response(response=output[:-1], status=200)



@app.route('/harddisk', methods = ['GET'])
def harddisk():
    if request.method == 'GET':
        stream = os.popen("df -h /dev/sda1 | awk '{ print $2 }' | tail -n 1 | sed 's/[^0-9|\,]*//g'")
        output = stream.read()
    return Response(response=output[:-1], status=200)

'''
if __name__ == '__main__':
     app.run(host='0.0.0.0', port='5002')
