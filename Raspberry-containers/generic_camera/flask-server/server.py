from flask import Flask, Response, request
import subprocess
import os
import docker
from flask_httpauth import HTTPBasicAuth
from werkzeug.security import generate_password_hash, check_password_hash

#client = docker.APIClient(base_url='unix://var/run/docker.sock')
client = docker.from_env()

app = Flask(__name__)
auth = HTTPBasicAuth()

users = {
    os.getenv('USER'): generate_password_hash(os.getenv('PASSWORD')),
}

@auth.verify_password
def verify_password(username, password):
    if username in users and \
            check_password_hash(users.get(username), password):
        return username

@app.route('/docker')
@auth.login_required
def docker():
    client.images.pull('rio05docker/raspberry_container_camera:v1')
    devices=['/dev/vchiq:rwm']
    environments=['USER={}'.format(os.getenv('USER')), 'PASSWORD={}'.format(os.getenv('PASSWORD'))]
    ports={'8000/tcp':'8000'}
    client.containers.run("rio05docker/raspberry_container_camera:v1", "", name='camera', remove=True, privileged=True, detach=True, devices=devices, environment=environments, ports=ports)
    #container = client.containers.get('camera')

    #for line in container.logs(stream=True):
    #    print(line.strip())

    #return "Hello, {}!".format(auth.current_user())
    return Response(status=200)

@app.route('/dockerstop')
@auth.login_required
def dockerstop():
    container = client.containers.get('camera')
    container.stop()
    return Response(status=200)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5002)
