#!/bin/bash
#g++ `root-config --cflags --libs` run_loop.cc -o run_loop
#./run_loop sig ggF Resolved ggH _SRCR_ 300 a angle
#./run_loop sig VBF Merged VBFH _SRCR_ 1000A2000A3000 ad VBFjets

shopt -s expand_aliases

queueID=$1

# isBkg
isSig=$2

# regions
categList=('ggF') # not in use
regimeList=('Resolved' 'Merged')
#sigTypeList=('ggH' 'HVT' 'RSG' 'VBFH' 'VBFHVT')
sigTypeList=('VBFH' 'VBFHVT')
regionList=('_SRCR_') 
region=${regionList[$3]}
massList=(300 400 500 600 700 800 900 1000
	  1100 1200 1300 1400 1500 1600 1700 1800 1900
	  2000 2200 2400 2600 2800 3000
          3500 4000 4500 5000
          '300to800' '300to1400' '300to3000' '900to3000'
          '300to5000' '900to5000' '300to4000' '900to4000') # spin-0,1,2, 35*3  loop
#massList=('300to1400' '500to3000' '500to4000' '500to5000') # spin-0,1,2, 2*3  loop
massList=(300 700 1000 2000 3000 '300A700A1000A2000' '700A1000A2000A3000') # spin-0,1,2, 2*3  loop
mc=('d')
MVAtype=('VBFjets') #VBFjets angle

# Option (default : '')
#nameOption="None"

shift
shift
shift
shift
shift

cd /nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/sampleMake/
source /nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/sampleMake/setup.sh

count=0
if $isSig ; then
	for i in ${categList[@]}
	do
		for j in ${regimeList[@]}
		do 
			for k in ${sigTypeList[@]}
			do
				for l in ${massList[@]}
				do
					for m in ${mc[@]}
					do
       	 					if test $count -eq $queueID ; then
							./run_loop sig $i $j $k $region $l $m $MVAtype
						fi
						count=$((count+1))
					done
				done
			done
		done
	done
else
	for i in ${categList[@]}
	do
		for j in ${regimeList[@]}
		do 
			for k in ${sigTypeList[@]}
			do
				for m in ${mc[@]}
				do
       					#if test $count -eq $queueID ; then
						./run_loop bkg $i $j $k $region 500 $m $MVAtype
       					#fi
       					count=$((count+1))
				done
			done
		done
	done
fi
#echo $count
