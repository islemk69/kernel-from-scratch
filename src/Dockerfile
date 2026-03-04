FROM techiekeith/gcc-cross-i686-elf

RUN apt-get update && apt-get install -y \
    make \
    nasm \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/env
