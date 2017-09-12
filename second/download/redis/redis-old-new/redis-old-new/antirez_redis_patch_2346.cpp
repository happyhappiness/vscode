@@ -65,7 +65,7 @@
 /* Static server configuration */
 #define REDIS_SERVERPORT        6379    /* TCP port */
 #define REDIS_MAXIDLETIME       (60*5)  /* default client timeout */
-#define REDIS_QUERYBUF_LEN      1024
+#define REDIS_IOBUF_LEN         1024
 #define REDIS_LOADBUF_LEN       1024
 #define REDIS_MAX_ARGS          16
 #define REDIS_DEFAULT_DBNUM     16
@@ -194,7 +194,7 @@ typedef struct redisClient {
     int authenticated;      /* when requirepass is non-NULL */
     int replstate;          /* replication state if this is a slave */
     int repldbfd;           /* replication DB file descriptor */
-    int repldboff;          /* replication DB file offset */
+    long repldboff;          /* replication DB file offset */
     off_t repldbsize;       /* replication DB file size */
 } redisClient;
 
@@ -304,6 +304,7 @@ static int deleteIfVolatile(redisDb *db, robj *key);
 static int deleteKey(redisDb *db, robj *key);
 static time_t getExpire(redisDb *db, robj *key);
 static int setExpire(redisDb *db, robj *key, time_t when);
+static void updateSalvesWaitingBgsave(int bgsaveerr);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -633,21 +634,18 @@ static void oom(const char *msg) {
 /* ====================== Redis server networking stuff ===================== */
 void closeTimedoutClients(void) {
     redisClient *c;
-    listIter *li;
     listNode *ln;
     time_t now = time(NULL);
 
-    li = listGetIterator(server.clients,AL_START_HEAD);
-    if (!li) return;
-    while ((ln = listNextElement(li)) != NULL) {
+    listRewind(server.clients);
+    while ((ln = listYield(server.clients)) != NULL) {
         c = listNodeValue(ln);
         if (!(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
              (now - c->lastinteraction > server.maxidletime)) {
             redisLog(REDIS_DEBUG,"Closing idle client");
             freeClient(c);
         }
     }
-    listReleaseIterator(li);
 }
 
 int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
@@ -695,6 +693,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* Check if a background saving in progress terminated */
     if (server.bgsaveinprogress) {
         int statloc;
+        /* XXX: TODO handle the case of the saving child killed */
         if (wait4(-1,&statloc,WNOHANG,NULL)) {
             int exitcode = WEXITSTATUS(statloc);
             if (exitcode == 0) {
@@ -707,6 +706,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                     "Background saving error");
             }
             server.bgsaveinprogress = 0;
+            updateSalvesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
         }
     } else {
         /* If there is not a background saving in progress check if
@@ -1041,6 +1041,8 @@ static void freeClient(redisClient *c) {
     assert(ln != NULL);
     listDelNode(server.clients,ln);
     if (c->flags & REDIS_SLAVE) {
+        if (c->replstate == REDIS_REPL_SEND_BULK && c->repldbfd != -1)
+            close(c->repldbfd);
         list *l = (c->flags & REDIS_MONITOR) ? server.monitors : server.slaves;
         ln = listSearchKey(l,c);
         assert(ln != NULL);
@@ -1055,13 +1057,13 @@ static void freeClient(redisClient *c) {
 
 static void glueReplyBuffersIfNeeded(redisClient *c) {
     int totlen = 0;
-    listNode *ln = c->reply->head, *next;
+    listNode *ln;
     robj *o;
 
-    while(ln) {
+    listRewind(c->reply);
+    while((ln = listYield(c->reply))) {
         o = ln->value;
         totlen += sdslen(o->ptr);
-        ln = ln->next;
         /* This optimization makes more sense if we don't have to copy
          * too much data */
         if (totlen > 1024) return;
@@ -1070,14 +1072,12 @@ static void glueReplyBuffersIfNeeded(redisClient *c) {
         char buf[1024];
         int copylen = 0;
 
-        ln = c->reply->head;
-        while(ln) {
-            next = ln->next;
+        listRewind(c->reply);
+        while((ln = listYield(c->reply))) {
             o = ln->value;
             memcpy(buf+copylen,o->ptr,sdslen(o->ptr));
             copylen += sdslen(o->ptr);
             listDelNode(c->reply,ln);
-            ln = next;
         }
         /* Now the output buffer is empty, add the new single element */
         addReplySds(c,sdsnewlen(buf,totlen));
@@ -1231,7 +1231,7 @@ static int processCommand(redisClient *c) {
 }
 
 static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int dictid, robj **argv, int argc) {
-    listNode *ln = slaves->head;
+    listNode *ln;
     robj *outv[REDIS_MAX_ARGS*4]; /* enough room for args, spaces, newlines */
     int outc = 0, j;
     
@@ -1253,14 +1253,12 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
      * be sure to free objects if there is no slave in a replication state
      * able to be feed with commands */
     for (j = 0; j < outc; j++) incrRefCount(outv[j]);
-    while(ln) {
+    listRewind(slaves);
+    while((ln = listYield(slaves))) {
         redisClient *slave = ln->value;
 
         /* Don't feed slaves that are still waiting for BGSAVE to start */
-        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
-            ln = ln->next;
-            continue;
-        }
+        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;
 
         /* Feed all the other slaves, MONITORs and so on */
         if (slave->slaveseldb != dictid) {
@@ -1287,19 +1285,18 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
             slave->slaveseldb = dictid;
         }
         for (j = 0; j < outc; j++) addReply(slave,outv[j]);
-        ln = ln->next;
     }
     for (j = 0; j < outc; j++) decrRefCount(outv[j]);
 }
 
 static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *c = (redisClient*) privdata;
-    char buf[REDIS_QUERYBUF_LEN];
+    char buf[REDIS_IOBUF_LEN];
     int nread;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
 
-    nread = read(fd, buf, REDIS_QUERYBUF_LEN);
+    nread = read(fd, buf, REDIS_IOBUF_LEN);
     if (nread == -1) {
         if (errno == EAGAIN) {
             nread = 0;
@@ -1428,6 +1425,8 @@ static redisClient *createClient(int fd) {
 
 static void addReply(redisClient *c, robj *obj) {
     if (listLength(c->reply) == 0 &&
+        (c->replstate == REDIS_REPL_NONE ||
+         c->replstate == REDIS_REPL_ONLINE) &&
         aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
         sendReplyToClient, c, NULL) == AE_ERR) return;
     if (!listAddNodeTail(c->reply,obj)) oom("listAddNodeTail");
@@ -1804,14 +1803,14 @@ static int rdbSave(char *filename) {
             } else if (o->type == REDIS_LIST) {
                 /* Save a list value */
                 list *list = o->ptr;
-                listNode *ln = list->head;
+                listNode *ln;
 
+                listRewind(list);
                 if (rdbSaveLen(fp,listLength(list)) == -1) goto werr;
-                while(ln) {
+                while((ln = listYield(list))) {
                     robj *eleobj = listNodeValue(ln);
 
                     if (rdbSaveStringObject(fp,eleobj) == -1) goto werr;
-                    ln = ln->next;
                 }
             } else if (o->type == REDIS_SET) {
                 /* Save a set value */
@@ -2373,6 +2372,7 @@ static void bgsaveCommand(redisClient *c) {
 
 static void shutdownCommand(redisClient *c) {
     redisLog(REDIS_WARNING,"User requested shutdown, saving DB...");
+    /* XXX: TODO kill the child if there is a bgsave in progress */
     if (rdbSave(server.dbfilename) == REDIS_OK) {
         if (server.daemonize) {
           unlink(server.pidfile);
@@ -3224,13 +3224,14 @@ static void sortCommand(redisClient *c) {
     j = 0;
     if (sortval->type == REDIS_LIST) {
         list *list = sortval->ptr;
-        listNode *ln = list->head;
-        while(ln) {
+        listNode *ln;
+
+        listRewind(list);
+        while((ln = listYield(list))) {
             robj *ele = ln->value;
             vector[j].obj = ele;
             vector[j].u.score = 0;
             vector[j].u.cmpobj = NULL;
-            ln = ln->next;
             j++;
         }
     } else {
@@ -3292,14 +3293,15 @@ static void sortCommand(redisClient *c) {
     outputlen = getop ? getop*(end-start+1) : end-start+1;
     addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
     for (j = start; j <= end; j++) {
-        listNode *ln = operations->head;
+        listNode *ln;
         if (!getop) {
             addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                 sdslen(vector[j].obj->ptr)));
             addReply(c,vector[j].obj);
             addReply(c,shared.crlf);
         }
-        while(ln) {
+        listRewind(operations);
+        while((ln = listYield(operations))) {
             redisSortOperation *sop = ln->value;
             robj *val = lookupKeyByPattern(c->db,sop->pattern,
                 vector[j].obj);
@@ -3316,7 +3318,6 @@ static void sortCommand(redisClient *c) {
             } else if (sop->type == REDIS_SORT_DEL) {
                 /* TODO */
             }
-            ln = ln->next;
         }
     }
 
@@ -3455,23 +3456,6 @@ static void expireCommand(redisClient *c) {
 
 /* =============================== Replication  ============================= */
 
-/* Send the whole output buffer syncronously to the slave. This a general operation in theory, but it is actually useful only for replication. */
-static int flushClientOutput(redisClient *c) {
-    int retval;
-    time_t start = time(NULL);
-
-    while(listLength(c->reply)) {
-        if (time(NULL)-start > 5) return REDIS_ERR; /* 5 seconds timeout */
-        retval = aeWait(c->fd,AE_WRITABLE,1000);
-        if (retval == -1) {
-            return REDIS_ERR;
-        } else if (retval & AE_WRITABLE) {
-            sendReplyToClient(NULL, c->fd, c, AE_WRITABLE);
-        }
-    }
-    return REDIS_OK;
-}
-
 static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {
     ssize_t nwritten, ret = size;
     time_t start = time(NULL);
@@ -3557,11 +3541,10 @@ static void syncCommand(redisClient *c) {
         redisClient *slave;
         listNode *ln;
 
-        ln = server.slaves->head;
-        while(ln) {
+        listRewind(server.slaves);
+        while((ln = listYield(server.slaves))) {
             slave = ln->value;
             if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) break;
-            ln = ln->next;
         }
         if (ln) {
             /* Perfect, the server is already registering differences for
@@ -3587,59 +3570,115 @@ static void syncCommand(redisClient *c) {
         }
         c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
     }
+    c->repldbfd = -1;
     c->flags |= REDIS_SLAVE;
     c->slaveseldb = 0;
     if (!listAddNodeTail(server.slaves,c)) oom("listAddNodeTail");
-    redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
     return;
 }
 
-#if 0
-static void _syncCommand(redisClient *c) {
-    struct stat sb;
-    int fd = -1, len;
-    time_t start = time(NULL);
-    char sizebuf[32];
-
-    /* ignore SYNC if aleady slave or in monitor mode */
-    if (c->flags & REDIS_SLAVE) return;
-
-    redisLog(REDIS_NOTICE,"Slave ask for synchronization");
-    if (flushClientOutput(c) == REDIS_ERR ||
-        rdbSave(server.dbfilename) != REDIS_OK)
-        goto closeconn;
+static void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
+    redisClient *slave = privdata;
+    REDIS_NOTUSED(el);
+    REDIS_NOTUSED(mask);
+    char buf[REDIS_IOBUF_LEN];
+    ssize_t nwritten, buflen;
+
+    if (slave->repldboff == 0) {
+        /* Write the bulk write count before to transfer the DB. In theory here
+         * we don't know how much room there is in the output buffer of the
+         * socket, but in pratice SO_SNDLOWAT (the minimum count for output
+         * operations) will never be smaller than the few bytes we need. */
+        sds bulkcount;
+
+        bulkcount = sdscatprintf(sdsempty(),"$%lld\r\n",(unsigned long long)
+            slave->repldbsize);
+        if (write(fd,bulkcount,sdslen(bulkcount)) != (signed)sdslen(bulkcount))
+        {
+            sdsfree(bulkcount);
+            freeClient(slave);
+            return;
+        }
+        sdsfree(bulkcount);
+    }
+    lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
+    buflen = read(slave->repldbfd,buf,REDIS_IOBUF_LEN);
+    if (buflen <= 0) {
+        redisLog(REDIS_WARNING,"Read error sending DB to slave: %s",
+            (buflen == 0) ? "premature EOF" : strerror(errno));
+        freeClient(slave);
+        return;
+    }
+    if ((nwritten = write(fd,buf,buflen)) == -1) {
+        redisLog(REDIS_DEBUG,"Write error sending DB to slave: %s",
+            strerror(errno));
+        freeClient(slave);
+        return;
+    }
+    slave->repldboff += nwritten;
+    if (slave->repldboff == slave->repldbsize) {
+        close(slave->repldbfd);
+        slave->repldbfd = -1;
+        aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
+        slave->replstate = REDIS_REPL_ONLINE;
+        if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
+            sendReplyToClient, slave, NULL) == AE_ERR) {
+            freeClient(slave);
+            return;
+        }
+        addReplySds(slave,sdsempty());
+        redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
+    }
+}
 
-    fd = open(server.dbfilename, O_RDONLY);
-    if (fd == -1 || fstat(fd,&sb) == -1) goto closeconn;
-    len = sb.st_size;
+static void updateSalvesWaitingBgsave(int bgsaveerr) {
+    listNode *ln;
+    int startbgsave = 0;
 
-    snprintf(sizebuf,32,"$%d\r\n",len);
-    if (syncWrite(c->fd,sizebuf,strlen(sizebuf),5) == -1) goto closeconn;
-    while(len) {
-        char buf[1024];
-        int nread;
+    listRewind(server.slaves);
+    while((ln = listYield(server.slaves))) {
+        redisClient *slave = ln->value;
 
-        if (time(NULL)-start > REDIS_MAX_SYNC_TIME) goto closeconn;
-        nread = read(fd,buf,1024);
-        if (nread == -1) goto closeconn;
-        len -= nread;
-        if (syncWrite(c->fd,buf,nread,5) == -1) goto closeconn;
+        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
+            startbgsave = 1;
+            slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+        } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
+            struct stat buf;
+           
+            if (bgsaveerr != REDIS_OK) {
+                freeClient(slave);
+                redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
+                continue;
+            }
+            if ((slave->repldbfd = open(server.dbfilename,O_RDONLY)) == -1 ||
+                fstat(slave->repldbfd,&buf) == -1) {
+                freeClient(slave);
+                redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
+                continue;
+            }
+            slave->repldboff = 0;
+            slave->repldbsize = buf.st_size;
+            slave->replstate = REDIS_REPL_SEND_BULK;
+            aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
+            if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE, sendBulkToSlave, slave, NULL) == AE_ERR) {
+                freeClient(slave);
+                continue;
+            }
+        }
     }
-    if (syncWrite(c->fd,"\r\n",2,5) == -1) goto closeconn;
-    close(fd);
-    c->flags |= REDIS_SLAVE;
-    c->slaveseldb = 0;
-    if (!listAddNodeTail(server.slaves,c)) oom("listAddNodeTail");
-    redisLog(REDIS_NOTICE,"Synchronization with slave succeeded");
-    return;
+    if (startbgsave) {
+        if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
+            listRewind(server.slaves);
+            redisLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
+            while((ln = listYield(server.slaves))) {
+                redisClient *slave = ln->value;
 
-closeconn:
-    if (fd != -1) close(fd);
-    c->flags |= REDIS_CLOSE;
-    redisLog(REDIS_WARNING,"Synchronization with slave failed");
-    return;
+                if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
+                    freeClient(slave);
+            }
+        }
+    }
 }
-#endif
 
 static int syncWithMaster(void) {
     char buf[1024], tmpfile[256];