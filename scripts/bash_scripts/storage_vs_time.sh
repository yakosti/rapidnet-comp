#!/bin/bash
# Argument 1 : Driver File Name
# Argument 2 : Storage Directory
# Argument 3 : Depth of the DNS Tree
# Argument 4 : Fanout 
# Argument 5 : Output File for results
# Argument 6 : Number of nodes in the DNS tree
# Argument 7 : Mode of Experiment (online, rmitm , nocomp)
# Argument 8 : Lower limit of Experiment
# Argument 9 : Upper limit of Experiment
# Argument 10 : Increment Size
# Argument 11 : Stop Time of the Experiment
# Argument 12 : URL insertion Rate


DIRECTORY="$4/*"

outputFile="$5"

rm -f outputFile

numNodes=100
declare -a previousStorage=( $(for i in {1..101}; do echo 0; done) )
declare -a avgRate=( $(for i in {1..101}; do echo 0; done) )
intervalTime=10
#printf "%s \t %s\n" "0" "0">> "$outputFile"
for interval in {1..100..10}
do
    rm -f $DIRECTORY
    # Run the experiment
    numURLRate=${12}
    numURL=$((numURLRate*interval))
    echo "Interval $interval starts at $(date +"%T")" >> "$2/../timer.log"
    nohup ./waf --run "$1 --storePth=$2/ --depth=$3 --fanout=$4 --stopTime=$interval --numNodes=100 --type=$7 --numURL=$numURL"
    echo "Interval $interval ends at $(date +"%T")" >> "$2/../timer.log"
    #echo "$interval" >> "$4/../timer.log" 
    #nohup ./waf --run "$1 --storePth=$4/ --depth=$2 --fanout=$5 --stopTime=$interval --timedRequests=1 --numNodes=100 --numRequests=$6"
    for file in $DIRECTORY
    do
	fsize=$(stat --printf="%s" "$file")
	((sum+=fsize))
	((count+=1))
    done
    fileNum=$count
    avg=$((sum))
    #/fileNum))
    printf "%s \t %s\n" "$interval" "$avg">> "$outputFile"
done