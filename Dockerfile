# SFML Multi-Player Games Collection Development Environment
# Multi-stage build for different SFML versions and platforms

# Base image with common build tools
FROM ubuntu:22.04 AS base

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    pkg-config \
    libfreetype6-dev \
    libopenal-dev \
    libvorbis-dev \
    libflac-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxinerama-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libudev-dev \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# SFML 2.5.1 build stage
FROM base AS sfml-2.5.1

# Download and build SFML 2.5.1
RUN wget https://github.com/SFML/SFML/archive/2.5.1.tar.gz \
    && tar -xzf 2.5.1.tar.gz \
    && cd SFML-2.5.1 \
    && mkdir build && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release -DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_DOC=OFF \
    && make -j$(nproc) \
    && make install \
    && ldconfig

# SFML 3.0.0 build stage
FROM base AS sfml-3.0.0

# Download and build SFML 3.0.0
RUN wget https://github.com/SFML/SFML/archive/3.0.0.tar.gz \
    && tar -xzf 3.0.0.tar.gz \
    && cd SFML-3.0.0 \
    && mkdir build && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release -DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_DOC=OFF \
    && make -j$(nproc) \
    && make install \
    && ldconfig

# Development environment with SFML 2.5.1 (default)
FROM sfml-2.5.1 AS dev-2.5.1

# Install additional development tools
RUN apt-get update && apt-get install -y \
    valgrind \
    gdb \
    clang \
    clang-tidy \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

# Copy project files
COPY . .

# Create build directory
RUN mkdir -p build

# Set environment variables
ENV SFML_VERSION=2.5.1
ENV CC=gcc
ENV CXX=g++

# Default command
CMD ["/bin/bash"]

# Development environment with SFML 3.0.0
FROM sfml-3.0.0 AS dev-3.0.0

# Install additional development tools
RUN apt-get update && apt-get install -y \
    valgrind \
    gdb \
    clang \
    clang-tidy \
    cppcheck \
    && rm -rf /var/lib/apt/lists/*

# Copy project files
COPY . .

# Create build directory
RUN mkdir -p build

# Set environment variables
ENV SFML_VERSION=3.0.0
ENV CC=gcc
ENV CXX=g++

# Default command
CMD ["/bin/bash"]

# Production build stage
FROM base AS production

# Install runtime dependencies only
RUN apt-get update && apt-get install -y \
    libfreetype6 \
    libopenal1 \
    libvorbis0a \
    libflac8 \
    libxrandr2 \
    libxcursor1 \
    libxinerama1 \
    libxi6 \
    libgl1-mesa-glx \
    libudev1 \
    && rm -rf /var/lib/apt/lists/*

# Copy built executable and assets
COPY --from=dev-2.5.1 /workspace/build/bin/sfml-app /usr/local/bin/
COPY --from=dev-2.5.1 /workspace/assets /usr/local/share/sfml-app/assets/

# Set working directory
WORKDIR /usr/local/share/sfml-app

# Expose port (if needed for future network features)
EXPOSE 8080

# Default command
CMD ["sfml-app"]

# Multi-arch build support
FROM dev-2.5.1 AS multiarch

# Install cross-compilation tools
RUN apt-get update && apt-get install -y \
    gcc-mingw-w64 \
    g++-mingw-w64 \
    mingw-w64-tools \
    && rm -rf /var/lib/apt/lists/*

# Set environment variables for cross-compilation
ENV CROSS_COMPILE=true

# Default command
CMD ["/bin/bash"]

# Usage instructions
# Build different versions:
# docker build --target dev-2.5.1 -t sfml-xo:2.5.1 .
# docker build --target dev-3.0.0 -t sfml-xo:3.0.0 .
# docker build --target production -t sfml-xo:prod .
# docker build --target multiarch -t sfml-xo:multiarch .

# Run development environment:
# docker run -it --rm -v $(pwd):/workspace sfml-xo:2.5.1
# docker run -it --rm -v $(pwd):/workspace sfml-xo:3.0.0

# Build in container:
# docker run --rm -v $(pwd):/workspace sfml-xo:2.5.1 bash -c "cd build && cmake .. && make"
