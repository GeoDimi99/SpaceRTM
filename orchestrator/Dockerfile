FROM ubuntu:24.04

# Install dependencies
RUN apt-get update 
RUN apt-get install -y ca-certificates curl
RUN install -m 0755 -d /etc/apt/keyrings
RUN curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
RUN chmod a+r /etc/apt/keyrings/docker.asc

RUN echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
  tee /etc/apt/sources.list.d/docker.list > /dev/null

RUN apt-get update && apt-get install -y build-essential \
                                        libmemcached-dev \
                                        libcurl4-openssl-dev \
                                        rapidjson-dev \
                                        docker-ce-cli
# Set working directory
WORKDIR /usr/src/app


# Copy all the files 
COPY . .

# Compile the code
RUN make build

CMD ["./bin/main"]
