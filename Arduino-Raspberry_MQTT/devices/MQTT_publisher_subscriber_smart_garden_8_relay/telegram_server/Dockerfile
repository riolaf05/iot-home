FROM ubuntu:18.04

RUN apt-get update && apt install -y python3-pip

COPY requirements.txt /src/requirements.txt
RUN pip3 install --upgrade pip
RUN pip3 install -r /src/requirements.txt

RUN mkdir /src/Models

COPY inference.py /src/inference.py
COPY pots.txt /src/pots.txt

CMD ["python3", "/src/inference.py"]
