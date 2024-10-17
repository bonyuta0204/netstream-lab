# Use the base image from Microsoft as the starting point
FROM mcr.microsoft.com/devcontainers/base:jammy

# Install necessary build tools and gdb
RUN apt-get update && apt-get install -y \
    gdb \
    python3 \
    build-essential \
    libssl-dev \
    curl \
    git \
    && apt-get clean

# Clone the Node.js source code from the official GitHub repository
RUN git clone --depth 1 --branch v20.x https://github.com/nodejs/node.git /usr/src/node


# Navigate to the Node.js source directory
WORKDIR /usr/src/node

# Configure the build to include debug symbols
RUN ./configure --debug

# Build Node.js with debug symbols (this may take some time)
RUN make -j$(nproc)

# Install the built Node.js
RUN make install

# Set up gdb for debugging
CMD ["gdb", "/usr/local/bin/node"]
