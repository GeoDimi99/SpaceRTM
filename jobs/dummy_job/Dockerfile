FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y build-essential 

WORKDIR /app/api
COPY api .

RUN make

# Start both applications
# CMD sh -c "/app/api/rtjob -t 1 -p rr -r 1"
