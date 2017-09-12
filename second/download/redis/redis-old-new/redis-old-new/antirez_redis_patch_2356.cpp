@@ -27,7 +27,7 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#define REDIS_VERSION "0.07"
+#define REDIS_VERSION "0.08"
 
 #include <stdio.h>
 #include <stdlib.h>
@@ -89,6 +89,7 @@
 #define REDIS_CLOSE 1       /* This client connection should be closed ASAP */
 #define REDIS_SLAVE 2       /* This client is a slave server */
 #define REDIS_MASTER 4      /* This client is a master server */
+#define REDIS_MONITOR 8      /* This client is a slave monitor, see MONITOR */
 
 /* Server replication state */
 #define REDIS_REPL_NONE 0   /* No active replication */
@@ -138,7 +139,7 @@ typedef struct redisClient {
     list *reply;
     int sentlen;
     time_t lastinteraction; /* time of the last interaction, used for timeout */
-    int flags; /* REDIS_CLOSE | REDIS_SLAVE */
+    int flags; /* REDIS_CLOSE | REDIS_SLAVE | REDIS_MONITOR */
     int slaveseldb; /* slave selected db, if this client is a slave */
 } redisClient;
 
@@ -154,7 +155,7 @@ struct redisServer {
     dict **dict;
     long long dirty;            /* changes to DB from the last save */
     list *clients;
-    list *slaves;
+    list *slaves, *monitors;
     char neterr[ANET_ERR_LEN];
     aeEventLoop *el;
     int cronloops;              /* number of times the cron function run */
@@ -171,6 +172,7 @@ struct redisServer {
     int maxidletime;
     int dbnum;
     int daemonize;
+    char *pidfile;
     int bgsaveinprogress;
     struct saveparam *saveparams;
     int saveparamslen;
@@ -212,10 +214,10 @@ typedef struct _redisSortOperation {
 } redisSortOperation;
 
 struct sharedObjectsStruct {
-    robj *crlf, *ok, *err, *zerobulk, *nil, *zero, *one, *pong, *space,
-    *minus1, *minus2, *minus3, *minus4,
-    *wrongtypeerr, *nokeyerr, *wrongtypeerrbulk, *nokeyerrbulk,
-    *syntaxerr, *syntaxerrbulk,
+    robj *crlf, *ok, *err, *emptybulk, *czero, *cone, *pong, *space,
+    *colon, *minus1, *nullbulk, *nullmultibulk,
+    *emptymultibulk, *wrongtypeerr, *nokeyerr, *syntaxerr, *sameobjecterr,
+    *outofrangeerr, *plus,
     *select0, *select1, *select2, *select3, *select4,
     *select5, *select6, *select7, *select8, *select9;
 } shared;
@@ -234,7 +236,7 @@ static void addReplySds(redisClient *c, sds s);
 static void incrRefCount(robj *o);
 static int saveDbBackground(char *filename);
 static robj *createStringObject(char *ptr, size_t len);
-static void replicationFeedSlaves(struct redisCommand *cmd, int dictid, robj **argv, int argc);
+static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 
 static void pingCommand(redisClient *c);
@@ -282,6 +284,7 @@ static void sortCommand(redisClient *c);
 static void lremCommand(redisClient *c);
 static void infoCommand(redisClient *c);
 static void mgetCommand(redisClient *c);
+static void monitorCommand(redisClient *c);
 
 /*================================= Globals ================================= */
 
@@ -334,6 +337,7 @@ static struct redisCommand cmdTable[] = {
     {"flushall",flushallCommand,1,REDIS_CMD_INLINE},
     {"sort",sortCommand,-2,REDIS_CMD_INLINE},
     {"info",infoCommand,1,REDIS_CMD_INLINE},
+    {"monitor",monitorCommand,1,REDIS_CMD_INLINE},
     {NULL,NULL,0,0}
 };
 
@@ -656,29 +660,28 @@ static void createSharedObjects(void) {
     shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
     shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
     shared.err = createObject(REDIS_STRING,sdsnew("-ERR\r\n"));
-    shared.zerobulk = createObject(REDIS_STRING,sdsnew("0\r\n\r\n"));
-    shared.nil = createObject(REDIS_STRING,sdsnew("nil\r\n"));
-    shared.zero = createObject(REDIS_STRING,sdsnew("0\r\n"));
-    shared.one = createObject(REDIS_STRING,sdsnew("1\r\n"));
+    shared.emptybulk = createObject(REDIS_STRING,sdsnew("$0\r\n\r\n"));
+    shared.czero = createObject(REDIS_STRING,sdsnew(":0\r\n"));
+    shared.cone = createObject(REDIS_STRING,sdsnew(":1\r\n"));
+    shared.nullbulk = createObject(REDIS_STRING,sdsnew("$-1\r\n"));
+    shared.nullmultibulk = createObject(REDIS_STRING,sdsnew("*-1\r\n"));
+    shared.emptymultibulk = createObject(REDIS_STRING,sdsnew("*0\r\n"));
     /* no such key */
     shared.minus1 = createObject(REDIS_STRING,sdsnew("-1\r\n"));
-    /* operation against key holding a value of the wrong type */
-    shared.minus2 = createObject(REDIS_STRING,sdsnew("-2\r\n"));
-    /* src and dest objects are the same */
-    shared.minus3 = createObject(REDIS_STRING,sdsnew("-3\r\n"));
-    /* out of range argument */
-    shared.minus4 = createObject(REDIS_STRING,sdsnew("-4\r\n"));
     shared.pong = createObject(REDIS_STRING,sdsnew("+PONG\r\n"));
     shared.wrongtypeerr = createObject(REDIS_STRING,sdsnew(
         "-ERR Operation against a key holding the wrong kind of value\r\n"));
-    shared.wrongtypeerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.wrongtypeerr->ptr)+2,shared.wrongtypeerr->ptr));
     shared.nokeyerr = createObject(REDIS_STRING,sdsnew(
         "-ERR no such key\r\n"));
-    shared.nokeyerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.nokeyerr->ptr)+2,shared.nokeyerr->ptr));
     shared.syntaxerr = createObject(REDIS_STRING,sdsnew(
         "-ERR syntax error\r\n"));
-    shared.syntaxerrbulk = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%d\r\n%s",-sdslen(shared.syntaxerr->ptr)+2,shared.syntaxerr->ptr));
+    shared.sameobjecterr = createObject(REDIS_STRING,sdsnew(
+        "-ERR source and destination objects are the same\r\n"));
+    shared.outofrangeerr = createObject(REDIS_STRING,sdsnew(
+        "-ERR index out of range\r\n"));
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
+    shared.colon = createObject(REDIS_STRING,sdsnew(":"));
+    shared.plus = createObject(REDIS_STRING,sdsnew("+"));
     shared.select0 = createStringObject("select 0\r\n",10);
     shared.select1 = createStringObject("select 1\r\n",10);
     shared.select2 = createStringObject("select 2\r\n",10);
@@ -715,6 +718,7 @@ static void initServerConfig() {
     server.bindaddr = NULL;
     server.glueoutputbuf = 1;
     server.daemonize = 0;
+    server.pidfile = "/var/run/redis.pid";
     server.dbfilename = "dump.rdb";
     ResetServerSaveParams();
 
@@ -737,11 +741,12 @@ static void initServer() {
 
     server.clients = listCreate();
     server.slaves = listCreate();
+    server.monitors = listCreate();
     server.objfreelist = listCreate();
     createSharedObjects();
     server.el = aeCreateEventLoop();
     server.dict = zmalloc(sizeof(dict*)*server.dbnum);
-    if (!server.dict || !server.clients || !server.slaves || !server.el || !server.objfreelist)
+    if (!server.dict || !server.clients || !server.slaves || !server.monitors || !server.el || !server.objfreelist)
         oom("server initialization"); /* Fatal OOM */
     server.fd = anetTcpServer(server.neterr, server.port, server.bindaddr);
     if (server.fd == -1) {
@@ -878,6 +883,8 @@ static void loadServerConfig(char *filename) {
             else {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcmp(argv[0],"pidfile") && argc == 2) {
+          server.pidfile = zstrdup(argv[1]);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -918,9 +925,10 @@ static void freeClient(redisClient *c) {
     assert(ln != NULL);
     listDelNode(server.clients,ln);
     if (c->flags & REDIS_SLAVE) {
-        ln = listSearchKey(server.slaves,c);
+        list *l = (c->flags & REDIS_MONITOR) ? server.monitors : server.slaves;
+        ln = listSearchKey(l,c);
         assert(ln != NULL);
-        listDelNode(server.slaves,ln);
+        listDelNode(l,ln);
     }
     if (c->flags & REDIS_MASTER) {
         server.master = NULL;
@@ -1079,7 +1087,9 @@ static int processCommand(redisClient *c) {
     dirty = server.dirty;
     cmd->proc(c);
     if (server.dirty-dirty != 0 && listLength(server.slaves))
-        replicationFeedSlaves(cmd,c->dictid,c->argv,c->argc);
+        replicationFeedSlaves(server.slaves,cmd,c->dictid,c->argv,c->argc);
+    if (listLength(server.monitors))
+        replicationFeedSlaves(server.monitors,cmd,c->dictid,c->argv,c->argc);
     server.stat_numcommands++;
 
     /* Prepare the client for the next command */
@@ -1091,8 +1101,8 @@ static int processCommand(redisClient *c) {
     return 1;
 }
 
-static void replicationFeedSlaves(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
-    listNode *ln = server.slaves->head;
+static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc) {
+    listNode *ln = slaves->head;
     robj *outv[REDIS_MAX_ARGS*4]; /* enough room for args, spaces, newlines */
     int outc = 0, j;
     
@@ -1643,7 +1653,7 @@ static void pingCommand(redisClient *c) {
 }
 
 static void echoCommand(redisClient *c) {
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
         (int)sdslen(c->argv[1]->ptr)));
     addReply(c,c->argv[1]);
     addReply(c,shared.crlf);
@@ -1660,15 +1670,15 @@ static void setGenericCommand(redisClient *c, int nx) {
             dictReplace(c->dict,c->argv[1],c->argv[2]);
             incrRefCount(c->argv[2]);
         } else {
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
             return;
         }
     } else {
         incrRefCount(c->argv[1]);
         incrRefCount(c->argv[2]);
     }
     server.dirty++;
-    addReply(c, nx ? shared.one : shared.ok);
+    addReply(c, nx ? shared.cone : shared.ok);
 }
 
 static void setCommand(redisClient *c) {
@@ -1684,14 +1694,14 @@ static void getCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullbulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_STRING) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(o->ptr)));
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
             addReply(c,o);
             addReply(c,shared.crlf);
         }
@@ -1702,18 +1712,18 @@ static void mgetCommand(redisClient *c) {
     dictEntry *de;
     int j;
   
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",c->argc-1));
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-1));
     for (j = 1; j < c->argc; j++) {
         de = dictFind(c->dict,c->argv[j]);
         if (de == NULL) {
-            addReply(c,shared.minus1);
+            addReply(c,shared.nullbulk);
         } else {
             robj *o = dictGetEntryVal(de);
             
             if (o->type != REDIS_STRING) {
-                addReply(c,shared.minus1);
+                addReply(c,shared.nullbulk);
             } else {
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(o->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
                 addReply(c,o);
                 addReply(c,shared.crlf);
             }
@@ -1751,6 +1761,7 @@ static void incrDecrCommand(redisClient *c, int incr) {
         incrRefCount(c->argv[1]);
     }
     server.dirty++;
+    addReply(c,shared.colon);
     addReply(c,o);
     addReply(c,shared.crlf);
 }
@@ -1778,9 +1789,9 @@ static void decrbyCommand(redisClient *c) {
 static void delCommand(redisClient *c) {
     if (dictDelete(c->dict,c->argv[1]) == DICT_OK) {
         server.dirty++;
-        addReply(c,shared.one);
+        addReply(c,shared.cone);
     } else {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     }
 }
 
@@ -1789,9 +1800,9 @@ static void existsCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL)
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     else
-        addReply(c,shared.one);
+        addReply(c,shared.cone);
 }
 
 static void selectCommand(redisClient *c) {
@@ -1811,6 +1822,7 @@ static void randomkeyCommand(redisClient *c) {
     if (de == NULL) {
         addReply(c,shared.crlf);
     } else {
+        addReply(c,shared.plus);
         addReply(c,dictGetEntryKey(de));
         addReply(c,shared.crlf);
     }
@@ -1841,18 +1853,18 @@ static void keysCommand(redisClient *c) {
         }
     }
     dictReleaseIterator(di);
-    lenobj->ptr = sdscatprintf(sdsempty(),"%lu\r\n",keyslen+(numkeys ? (numkeys-1) : 0));
+    lenobj->ptr = sdscatprintf(sdsempty(),"$%lu\r\n",keyslen+(numkeys ? (numkeys-1) : 0));
     addReply(c,shared.crlf);
 }
 
 static void dbsizeCommand(redisClient *c) {
     addReplySds(c,
-        sdscatprintf(sdsempty(),"%lu\r\n",dictGetHashTableUsed(c->dict)));
+        sdscatprintf(sdsempty(),":%lu\r\n",dictGetHashTableUsed(c->dict)));
 }
 
 static void lastsaveCommand(redisClient *c) {
     addReplySds(c,
-        sdscatprintf(sdsempty(),"%lu\r\n",server.lastsave));
+        sdscatprintf(sdsempty(),":%lu\r\n",server.lastsave));
 }
 
 static void typeCommand(redisClient *c) {
@@ -1861,14 +1873,14 @@ static void typeCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        type = "none";
+        type = "+none";
     } else {
         robj *o = dictGetEntryVal(de);
         
         switch(o->type) {
-        case REDIS_STRING: type = "string"; break;
-        case REDIS_LIST: type = "list"; break;
-        case REDIS_SET: type = "set"; break;
+        case REDIS_STRING: type = "+string"; break;
+        case REDIS_LIST: type = "+list"; break;
+        case REDIS_SET: type = "+set"; break;
         default: type = "unknown"; break;
         }
     }
@@ -1899,6 +1911,9 @@ static void bgsaveCommand(redisClient *c) {
 static void shutdownCommand(redisClient *c) {
     redisLog(REDIS_WARNING,"User requested shutdown, saving DB...");
     if (saveDb(server.dbfilename) == REDIS_OK) {
+        if (server.daemonize) {
+          unlink(server.pidfile);
+        }
         redisLog(REDIS_WARNING,"Server exit now, bye bye...");
         exit(1);
     } else {
@@ -1913,27 +1928,21 @@ static void renameGenericCommand(redisClient *c, int nx) {
 
     /* To use the same key as src and dst is probably an error */
     if (sdscmp(c->argv[1]->ptr,c->argv[2]->ptr) == 0) {
-        if (nx)
-            addReply(c,shared.minus3);
-        else
-            addReplySds(c,sdsnew("-ERR src and dest key are the same\r\n"));
+        addReply(c,shared.sameobjecterr);
         return;
     }
 
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        if (nx)
-            addReply(c,shared.minus1);
-        else
-            addReply(c,shared.nokeyerr);
+        addReply(c,shared.nokeyerr);
         return;
     }
     o = dictGetEntryVal(de);
     incrRefCount(o);
     if (dictAdd(c->dict,c->argv[2],o) == DICT_ERR) {
         if (nx) {
             decrRefCount(o);
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
             return;
         }
         dictReplace(c->dict,c->argv[2],o);
@@ -1942,7 +1951,7 @@ static void renameGenericCommand(redisClient *c, int nx) {
     }
     dictDelete(c->dict,c->argv[1]);
     server.dirty++;
-    addReply(c,nx ? shared.one : shared.ok);
+    addReply(c,nx ? shared.cone : shared.ok);
 }
 
 static void renameCommand(redisClient *c) {
@@ -1963,7 +1972,7 @@ static void moveCommand(redisClient *c) {
     src = c->dict;
     srcid = c->dictid;
     if (selectDb(c,atoi(c->argv[2]->ptr)) == REDIS_ERR) {
-        addReply(c,shared.minus4);
+        addReply(c,shared.outofrangeerr);
         return;
     }
     dst = c->dict;
@@ -1973,22 +1982,22 @@ static void moveCommand(redisClient *c) {
     /* If the user is moving using as target the same
      * DB as the source DB it is probably an error. */
     if (src == dst) {
-        addReply(c,shared.minus3);
+        addReply(c,shared.sameobjecterr);
         return;
     }
 
     /* Check if the element exists and get a reference */
     de = dictFind(c->dict,c->argv[1]);
     if (!de) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     }
 
     /* Try to add the element to the target DB */
     key = dictGetEntryKey(de);
     o = dictGetEntryVal(de);
     if (dictAdd(dst,key,o) == DICT_ERR) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     }
     incrRefCount(key);
@@ -1997,7 +2006,7 @@ static void moveCommand(redisClient *c) {
     /* OK! key moved, free the entry in the source DB */
     dictDelete(src,c->argv[1]);
     server.dirty++;
-    addReply(c,shared.one);
+    addReply(c,shared.cone);
 }
 
 /* =================================== Lists ================================ */
@@ -2050,15 +2059,15 @@ static void llenCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     } else {
         robj *o = dictGetEntryVal(de);
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
         } else {
             l = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",listLength(l)));
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(l)));
         }
     }
 }
@@ -2069,22 +2078,22 @@ static void lindexCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullbulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln;
             
             ln = listIndex(list, index);
             if (ln == NULL) {
-                addReply(c,shared.nil);
+                addReply(c,shared.nullbulk);
             } else {
                 robj *ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                 addReply(c,ele);
                 addReply(c,shared.crlf);
             }
@@ -2110,7 +2119,7 @@ static void lsetCommand(redisClient *c) {
             
             ln = listIndex(list, index);
             if (ln == NULL) {
-                addReplySds(c,sdsnew("-ERR index out of range\r\n"));
+                addReply(c,shared.outofrangeerr);
             } else {
                 robj *ele = listNodeValue(ln);
 
@@ -2129,12 +2138,12 @@ static void popGenericCommand(redisClient *c, int where) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullbulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln;
@@ -2145,10 +2154,10 @@ static void popGenericCommand(redisClient *c, int where) {
                 ln = listLast(list);
 
             if (ln == NULL) {
-                addReply(c,shared.nil);
+                addReply(c,shared.nullbulk);
             } else {
                 robj *ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 listDelNode(list,ln);
@@ -2173,12 +2182,12 @@ static void lrangeCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nil);
+        addReply(c,shared.nullmultibulk);
     } else {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln;
@@ -2195,18 +2204,18 @@ static void lrangeCommand(redisClient *c) {
             /* indexes sanity checks */
             if (start > end || start >= llen) {
                 /* Out of range start or start > end result in empty list */
-                addReply(c,shared.zero);
+                addReply(c,shared.emptymultibulk);
                 return;
             }
             if (end >= llen) end = llen-1;
             rangelen = (end-start)+1;
 
             /* Return the result in form of a multi-bulk reply */
             ln = listIndex(list, start);
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",rangelen));
+            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
             for (j = 0; j < rangelen; j++) {
                 ele = listNodeValue(ln);
-                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
+                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                 addReply(c,ele);
                 addReply(c,shared.crlf);
                 ln = ln->next;
@@ -2276,7 +2285,7 @@ static void lremCommand(redisClient *c) {
         robj *o = dictGetEntryVal(de);
         
         if (o->type != REDIS_LIST) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
         } else {
             list *list = o->ptr;
             listNode *ln, *next;
@@ -2300,7 +2309,7 @@ static void lremCommand(redisClient *c) {
                 }
                 ln = next;
             }
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",removed));
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
         }
     }
 }
@@ -2319,16 +2328,16 @@ static void saddCommand(redisClient *c) {
     } else {
         set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
     }
     if (dictAdd(set->ptr,c->argv[2],NULL) == DICT_OK) {
         incrRefCount(c->argv[2]);
         server.dirty++;
-        addReply(c,shared.one);
+        addReply(c,shared.cone);
     } else {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     }
 }
 
@@ -2337,20 +2346,20 @@ static void sremCommand(redisClient *c) {
 
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     } else {
         robj *set;
 
         set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
         if (dictDelete(set->ptr,c->argv[2]) == DICT_OK) {
             server.dirty++;
-            addReply(c,shared.one);
+            addReply(c,shared.cone);
         } else {
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
         }
     }
 }
@@ -2360,19 +2369,19 @@ static void sismemberCommand(redisClient *c) {
 
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
     } else {
         robj *set;
 
         set = dictGetEntryVal(de);
         if (set->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
         if (dictFind(set->ptr,c->argv[2]))
-            addReply(c,shared.one);
+            addReply(c,shared.cone);
         else
-            addReply(c,shared.zero);
+            addReply(c,shared.czero);
     }
 }
 
@@ -2382,15 +2391,15 @@ static void scardCommand(redisClient *c) {
     
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.zero);
+        addReply(c,shared.czero);
         return;
     } else {
         robj *o = dictGetEntryVal(de);
         if (o->type != REDIS_SET) {
-            addReply(c,shared.minus2);
+            addReply(c,shared.wrongtypeerr);
         } else {
             s = o->ptr;
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
                 dictGetHashTableUsed(s)));
         }
     }
@@ -2417,13 +2426,13 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         de = dictFind(c->dict,setskeys[j]);
         if (!de) {
             zfree(dv);
-            addReply(c,dstkey ? shared.nokeyerr : shared.nil);
+            addReply(c,shared.nokeyerr);
             return;
         }
         setobj = dictGetEntryVal(de);
         if (setobj->type != REDIS_SET) {
             zfree(dv);
-            addReply(c,dstkey ? shared.wrongtypeerr : shared.wrongtypeerrbulk);
+            addReply(c,shared.wrongtypeerr);
             return;
         }
         dv[j] = setobj->ptr;
@@ -2465,7 +2474,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
             continue; /* at least one set does not contain the member */
         ele = dictGetEntryKey(de);
         if (!dstkey) {
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(ele->ptr)));
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
             addReply(c,ele);
             addReply(c,shared.crlf);
             cardinality++;
@@ -2477,7 +2486,7 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
     dictReleaseIterator(di);
 
     if (!dstkey)
-        lenobj->ptr = sdscatprintf(sdsempty(),"%d\r\n",cardinality);
+        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
     else
         addReply(c,shared.ok);
     zfree(dv);
@@ -2607,19 +2616,19 @@ static void sortCommand(redisClient *c) {
     /* Lookup the key to sort. It must be of the right types */
     de = dictFind(c->dict,c->argv[1]);
     if (de == NULL) {
-        addReply(c,shared.nokeyerrbulk);
+        addReply(c,shared.nokeyerr);
         return;
     }
     sortval = dictGetEntryVal(de);
     if (sortval->type != REDIS_SET && sortval->type != REDIS_LIST) {
-        addReply(c,shared.wrongtypeerrbulk);
+        addReply(c,shared.wrongtypeerr);
         return;
     }
 
     /* Create a list of operations to perform for every sorted element.
      * Operations can be GET/DEL/INCR/DECR */
     operations = listCreate();
-    listSetFreeMethod(operations,free);
+    listSetFreeMethod(operations,zfree);
     j = 2;
 
     /* Now we need to protect sortval incrementing its count, in the future
@@ -2666,7 +2675,7 @@ static void sortCommand(redisClient *c) {
         } else {
             decrRefCount(sortval);
             listRelease(operations);
-            addReply(c,shared.syntaxerrbulk);
+            addReply(c,shared.syntaxerr);
             return;
         }
         j++;
@@ -2747,11 +2756,11 @@ static void sortCommand(redisClient *c) {
     /* Send command output to the output buffer, performing the specified
      * GET/DEL/INCR/DECR operations if any. */
     outputlen = getop ? getop*(end-start+1) : end-start+1;
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",outputlen));
+    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
     for (j = start; j <= end; j++) {
         listNode *ln = operations->head;
         if (!getop) {
-            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                 sdslen(vector[j].obj->ptr)));
             addReply(c,vector[j].obj);
             addReply(c,shared.crlf);
@@ -2763,9 +2772,9 @@ static void sortCommand(redisClient *c) {
 
             if (sop->type == REDIS_SORT_GET) {
                 if (!val || val->type != REDIS_STRING) {
-                    addReply(c,shared.minus1);
+                    addReply(c,shared.nullbulk);
                 } else {
-                    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
+                    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                         sdslen(val->ptr)));
                     addReply(c,val);
                     addReply(c,shared.crlf);
@@ -2813,7 +2822,7 @@ static void infoCommand(redisClient *c) {
         uptime,
         uptime/(3600*24)
     );
-    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(info)));
+    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);
 }
@@ -2905,6 +2914,9 @@ static void syncCommand(redisClient *c) {
     time_t start = time(NULL);
     char sizebuf[32];
 
+    /* ignore SYNC if aleady slave or in monitor mode */
+    if (c->flags & REDIS_SLAVE) return;
+
     redisLog(REDIS_NOTICE,"Slave ask for syncronization");
     if (flushClientOutput(c) == REDIS_ERR || saveDb(server.dbfilename) != REDIS_OK)
         goto closeconn;
@@ -2913,7 +2925,7 @@ static void syncCommand(redisClient *c) {
     if (fd == -1 || fstat(fd,&sb) == -1) goto closeconn;
     len = sb.st_size;
 
-    snprintf(sizebuf,32,"%d\r\n",len);
+    snprintf(sizebuf,32,"$%d\r\n",len);
     if (syncWrite(c->fd,sizebuf,strlen(sizebuf),5) == -1) goto closeconn;
     while(len) {
         char buf[1024];
@@ -2965,7 +2977,7 @@ static int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
-    dumpsize = atoi(buf);
+    dumpsize = atoi(buf+1);
     redisLog(REDIS_NOTICE,"Receiving %d bytes data dump from MASTER",dumpsize);
     /* Read the bulk write data on a temp file */
     snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
@@ -3014,6 +3026,16 @@ static int syncWithMaster(void) {
     return REDIS_OK;
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
 /* =================================== Main! ================================ */
 
 static void daemonize(void) {
@@ -3033,7 +3055,7 @@ static void daemonize(void) {
         if (fd > STDERR_FILENO) close(fd);
     }
     /* Try to write the pid file */
-    fp = fopen("/var/run/redis.pid","w");
+    fp = fopen(server.pidfile,"w");
     if (fp) {
         fprintf(fp,"%d\n",getpid());
         fclose(fp);
@@ -3056,7 +3078,7 @@ int main(int argc, char **argv) {
         redisLog(REDIS_NOTICE,"DB loaded from disk");
     if (aeCreateFileEvent(server.el, server.fd, AE_READABLE,
         acceptHandler, NULL, NULL) == AE_ERR) oom("creating file event");
-    redisLog(REDIS_NOTICE,"The server is now ready to accept connections");
+    redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
     aeMain(server.el);
     aeDeleteEventLoop(server.el);
     return 0;