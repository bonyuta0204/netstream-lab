# Use Ubuntu as the base image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /workspace

# Copy the current directory contents into the container
COPY . .

# Update and install build dependencies for C and Assembly
RUN apt-get update && apt-get install -y \
    build-essential \
    bash \
    nasm \
    git \
    neovim \
    vim \
    gdb \
    curl \
    fzf \
    npm \
    fish \
    && apt-get clean

# Clone your dotfiles repository
RUN git clone https://github.com/bonyuta0204/dotfiles.git ~/dotfiles

# Run the setup script from the dotfiles repository
RUN cd ~/dotfiles && ./setup -a

# Set the default command to bash
CMD ["/bin/bash"]
