FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential g++ make cmake git wget \
    libpthread-stubs0-dev \
    libgl1-mesa-dev libjpeg-dev \
    libx11-dev libx11-xcb-dev \
    libxcb-image0-dev libxcb-randr0-dev \
    libfreetype6-dev libopenal-dev \
    libvorbis-dev libflac-dev libxrandr-dev \
    libudev-dev \
    libxcursor-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /tmp
RUN git clone --branch 2.6.x --depth 1 https://github.com/SFML/SFML.git && \
    cd SFML && mkdir build && cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j$(nproc) && make install && \
    ldconfig && cd /tmp && rm -rf SFML

RUN ln -sf /usr/lib/x86_64-linux-gnu/libGL.so.1 /usr/local/lib/ && \
    ln -sf /usr/lib/x86_64-linux-gnu/libjpeg.so.8 /usr/local/lib/ && \
    ln -sf /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1 /usr/local/lib/ && \
    ln -sf /usr/lib/x86_64-linux-gnu/libxcb-image.so.0 /usr/local/lib/ && \
    ln -sf /usr/lib/x86_64-linux-gnu/libxcb-randr.so.0 /usr/local/lib/

ENV LD_LIBRARY_PATH=/usr/local/lib:/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH

WORKDIR /app
CMD ["make", "clean", "all"]