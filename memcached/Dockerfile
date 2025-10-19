FROM memcached:latest

USER root

# Install Python and pymemcache safely via apt
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pymemcache \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /usr/src/app

# Copy initialization script and entrypoint
COPY init-memcached.py .
COPY docker-entrypoint.sh /usr/local/bin/

# Ensure entrypoint is executable
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

# Use memcache user for runtime security
USER memcache

# Define entrypoint (runs memcached + init script)
ENTRYPOINT ["docker-entrypoint.sh"]


