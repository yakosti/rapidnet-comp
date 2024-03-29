/*Materialized table*/
materialize(initPacket,infinity,infinity,keys(2,3,4:str)). /*Input packets at hosts*/
materialize(recvPacket,infinity,infinity,keys(2,3,4:str)). /*Received packets at hosts*/
materialize(link,infinity,infinity,keys(2)). /*Links connecting network devices*/
materialize(flowEntry,infinity,infinity,keys(2)). /*Links between routers and other devices*/

/*Packet forwarding*/
rs1 packet(@Next, SrcAdd, DstAdd, Data) :-
        packet(@Node, SrcAdd, DstAdd, Data),
 flowEntry(@Node, DstAdd, Next),
 link(@Node, Next).

/*Packet initialization*/
rh1 packet(@Next, SrcAdd, DstAdd, Data) :-
 initPacket(@Node, SrcAdd, DstAdd, Data),
 link(@Node, Next).

/*Packet receipt*/
rh2 recvPacket(@Node, SrcAdd, DstAdd, Data) :-
 packet(@Node, SrcAdd, DstAdd, Data),
 DstAdd == Node.
