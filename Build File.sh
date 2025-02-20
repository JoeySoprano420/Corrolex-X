#!/bin/bash

# Build script for Corrolex-X Project

echo "Starting build process..."

# Clean previous builds
make clean

# Build project
make all

echo "Build process complete."
