FROM techiekeith/gcc-cross-i686-elf

RUN apt-get update && apt-get install -y \
    make \
    nasm \
    libmpc3 \
    libmpfr6 \
    libgmp10 \
    binutils \
    grub-pc-bin \
    grub-common \
    xorriso \
    mtools \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/env
