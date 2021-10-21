#!/bin/bash

if ! [[ -d ../bin/ ]]; then
	mkdir ../bin
    echo "mkdir ../bin"
fi

if ! [[ -d ../build/ ]]; then
	mkdir ../build
    echo "mkdir ../build"
fi
