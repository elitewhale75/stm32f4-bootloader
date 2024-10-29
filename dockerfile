# use the official Debian 11 (Bullseye) as the base image
FROM debian:11

# set non-interactive frontend for apt
ENV DEBIAN_FRONTEND=noninteractive

# update and install necessary packages
RUN apt-get update && apt-get install -y \
    gcc \
    git \
    vim \
    wget \
    make \
    python3 \
    python3-pip \
    cmake \
    && rm -rf /var/lib/apt/lists/*

# symbolic link for python3
RUN ln -s /usr/bin/python3 /usr/bin/python

# set environment variables and directories
ENV LIBOPENCM3_PATH=/opt/libopencm3
ENV PATH=$PATH:/opt/gcc-arm-none-eabi/bin

# create necessary directories
RUN mkdir -p /opt/libopencm3 /opt/gcc-arm-none-eabi

# clone the libopencm3 repository
RUN git clone https://github.com/libopencm3/libopencm3.git /opt/libopencm3

# download and extract the ARM toolchain
RUN wget -O /tmp/gcc-arm-none-eabi.tar.bz2 \
    https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 && \
    tar -xjf /tmp/gcc-arm-none-eabi.tar.bz2 -C /opt/gcc-arm-none-eabi --strip-components=1 && \
    rm /tmp/gcc-arm-none-eabi.tar.bz2

# set work directory
WORKDIR /workspace

# default command
CMD ["/bin/bash"]
