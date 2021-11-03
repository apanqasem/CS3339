#!/bin/sh
#
# @author: Apan Qasem
# @date: 03/31/21
#
# Calculate LLC miss rates for a program. Program is expected to a accept a single
# command-line argument sets its input size. Program is run with input sizes 500 to 4000 in
# steps of 500. Values are coded. Can be easily modified. 
#

# name of executable 
prog=$1

# block size 
block=$2

[ -x $prog ] || { echo "Could not find exectutable $prog. Exiting ..."; exit 0; }

i=500
while [ $i -le 4000 ]; do 
	LLC=`perf stat -e LLC-loads,LLC-load-misses ./$prog $i $block 2>&1 | grep hits | awk '{print $4}'` 
	echo "$i\t$LLC"
  i=$(($i+500))
done
