
# Netstream Lab

**Netstream Lab** is a project for studying low-level network programming using TCP, sockets, and protocols. This environment is designed for Linux, and a Docker setup is provided for ease of use across various development environments.

## Prerequisites

- Docker
- Docker Compose

## Getting Started

1. First, start the Docker container:

   ```bash
   docker compose up -d
   ```

2. Then, enter the development environment inside the running container:

   ```bash
   docker compose exec dev /bin/bash
   ```

This will launch a bash session inside the container, allowing you to work in a Linux environment regardless of your host operating system.

## Notes

- This project is optimized to run on Linux, but the Docker environment is provided to ensure a consistent development setup across different platforms.
- The Dockerfile is based on Ubuntu and contains all necessary tools for C, Assembly, and network programming.
