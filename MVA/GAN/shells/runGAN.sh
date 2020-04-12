#!/bin/bash
shopt -s expand_aliases

#queueID=$1

shift
shift
shift
shift
shift

cd /nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/MVA/GAN
source /nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/MVA/GAN/setup_keras.sh

python angularGAN.py

#############################################
#############################################
#count=0
#if test $count -eq $queueID ; then
#	./run_loop sig $i $j $k $region $l $m
#fi
#count=$((count+1))
