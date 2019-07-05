#!/usr/bin/env bash

# Setup
set -e

BUILD_DIR=`pwd`/build/cpu1
EXE_DIR=$BUILD_DIR/exe

echo Builld = $BUILD_DIR
echo Exe = $EXE_DIR

# Env variables
. ./setvars.sh

# Build
pushd $BUILD_DIR
# make distclean || fail "make distclean"
make config || fail "make config"
make || fail "make"

# Run
pushd $EXE_DIR
sudo ./core-linux.bin --reset PO
popd
popd
