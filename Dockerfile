FROM ubuntu:14.04

MAINTAINER Erik Garrison <erik.garrison@gmail.com>

# Make sure the en_US.UTF-8 locale exists, since we need it for tests
RUN locale-gen en_US en_US.UTF-8 && dpkg-reconfigure locales

# Set up for make get-deps
RUN mkdir /app
WORKDIR /app
COPY Makefile /app/Makefile

# Install vg dependencies and clear the package index
RUN \
    echo "deb http://archive.ubuntu.com/ubuntu trusty-backports main restricted universe multiverse" | sudo tee -a /etc/apt/sources.list && \
    apt-get update && \
    apt-get install -y \
	    software-properties-common \
        python-software-properties \
        build-essential \
        pkg-config \
        jq/trusty-backports \
        sudo \
        dh-autoreconf \
        git vim 

RUN \ 
    apt-get remove gcc-4.8 g++-4.8 gcc-4.8-base:amd64 \ 
	apt-get autoremove

RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y gcc-4.9 g++-4.9 libtool autoconf && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 100 && \ 
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 100 
    update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-4.9 100 


# RUN make get-deps 
    
# Move in all the other files
COPY . /app
    
# Build vg
RUN . ./source_me.sh && make -j8

# # Make tests. We can't do it in parallel since it cleans up the test binary
RUN make test

ENV LD_LIBRARY_PATH=/app/lib

ENTRYPOINT ["/app/bin/vg"]

