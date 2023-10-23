#!/bin/bash

# Trap SIGINT (CTRL+C) and SIGTERM signals to ensure graceful exit
# This will kill the Python server process before exiting the script
trap "echo 'Stopping server...'; kill $!; exit" SIGINT SIGTERM

# Run the program with the profiler
CPUPROFILE=out.prof ./main

# Convert the profile data to flamegraph format
/usr/local/bin/pprof --collapsed ./main out.prof > out.collapsed

# Generate the flame graph
/tmp/FlameGraph/flamegraph.pl out.collapsed > out.svg

# Start the Python HTTP server in the background to serve the flamegraph
# This allows users to access the flamegraph via http://<container_ip>:8080/out.svg
python3 -m http.server 8080 &

# Keep the script alive to maintain the background server
wait $!
