/*Materialized table*/
materialize(initPacket,infinity,infinity,keys(2,3,4:str)). /*Input packets at hosts*/
materialize(recvPacket,infinity,infinity,keys(2,3,4:str)). /*Received packets at hosts*/
materialize(link,infinity,infinity,keys(2)). /*Links between routers and other devices*/
materialize(flowEntry,infinity,infinity,keys(2)). /*Links between routers and other devices*/

/* Provenance tables*/
materialize(ruleExec, infinity, infinity, keys(2:cid,5,6:cid)).
materialize(prov, infinity, infinity, keys(2:cid,3,4:cid)).


/* Forward a packet*/
prov_rs1_1 epacketTemp(@RLOC, Next, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist) :-
    packet(@Node, SrcAdd, DstAdd, Data, PreLoc, PreRID),
    flowEntry(@Node, DstAdd, Next),
    link(@Node, Next),
    PID2 := f_sha1(((("packet"+ Node)+ SrcAdd)+ DstAdd)+ Data),
    List := f_append(PID2),
    PID3 := f_sha1((("flowEntry"+ Node)+ DstAdd)+ Next),
    List3 := f_append(PID3),
    List := f_concat(List, List3),
    PID4 := f_sha1(("link"+ Node)+ Next),
    List4 := f_append(PID4),
    List := f_concat(List, List4),
    RLOC := Node,
    R := "rs1",
    RID := f_sha1((R+ RLOC)+ List),
    PreLoclist := f_append(PreLoc),
    PreRIDlist := f_append(PreRID),
    PreInfolist := f_concat(PreLoclist, PreRIDlist).

prov_rs1_2 ruleExec(@RLOC, RID, R, List, PreLoc, PreRID) :-
    epacketTemp(@RLOC, Next, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist),
    PreLoc := f_first(PreInfolist),
    Remainlist := f_removeFirst(PreInfolist),
    PreRID := f_first(Remainlist).

prov_rs1_3 packet(@Next, SrcAdd, DstAdd, Data, RLOC, RID) :-
    epacketTemp(@RLOC, Next, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist).

/* Packet initialization*/
prov_rh1_1 epacketTemp(@RLOC, Next, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist) :-
    initPacket(@Node, SrcAdd, DstAdd, Data),
    link(@Node, Next),
    PID2 := f_sha1(((("initPacket"+ Node)+ SrcAdd)+ DstAdd)+ Data),
    List := f_append(PID2),
    PID3 := f_sha1(("linkhr"+ Node)+ Next),
    List3 := f_append(PID3),
    List := f_concat(List, List3),
    PreLoc := RLOC,
    PreLoclist := f_append(PreLoc),
    PreRID := f_sha1("NULL"),
    PreRIDlist := f_append(PreRID),
    RLOC := Node,
    R := "rh1",
    RID := f_sha1((R+ RLOC)+ List),
    PreInfolist := f_concat(PreLoclist, PreRIDlist).

/*Receive a packet*/
prov_rh2_1 erecvPacketTemp(@RLOC, Node, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist) :-
    packet(@Node, SrcAdd, DstAdd, Data, PreLoc, PreRID),
    DstAdd == Node,
    PID2 := f_sha1(((("packet"+ Node)+ SrcAdd)+ DstAdd)+ Data),
    List := f_append(PID2),
    RLOC := Node,
    R := "rh2",
    RID := f_sha1((R+ RLOC)+ List),
    PreLoclist := f_append(PreLoc),
    PreRIDlist := f_append(PreRID),
    PreInfolist := f_concat(PreLoclist, PreRIDlist).

prov_rh2_2 ruleExec(@RLOC, RID, R, List, PreLoc, PreRID) :-
    erecvPacketTemp(@RLOC, Node, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist),
    PreLoc := f_first(PreInfolist),
    Remainlist := f_removeFirst(PreInfolist),
    PreRID := f_first(Remainlist).

prov_rh2_3 recvPacket(@Node, SrcAdd, DstAdd, Data, RID, RLOC) :-
    erecvPacketTemp(@RLOC, Node, SrcAdd, DstAdd, Data, RID, R, List, PreInfolist).

prov_rh2_5 prov(@Node, VID, RLOC, RID) :-
    recvPacket(@Node, SrcAdd, DstAdd, Data, RID, RLOC),
    VID := f_sha1(((("recvPacket"+ Node)+ SrcAdd)+ DstAdd)+ Data).
