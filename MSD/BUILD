#!/bin/bash

g++ -g calc_msd.cpp -o calc_msd.o -c
g++ -g read_xyz.cpp -o read_xyz.o -c
g++ -g msd_time.cpp -o msd_time.o -c

g++ -g -pedantic -Wall -Wextra -o msd calc_msd.o read_xyz.o msd_time.o -lm

# cp msd ~/infiltration/
cp msd ../
