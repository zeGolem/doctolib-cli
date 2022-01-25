#!/bin/sh

set -ex;

clang++ \
	-O3 -std=c++20 -lcurl \
	src/*.cpp src/**/*.cpp \
	-o doctolib-cli;

