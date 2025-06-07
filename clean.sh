#!/bin/bash

# Directory where the build output is stored
BUILD_DIR="build"

echo "Cleaning build directory: $BUILD_DIR"
rm -rf "$BUILD_DIR"/*

echo "Build directory cleaned."