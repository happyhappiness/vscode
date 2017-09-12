@@ -158,11 +158,17 @@ typedef struct redisObject {
     int refcount;
 } robj;
 
+typedef struct redisDb {
+    dict *dict;
+    dict *expires;
+    int id;
+} redisDb;
+
 /* With multiplexing we need to take per-clinet state.
  * Clients are taken in a liked list. */
 typedef struct redisClient {
     int fd;
-    dict *dict;
+    redisDb *db;
     int dictid;
     sds querybuf;
     robj *argv[REDIS_MAX_ARGS];
@@ -185,7 +191,7 @@ struct saveparam {
 struct redisServer {
     int port;
     int fd;
-    dict **dict;
+    redisDb *db;
     dict *sharingpool;
     unsigned int sharingpoolsize;
     long long dirty;            /* changes to DB from the last save */
@@ -276,6 +282,9 @@ static robj *createStringObject(char *ptr, size_t len);
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 static robj *tryObjectSharing(robj *o);
+static int removeExpire(redisDb *db, robj *key);
+static int expireIfNeeded(redisDb *db, robj *key);
+static int deleteIfVolatile(redisDb *db, robj *key);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -324,6 +333,7 @@ static void lremCommand(redisClient *c);
 static void infoCommand(redisClient *c);
 static void mgetCommand(redisClient *c);
 static void monitorCommand(redisClient *c);
+static void expireCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -378,6 +388,7 @@ static struct redisCommand cmdTable[] = {
     {"sort",sortCommand,-2,REDIS_CMD_INLINE},
     {"info",infoCommand,1,REDIS_CMD_INLINE},
     {"monitor",monitorCommand,1,REDIS_CMD_INLINE},
+    {"expire",expireCommand,3,REDIS_CMD_INLINE},
     {NULL,NULL,0,0}
 };
 
@@ -628,16 +639,16 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* If the percentage of used slots in the HT reaches REDIS_HT_MINFILL
      * we resize the hash table to save memory */
     for (j = 0; j < server.dbnum; j++) {
-        size = dictGetHashTableSize(server.dict[j]);
-        used = dictGetHashTableUsed(server.dict[j]);
+        size = dictSlots(server.db[j].dict);
+        used = dictSize(server.db[j].dict);
         if (!(loops % 5) && used > 0) {
             redisLog(REDIS_DEBUG,"DB %d: %d keys in %d slots HT.",j,used,size);
             /* dictPrintStats(server.dict); */
         }
         if (size && used && size > REDIS_HT_MINSLOTS &&
             (used*100/size < REDIS_HT_MINFILL)) {
             redisLog(REDIS_NOTICE,"The hash table %d is too sparse, resize it...",j);
-            dictResize(server.dict[j]);
+            dictResize(server.db[j].dict);
             redisLog(REDIS_NOTICE,"Hash table %d resized.",j);
         }
     }
@@ -648,7 +659,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             listLength(server.clients)-listLength(server.slaves),
             listLength(server.slaves),
             server.usedmemory,
-            dictGetHashTableUsed(server.sharingpool));
+            dictSize(server.sharingpool));
     }
 
     /* Close connections of timedout clients */
@@ -787,18 +798,21 @@ static void initServer() {
     server.objfreelist = listCreate();
     createSharedObjects();
     server.el = aeCreateEventLoop();
-    server.dict = zmalloc(sizeof(dict*)*server.dbnum);
+    server.db = zmalloc(sizeof(redisDb)*server.dbnum);
     server.sharingpool = dictCreate(&setDictType,NULL);
     server.sharingpoolsize = 1024;
-    if (!server.dict || !server.clients || !server.slaves || !server.monitors || !server.el || !server.objfreelist)
+    if (!server.db || !server.clients || !server.slaves || !server.monitors || !server.el || !server.objfreelist)
         oom("server initialization"); /* Fatal OOM */
     server.fd = anetTcpServer(server.neterr, server.port, server.bindaddr);
     if (server.fd == -1) {
         redisLog(REDIS_WARNING, "Opening TCP port: %s", server.neterr);
         exit(1);
     }
-    for (j = 0; j < server.dbnum; j++)
-        server.dict[j] = dictCreate(&hashDictType,NULL);
+    for (j = 0; j < server.dbnum; j++) {
+        server.db[j].dict = dictCreate(&hashDictType,NULL);
+        server.db[j].expires = dictCreate(&setDictType,NULL);
+        server.db[j].id = j;
+    }
     server.cronloops = 0;
     server.bgsaveinprogress = 0;
     server.lastsave = time(NULL);
@@ -814,8 +828,10 @@ static void initServer() {
 static void emptyDb() {
     int j;
 
-    for (j = 0; j < server.dbnum; j++)
-        dictEmpty(server.dict[j]);
+    for (j = 0; j < server.dbnum; j++) {
+        dictEmpty(server.db[j].dict);
+        dictEmpty(server.db[j].expires);
+    }
 }
 
 /* I agree, this is a very rudimental way to load a configuration...
@@ -1150,9 +1166,9 @@ static int processCommand(redisClient *c) {
     dirty = server.dirty;
     cmd->proc(c);
     if (server.dirty-dirty != 0 && listLength(server.slaves))
-        replicationFeedSlaves(server.slaves,cmd,c->dictid,c->argv,c->argc);
+        replicationFeedSlaves(server.slaves,cmd,c->db->id,c->argv,c->argc);
     if (listLength(server.monitors))
-        replicationFeedSlaves(server.monitors,cmd,c->dictid,c->argv,c->argc);
+        replicationFeedSlaves(server.monitors,cmd,c->db->id,c->argv,c->argc);
     server.stat_numcommands++;
 
     /* Prepare the client for the next command */
@@ -1310,8 +1326,7 @@ static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mas
 static int selectDb(redisClient *c, int id) {
     if (id < 0 || id >= server.dbnum)
         return REDIS_ERR;
-    c->dict = server.dict[id];
-    c->dictid = id;
+    c->db = &server.db[id];
     return REDIS_OK;
 }
 
@@ -1413,14 +1428,6 @@ static robj *createSetObject(void) {
     return createObject(REDIS_SET,d);
 }
 
-#if 0
-static robj *createHashObject(void) {
-    dict *d = dictCreate(&hashDictType,NULL);
-    if (!d) oom("dictCreate");
-    return createObject(REDIS_SET,d);
-}
-#endif
-
 static void freeStringObject(robj *o) {
     sdsfree(o->ptr);
 }
@@ -1462,7 +1469,7 @@ static robj *tryObjectSharing(robj *o) {
     struct dictEntry *de;
     unsigned long c;
 
-    if (server.shareobjects == 0) return o;
+    if (o == NULL || server.shareobjects == 0) return o;
 
     assert(o->type == REDIS_STRING);
     de = dictFind(server.sharingpool,o);
@@ -1479,7 +1486,7 @@ static robj *tryObjectSharing(robj *o) {
          * shared we increment its count, everytime there is a miss we
          * recrement the counter of a random object. If this object reaches
          * zero we remove the object and put the current object instead. */
-        if (dictGetHashTableUsed(server.sharingpool) >=
+        if (dictSize(server.sharingpool) >=
                 server.sharingpoolsize) {
             de = dictGetRandomKey(server.sharingpool);
             assert(de != NULL);
@@ -1502,6 +1509,26 @@ static robj *tryObjectSharing(robj *o) {
     }
 }
 
+static robj *lookupKey(redisDb *db, robj *key) {
+    dictEntry *de = dictFind(db->dict,key);
+    return de ? dictGetEntryVal(de) : NULL;
+}
+
+static robj *lookupKeyRead(redisDb *db, robj *key) {
+    expireIfNeeded(db,key);
+    return lookupKey(db,key);
+}
+
+static robj *lookupKeyWrite(redisDb *db, robj *key) {
+    deleteIfVolatile(db,key);
+    return lookupKey(db,key);
+}
+
+static int deleteKey(redisDb *db, robj *key) {
+    if (dictSize(db->expires)) dictDelete(db->expires,key);
+    return dictDelete(db->dict,key) == DICT_OK;
+}
+
 /*============================ DB saving/loading ============================ */
 
 static int rdbSaveType(FILE *fp, unsigned char type) {
@@ -1604,8 +1631,8 @@ static int rdbSave(char *filename) {
     }
     if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
     for (j = 0; j < server.dbnum; j++) {
-        dict *d = server.dict[j];
-        if (dictGetHashTableUsed(d) == 0) continue;
+        dict *d = server.db[j].dict;
+        if (dictSize(d) == 0) continue;
         di = dictGetIterator(d);
         if (!di) {
             fclose(fp);
@@ -1645,7 +1672,7 @@ static int rdbSave(char *filename) {
                 dictEntry *de;
 
                 if (!set) oom("dictGetIteraotr");
-                if (rdbSaveLen(fp,dictGetHashTableUsed(set)) == -1) goto werr;
+                if (rdbSaveLen(fp,dictSize(set)) == -1) goto werr;
                 while((de = dictNext(di)) != NULL) {
                     robj *eleobj = dictGetEntryKey(de);
 
@@ -1785,7 +1812,7 @@ static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
         case REDIS_RDB_ENC_INT8:
         case REDIS_RDB_ENC_INT16:
         case REDIS_RDB_ENC_INT32:
-            return rdbLoadIntegerObject(fp,len);
+            return tryObjectSharing(rdbLoadIntegerObject(fp,len));
         default:
             assert(0!=0);
         }
@@ -1806,7 +1833,7 @@ static int rdbLoad(char *filename) {
     uint32_t dbid;
     int type;
     int retval;
-    dict *d = server.dict[0];
+    dict *d = server.db[0].dict;
     char buf[1024];
     int rdbver;
     fp = fopen(filename,"r");
@@ -1838,7 +1865,7 @@ static int rdbLoad(char *filename) {
                 redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
                 exit(1);
             }
-            d = server.dict[dbid];
+            d = server.db[dbid].dict;
             continue;
         }
         /* Read key */
@@ -1916,10 +1943,10 @@ static void echoCommand(redisClient *c) {
 static void setGenericCommand(redisClient *c, int nx) {
     int retval;
 
-    retval = dictAdd(c->dict,c->argv[1],c->argv[2]);
+    retval = dictAdd(c->db->dict,c->argv[1],c->argv[2]);
     if (retval == DICT_ERR) {
         if (!nx) {
-            dictReplace(c->dict,c->argv[1],c->argv[2]);
+            dictReplace(c->db->dict,c->argv[1],c->argv[2]);
             incrRefCount(c->argv[2]);
         } else {
             addReply(c,shared.czero);
@@ -1930,6 +1957,7 @@ static void setGenericCommand(redisClient *c, int nx) {
         incrRefCount(c->argv[2]);
     }
     server.dirty++;
+    removeExpire(c->db,c->argv[1]);
     addReply(c, nx ? shared.cone : shared.ok);
 }
 
@@ -1942,14 +1970,11 @@ static void setnxCommand(redisClient *c) {
 }
 
 static void getCommand(redisClient *c) {
-    dictEntry *de;
-    
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    robj *o = lookupKeyRead(c->db,c->argv[1]);
+
+    if (o == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_STRING) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -1961,17 +1986,14 @@ static void getCommand(redisClient *c) {
 }
 
 static void mgetCommand(redisClient *c) {
-    dictEntry *de;
     int j;
   
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-1));
     for (j = 1; j < c->argc; j++) {
-        de = dictFind(c->dict,c->argv[j]);
-        if (de == NULL) {
+        robj *o = lookupKeyRead(c->db,c->argv[j]);
+        if (o == NULL) {
             addReply(c,shared.nullbulk);
         } else {
-            robj *o = dictGetEntryVal(de);
-            
             if (o->type != REDIS_STRING) {
                 addReply(c,shared.nullbulk);
             } else {
@@ -1984,17 +2006,14 @@ static void mgetCommand(redisClient *c) {
 }
 
 static void incrDecrCommand(redisClient *c, int incr) {
-    dictEntry *de;
     long long value;
     int retval;
     robj *o;
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
         value = 0;
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_STRING) {
             value = 0;
         } else {
@@ -2006,9 +2025,10 @@ static void incrDecrCommand(redisClient *c, int incr) {
 
     value += incr;
     o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-    retval = dictAdd(c->dict,c->argv[1],o);
+    retval = dictAdd(c->db->dict,c->argv[1],o);
     if (retval == DICT_ERR) {
-        dictReplace(c->dict,c->argv[1],o);
+        dictReplace(c->db->dict,c->argv[1],o);
+        removeExpire(c->db,c->argv[1]);
     } else {
         incrRefCount(c->argv[1]);
     }
@@ -2039,7 +2059,7 @@ static void decrbyCommand(redisClient *c) {
 /* ========================= Type agnostic commands ========================= */
 
 static void delCommand(redisClient *c) {
-    if (dictDelete(c->dict,c->argv[1]) == DICT_OK) {
+    if (deleteKey(c->db,c->argv[1])) {
         server.dirty++;
         addReply(c,shared.cone);
     } else {
@@ -2048,13 +2068,7 @@ static void delCommand(redisClient *c) {
 }
 
 static void existsCommand(redisClient *c) {
-    dictEntry *de;
-    
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL)
-        addReply(c,shared.czero);
-    else
-        addReply(c,shared.cone);
+    addReply(c,lookupKeyRead(c->db,c->argv[1]) ? shared.cone : shared.czero);
 }
 
 static void selectCommand(redisClient *c) {
@@ -2069,8 +2083,11 @@ static void selectCommand(redisClient *c) {
 
 static void randomkeyCommand(redisClient *c) {
     dictEntry *de;
-    
-    de = dictGetRandomKey(c->dict);
+   
+    while(1) {
+        de = dictGetRandomKey(c->db->dict);
+        if (expireIfNeeded(c->db,dictGetEntryKey(de)) == 0) break;
+    }
     if (de == NULL) {
         addReply(c,shared.crlf);
     } else {
@@ -2088,20 +2105,23 @@ static void keysCommand(redisClient *c) {
     int numkeys = 0, keyslen = 0;
     robj *lenobj = createObject(REDIS_STRING,NULL);
 
-    di = dictGetIterator(c->dict);
+    di = dictGetIterator(c->db->dict);
     if (!di) oom("dictGetIterator");
     addReply(c,lenobj);
     decrRefCount(lenobj);
     while((de = dictNext(di)) != NULL) {
         robj *keyobj = dictGetEntryKey(de);
+
         sds key = keyobj->ptr;
         if ((pattern[0] == '*' && pattern[1] == '\0') ||
             stringmatchlen(pattern,plen,key,sdslen(key),0)) {
-            if (numkeys != 0)
-                addReply(c,shared.space);
-            addReply(c,keyobj);
-            numkeys++;
-            keyslen += sdslen(key);
+            if (expireIfNeeded(c->db,keyobj) == 0) {
+                if (numkeys != 0)
+                    addReply(c,shared.space);
+                addReply(c,keyobj);
+                numkeys++;
+                keyslen += sdslen(key);
+            }
         }
     }
     dictReleaseIterator(di);
@@ -2111,7 +2131,7 @@ static void keysCommand(redisClient *c) {
 
 static void dbsizeCommand(redisClient *c) {
     addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",dictGetHashTableUsed(c->dict)));
+        sdscatprintf(sdsempty(),":%lu\r\n",dictSize(c->db->dict)));
 }
 
 static void lastsaveCommand(redisClient *c) {
@@ -2120,15 +2140,13 @@ static void lastsaveCommand(redisClient *c) {
 }
 
 static void typeCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     char *type;
-    
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
         type = "+none";
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         switch(o->type) {
         case REDIS_STRING: type = "+string"; break;
         case REDIS_LIST: type = "+list"; break;
@@ -2175,7 +2193,6 @@ static void shutdownCommand(redisClient *c) {
 }
 
 static void renameGenericCommand(redisClient *c, int nx) {
-    dictEntry *de;
     robj *o;
 
     /* To use the same key as src and dst is probably an error */
@@ -2184,24 +2201,24 @@ static void renameGenericCommand(redisClient *c, int nx) {
         return;
     }
 
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nokeyerr);
         return;
     }
-    o = dictGetEntryVal(de);
     incrRefCount(o);
-    if (dictAdd(c->dict,c->argv[2],o) == DICT_ERR) {
+    deleteIfVolatile(c->db,c->argv[2]);
+    if (dictAdd(c->db->dict,c->argv[2],o) == DICT_ERR) {
         if (nx) {
             decrRefCount(o);
             addReply(c,shared.czero);
             return;
         }
-        dictReplace(c->dict,c->argv[2],o);
+        dictReplace(c->db->dict,c->argv[2],o);
     } else {
         incrRefCount(c->argv[2]);
     }
-    dictDelete(c->dict,c->argv[1]);
+    deleteKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,nx ? shared.cone : shared.ok);
 }
@@ -2215,21 +2232,19 @@ static void renamenxCommand(redisClient *c) {
 }
 
 static void moveCommand(redisClient *c) {
-    dictEntry *de;
-    robj *o, *key;
-    dict *src, *dst;
+    robj *o;
+    redisDb *src, *dst;
     int srcid;
 
     /* Obtain source and target DB pointers */
-    src = c->dict;
-    srcid = c->dictid;
+    src = c->db;
+    srcid = c->db->id;
     if (selectDb(c,atoi(c->argv[2]->ptr)) == REDIS_ERR) {
         addReply(c,shared.outofrangeerr);
         return;
     }
-    dst = c->dict;
-    c->dict = src;
-    c->dictid = srcid;
+    dst = c->db;
+    selectDb(c,srcid); /* Back to the source DB */
 
     /* If the user is moving using as target the same
      * DB as the source DB it is probably an error. */
@@ -2239,48 +2254,45 @@ static void moveCommand(redisClient *c) {
     }
 
     /* Check if the element exists and get a reference */
-    de = dictFind(c->dict,c->argv[1]);
-    if (!de) {
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (!o) {
         addReply(c,shared.czero);
         return;
     }
 
     /* Try to add the element to the target DB */
-    key = dictGetEntryKey(de);
-    o = dictGetEntryVal(de);
-    if (dictAdd(dst,key,o) == DICT_ERR) {
+    deleteIfVolatile(dst,c->argv[1]);
+    if (dictAdd(dst->dict,c->argv[1],o) == DICT_ERR) {
         addReply(c,shared.czero);
         return;
     }
-    incrRefCount(key);
+    incrRefCount(c->argv[1]);
     incrRefCount(o);
 
     /* OK! key moved, free the entry in the source DB */
-    dictDelete(src,c->argv[1]);
+    deleteKey(src,c->argv[1]);
     server.dirty++;
     addReply(c,shared.cone);
 }
 
 /* =================================== Lists ================================ */
 static void pushGenericCommand(redisClient *c, int where) {
     robj *lobj;
-    dictEntry *de;
     list *list;
-    
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+
+    lobj = lookupKeyWrite(c->db,c->argv[1]);
+    if (lobj == NULL) {
         lobj = createListObject();
         list = lobj->ptr;
         if (where == REDIS_HEAD) {
             if (!listAddNodeHead(list,c->argv[2])) oom("listAddNodeHead");
         } else {
             if (!listAddNodeTail(list,c->argv[2])) oom("listAddNodeTail");
         }
-        dictAdd(c->dict,c->argv[1],lobj);
+        dictAdd(c->db->dict,c->argv[1],lobj);
         incrRefCount(c->argv[1]);
         incrRefCount(c->argv[2]);
     } else {
-        lobj = dictGetEntryVal(de);
         if (lobj->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
             return;
@@ -2306,15 +2318,14 @@ static void rpushCommand(redisClient *c) {
 }
 
 static void llenCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     list *l;
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.czero);
         return;
     } else {
-        robj *o = dictGetEntryVal(de);
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2325,15 +2336,13 @@ static void llenCommand(redisClient *c) {
 }
 
 static void lindexCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     int index = atoi(c->argv[2]->ptr);
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2354,15 +2363,13 @@ static void lindexCommand(redisClient *c) {
 }
 
 static void lsetCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     int index = atoi(c->argv[2]->ptr);
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nokeyerr);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2386,14 +2393,12 @@ static void lsetCommand(redisClient *c) {
 }
 
 static void popGenericCommand(redisClient *c, int where) {
-    dictEntry *de;
-    
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    robj *o;
+
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nullbulk);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2428,16 +2433,14 @@ static void rpopCommand(redisClient *c) {
 }
 
 static void lrangeCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
-    
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nullmultibulk);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2477,16 +2480,14 @@ static void lrangeCommand(redisClient *c) {
 }
 
 static void ltrimCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     int start = atoi(c->argv[2]->ptr);
     int end = atoi(c->argv[3]->ptr);
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nokeyerr);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2528,14 +2529,12 @@ static void ltrimCommand(redisClient *c) {
 }
 
 static void lremCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.nokeyerr);
     } else {
-        robj *o = dictGetEntryVal(de);
-        
         if (o->type != REDIS_LIST) {
             addReply(c,shared.wrongtypeerr);
         } else {
@@ -2570,16 +2569,14 @@ static void lremCommand(redisClient *c) {
 /* ==================================== Sets ================================ */
 
 static void saddCommand(redisClient *c) {
-    dictEntry *de;
     robj *set;
 
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    set = lookupKeyWrite(c->db,c->argv[1]);
+    if (set == NULL) {
         set = createSetObject();
-        dictAdd(c->dict,c->argv[1],set);
+        dictAdd(c->db->dict,c->argv[1],set);
         incrRefCount(c->argv[1]);
     } else {
-        set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
             return;
@@ -2595,15 +2592,12 @@ static void saddCommand(redisClient *c) {
 }
 
 static void sremCommand(redisClient *c) {
-    dictEntry *de;
+    robj *set;
 
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    set = lookupKeyWrite(c->db,c->argv[1]);
+    if (set == NULL) {
         addReply(c,shared.czero);
     } else {
-        robj *set;
-
-        set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
             return;
@@ -2618,15 +2612,12 @@ static void sremCommand(redisClient *c) {
 }
 
 static void sismemberCommand(redisClient *c) {
-    dictEntry *de;
+    robj *set;
 
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    set = lookupKeyRead(c->db,c->argv[1]);
+    if (set == NULL) {
         addReply(c,shared.czero);
     } else {
-        robj *set;
-
-        set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
             return;
@@ -2639,29 +2630,28 @@ static void sismemberCommand(redisClient *c) {
 }
 
 static void scardCommand(redisClient *c) {
-    dictEntry *de;
+    robj *o;
     dict *s;
     
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
         addReply(c,shared.czero);
         return;
     } else {
-        robj *o = dictGetEntryVal(de);
         if (o->type != REDIS_SET) {
             addReply(c,shared.wrongtypeerr);
         } else {
             s = o->ptr;
             addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
-                dictGetHashTableUsed(s)));
+                dictSize(s)));
         }
     }
 }
 
 static int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
     dict **d1 = (void*) s1, **d2 = (void*) s2;
 
-    return dictGetHashTableUsed(*d1)-dictGetHashTableUsed(*d2);
+    return dictSize(*d1)-dictSize(*d2);
 }
 
 static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
@@ -2674,15 +2664,15 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     if (!dv) oom("sinterCommand");
     for (j = 0; j < setsnum; j++) {
         robj *setobj;
-        dictEntry *de;
-        
-        de = dictFind(c->dict,setskeys[j]);
-        if (!de) {
+
+        setobj = dstkey ?
+                    lookupKeyWrite(c->db,setskeys[j]) :
+                    lookupKeyRead(c->db,setskeys[j]);
+        if (!setobj) {
             zfree(dv);
             addReply(c,shared.nokeyerr);
             return;
         }
-        setobj = dictGetEntryVal(de);
         if (setobj->type != REDIS_SET) {
             zfree(dv);
             addReply(c,shared.wrongtypeerr);
@@ -2707,8 +2697,8 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         /* If we have a target key where to store the resulting set
          * create this key with an empty set inside */
         dstset = createSetObject();
-        dictDelete(c->dict,dstkey);
-        dictAdd(c->dict,dstkey,dstset);
+        deleteKey(c->db,dstkey);
+        dictAdd(c->db->dict,dstkey,dstset);
         incrRefCount(dstkey);
     }
 
@@ -2754,7 +2744,8 @@ static void sinterstoreCommand(redisClient *c) {
 }
 
 static void flushdbCommand(redisClient *c) {
-    dictEmpty(c->dict);
+    dictEmpty(c->db->dict);
+    dictEmpty(c->db->expires);
     addReply(c,shared.ok);
     rdbSave(server.dbfilename);
 }
@@ -2775,20 +2766,18 @@ redisSortOperation *createSortOperation(int type, robj *pattern) {
 
 /* Return the value associated to the key with a name obtained
  * substituting the first occurence of '*' in 'pattern' with 'subst' */
-robj *lookupKeyByPattern(dict *dict, robj *pattern, robj *subst) {
+robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     char *p;
     sds spat, ssub;
     robj keyobj;
     int prefixlen, sublen, postfixlen;
-    dictEntry *de;
     /* Expoit the internal sds representation to create a sds string allocated on the stack in order to make this function faster */
     struct {
         long len;
         long free;
         char buf[REDIS_SORTKEY_MAX+1];
     } keyname;
 
-
     spat = pattern->ptr;
     ssub = subst->ptr;
     if (sdslen(spat)+sdslen(ssub)-1 > REDIS_SORTKEY_MAX) return NULL;
@@ -2808,10 +2797,8 @@ robj *lookupKeyByPattern(dict *dict, robj *pattern, robj *subst) {
     keyobj.type = REDIS_STRING;
     keyobj.ptr = ((char*)&keyname)+(sizeof(long)*2);
 
-    de = dictFind(dict,&keyobj);
     /* printf("lookup '%s' => %p\n", keyname.buf,de); */
-    if (!de) return NULL;
-    return dictGetEntryVal(de);
+    return lookupKeyRead(db,&keyobj);
 }
 
 /* sortCompare() is used by qsort in sortCommand(). Given that qsort_r with
@@ -2856,7 +2843,6 @@ static int sortCompare(const void *s1, const void *s2) {
 /* The SORT command is the most complex command in Redis. Warning: this code
  * is optimized for speed and a bit less for readability */
 static void sortCommand(redisClient *c) {
-    dictEntry *de;
     list *operations;
     int outputlen = 0;
     int desc = 0, alpha = 0;
@@ -2867,12 +2853,11 @@ static void sortCommand(redisClient *c) {
     redisSortObject *vector; /* Resulting vector to sort */
 
     /* Lookup the key to sort. It must be of the right types */
-    de = dictFind(c->dict,c->argv[1]);
-    if (de == NULL) {
+    sortval = lookupKeyRead(c->db,c->argv[1]);
+    if (sortval == NULL) {
         addReply(c,shared.nokeyerr);
         return;
     }
-    sortval = dictGetEntryVal(de);
     if (sortval->type != REDIS_SET && sortval->type != REDIS_LIST) {
         addReply(c,shared.wrongtypeerr);
         return;
@@ -2937,7 +2922,7 @@ static void sortCommand(redisClient *c) {
     /* Load the sorting vector with all the objects to sort */
     vectorlen = (sortval->type == REDIS_LIST) ?
         listLength((list*)sortval->ptr) :
-        dictGetHashTableUsed((dict*)sortval->ptr);
+        dictSize((dict*)sortval->ptr);
     vector = zmalloc(sizeof(redisSortObject)*vectorlen);
     if (!vector) oom("allocating objects vector for SORT");
     j = 0;
@@ -2975,7 +2960,7 @@ static void sortCommand(redisClient *c) {
             if (sortby) {
                 robj *byval;
 
-                byval = lookupKeyByPattern(c->dict,sortby,vector[j].obj);
+                byval = lookupKeyByPattern(c->db,sortby,vector[j].obj);
                 if (!byval || byval->type != REDIS_STRING) continue;
                 if (alpha) {
                     vector[j].u.cmpobj = byval;
@@ -3020,7 +3005,7 @@ static void sortCommand(redisClient *c) {
         }
         while(ln) {
             redisSortOperation *sop = ln->value;
-            robj *val = lookupKeyByPattern(c->dict,sop->pattern,
+            robj *val = lookupKeyByPattern(c->db,sop->pattern,
                 vector[j].obj);
 
             if (sop->type == REDIS_SORT_GET) {
@@ -3080,6 +3065,85 @@ static void infoCommand(redisClient *c) {
     addReply(c,shared.crlf);
 }
 
+static void monitorCommand(redisClient *c) {
+    /* ignore MONITOR if aleady slave or in monitor mode */
+    if (c->flags & REDIS_SLAVE) return;
+
+    c->flags |= (REDIS_SLAVE|REDIS_MONITOR);
+    c->slaveseldb = 0;
+    if (!listAddNodeTail(server.monitors,c)) oom("listAddNodeTail");
+    addReply(c,shared.ok);
+}
+
+/* ================================= Expire ================================= */
+static int removeExpire(redisDb *db, robj *key) {
+    if (dictDelete(db->expires,key) == DICT_OK) {
+        return 1;
+    } else {
+        return 0;
+    }
+}
+
+static int setExpire(redisDb *db, robj *key, time_t when) {
+    if (dictAdd(db->expires,key,(void*)when) == DICT_ERR) {
+        return 0;
+    } else {
+        incrRefCount(key);
+        return 1;
+    }
+}
+
+static int expireIfNeeded(redisDb *db, robj *key) {
+    time_t when;
+    dictEntry *de;
+
+    /* No expire? return ASAP */
+    if (dictSize(db->expires) == 0 ||
+       (de = dictFind(db->expires,key)) == NULL) return 0;
+
+    /* Lookup the expire */
+    when = (time_t) dictGetEntryVal(de);
+    if (time(NULL) <= when) return 0;
+
+    /* Delete the key */
+    dictDelete(db->expires,key);
+    return dictDelete(db->dict,key) == DICT_OK;
+}
+
+static int deleteIfVolatile(redisDb *db, robj *key) {
+    dictEntry *de;
+
+    /* No expire? return ASAP */
+    if (dictSize(db->expires) == 0 ||
+       (de = dictFind(db->expires,key)) == NULL) return 0;
+
+    /* Delete the key */
+    dictDelete(db->expires,key);
+    return dictDelete(db->dict,key) == DICT_OK;
+}
+
+static void expireCommand(redisClient *c) {
+    dictEntry *de;
+    int seconds = atoi(c->argv[2]->ptr);
+
+    de = dictFind(c->db->dict,c->argv[1]);
+    if (de == NULL) {
+        addReply(c,shared.czero);
+        return;
+    }
+    if (seconds <= 0) {
+        addReply(c, shared.czero);
+        return;
+    } else {
+        time_t when = time(NULL)+seconds;
+        if (setExpire(c->db,c->argv[1],when))
+            addReply(c,shared.cone);
+        else
+            addReply(c,shared.czero);
+        return;
+    }
+}
+
 /* =============================== Replication  ============================= */
 
 /* Send the whole output buffer syncronously to the slave. This a general operation in theory, but it is actually useful only for replication. */
@@ -3280,16 +3344,6 @@ static int syncWithMaster(void) {
     return REDIS_OK;
 }
 
-static void monitorCommand(redisClient *c) {
-    /* ignore MONITOR if aleady slave or in monitor mode */
-    if (c->flags & REDIS_SLAVE) return;
-
-    c->flags |= (REDIS_SLAVE|REDIS_MONITOR);
-    c->slaveseldb = 0;
-    if (!listAddNodeTail(server.monitors,c)) oom("listAddNodeTail");
-    addReply(c,shared.ok);
-}
-
 /* =================================== Main! ================================ */
 
 static void daemonize(void) {