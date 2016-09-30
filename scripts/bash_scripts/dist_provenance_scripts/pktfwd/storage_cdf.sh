# Aim : To run the experiment to measure cdf of rate of growth of storage

#!/bin/bash
# Argument 1: name of the test file
# Argument 2: number of hostPairs
# Argument 3: name of the output file
# Argument 4: store path for the output of the experiment
# Argument 5: path Length
# Argument 6: Size of the payload
# Argument 7: Number of packets to be sent
# Argumwnr 8: Lower limit for experiment 
# Argument 9: Upper Limit for experiment
# Argument 10: Interval length for the experiment
# Argument 11: Mode of the experiment online, rmitm and nocomp


DIRECTORY="$4/*"

outputFile="$3"

rm -f outputFile
declare -a previousStorage=( $(for i in {1..100}; do echo 0; done) )
declare -a avgRate=( $(for i in {1..100}; do echo 0; done) )
intervalTime=10
stopTime=500
#printf "%s \t %s\n" "0" "0">> "$outputFile"
for interval in {1..100..10}
do
    rm -f $DIRECTORY
    # Run the experiment
     echo "Interval $interval starts at $(date +"%T")" >> "$4/../timer.log"
    nohup ./waf --run "$1 --hostPairs=$2 --packetNum=$7 --storePath=$4/ --pathLength=$5 --dataSize=$6 --stopTime=$interval --mode=${11}"
    echo "Interval $interval ends at $(date +"%T")" >> "$4/../timer.log"
    for file in $DIRECTORY
    do
	baseName="$(basename $file)"
	fsize=$(stat --printf="%s" "$file")
	currentRate=$((($fsize-${previousStorage[$(($baseName-1))]})/$intervalTime))
	avgRate[$(($baseName-1))]=$((${avgRate[$(($baseName-1))]}+$currentRate))
    done
done
for i in {1..100}
do
    printf "%s \t %s\n" "$i" "$((${avgRate[$(($i-1))]}/10))">> "$outputFile"
done