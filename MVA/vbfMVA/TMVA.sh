#!/bin/bash
#g++ `root-config --cflags --libs` -lTMVA TMVAClassification.C -o TMVAClassification

#python angularMVA.py ggH Resolved 700 ad
#python angularMVA.py ggH Merged 2000 ad
#python angularMVA.py VBFH Resolved 700 ad
#python angularMVA.py VBFH Merged 2000 ad

shopt -s expand_aliases

#python angularMVA.py ggH Resolved 700 d
#python scoreCheck.py ggH Resolved 700 d sig

queueID=$1

# regions
#sigTypeList=('ggH' 'HVT' 'RSG' 'VBFH' 'VBFHVT')
sigTypeList=('ggH' 'VBFH')
regimeList=('Resolved' 'Merged')
regionList=('_SRCR_') 
region=${regionList[$2]}
massList=(700 2000)
#massList=(300 700 1000 2000 3000)
#massList=(300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2200 2400 2600 2800 3000 3500 4000 4500 5000 '300to800' '300to1400' '900to3000' '900to5000') # spin-0,1,2, 31*3  loop
#massList=('300to800' '900to3000' '900to4000' '900to5000') # spin-0,1,2, 31*3  loop
#mcList=('a' 'd' 'ad') 
mcList=('ad') 

# Option (default : 'None')
#nameOption='None'

depthList=(3 10 20)
treeList=(300 1000 2000)
#n_train_bkg=(400000 600000 800000 0)
n_train_bkg=(0)

shift
shift
shift
shift
shift
shift
shift
shift

cd /nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/MVA/angularMVA
source /nfs_home/home1/myamatan/data3/angularAna/MVA_workspace/MVA/angularMVA/setup.sh

count=0
for i in ${sigTypeList[@]}
do 
	for j in ${regimeList[@]}
	do
		for k in ${massList[@]}
		do
			for l in ${mcList[@]}
			do
        			if test $count -eq $queueID ; then
					echo python angularMVA.py $i $j $k $l
        			fi
        			count=$((count+1))
			done
		done
	done
done
