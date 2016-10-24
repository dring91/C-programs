#!/bin/bash

g++ -g chain_stats.cpp -o chain_stats.o -c
# g++ -g read_xyz.cpp -o read_xyz.o -c
g++ -g read_dump.cpp -o read_dump.o -c
g++ -g unwrap.cpp -o unwrap.o -c
g++ -g write_traj.cpp -o write_traj.o -c
# g++ -g rg_re_com.cpp -o rg_re_com.o -c
g++ -g distributions.cpp -o distributions.o -c

g++ -g -pedantic -Wall -Wextra -o rg chain_stats.o read_dump.o write_traj.o unwrap.o distributions.o -lm

cp rg ../
