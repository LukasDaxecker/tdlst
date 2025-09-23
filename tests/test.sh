#!/bin/bash

g++ ../tdlst.cpp -o tdlst
if [ $? -eq 0 ]; then
    echo "Compiled tdlst"
else
    echo "Failed compiling tdlst"
    exit 0
fi

g++ ./tests.cpp -o tests
if [ $? -eq 0 ]; then
    echo "Compiled tests"
else
    echo "Failed compiling tests"
    exit 0
fi

./tests
if [ $? -eq 0 ]; then
    echo "Executed tests"
else
    echo "Failed tests"
    exit 0
fi
