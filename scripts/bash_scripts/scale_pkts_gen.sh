#!/bin/bash
# Argument 1: name of the test file
# Argument 2: packet number
# Argument 3: name of the output file
# Argument 4: store path for the output of the experiment

DIRECTORY="$4/*"
storeDir="$4"
mkdir -p $storeDir

outputFile="$3"
for pktNum in {0..200..20}
do
    rm -f $DIRECTORY
    # Run the experiment
    nohup ./waf --run "$1 --hostPairs=$2 --packetNum=$pktNum --storePath=$4/"
    # Calculate the average size of all files
    count=0
    sum=0
    for file in $DIRECTORY
    do
	fsize=$(stat --printf="%s" "$file")
	((sum+=fsize))
	((count+=1))
    done
    fileNum=$count
    avg=$((sum/fileNum))
    printf "%s \t %s\n" "$pktNum" "$avg">> "$outputFile"
done