#!/bin/bash

./consumer

./producer a
./producer b
./producer c
./producer d # this would produce output to file_d, for example

sleep 5

./producer
./producer
./producer
./producer

