materialize(url,infinity,infinity,keys(1,2:str,3,4:int32)).
materialize(address_record,infinity,infinity,keys(1,2:str,3)).
materialize(name_server,infinity,infinity,keys(1,2:str,3:str)).
materialize(results,infinity,infinity,keys(1,2:str,3,4:int32)).

/*Provenance table*/
materialize(ruleExec,infinity,infinity,keys(4:list)).
materialize(prov,infinity,infinity,keys(1,2:cid,3:cid,4)).


/*Rule r1, Initialize URL tables ar root*/
prov_r1_1 eRequestTemp(@RLOC,X,URL,HOST,REQUESTID,RID,R,List,PreInfolist) :-
     url(@X,URL,HOST,REQUESTID),
  name_server(@X,DOMAIN,SERVER),
    address_record(@X,SERVER,ADDR),
    f_indexof(URL,DOMAIN)!=-1,
    URL!=DOMAIN,
  List := f_empty(),
  RLOC := X,
     R := "r1",
     RID := f_sha1((R+RLOC)+List),
  PID2 := f_sha1("url"+ X+ URL+ HOST+ REQUESTID),
    List := f_append(PID2),
     PreLoc := X,
     PreLoclist := f_append(PreLoc),
     PreRID := f_sha1("NULL"),
     PreRIDlist := f_append(PreRID),
     PreInfolist := f_concat(PreLoclist, PreRIDlist).

/*Rule r2, traverse the DNS tree*/
prov_r2_1 eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,PreInfoList) :-
  request(@X,URL,HOST,REQUESTID,PreLoc,PreRID),
    name_server(@X,DOMAIN,SERVER),
    address_record(@X,SERVER,ADDR),
    f_indexof(URL,DOMAIN)!=-1,
    URL!=DOMAIN,
    List := f_empty(),
  PID1 := f_sha1("request"+X+URL+HOST+REQUESTID),
  List1 := f_append(PID1),
  List :=f_concat(List,List1),
    PID2 := f_sha1(("name_server"+X)+DOMAIN+SERVER),
    List2 := f_append(PID2),
    List := f_concat(List,List2),
    PID3 := f_sha1(("address_record"+X)+SERVER+ADDR),
    List3 := f_append(PID3),
    List := f_concat(List,List3),
    RLOC := X,
    R := "r2",
    RID := f_sha1((R+RLOC)+List),
                PreLoclist := f_append(PreLoc),
     PreRIDlist := f_append(PreRID),
     PreInfoList := f_concat(PreLoclist, PreRIDlist).

prov_r2_2 ruleExec(@RLOC, RID, R, List, PreLoc, PreRID) :-
    eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,PreInfolist),
    PreLoc := f_first(PreInfolist),
    Remainlist := f_removeFirst(PreInfolist),
    PreRID := f_first(Remainlist).

prov_r2_3 request(@ADDR, URL, HOST, REQUESTID, RLOC, RID) :-
   eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,PreInfoList).

/*Rule r3, Generate the final results*/
prov_r3_1 eResultTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,PreInfolist) :-
   request(@X,URL,HOST,REQUESTID,PreLoc,PreRID),
   name_server(@X,DOMAIN,SERVER),
   address_record(@X,SERVER,ADDR),
   f_indexof(URL,DOMAIN)!=-1,
   URL==DOMAIN,
   PID1:= f_sha1(("request"+X)+URL+HOST+REQUESTID),
   List := f_append(PID1),
   PID2 := f_sha1(("name_server"+X)+DOMAIN+SERVER),
   List2 := f_append(PID2),
   List := f_concat(List,List2),
   PID3 := f_sha1(("address_record"+X)+SERVER+ADDR),
   List3 := f_append(PID3),
   List := f_concat(List,List3),
   RLOC := X,
   R :="r3",
   RID := f_sha1((R+RLOC)+List),
   PreLoclist := f_append(PreLoc),
   PreRIDlist := f_append(PreRID),
   PreInfolist := f_concat(PreLoclist, PreRIDlist).

prov_r3_2 ruleExec(@RLOC, RID, R, List, PreLoc, PreRID) :-
   eResultTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,PreInfolist),
    PreLoc := f_first(PreInfolist),
    Remainlist := f_removeFirst(PreInfolist),
    PreRID := f_first(Remainlist).

prov_r3_3 results(@ADDR, URL, HOST, REQUESTID, RID, RLOC) :-
     eResultTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,PreInfolist).

prov_r3_4 prov(@ADDR, VID ,RID,RLOC):-
   results(@ADDR, URL, HOST, REQUESTID, RID, RLOC),
   VID := f_sha1(("result"+ADDR)+URL+HOST+REQUESTID).
