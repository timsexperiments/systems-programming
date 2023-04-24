FROM ubuntu:latest

# Update package list and install required dependencies (including c and c++ compilers)
RUN apt-get update && apt-get install -y curl wget build-essential
RUN apt-get update --fix-missing

# Install valgrind for use with c amd c++
RUN apt-get install -y valgrind

# Install Go
RUN apt-get install -y wget && \
    wget https://golang.org/dl/go1.20.3.linux-amd64.tar.gz && \
    tar -C /usr/local -xzf go1.20.3.linux-amd64.tar.gz && \
    rm go1.20.3.linux-amd64.tar.gz
ENV PATH $PATH:/usr/local/go/bin
ENV PATH $PATH:/root/go/bin

# Install bazel (bazelisk) and other useful tools
RUN wget https://github.com/bazelbuild/bazelisk/releases/download/v1.8.1/bazelisk-linux-amd64 && \
    chmod +x bazelisk-linux-amd64 && \
    mv bazelisk-linux-amd64 /usr/local/bin/bazel
# Buldifier a tool for formatting bazel
RUN go install github.com/bazelbuild/buildtools/buildifier@latest 

# Install Rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH=/root/.cargo/bin:$PATH

# Install Node.js
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - \
    && apt-get install -y nodejs


# Create symbolic links for python and pip
RUN ln -s /usr/bin/python3 /usr/bin/python && \
    ln -s /usr/bin/pip3 /usr/bin/pip

# Install git
RUN apt-get install -y git

# Set up colorized zsh shell.
RUN echo 'export PS1="\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ "' >> /root/.bashrc

# Install PNPM
RUN npm i -g pnpm

