#!/bin/bash

g++ -g calc_msd.cpp -o calc_msd.o -c
#g++ -g read_xyz.cpp -o read_xyz.o -c
g++ -g read_dump.cpp -o read_dump.o -c
g++ -g msd_time.cpp -o msd_time.o -c
g++ -g unwrap.cpp -o unwrap.o -c

g++ -g -pedantic -Wall -Wextra -o msd calc_msd.o read_xyz.o msd_time.o unwrap.o -lm

# cp msd ~/infiltration/
cp msd ../
