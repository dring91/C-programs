#!/bin/bash

g++ -g bond_lengths.cpp -o bond_lengths.o -c
g++ -g read_dump.cpp -o read_dump.o -c
g++ -g unwrap.cpp -o unwrap.o -c
g++ -g write_traj.cpp -o write_traj.o -c

g++ -g -pedantic -Wall -Wextra -o blen bond_lengths.o read_dump.o write_traj.o unwrap.o -lm

cp blen ../
