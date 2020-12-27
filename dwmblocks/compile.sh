#! /bin/sh

make clean
CC=clang make
sudo mkdir -p /usr/local/bin/
sudo install -m 0755 dwmblocks /usr/local/bin/dwmblocks
