@@ -275,8 +275,9 @@ struct redisServer {
     int appendfd;
     int appendseldb;
     char *pidfile;
-    int bgsaveinprogress;
     pid_t bgsavechildpid;
+    pid_t bgrewritechildpid;
+    sds bgrewritebuf; /* buffer taken by parent during oppend only rewrite */
     struct saveparam *saveparams;
     int saveparamslen;
     char *logfile;
@@ -383,7 +384,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
 static int syncWithMaster(void);
 static robj *tryObjectSharing(robj *o);
 static int tryObjectEncoding(robj *o);
-static robj *getDecodedObject(const robj *o);
+static robj *getDecodedObject(robj *o);
 static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
 static int deleteIfVolatile(redisDb *db, robj *key);
@@ -395,6 +396,7 @@ static void freeMemoryIfNeeded(void);
 static int processCommand(redisClient *c);
 static void setupSigSegvAction(void);
 static void rdbRemoveTempFile(pid_t childpid);
+static void aofRemoveTempFile(pid_t childpid);
 static size_t stringObjectLen(robj *o);
 static void processInputBuffer(redisClient *c);
 static zskiplist *zslCreate(void);
@@ -421,6 +423,7 @@ static void dbsizeCommand(redisClient *c);
 static void lastsaveCommand(redisClient *c);
 static void saveCommand(redisClient *c);
 static void bgsaveCommand(redisClient *c);
+static void bgrewriteaofCommand(redisClient *c);
 static void shutdownCommand(redisClient *c);
 static void moveCommand(redisClient *c);
 static void renameCommand(redisClient *c);
@@ -541,6 +544,7 @@ static struct redisCommand cmdTable[] = {
     {"echo",echoCommand,2,REDIS_CMD_BULK},
     {"save",saveCommand,1,REDIS_CMD_INLINE},
     {"bgsave",bgsaveCommand,1,REDIS_CMD_INLINE},
+    {"bgrewriteaof",bgrewriteaofCommand,1,REDIS_CMD_INLINE},
     {"shutdown",shutdownCommand,1,REDIS_CMD_INLINE},
     {"lastsave",lastsaveCommand,1,REDIS_CMD_INLINE},
     {"type",typeCommand,2,REDIS_CMD_INLINE},
@@ -752,37 +756,24 @@ static unsigned int dictObjHash(const void *key) {
 static int dictEncObjKeyCompare(void *privdata, const void *key1,
         const void *key2)
 {
-    const robj *o1 = key1, *o2 = key2;
-
-    if (o1->encoding == REDIS_ENCODING_RAW &&
-        o2->encoding == REDIS_ENCODING_RAW)
-        return sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
-    else {
-        robj *dec1, *dec2;
-        int cmp;
+    robj *o1 = (robj*) key1, *o2 = (robj*) key2;
+    int cmp;
 
-        dec1 = o1->encoding != REDIS_ENCODING_RAW ?
-            getDecodedObject(o1) : (robj*)o1;
-        dec2 = o2->encoding != REDIS_ENCODING_RAW ?
-            getDecodedObject(o2) : (robj*)o2;
-        cmp = sdsDictKeyCompare(privdata,dec1->ptr,dec2->ptr);
-        if (dec1 != o1) decrRefCount(dec1);
-        if (dec2 != o2) decrRefCount(dec2);
-        return cmp;
-    }
+    o1 = getDecodedObject(o1);
+    o2 = getDecodedObject(o2);
+    cmp = sdsDictKeyCompare(privdata,o1->ptr,o2->ptr);
+    decrRefCount(o1);
+    decrRefCount(o2);
+    return cmp;
 }
 
 static unsigned int dictEncObjHash(const void *key) {
-    const robj *o = key;
+    robj *o = (robj*) key;
 
-    if (o->encoding == REDIS_ENCODING_RAW)
-        return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
-    else {
-        robj *dec = getDecodedObject(o);
-        unsigned int hash = dictGenHashFunction(dec->ptr, sdslen((sds)dec->ptr));
-        decrRefCount(dec);
-        return hash;
-    }
+    o = getDecodedObject(o);
+    unsigned int hash = dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
+    decrRefCount(o);
+    return hash;
 }
 
 static dictType setDictType = {
@@ -869,6 +860,89 @@ static void tryResizeHashTables(void) {
     }
 }
 
+/* A background saving child (BGSAVE) terminated its work. Handle this. */
+void backgroundSaveDoneHandler(int statloc) {
+    int exitcode = WEXITSTATUS(statloc);
+    int bysignal = WIFSIGNALED(statloc);
+
+    if (!bysignal && exitcode == 0) {
+        redisLog(REDIS_NOTICE,
+            "Background saving terminated with success");
+        server.dirty = 0;
+        server.lastsave = time(NULL);
+    } else if (!bysignal && exitcode != 0) {
+        redisLog(REDIS_WARNING, "Background saving error");
+    } else {
+        redisLog(REDIS_WARNING,
+            "Background saving terminated by signal");
+        rdbRemoveTempFile(server.bgsavechildpid);
+    }
+    server.bgsavechildpid = -1;
+    /* Possibly there are slaves waiting for a BGSAVE in order to be served
+     * (the first stage of SYNC is a bulk transfer of dump.rdb) */
+    updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
+}
+
+/* A background append only file rewriting (BGREWRITEAOF) terminated its work.
+ * Handle this. */
+void backgroundRewriteDoneHandler(int statloc) {
+    int exitcode = WEXITSTATUS(statloc);
+    int bysignal = WIFSIGNALED(statloc);
+
+    if (!bysignal && exitcode == 0) {
+        int fd;
+        char tmpfile[256];
+
+        redisLog(REDIS_NOTICE,
+            "Background append only file rewriting terminated with success");
+        /* Now it's time to flush the differences accumulated by the parent */
+        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) server.bgrewritechildpid);
+        fd = open(tmpfile,O_WRONLY|O_APPEND);
+        if (fd == -1) {
+            redisLog(REDIS_WARNING, "Not able to open the temp append only file produced by the child: %s", strerror(errno));
+            goto cleanup;
+        }
+        /* Flush our data... */
+        if (write(fd,server.bgrewritebuf,sdslen(server.bgrewritebuf)) !=
+                (signed) sdslen(server.bgrewritebuf)) {
+            redisLog(REDIS_WARNING, "Error or short write trying to flush the parent diff of the append log file in the child temp file: %s", strerror(errno));
+            close(fd);
+            goto cleanup;
+        }
+        redisLog(REDIS_WARNING,"Parent diff flushed into the new append log file with success");
+        /* Now our work is to rename the temp file into the stable file. And
+         * switch the file descriptor used by the server for append only. */
+        if (rename(tmpfile,server.appendfilename) == -1) {
+            redisLog(REDIS_WARNING,"Can't rename the temp append only file into the stable one: %s", strerror(errno));
+            close(fd);
+            goto cleanup;
+        }
+        /* Mission completed... almost */
+        redisLog(REDIS_NOTICE,"Append only file successfully rewritten.");
+        if (server.appendfd != -1) {
+            /* If append only is actually enabled... */
+            close(server.appendfd);
+            server.appendfd = fd;
+            fsync(fd);
+            redisLog(REDIS_NOTICE,"The new append only file was selected for future appends.");
+        } else {
+            /* If append only is disabled we just generate a dump in this
+             * format. Why not? */
+            close(fd);
+        }
+    } else if (!bysignal && exitcode != 0) {
+        redisLog(REDIS_WARNING, "Background append only file rewriting error");
+    } else {
+        redisLog(REDIS_WARNING,
+            "Background append only file rewriting terminated by signal");
+    }
+cleanup:
+    sdsfree(server.bgrewritebuf);
+    server.bgrewritebuf = sdsempty();
+    aofRemoveTempFile(server.bgrewritechildpid);
+    server.bgrewritechildpid = -1;
+}
+
 static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     int j, loops = server.cronloops++;
     REDIS_NOTUSED(eventLoop);
@@ -897,7 +971,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
      * if we resize the HT while there is the saving child at work actually
      * a lot of memory movements in the parent will cause a lot of pages
      * copied. */
-    if (!server.bgsaveinprogress) tryResizeHashTables();
+    if (server.bgsavechildpid == -1) tryResizeHashTables();
 
     /* Show information about connected clients */
     if (!(loops % 5)) {
@@ -912,28 +986,17 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
     if (server.maxidletime && !(loops % 10))
         closeTimedoutClients();
 
-    /* Check if a background saving in progress terminated */
-    if (server.bgsaveinprogress) {
+    /* Check if a background saving or AOF rewrite in progress terminated */
+    if (server.bgsavechildpid != -1 || server.bgrewritechildpid != -1) {
         int statloc;
-        if (wait3(&statloc,WNOHANG,NULL)) {
-            int exitcode = WEXITSTATUS(statloc);
-            int bysignal = WIFSIGNALED(statloc);
-
-            if (!bysignal && exitcode == 0) {
-                redisLog(REDIS_NOTICE,
-                    "Background saving terminated with success");
-                server.dirty = 0;
-                server.lastsave = time(NULL);
-            } else if (!bysignal && exitcode != 0) {
-                redisLog(REDIS_WARNING, "Background saving error");
+        pid_t pid;
+
+        if ((pid = wait3(&statloc,WNOHANG,NULL)) != 0) {
+            if (pid == server.bgsavechildpid) {
+                backgroundSaveDoneHandler(statloc);
             } else {
-                redisLog(REDIS_WARNING,
-                    "Background saving terminated by signal");
-                rdbRemoveTempFile(server.bgsavechildpid);
+                backgroundRewriteDoneHandler(statloc);
             }
-            server.bgsaveinprogress = 0;
-            server.bgsavechildpid = -1;
-            updateSlavesWaitingBgsave(exitcode == 0 ? REDIS_OK : REDIS_ERR);
         }
     } else {
         /* If there is not a background saving in progress check if
@@ -1060,7 +1123,7 @@ static void initServerConfig() {
     server.appendseldb = -1; /* Make sure the first time will not match */
     server.pidfile = "/var/run/redis.pid";
     server.dbfilename = "dump.rdb";
-    server.appendfilename = "appendonly.log";
+    server.appendfilename = "appendonly.aof";
     server.requirepass = NULL;
     server.shareobjects = 0;
     server.sharingpoolsize = 1024;
@@ -1112,8 +1175,9 @@ static void initServer() {
         server.db[j].id = j;
     }
     server.cronloops = 0;
-    server.bgsaveinprogress = 0;
     server.bgsavechildpid = -1;
+    server.bgrewritechildpid = -1;
+    server.bgrewritebuf = sdsempty();
     server.lastsave = time(NULL);
     server.dirty = 0;
     server.usedmemory = 0;
@@ -1926,12 +1990,7 @@ static void addReply(redisClient *c, robj *obj) {
          c->replstate == REDIS_REPL_ONLINE) &&
         aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
         sendReplyToClient, c) == AE_ERR) return;
-    if (obj->encoding != REDIS_ENCODING_RAW) {
-        obj = getDecodedObject(obj);
-    } else {
-        incrRefCount(obj);
-    }
-    listAddNodeTail(c->reply,obj);
+    listAddNodeTail(c->reply,getDecodedObject(obj));
 }
 
 static void addReplySds(redisClient *c, sds s) {
@@ -2226,11 +2285,15 @@ static int tryObjectEncoding(robj *o) {
     return REDIS_OK;
 }
 
-/* Get a decoded version of an encoded object (returned as a new object) */
-static robj *getDecodedObject(const robj *o) {
+/* Get a decoded version of an encoded object (returned as a new object).
+ * If the object is already raw-encoded just increment the ref count. */
+static robj *getDecodedObject(robj *o) {
     robj *dec;
     
-    assert(o->encoding != REDIS_ENCODING_RAW);
+    if (o->encoding == REDIS_ENCODING_RAW) {
+        incrRefCount(o);
+        return o;
+    }
     if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_INT) {
         char buf[32];
 
@@ -2419,16 +2482,11 @@ static int rdbSaveStringObjectRaw(FILE *fp, robj *obj) {
 /* Like rdbSaveStringObjectRaw() but handle encoded objects */
 static int rdbSaveStringObject(FILE *fp, robj *obj) {
     int retval;
-    robj *dec;
 
-    if (obj->encoding != REDIS_ENCODING_RAW) {
-        dec = getDecodedObject(obj);
-        retval = rdbSaveStringObjectRaw(fp,dec);
-        decrRefCount(dec);
-        return retval;
-    } else {
-        return rdbSaveStringObjectRaw(fp,obj);
-    }
+    obj = getDecodedObject(obj);
+    retval = rdbSaveStringObjectRaw(fp,obj);
+    decrRefCount(obj);
+    return retval;
 }
 
 /* Save a double value. Doubles are saved as strings prefixed by an unsigned
@@ -2584,7 +2642,7 @@ static int rdbSave(char *filename) {
 static int rdbSaveBackground(char *filename) {
     pid_t childpid;
 
-    if (server.bgsaveinprogress) return REDIS_ERR;
+    if (server.bgsavechildpid != -1) return REDIS_ERR;
     if ((childpid = fork()) == 0) {
         /* Child */
         close(server.fd);
@@ -2601,7 +2659,6 @@ static int rdbSaveBackground(char *filename) {
             return REDIS_ERR;
         }
         redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
-        server.bgsaveinprogress = 1;
         server.bgsavechildpid = childpid;
         return REDIS_OK;
     }
@@ -3193,7 +3250,7 @@ static void typeCommand(redisClient *c) {
 }
 
 static void saveCommand(redisClient *c) {
-    if (server.bgsaveinprogress) {
+    if (server.bgsavechildpid != -1) {
         addReplySds(c,sdsnew("-ERR background save in progress\r\n"));
         return;
     }
@@ -3205,7 +3262,7 @@ static void saveCommand(redisClient *c) {
 }
 
 static void bgsaveCommand(redisClient *c) {
-    if (server.bgsaveinprogress) {
+    if (server.bgsavechildpid != -1) {
         addReplySds(c,sdsnew("-ERR background save already in progress\r\n"));
         return;
     }
@@ -3221,7 +3278,7 @@ static void shutdownCommand(redisClient *c) {
     /* Kill the saving child if there is a background saving in progress.
        We want to avoid race conditions, for instance our saving child may
        overwrite the synchronous saving did by SHUTDOWN. */
-    if (server.bgsaveinprogress) {
+    if (server.bgsavechildpid != -1) {
         redisLog(REDIS_WARNING,"There is a live saving child. Killing it!");
         kill(server.bgsavechildpid,SIGKILL);
         rdbRemoveTempFile(server.bgsavechildpid);
@@ -4628,15 +4685,9 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     }
 
     /* The substitution object may be specially encoded. If so we create
-     * a decoded object on the fly. */
-    if (subst->encoding == REDIS_ENCODING_RAW)
-        /* If we don't need to get a decoded object increment the refcount
-         * so that the final decrRefCount() call will restore the original
-         * count */
-        incrRefCount(subst);
-    else {
-        subst = getDecodedObject(subst);
-    }
+     * a decoded object on the fly. Otherwise getDecodedObject will just
+     * increment the ref count, that we'll decrement later. */
+    subst = getDecodedObject(subst);
 
     ssub = subst->ptr;
     if (sdslen(spat)+sdslen(ssub)-1 > REDIS_SORTKEY_MAX) return NULL;
@@ -4698,20 +4749,13 @@ static int sortCompare(const void *s1, const void *s2) {
             }
         } else {
             /* Compare elements directly */
-            if (so1->obj->encoding == REDIS_ENCODING_RAW &&
-                so2->obj->encoding == REDIS_ENCODING_RAW) {
-                cmp = strcoll(so1->obj->ptr,so2->obj->ptr);
-            } else {
-                robj *dec1, *dec2;
-
-                dec1 = so1->obj->encoding == REDIS_ENCODING_RAW ?
-                    so1->obj : getDecodedObject(so1->obj);
-                dec2 = so2->obj->encoding == REDIS_ENCODING_RAW ?
-                    so2->obj : getDecodedObject(so2->obj);
-                cmp = strcoll(dec1->ptr,dec2->ptr);
-                if (dec1 != so1->obj) decrRefCount(dec1);
-                if (dec2 != so2->obj) decrRefCount(dec2);
-            }
+            robj *dec1, *dec2;
+
+            dec1 = getDecodedObject(so1->obj);
+            dec2 = getDecodedObject(so2->obj);
+            cmp = strcoll(dec1->ptr,dec2->ptr);
+            decrRefCount(dec1);
+            decrRefCount(dec2);
         }
     }
     return server.sort_desc ? -cmp : cmp;
@@ -4830,16 +4874,14 @@ static void sortCommand(redisClient *c) {
                 byval = lookupKeyByPattern(c->db,sortby,vector[j].obj);
                 if (!byval || byval->type != REDIS_STRING) continue;
                 if (alpha) {
-                    if (byval->encoding == REDIS_ENCODING_RAW) {
-                        vector[j].u.cmpobj = byval;
-                        incrRefCount(byval);
-                    } else {
-                        vector[j].u.cmpobj = getDecodedObject(byval);
-                    }
+                    vector[j].u.cmpobj = getDecodedObject(byval);
                 } else {
                     if (byval->encoding == REDIS_ENCODING_RAW) {
                         vector[j].u.score = strtod(byval->ptr,NULL);
                     } else {
+                        /* Don't need to decode the object if it's
+                         * integer-encoded (the only encoding supported) so
+                         * far. We can just cast it */
                         if (byval->encoding == REDIS_ENCODING_INT) {
                             vector[j].u.score = (long)byval->ptr;
                         } else
@@ -4989,7 +5031,7 @@ static void infoCommand(redisClient *c) {
         listLength(server.slaves),
         server.usedmemory,
         server.dirty,
-        server.bgsaveinprogress,
+        server.bgsavechildpid != -1,
         server.lastsave,
         server.stat_numconnections,
         server.stat_numcommands,
@@ -5014,7 +5056,7 @@ static void infoCommand(redisClient *c) {
         keys = dictSize(server.db[j].dict);
         vkeys = dictSize(server.db[j].expires);
         if (keys || vkeys) {
-            info = sdscatprintf(info, "db%d: keys=%lld,expires=%lld\r\n",
+            info = sdscatprintf(info, "db%d:keys=%lld,expires=%lld\r\n",
                 j, keys, vkeys);
         }
     }
@@ -5217,7 +5259,7 @@ static void syncCommand(redisClient *c) {
     redisLog(REDIS_NOTICE,"Slave ask for synchronization");
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
-    if (server.bgsaveinprogress) {
+    if (server.bgsavechildpid != -1) {
         /* Ok a background save is in progress. Let's check if it is a good
          * one for replication, i.e. if there is another slave that is
          * registering differences since the server forked to save */
@@ -5584,13 +5626,11 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
     for (j = 0; j < argc; j++) {
         robj *o = argv[j];
 
-        if (o->encoding != REDIS_ENCODING_RAW)
-            o = getDecodedObject(o);
+        o = getDecodedObject(o);
         buf = sdscatprintf(buf,"$%d\r\n",sdslen(o->ptr));
         buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
         buf = sdscatlen(buf,"\r\n",2);
-        if (o != argv[j])
-            decrRefCount(o);
+        decrRefCount(o);
     }
 
     /* Free the objects from the modified argv for EXPIREAT */
@@ -5737,6 +5777,238 @@ int loadAppendOnlyFile(char *filename) {
     exit(1);
 }
 
+/* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
+static int fwriteBulk(FILE *fp, robj *obj) {
+    char buf[128];
+    obj = getDecodedObject(obj);
+    snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
+    if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
+    if (fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0) goto err;
+    if (fwrite("\r\n",2,1,fp) == 0) goto err;
+    decrRefCount(obj);
+    return 1;
+err:
+    decrRefCount(obj);
+    return 0;
+}
+
+/* Write a double value in bulk format $<count>\r\n<payload>\r\n */
+static int fwriteBulkDouble(FILE *fp, double d) {
+    char buf[128], dbuf[128];
+
+    snprintf(dbuf,sizeof(dbuf),"%.17g\r\n",d);
+    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(dbuf)-2);
+    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
+    if (fwrite(dbuf,strlen(dbuf),1,fp) == 0) return 0;
+    return 1;
+}
+
+/* Write a long value in bulk format $<count>\r\n<payload>\r\n */
+static int fwriteBulkLong(FILE *fp, long l) {
+    char buf[128], lbuf[128];
+
+    snprintf(lbuf,sizeof(lbuf),"%ld\r\n",l);
+    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(lbuf)-2);
+    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
+    if (fwrite(lbuf,strlen(lbuf),1,fp) == 0) return 0;
+    return 1;
+}
+
+/* Write a sequence of commands able to fully rebuild the dataset into
+ * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
+static int rewriteAppendOnlyFile(char *filename) {
+    dictIterator *di = NULL;
+    dictEntry *de;
+    FILE *fp;
+    char tmpfile[256];
+    int j;
+    time_t now = time(NULL);
+
+    /* Note that we have to use a different temp name here compared to the
+     * one used by rewriteAppendOnlyFileBackground() function. */
+    snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
+    fp = fopen(tmpfile,"w");
+    if (!fp) {
+        redisLog(REDIS_WARNING, "Failed rewriting the append only file: %s", strerror(errno));
+        return REDIS_ERR;
+    }
+    for (j = 0; j < server.dbnum; j++) {
+        char selectcmd[] = "*2\r\n$6\r\nSELECT\r\n";
+        redisDb *db = server.db+j;
+        dict *d = db->dict;
+        if (dictSize(d) == 0) continue;
+        di = dictGetIterator(d);
+        if (!di) {
+            fclose(fp);
+            return REDIS_ERR;
+        }
+
+        /* SELECT the new DB */
+        if (fwrite(selectcmd,sizeof(selectcmd)-1,1,fp) == 0) goto werr;
+        if (fwriteBulkLong(fp,j+1) == 0) goto werr;
+
+        /* Iterate this DB writing every entry */
+        while((de = dictNext(di)) != NULL) {
+            robj *key = dictGetEntryKey(de);
+            robj *o = dictGetEntryVal(de);
+            time_t expiretime = getExpire(db,key);
+
+            /* Save the key and associated value */
+            if (rdbSaveStringObject(fp,key) == -1) goto werr;
+            if (o->type == REDIS_STRING) {
+                /* Emit a SET command */
+                char cmd[]="*3\r\n$3\r\nSET\r\n";
+                if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                /* Key and value */
+                if (fwriteBulk(fp,key) == 0) goto werr;
+                if (fwriteBulk(fp,o) == 0) goto werr;
+            } else if (o->type == REDIS_LIST) {
+                /* Emit the RPUSHes needed to rebuild the list */
+                list *list = o->ptr;
+                listNode *ln;
+
+                listRewind(list);
+                while((ln = listYield(list))) {
+                    char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
+                    robj *eleobj = listNodeValue(ln);
+
+                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                    if (fwriteBulk(fp,key) == 0) goto werr;
+                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
+                }
+            } else if (o->type == REDIS_SET) {
+                /* Emit the SADDs needed to rebuild the set */
+                dict *set = o->ptr;
+                dictIterator *di = dictGetIterator(set);
+                dictEntry *de;
+
+                while((de = dictNext(di)) != NULL) {
+                    char cmd[]="*3\r\n$4\r\nSADD\r\n";
+                    robj *eleobj = dictGetEntryKey(de);
+
+                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                    if (fwriteBulk(fp,key) == 0) goto werr;
+                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
+                }
+                dictReleaseIterator(di);
+            } else if (o->type == REDIS_ZSET) {
+                /* Emit the ZADDs needed to rebuild the sorted set */
+                zset *zs = o->ptr;
+                dictIterator *di = dictGetIterator(zs->dict);
+                dictEntry *de;
+
+                while((de = dictNext(di)) != NULL) {
+                    char cmd[]="*4\r\n$4\r\nZADD\r\n";
+                    robj *eleobj = dictGetEntryKey(de);
+                    double *score = dictGetEntryVal(de);
+
+                    if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                    if (fwriteBulk(fp,key) == 0) goto werr;
+                    if (fwriteBulkDouble(fp,*score) == 0) goto werr;
+                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
+                }
+                dictReleaseIterator(di);
+            } else {
+                assert(0 != 0);
+            }
+            /* Save the expire time */
+            if (expiretime != -1) {
+                char cmd[]="*3\r\n$6\r\nEXPIRE\r\n";
+                /* If this key is already expired skip it */
+                if (expiretime < now) continue;
+                if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                if (fwriteBulk(fp,key) == 0) goto werr;
+                if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
+            }
+        }
+        dictReleaseIterator(di);
+    }
+
+    /* Make sure data will not remain on the OS's output buffers */
+    fflush(fp);
+    fsync(fileno(fp));
+    fclose(fp);
+    
+    /* Use RENAME to make sure the DB file is changed atomically only
+     * if the generate DB file is ok. */
+    if (rename(tmpfile,filename) == -1) {
+        redisLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
+        unlink(tmpfile);
+        return REDIS_ERR;
+    }
+    redisLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
+    return REDIS_OK;
+
+werr:
+    fclose(fp);
+    unlink(tmpfile);
+    redisLog(REDIS_WARNING,"Write error writing append only fileon disk: %s", strerror(errno));
+    if (di) dictReleaseIterator(di);
+    return REDIS_ERR;
+}
+
+/* This is how rewriting of the append only file in background works:
+ *
+ * 1) The user calls BGREWRITEAOF
+ * 2) Redis calls this function, that forks():
+ *    2a) the child rewrite the append only file in a temp file.
+ *    2b) the parent accumulates differences in server.bgrewritebuf.
+ * 3) When the child finished '2a' exists.
+ * 4) The parent will trap the exit code, if it's OK, will append the
+ *    data accumulated into server.bgrewritebuf into the temp file, and
+ *    finally will rename(2) the temp file in the actual file name.
+ *    The the new file is reopened as the new append only file. Profit!
+ */
+static int rewriteAppendOnlyFileBackground(void) {
+    pid_t childpid;
+
+    if (server.bgrewritechildpid != -1) return REDIS_ERR;
+    if ((childpid = fork()) == 0) {
+        /* Child */
+        char tmpfile[256];
+        close(server.fd);
+
+        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
+        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
+            exit(0);
+        } else {
+            exit(1);
+        }
+    } else {
+        /* Parent */
+        if (childpid == -1) {
+            redisLog(REDIS_WARNING,
+                "Can't rewrite append only file in background: fork: %s",
+                strerror(errno));
+            return REDIS_ERR;
+        }
+        redisLog(REDIS_NOTICE,
+            "Background append only file rewriting started by pid %d",childpid);
+        server.bgrewritechildpid = childpid;
+        return REDIS_OK;
+    }
+    return REDIS_OK; /* unreached */
+}
+
+static void bgrewriteaofCommand(redisClient *c) {
+    if (server.bgrewritechildpid != -1) {
+        addReplySds(c,sdsnew("-ERR background append only file rewriting already in progress\r\n"));
+        return;
+    }
+    if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
+        addReply(c,shared.ok);
+    } else {
+        addReply(c,shared.err);
+    }
+}
+
+static void aofRemoveTempFile(pid_t childpid) {
+    char tmpfile[256];
+
+    snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) childpid);
+    unlink(tmpfile);
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {
@@ -5909,7 +6181,7 @@ static void segvHandler(int sig, siginfo_t *info, void *secret) {
         listLength(server.slaves),
         server.usedmemory,
         server.dirty,
-        server.bgsaveinprogress,
+        server.bgsavechildpid != -1,
         server.lastsave,
         server.stat_numconnections,
         server.stat_numcommands,