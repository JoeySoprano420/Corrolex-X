#!/bin/bash

# Execution script for Corrolex-X binary

if [ ! -f bin/corrolex-x ]; then
    echo "Error: Binary not found. Please build the project first."
    exit 1
fi

# Run the binary
./bin/corrolex-x

echo "Execution complete."
