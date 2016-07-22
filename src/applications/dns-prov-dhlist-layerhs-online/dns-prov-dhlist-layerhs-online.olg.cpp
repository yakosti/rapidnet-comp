materialize(url,infinity,infinity,keys(1,2:str,3,4:int32)).
materialize(address_record,infinity,infinity,keys(1,2:str,3)).
materialize(name_server,infinity,infinity,keys(1,2:str,3:str)).
materialize(results,infinity,infinity,keys(1,2:str,3,4:int32)).

materialize(programID,infinity,infinity,keys(2:str)). /*Allow the user to specify program ID*/

/* Provenance tables*/
materialize(ruleExec, infinity, infinity, keys(4:list)).
materialize(equiHashTable,infinity,infinity,keys(2:str)). /*Hash table for equivalence detection*/
materialize(provHashTable,infinity,infinity,keys(3)). /*Hash table for provenance query*/
materialize(provLink,infinity,infinity,keys(2:str,3:cid,4:cid,5,6:cid)).
materialize(resultsQry, infinity, infinity, keys(2:cid)).


/*Program for initialization of rule table*/
prov_r1_1 eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag) :-
  requestProv(@X,URL,HOST,REQUESTID,Tag),
    name_server(@X,DOMAIN,SERVER),
    address_record(@X,SERVER,ADDR),
    f_indexof(URL,DOMAIN)!=-1,
    URL!=DOMAIN,
    List := f_empty(),
    PID1 := f_sha1(("name_server"+X)+DOMAIN+SERVER),
    List1 := f_append(PID1),
    List := f_concat(List,List1),
    PID2 := f_sha1(("address_record"+X)+SERVER+ADDR),
    List2 := f_append(PID2),
    List := f_concat(List,List2),
    RLOC := X,
    R := "r2",
    RID := f_sha1(R+List).

prov_r1_2 eRequestCount(@RLOC, RID, R, List, a_COUNT<*>) :-
    eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag),
    ruleExec(@RLOC, RID, R, List).

prov_r1_3 ruleExec(@RLOC, RID, R, List) :-
    eRequestCount(@RLOC, RID, R, List, Rcount),
    Rcount == 0.

prov_r1_4 provLink(@RLOC, ProgID, RID, CurLhash, Preloc, PreRID, PreLhash) :-
   eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag),
   Preloc := f_first(Tag),
   TempTag1 := f_removeFirst(Tag),
   PreRID := f_first(TempTag1),
   TempTag2 := f_removeFirst(TempTag1),
   PreLhash := f_first(TempTag2),
   TempTag3 := f_removeFirst(TempTag2),
   ProgID := f_first(TempTag3),
   CurLhash := f_sha1(PreLhash + RID).

prov_r1_5 requestProv(@ADDR,URL,HOST,REQUESTID,NewTag) :-
    eRequestTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag),
    TempNewTag1 := f_removeFirst(Tag),
    TempNewTag2 := f_removeFirst(TempNewTag1),
    PreLhash := f_first(TempNewTag2),
    CurLhash := f_sha1(PreLhash + RID),
    CurLhashlist := f_append(CurLhash),
    TempNewTag3 := f_removeFirst(TempNewTag2),
    RIDlist := f_append(RID),
    Loclist := f_append(RLOC),
    TempNewTag4 := f_concat(CurLhashlist, TempNewTag3),
    TempNewTag5 := f_concat(RIDlist, TempNewTag4),
    NewTag := f_concat(Loclist, TempNewTag5).

r1 request(@ADDR,URL,HOST,REQUESTID,PIDHash) :-
       request(@X,URL,HOST,REQUESTID,PIDHash),
       name_server(@X,DOMAIN,SERVER),
          address_record(@X,SERVER,ADDR),f_indexof(URL,DOMAIN)!=-1,
       URL!=DOMAIN.

/*Hash on equivalence attributes*/
prov_ri1 urlHash(@X,URL,HOST,REQUESTID,PIDequi,ProgID) :-
            url(@X,URL,HOST,REQUESTID),
     programID(@X,URL,ProgID),
     PIDequi := f_sha1(""+X+URL).

prov_ri2 urlCount(@X,URL,HOST,REQUESTID,PIDequi,ProgID,a_COUNT<*>) :-
     urlHash(@X,URL,HOST,REQUESTID,PIDequi,ProgID),
     equiHashTable(@X,URL,PIDequi).

prov_ri3 equiHashTable(@X,URL,PIDequi) :-
     urlCount(@X,URL,HOST,REQUESTID,PIDequi,PIDCount),
            PIDCount == 0.

r103 request(@X,URL,HOST,REQUESTID,PIDHash) :-
     urlCount(@X,URL,HOST,REQUESTID,PIDequi,ProgID,PIDCount),
  PIDCount != 0,
  PIDev := f_sha1("url"+X+URL+HOST+REQUESTID),
  PIDequiHash := f_append(PIDequi),
      PIDevHash := f_append(PIDev),
  ProgIDlist := f_concat(PIDequiHash, PIDevHash),
  PIDHash1 := f_concat(PIDequiHash, PIDevHash),
                PIDHash := f_concat(PIDHash1, ProgIDlist).

prov_r2_1 eRequestTemp(@RLOC,X,URL,HOST,REQUESTID,RID,R,List,Tag) :-
  urlCount(@X,URL,HOST,REQUESTID,PIDequi,ProgID,PIDCount),
  name_server(@X,DOMAIN,SERVER),
  address_record(@X,SERVER,ADDR),
     f_indexof(URL,DOMAIN)!=-1,
  URL!=DOMAIN,
  PIDCount == 0,
  List := f_empty(),
    RLOC := X,
    R := "r1",
    RID := f_sha1(R+List),
  Equilist := f_append(PIDequi),
  PIDev := f_sha1("url"+X+URL+HOST+REQUESTID),
  Evlist := f_append(PIDev),
  ProgIDlist := f_append(ProgID),
     InitLhashlist := f_append("NULL"),
     InitProvNode := RLOC,
     InitProvNodelist := f_append(InitProvNode),
     InitProvHash := f_sha1("NULL"),
     InitProvHashlist := f_append(InitProvHash),
     TempTag1 := f_concat(InitProvNodelist, InitProvHashlist),
     TempTag2 := f_concat(TempTag1, InitLhashlist),
     TempTag3 := f_concat(TempTag2, ProgIDlist),
            TempTag4 := f_concat(TempTag3, Evlist),
     Tag := f_concat(TempTag4, Equilist).


prov_r3_1 eresultsTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag) :-
  requestProv(@X,URL,HOST,REQUESTID,Tag),
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
    RID := f_sha1(R+List).

prov_r3_2 eRequestCount(@RLOC, RID, R, List, a_COUNT<*>) :-
  eresultsTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag),
  ruleExec(@RLOC, RID, R, List).

prov_r3_3 ruleExec(@RLOC, RID, R, List) :-
     eRequestCount(@RLOC, RID, R, List, Rcount),
     Rcount == 0.


prov_r3_4 provLink(@RLOC, ProgID, RID, CurLhash, Preloc, PreRID, PreLhash) :-
   eresultsTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag),
    Preloc := f_first(Tag),
    TempTag1 := f_removeFirst(Tag),
    PreRID := f_first(TempTag1),
    TempTag2 := f_removeFirst(TempTag1),
    PreLhash := f_first(TempTag2),
    TempTag3 := f_removeFirst(TempTag2),
    ProgID := f_first(TempTag3),
    CurLhash := f_sha1(PreLhash + RID).


prov_r3_5 resultsProv(@ADDR, URL, HOST, REQUESTID, NewTag) :-
    eresultsTemp(@RLOC,ADDR,URL,HOST,REQUESTID,RID,R,List,Tag),
    TempNewTag1 := f_removeFirst(Tag),
    TempNewTag2 := f_removeFirst(TempNewTag1),
    PreLhash := f_first(TempNewTag2),
    CurLhash := f_sha1(PreLhash + RID),
    CurLhashlist := f_append(CurLhash),
    TempNewTag3 := f_removeFirst(TempNewTag2),
    RIDlist := f_append(RID),
    Loclist := f_append(RLOC),
    TempNewTag4 := f_concat(CurLhashlist, TempNewTag3),
    TempNewTag5 := f_concat(RIDlist, TempNewTag4),
    NewTag := f_concat(Loclist, TempNewTag5).


prov_r3_6 results(@ADDR,URL,HOST,REQUESTID):-
   resultsProv(@ADDR,URL,HOST,REQUESTID, NewTag).

ro1 provHashTable(@ADDR, ProvID,PreLoc, PreRID, PreLhash) :-
    resultsProv(@ADDR,URL,HOST,REQUESTID,Tag),
    PreLoc := f_first(Tag),
    RemainTag1 := f_removeFirst(Tag),
    PreRID := f_first(RemainTag1),
    RemainTag2 := f_removeFirst(RemainTag1),
    PreLhash := f_first(RemainTag2),
    RemainTag3 := f_removeFirst(RemainTag2),
     ProgID := f_first(RemainTag3),
    RemainTag4 := f_removeFirst(RemainTag3),
    EvHash := f_first(RemainTag4),
    RemainTag5 := f_removeFirst(RemainTag4),
    EqHash := f_first(RemainTag5),
    ProvID := f_sha1(""+ProgID+EqHash).

ro2 resultsQry(@ADDR, PID, ProvID, EvHash) :-
    resultsProv(@ADDR,URL,HOST,REQUESTID,Tag),
           PID := f_sha1("results" + ADDR + URL + HOST + REQUESTID),
    PreLoc := f_first(Tag),
    RemainTag1 := f_removeFirst(Tag),
    PreRID := f_first(RemainTag1),
    RemainTag2 := f_removeFirst(RemainTag1),
    PreLhash := f_first(RemainTag2),
    RemainTag3 := f_removeFirst(RemainTag2),
    ProgID := f_first(RemainTag3),
    RemainTag4 := f_removeFirst(RemainTag3),
    EvHash := f_first(RemainTag4),
    RemainTag5 := f_removeFirst(RemainTag4),
    EqHash := f_first(RemainTag5),
    ProvID := f_sha1(ProgID+""+EqHash).

/* Execution of original rh2*/
rh2 results(@ADDR,URL,HOST,REQUESTID) :-
        request(@X,URL,HOST,REQUESTID),
 name_server(@X,DOMAIN,SERVER),
    address_record(@X,SERVER,ADDR),
 f_indexof(URL,DOMAIN)!=-1,
 URL==DOMAIN.

rho3 resultsQry(@ADDR, PID, ProvID, PIDev) :-
 request(@X,URL,HOST,REQUESTID),
 name_server(@X,DOMAIN,SERVER),
    address_record(@X,SERVER,ADDR),
 f_indexof(URL,DOMAIN)!=-1,
 URL==DOMAIN,
        PID := f_sha1("results" + ADDR + URL + HOST + REQUESTID),
 PIDequi := f_first(PIDHash),
 PIDHash1 := f_removeFirst(PIDHash),
 PIDev := f_first(PIDHash1),
 PIDHash2 := f_removeFirst(PIDHash1),
 ProgID := f_first(PIDHash2),
 ProvID := f_sha1(ProgID+""+PIDequi).
