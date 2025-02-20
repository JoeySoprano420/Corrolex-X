#!/bin/bash

# Compile script for individual Corrolex-X files

if [ $# -eq 0 ]; then
    echo "Usage: $0 <source_file>"
    exit 1
fi

source_file=$1
output_file=${source_file%.corx}.o

# Compiler and flags
CC="corx"
CFLAGS="-O2 -Wall"

# Compile
$CC $CFLAGS -c $source_file -o $output_file

echo "Compilation of $source_file complete."
