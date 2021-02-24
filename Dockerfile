FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

COPY .gdbinit.root /root/.gdbinit

RUN apt-get update && \
    apt-get install -y \
    bat \
    binutils \
    cscope \
    ctags \
    curl \
    emacs \
    gcc-multilib \
    gdb \
    git \
    locate \
    make \
    netcat \
    perl \
    python \
    python3 \
    python3-pip \
    qemu-system-x86 \
    silversearcher-ag \
    valgrind \
    vim
