@@ -126,11 +126,20 @@
 #define REDIS_MASTER 4      /* This client is a master server */
 #define REDIS_MONITOR 8      /* This client is a slave monitor, see MONITOR */
 
-/* Server replication state */
+/* Slave replication state - slave side */
 #define REDIS_REPL_NONE 0   /* No active replication */
 #define REDIS_REPL_CONNECT 1    /* Must connect to master */
 #define REDIS_REPL_CONNECTED 2  /* Connected to master */
 
+/* Slave replication state - from the point of view of master
+ * Note that in SEND_BULK and ONLINE state the slave receives new updates
+ * in its output queue. In the WAIT_BGSAVE state instead the server is waiting
+ * to start the next background saving in order to send updates to it. */
+#define REDIS_REPL_WAIT_BGSAVE_START 3 /* master waits bgsave to start feeding it */
+#define REDIS_REPL_WAIT_BGSAVE_END 4 /* master waits bgsave to start bulk DB transmission */
+#define REDIS_REPL_SEND_BULK 5 /* master is sending the bulk DB */
+#define REDIS_REPL_ONLINE 6 /* bulk DB already transmitted, receive updates */
+
 /* List related stuff */
 #define REDIS_HEAD 0
 #define REDIS_TAIL 1
@@ -176,13 +185,17 @@ typedef struct redisClient {
     sds querybuf;
     robj *argv[REDIS_MAX_ARGS];
     int argc;
-    int bulklen;    /* bulk read len. -1 if not in bulk read mode */
+    int bulklen;            /* bulk read len. -1 if not in bulk read mode */
     list *reply;
     int sentlen;
     time_t lastinteraction; /* time of the last interaction, used for timeout */
-    int flags; /* REDIS_CLOSE | REDIS_SLAVE | REDIS_MONITOR */
-    int slaveseldb; /* slave selected db, if this client is a slave */
-    int authenticated;    /* when requirepass is non-NULL */
+    int flags;              /* REDIS_CLOSE | REDIS_SLAVE | REDIS_MONITOR */
+    int slaveseldb;         /* slave selected db, if this client is a slave */
+    int authenticated;      /* when requirepass is non-NULL */
+    int replstate;          /* replication state if this is a slave */
+    int repldbfd;           /* replication DB file descriptor */
+    int repldboff;          /* replication DB file offset */
+    off_t repldbsize;       /* replication DB file size */
 } redisClient;
 
 struct saveparam {
@@ -229,7 +242,7 @@ struct redisServer {
     int isslave;
     char *masterhost;
     int masterport;
-    redisClient *master;
+    redisClient *master;    /* client that is master for this slave */
     int replstate;
     /* Sort parameters - qsort_r() is only available under BSD so we
      * have to take this state global, in order to pass it to sortCompare() */
@@ -331,6 +344,8 @@ static void sismemberCommand(redisClient *c);
 static void scardCommand(redisClient *c);
 static void sinterCommand(redisClient *c);
 static void sinterstoreCommand(redisClient *c);
+static void sunionCommand(redisClient *c);
+static void sunionstoreCommand(redisClient *c);
 static void syncCommand(redisClient *c);
 static void flushdbCommand(redisClient *c);
 static void flushallCommand(redisClient *c);
@@ -370,6 +385,8 @@ static struct redisCommand cmdTable[] = {
     {"scard",scardCommand,2,REDIS_CMD_INLINE},
     {"sinter",sinterCommand,-2,REDIS_CMD_INLINE},
     {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_INLINE},
+    {"sunion",sunionCommand,-2,REDIS_CMD_INLINE},
+    {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_INLINE},
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE},
@@ -1232,8 +1249,20 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
     }
     outv[outc++] = shared.crlf;
 
+    /* Increment all the refcounts at start and decrement at end in order to
+     * be sure to free objects if there is no slave in a replication state
+     * able to be feed with commands */
+    for (j = 0; j < outc; j++) incrRefCount(outv[j]);
     while(ln) {
         redisClient *slave = ln->value;
+
+        /* Don't feed slaves that are still waiting for BGSAVE to start */
+        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+            ln = ln->next;
+            continue;
+        }
+
+        /* Feed all the other slaves, MONITORs and so on */
         if (slave->slaveseldb != dictid) {
             robj *selectcmd;
 
@@ -1260,6 +1289,7 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
         for (j = 0; j < outc; j++) addReply(slave,outv[j]);
         ln = ln->next;
     }
+    for (j = 0; j < outc; j++) decrRefCount(outv[j]);
 }
 
 static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -1363,6 +1393,11 @@ static int selectDb(redisClient *c, int id) {
     return REDIS_OK;
 }
 
+static void *dupClientReplyValue(void *o) {
+    incrRefCount((robj*)o);
+    return 0;
+}
+
 static redisClient *createClient(int fd) {
     redisClient *c = zmalloc(sizeof(*c));
 
@@ -1378,8 +1413,10 @@ static redisClient *createClient(int fd) {
     c->flags = 0;
     c->lastinteraction = time(NULL);
     c->authenticated = 0;
+    c->replstate = REDIS_REPL_NONE;
     if ((c->reply = listCreate()) == NULL) oom("listCreate");
     listSetFreeMethod(c->reply,decrRefCount);
+    listSetDupMethod(c->reply,dupClientReplyValue);
     if (aeCreateFileEvent(server.el, c->fd, AE_READABLE,
         readQueryFromClient, c, NULL) == AE_ERR) {
         freeClient(c);
@@ -2861,7 +2898,6 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         deleteKey(c->db,dstkey);
         dictAdd(c->db->dict,dstkey,dstset);
         incrRefCount(dstkey);
-        server.dirty++;
     }
 
     /* Iterate all the elements of the first (smallest) set, and test
@@ -2886,15 +2922,16 @@ static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
         } else {
             dictAdd(dstset->ptr,ele,NULL);
             incrRefCount(ele);
-            server.dirty++;
         }
     }
     dictReleaseIterator(di);
 
-    if (!dstkey)
+    if (!dstkey) {
         lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
-    else
+    } else {
         addReply(c,shared.ok);
+        server.dirty++;
+    }
     zfree(dv);
 }
 
@@ -2906,6 +2943,100 @@ static void sinterstoreCommand(redisClient *c) {
     sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
 }
 
+static void sunionGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
+    dict **dv = zmalloc(sizeof(dict*)*setsnum);
+    dictIterator *di;
+    dictEntry *de;
+    robj *lenobj = NULL, *dstset = NULL;
+    int j, cardinality = 0;
+
+    if (!dv) oom("sunionCommand");
+    for (j = 0; j < setsnum; j++) {
+        robj *setobj;
+
+        setobj = dstkey ?
+                    lookupKeyWrite(c->db,setskeys[j]) :
+                    lookupKeyRead(c->db,setskeys[j]);
+        if (!setobj) {
+            dv[j] = NULL;
+            continue;
+        }
+        if (setobj->type != REDIS_SET) {
+            zfree(dv);
+            addReply(c,shared.wrongtypeerr);
+            return;
+        }
+        dv[j] = setobj->ptr;
+    }
+
+    /* We need a temp set object to store our union. If the dstkey
+     * is not NULL (that is, we are inside an SUNIONSTORE operation) then
+     * this set object will be the resulting object to set into the target key*/
+    dstset = createSetObject();
+
+    /* The first thing we should output is the total number of elements...
+     * since this is a multi-bulk write, but at this stage we don't know
+     * the intersection set size, so we use a trick, append an empty object
+     * to the output list and save the pointer to later modify it with the
+     * right length */
+    if (!dstkey) {
+        lenobj = createObject(REDIS_STRING,NULL);
+        addReply(c,lenobj);
+        decrRefCount(lenobj);
+    } else {
+        /* If we have a target key where to store the resulting set
+         * create this key with an empty set inside */
+        deleteKey(c->db,dstkey);
+        dictAdd(c->db->dict,dstkey,dstset);
+        incrRefCount(dstkey);
+        server.dirty++;
+    }
+
+    /* Iterate all the elements of all the sets, add every element a single
+     * time to the result set */
+    for (j = 0; j < setsnum; j++) {
+        if (!dv[j]) continue; /* non existing keys are like empty sets */
+
+        di = dictGetIterator(dv[j]);
+        if (!di) oom("dictGetIterator");
+
+        while((de = dictNext(di)) != NULL) {
+            robj *ele;
+
+            /* dictAdd will not add the same element multiple times */
+            ele = dictGetEntryKey(de);
+            if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
+                incrRefCount(ele);
+                if (!dstkey) {
+                    addReplySds(c,sdscatprintf(sdsempty(),
+                            "$%d\r\n",sdslen(ele->ptr)));
+                    addReply(c,ele);
+                    addReply(c,shared.crlf);
+                    cardinality++;
+                }
+            }
+        }
+        dictReleaseIterator(di);
+    }
+
+    if (!dstkey) {
+        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
+        decrRefCount(dstset);
+    } else {
+        addReply(c,shared.ok);
+        server.dirty++;
+    }
+    zfree(dv);
+}
+
+static void sunionCommand(redisClient *c) {
+    sunionGenericCommand(c,c->argv+1,c->argc-1,NULL);
+}
+
+static void sunionstoreCommand(redisClient *c) {
+    sunionGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
+}
+
 static void flushdbCommand(redisClient *c) {
     dictEmpty(c->db->dict);
     dictEmpty(c->db->expires);
@@ -3404,6 +3535,67 @@ static int syncReadLine(int fd, char *ptr, ssize_t size, int timeout) {
 }
 
 static void syncCommand(redisClient *c) {
+    /* ignore SYNC if aleady slave or in monitor mode */
+    if (c->flags & REDIS_SLAVE) return;
+
+    /* SYNC can't be issued when the server has pending data to send to
+     * the client about already issued commands. We need a fresh reply
+     * buffer registering the differences between the BGSAVE and the current
+     * dataset, so that we can copy to other slaves if needed. */
+    if (listLength(c->reply) != 0) {
+        addReplySds(c,sdsnew("-ERR SYNC is invalid with pending input\r\n"));
+        return;
+    }
+
+    redisLog(REDIS_NOTICE,"Slave ask for synchronization");
+    /* Here we need to check if there is a background saving operation
+     * in progress, or if it is required to start one */
+    if (server.bgsaveinprogress) {
+        /* Ok a background save is in progress. Let's check if it is a good
+         * one for replication, i.e. if there is another slave that is
+         * registering differences since the server forked to save */
+        redisClient *slave;
+        listNode *ln;
+
+        ln = server.slaves->head;
+        while(ln) {
+            slave = ln->value;
+            if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) break;
+            ln = ln->next;
+        }
+        if (ln) {
+            /* Perfect, the server is already registering differences for
+             * another slave. Set the right state, and copy the buffer. */
+            listRelease(c->reply);
+            c->reply = listDup(slave->reply);
+            if (!c->reply) oom("listDup copying slave reply list");
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+            redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
+        } else {
+            /* No way, we need to wait for the next BGSAVE in order to
+             * register differences */
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+            redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
+        }
+    } else {
+        /* Ok we don't have a BGSAVE in progress, let's start one */
+        redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
+        if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
+            redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+            addReplySds(c,sdsnew("-ERR Unalbe to perform background save\r\n"));
+            return;
+        }
+        c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+    }
+    c->flags |= REDIS_SLAVE;
+    c->slaveseldb = 0;
+    if (!listAddNodeTail(server.slaves,c)) oom("listAddNodeTail");
+    redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
+    return;
+}
+
+#if 0
+static void _syncCommand(redisClient *c) {
     struct stat sb;
     int fd = -1, len;
     time_t start = time(NULL);
@@ -3412,7 +3604,7 @@ static void syncCommand(redisClient *c) {
     /* ignore SYNC if aleady slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
 
-    redisLog(REDIS_NOTICE,"Slave ask for syncronization");
+    redisLog(REDIS_NOTICE,"Slave ask for synchronization");
     if (flushClientOutput(c) == REDIS_ERR ||
         rdbSave(server.dbfilename) != REDIS_OK)
         goto closeconn;
@@ -3438,15 +3630,16 @@ static void syncCommand(redisClient *c) {
     c->flags |= REDIS_SLAVE;
     c->slaveseldb = 0;
     if (!listAddNodeTail(server.slaves,c)) oom("listAddNodeTail");
-    redisLog(REDIS_NOTICE,"Syncronization with slave succeeded");
+    redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
     return;
 
 closeconn:
     if (fd != -1) close(fd);
     c->flags |= REDIS_CLOSE;
-    redisLog(REDIS_WARNING,"Syncronization with slave failed");
+    redisLog(REDIS_WARNING,"Synchronization with slave failed");
     return;
 }
+#endif
 
 static int syncWithMaster(void) {
     char buf[1024], tmpfile[256];