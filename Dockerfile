# Use Ubuntu 20.04 as base image
FROM ubuntu:20.04

# Set environment to non-interactive to prevent unnecessary prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install required packages, then clean up
# Note: It's a good practice to remove the package lists after installing to reduce image size
# We also combine multiple commands in a single RUN statement to reduce the number of layers
RUN apt-get update && \
    apt-get install -y g++ make curl libgflags-dev libunwind-dev libgoogle-perftools-dev libpng-dev wget git autoconf libtool graphviz python3 perl && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    # Install gperftools from source
    cd /tmp && \
    git clone https://github.com/gperftools/gperftools.git && \
    cd gperftools && \
    ./autogen.sh && \
    ./configure --disable-dependency-tracking && \
    make -j$(nproc) && \
    make install && \
    # Clean up source to reduce image size
    rm -rf /tmp/gperftools && \
    # Clone FlameGraph
    cd /tmp && \
    git clone https://github.com/brendangregg/FlameGraph.git

# Copy the C++ source code and the shell script
COPY main.cpp /app/main.cpp
COPY run.sh /app/run.sh

# Build the C++ program with gperftools
# Note: We're setting WORKDIR earlier to reduce directory switching
WORKDIR /app
RUN chmod +x run.sh && \
    g++ -o main main.cpp -g -lprofiler -lpng && \
    chmod +x main

# Set the custom shell script as the default command to be executed
ENTRYPOINT ["./run.sh"]
