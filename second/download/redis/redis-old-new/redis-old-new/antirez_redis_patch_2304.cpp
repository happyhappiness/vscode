@@ -182,6 +182,8 @@
 /* Anti-warning macro... */
 #define REDIS_NOTUSED(V) ((void) V)
 
+#define ZSKIPLIST_MAXLEVEL 32 /* Should be enough for 2^32 elements */
+#define ZSKIPLIST_P 0.25      /* Skiplist P = 1/4 */
 
 /*================================= Data types ============================== */
 
@@ -305,11 +307,27 @@ typedef struct _redisSortOperation {
     robj *pattern;
 } redisSortOperation;
 
+/* ZSETs use a specialized version of Skiplists */
+
+typedef struct zskiplistNode {
+    struct zskiplistNode **forward;
+    double score;
+    robj *obj;
+} zskiplistNode;
+
+typedef struct zskiplist {
+    struct zskiplistNode *header;
+    long length;
+    int level;
+} zskiplist;
+
 typedef struct zset {
     dict *dict;
-    /* tree *tree; */
+    zskiplist *zsl;
 } zset;
 
+/* Our shared "common" objects */
+
 struct sharedObjectsStruct {
     robj *crlf, *ok, *err, *emptybulk, *czero, *cone, *pong, *space,
     *colon, *nullbulk, *nullmultibulk,
@@ -351,6 +369,7 @@ static void setupSigSegvAction(void);
 static void rdbRemoveTempFile(pid_t childpid);
 static size_t stringObjectLen(robj *o);
 static void processInputBuffer(redisClient *c);
+static zskiplist *zslCreate(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -639,13 +658,11 @@ static void redisLog(int level, const char *fmt, ...) {
  * keys and radis objects as values (objects can hold SDS strings,
  * lists, sets). */
 
-#if 0
 static void dictVanillaFree(void *privdata, void *val)
 {
     DICT_NOTUSED(privdata);
     zfree(val);
 }
-#endif
 
 static int sdsDictKeyCompare(void *privdata, const void *key1,
         const void *key2)
@@ -723,7 +740,6 @@ static dictType setDictType = {
     NULL                       /* val destructor */
 };
 
-#if 0
 static dictType zsetDictType = {
     dictEncObjHash,            /* hash function */
     NULL,                      /* key dup */
@@ -732,7 +748,6 @@ static dictType zsetDictType = {
     dictRedisObjectDestructor, /* key destructor */
     dictVanillaFree            /* val destructor */
 };
-#endif
 
 static dictType hashDictType = {
     dictObjHash,                /* hash function */
@@ -955,7 +970,6 @@ static void createSharedObjects(void) {
 
 static void appendServerSaveParams(time_t seconds, int changes) {
     server.saveparams = zrealloc(server.saveparams,sizeof(struct saveparam)*(server.saveparamslen+1));
-    if (server.saveparams == NULL) oom("appendServerSaveParams");
     server.saveparams[server.saveparamslen].seconds = seconds;
     server.saveparams[server.saveparamslen].changes = changes;
     server.saveparamslen++;
@@ -1012,8 +1026,6 @@ static void initServer() {
     server.el = aeCreateEventLoop();
     server.db = zmalloc(sizeof(redisDb)*server.dbnum);
     server.sharingpool = dictCreate(&setDictType,NULL);
-    if (!server.db || !server.clients || !server.slaves || !server.monitors || !server.el || !server.objfreelist)
-        oom("server initialization"); /* Fatal OOM */
     server.fd = anetTcpServer(server.neterr, server.port, server.bindaddr);
     if (server.fd == -1) {
         redisLog(REDIS_WARNING, "Opening TCP port: %s", server.neterr);
@@ -1264,7 +1276,7 @@ static void glueReplyBuffersIfNeeded(redisClient *c) {
         }
         /* Now the output buffer is empty, add the new single element */
         o = createObject(REDIS_STRING,sdsnewlen(buf,totlen));
-        if (!listAddNodeTail(c->reply,o)) oom("listAddNodeTail");
+        listAddNodeTail(c->reply,o);
     }
 }
 
@@ -1514,7 +1526,6 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
         outv = static_outv;
     } else {
         outv = zmalloc(sizeof(robj*)*(argc*2+1));
-        if (!outv) oom("replicationFeedSlaves");
     }
     
     for (j = 0; j < argc; j++) {
@@ -1602,12 +1613,10 @@ static void processInputBuffer(redisClient *c) {
                 return;
             }
             argv = sdssplitlen(query,sdslen(query)," ",1,&argc);
-            if (argv == NULL) oom("sdssplitlen");
             sdsfree(query);
 
             if (c->argv) zfree(c->argv);
             c->argv = zmalloc(sizeof(robj*)*argc);
-            if (c->argv == NULL) oom("allocating arguments list for client");
 
             for (j = 0; j < argc; j++) {
                 if (sdslen(argv[j])) {
@@ -1711,15 +1720,15 @@ static redisClient *createClient(int fd) {
     c->lastinteraction = time(NULL);
     c->authenticated = 0;
     c->replstate = REDIS_REPL_NONE;
-    if ((c->reply = listCreate()) == NULL) oom("listCreate");
+    c->reply = listCreate();
     listSetFreeMethod(c->reply,decrRefCount);
     listSetDupMethod(c->reply,dupClientReplyValue);
     if (aeCreateFileEvent(server.el, c->fd, AE_READABLE,
         readQueryFromClient, c, NULL) == AE_ERR) {
         freeClient(c);
         return NULL;
     }
-    if (!listAddNodeTail(server.clients,c)) oom("listAddNodeTail");
+    listAddNodeTail(server.clients,c);
     return c;
 }
 
@@ -1734,7 +1743,7 @@ static void addReply(redisClient *c, robj *obj) {
     } else {
         incrRefCount(obj);
     }
-    if (!listAddNodeTail(c->reply,obj)) oom("listAddNodeTail");
+    listAddNodeTail(c->reply,obj);
 }
 
 static void addReplySds(redisClient *c, sds s) {
@@ -1809,7 +1818,6 @@ static robj *createObject(int type, void *ptr) {
     } else {
         o = zmalloc(sizeof(*o));
     }
-    if (!o) oom("createObject");
     o->type = type;
     o->encoding = REDIS_ENCODING_RAW;
     o->ptr = ptr;
@@ -1824,24 +1832,22 @@ static robj *createStringObject(char *ptr, size_t len) {
 static robj *createListObject(void) {
     list *l = listCreate();
 
-    if (!l) oom("listCreate");
     listSetFreeMethod(l,decrRefCount);
     return createObject(REDIS_LIST,l);
 }
 
 static robj *createSetObject(void) {
     dict *d = dictCreate(&setDictType,NULL);
-    if (!d) oom("dictCreate");
     return createObject(REDIS_SET,d);
 }
 
-#if 0
 static robj *createZsetObject(void) {
-    dict *d = dictCreate(&zsetDictType,NULL);
-    if (!d) oom("dictCreate");
-    return createObject(REDIS_ZSET,d);
+    zset *zs = zmalloc(sizeof(*zs));
+
+    zs->dict = dictCreate(&zsetDictType,NULL);
+    zs->zsl = zslCreate();
+    return createObject(REDIS_ZSET,zs);
 }
-#endif
 
 static void freeStringObject(robj *o) {
     if (o->encoding == REDIS_ENCODING_RAW) {
@@ -2277,7 +2283,6 @@ static int rdbSave(char *filename) {
                 dictIterator *di = dictGetIterator(set);
                 dictEntry *de;
 
-                if (!set) oom("dictGetIteraotr");
                 if (rdbSaveLen(fp,dictSize(set)) == -1) goto werr;
                 while((de = dictNext(di)) != NULL) {
                     robj *eleobj = dictGetEntryKey(de);
@@ -2542,11 +2547,9 @@ static int rdbLoad(char *filename) {
                 if ((ele = rdbLoadStringObject(fp,rdbver)) == NULL) goto eoferr;
                 tryObjectEncoding(ele);
                 if (type == REDIS_LIST) {
-                    if (!listAddNodeTail((list*)o->ptr,ele))
-                        oom("listAddNodeTail");
+                    listAddNodeTail((list*)o->ptr,ele);
                 } else {
-                    if (dictAdd((dict*)o->ptr,ele,NULL) == DICT_ERR)
-                        oom("dictAdd");
+                    dictAdd((dict*)o->ptr,ele,NULL);
                 }
             }
         } else {
@@ -2799,7 +2802,6 @@ static void keysCommand(redisClient *c) {
     robj *lenobj = createObject(REDIS_STRING,NULL);
 
     di = dictGetIterator(c->db->dict);
-    if (!di) oom("dictGetIterator");
     addReply(c,lenobj);
     decrRefCount(lenobj);
     while((de = dictNext(di)) != NULL) {
@@ -2995,9 +2997,9 @@ static void pushGenericCommand(redisClient *c, int where) {
         lobj = createListObject();
         list = lobj->ptr;
         if (where == REDIS_HEAD) {
-            if (!listAddNodeHead(list,c->argv[2])) oom("listAddNodeHead");
+            listAddNodeHead(list,c->argv[2]);
         } else {
-            if (!listAddNodeTail(list,c->argv[2])) oom("listAddNodeTail");
+            listAddNodeTail(list,c->argv[2]);
         }
         dictAdd(c->db->dict,c->argv[1],lobj);
         incrRefCount(c->argv[1]);
@@ -3009,9 +3011,9 @@ static void pushGenericCommand(redisClient *c, int where) {
         }
         list = lobj->ptr;
         if (where == REDIS_HEAD) {
-            if (!listAddNodeHead(list,c->argv[2])) oom("listAddNodeHead");
+            listAddNodeHead(list,c->argv[2]);
         } else {
-            if (!listAddNodeTail(list,c->argv[2])) oom("listAddNodeTail");
+            listAddNodeTail(list,c->argv[2]);
         }
         incrRefCount(c->argv[2]);
     }
@@ -3460,7 +3462,6 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     robj *lenobj = NULL, *dstset = NULL;
     int j, cardinality = 0;
 
-    if (!dv) oom("sinterGenericCommand");
     for (j = 0; j < setsnum; j++) {
         robj *setobj;
 
@@ -3507,7 +3508,6 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
      * the element against all the other sets, if at least one set does
      * not include the element it is discarded */
     di = dictGetIterator(dv[0]);
-    if (!di) oom("dictGetIterator");
 
     while((de = dictNext(di)) != NULL) {
         robj *ele;
@@ -3564,7 +3564,6 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
     robj *dstset = NULL;
     int j, cardinality = 0;
 
-    if (!dv) oom("sunionDiffGenericCommand");
     for (j = 0; j < setsnum; j++) {
         robj *setobj;
 
@@ -3595,7 +3594,6 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
         if (!dv[j]) continue; /* non existing keys are like empty sets */
 
         di = dictGetIterator(dv[j]);
-        if (!di) oom("dictGetIterator");
 
         while((de = dictNext(di)) != NULL) {
             robj *ele;
@@ -3622,7 +3620,6 @@ static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnu
     if (!dstkey) {
         addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
         di = dictGetIterator(dstset->ptr);
-        if (!di) oom("dictGetIterator");
         while((de = dictNext(di)) != NULL) {
             robj *ele;
 
@@ -3667,6 +3664,83 @@ static void sdiffstoreCommand(redisClient *c) {
     sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_DIFF);
 }
 
+/* ==================================== ZSets =============================== */
+
+/* ZSETs are ordered sets using two data structures to hold the same elements
+ * in order to get O(log(N)) INSERT and REMOVE operations into a sorted
+ * data structure.
+ *
+ * The elements are added to an hash table mapping Redis objects to scores.
+ * At the same time the elements are added to a skip list mapping scores
+ * to Redis objects (so objects are sorted by scores in this "view"). */
+
+/* This skiplist implementation is almost a C translation of the original
+ * algorithm described by William Pugh in "Skip Lists: A Probabilistic
+ * Alternative to Balanced Trees", modified in three ways:
+ * a) this implementation allows for repeated values.
+ * b) the comparison is not just by key (our 'score') but by satellite data.
+ * c) there is a back pointer, so it's a doubly linked list with the back
+ * pointers being only at "level 1". This allows to traverse the list
+ * from tail to head, useful for ZREVRANGE. */
+
+static zskiplistNode *zslCreateNode(int level, double score, robj *obj) {
+    zskiplistNode *zn = zmalloc(sizeof(*zn));
+
+    zn->forward = zmalloc(sizeof(zskiplistNode*) * level);
+    zn->score = score;
+    zn->obj = obj;
+    return zn;
+}
+
+static zskiplist *zslCreate(void) {
+    int j;
+    zskiplist *zsl;
+    
+    zsl = zmalloc(sizeof(*zsl));
+    zsl->level = 1;
+    zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL,0,NULL);
+    for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++)
+        zsl->header->forward[j] = NULL;
+    return zsl;
+}
+
+static int zslRandomLevel(void) {
+    int level = 1;
+    while ((random()&0xFFFF) < (ZSKIPLIST_P * 0xFFFF))
+        level += 1;
+    return level;
+}
+
+static void zslInsert(zskiplist *zsl, double score, robj *obj) {
+    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
+    int i, level;
+
+    x = zsl->header;
+    for (i = zsl->level-1; i >= 0; i--) {
+        while (x->forward[i]->score < score)
+            x = x->forward[i];
+        update[i] = x;
+    }
+    x = x->forward[1];
+    /* we assume the key is not already inside, since we allow duplicated
+     * scores, and the re-insertion of score and redis object should never
+     * happpen since the caller of zslInsert() should test in the hash table
+     * if the element is already inside or not. */
+    level = zslRandomLevel();
+    if (level > zsl->level) {
+        for (i = zsl->level; i < level; i++)
+            update[i] = zsl->header;
+        zsl->level = level;
+    }
+    x = zslCreateNode(level,score,obj);
+    for (i = 0; i < level; i++) {
+        x->forward[i] = update[i]->forward[i];
+        update[i]->forward[i] = x;
+    }
+}
+
+/* ========================= Non type-specific commands  ==================== */
+
 static void flushdbCommand(redisClient *c) {
     server.dirty += dictSize(c->db->dict);
     dictEmpty(c->db->dict);
@@ -3683,7 +3757,6 @@ static void flushallCommand(redisClient *c) {
 
 static redisSortOperation *createSortOperation(int type, robj *pattern) {
     redisSortOperation *so = zmalloc(sizeof(*so));
-    if (!so) oom("createSortOperation");
     so->type = type;
     so->pattern = pattern;
     return so;
@@ -3870,7 +3943,6 @@ static void sortCommand(redisClient *c) {
         listLength((list*)sortval->ptr) :
         dictSize((dict*)sortval->ptr);
     vector = zmalloc(sizeof(redisSortObject)*vectorlen);
-    if (!vector) oom("allocating objects vector for SORT");
     j = 0;
     if (sortval->type == REDIS_LIST) {
         list *list = sortval->ptr;
@@ -3890,7 +3962,6 @@ static void sortCommand(redisClient *c) {
         dictEntry *setele;
 
         di = dictGetIterator(set);
-        if (!di) oom("dictGetIterator");
         while((setele = dictNext(di)) != NULL) {
             vector[j].obj = dictGetEntryKey(setele);
             vector[j].u.score = 0;
@@ -4069,7 +4140,7 @@ static void monitorCommand(redisClient *c) {
 
     c->flags |= (REDIS_SLAVE|REDIS_MONITOR);
     c->slaveseldb = 0;
-    if (!listAddNodeTail(server.monitors,c)) oom("listAddNodeTail");
+    listAddNodeTail(server.monitors,c);
     addReply(c,shared.ok);
 }
 
@@ -4309,7 +4380,6 @@ static void syncCommand(redisClient *c) {
              * another slave. Set the right state, and copy the buffer. */
             listRelease(c->reply);
             c->reply = listDup(slave->reply);
-            if (!c->reply) oom("listDup copying slave reply list");
             c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
             redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
@@ -4331,7 +4401,7 @@ static void syncCommand(redisClient *c) {
     c->repldbfd = -1;
     c->flags |= REDIS_SLAVE;
     c->slaveseldb = 0;
-    if (!listAddNodeTail(server.slaves,c)) oom("listAddNodeTail");
+    listAddNodeTail(server.slaves,c);
     return;
 }
 