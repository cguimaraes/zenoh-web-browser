FROM ubuntu:20.04

USER root
WORKDIR /root

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt upgrade -y && \
    apt install -y git build-essential cmake qt5-qmake qt5-default \
                   qtwebengine5-dev qml-module-qtquick-dialogs \
                   qml-module-qtquick-controls qml-module-qtwebengine && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/eclipse-zenoh/zenoh-pico.git && \
    cd zenoh-pico && \
    make && make install && \
    ldconfig

RUN useradd -ms /bin/bash user-docker
USER user-docker
WORKDIR /home/user-docker

RUN mkdir /home/user-docker/app
COPY . /home/user-docker/app/
RUN cd /home/user-docker/app && \
    qmake && make

CMD /home/user-docker/app/dist/zenoh-web-browser

