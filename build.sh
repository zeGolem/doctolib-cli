#!/bin/sh

set -ex;

clang++ \
	-O3 -std=c++20 -lcurl \
	utils/curl.cpp doctolib/doctolib_api.cpp main.cpp \
	-o doctolib-cli;

