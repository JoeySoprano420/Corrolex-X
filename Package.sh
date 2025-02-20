#!/bin/bash

# Packaging script for Corrolex-X Project

echo "Starting packaging process..."

# Clean previous packages
rm -rf package

# Package project
make package

echo "Packaging process complete. Package available in 'package' directory."
