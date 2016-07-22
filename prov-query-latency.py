import sys

fileName=sys.argv[1];

logFile=open(fileName)

initProvQueryTime=0.0;
recordProvQueryTime=0.0;

numPackets =0.0
for line in logFile:
    if "Inserted initProvQuery[" in line:
        timeStamp = line.split("ns]")[0][1:]
        print timeStamp, line
        initProvQueryTime+=int(timeStamp)
        numPackets+=1
    elif "Sending recordProv[" in line:
        timeStamp = line.split("ns]")[0][1:]
        print timeStamp, line
        recordProvQueryTime+=int(timeStamp)


print "\n"

latency=(recordProvQueryTime-initProvQueryTime)/numPackets
print "Latency ",latency/1000000000,"seconds"
