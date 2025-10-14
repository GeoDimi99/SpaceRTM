FROM ubuntu:24.04

# Install dependencies
RUN apt-get update && apt-get install -y build-essential libmemcached
# Set working directory
WORKDIR /usr/src/app


# Copy all the files 
COPY . .

# Compile the code
RUN make