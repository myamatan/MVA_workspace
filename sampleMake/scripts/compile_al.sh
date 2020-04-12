#!/bin/bash
#source /nfs_home/home1/myamatan/data3/ZVana/rcSetup.sh

g++ `root-config --cflags --libs` run_loop.cc -o run_loop
