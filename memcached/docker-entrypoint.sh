#!/bin/bash
set -e

# Start memcached in the background
memcached -u memcache &
MEMCACHED_PID=$!

# Wait for memcached to be ready (check port 11211)
echo "Waiting for memcached to start..."
until nc -z localhost 11211; do
    sleep 0.5
done
echo "Memcached is ready."

# Run initialization script
echo "Running init-memcached.py..."
python3 /usr/src/app/init-memcached.py || echo "Init script failed"

# Keep container running with memcached
wait $MEMCACHED_PID
