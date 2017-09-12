@@ -451,6 +451,7 @@ typedef struct pubsubPattern {
 } pubsubPattern;
 
 typedef void redisCommandProc(redisClient *c);
+typedef void redisVmPreloadProc(redisClient *c, struct redisCommand *cmd, int argc, robj **argv);
 struct redisCommand {
     char *name;
     redisCommandProc *proc;
@@ -459,7 +460,7 @@ struct redisCommand {
     /* Use a function to determine which keys need to be loaded
      * in the background prior to executing this command. Takes precedence
      * over vm_firstkey and others, ignored when NULL */
-    redisCommandProc *vm_preload_proc;
+    redisVmPreloadProc *vm_preload_proc;
     /* What keys should be loaded in background when calling this command? */
     int vm_firstkey; /* The first argument that's a key (0 = no keys) */
     int vm_lastkey;  /* THe last argument that's a key */
@@ -609,8 +610,9 @@ static robj *vmReadObjectFromSwap(off_t page, int type);
 static void waitEmptyIOJobsQueue(void);
 static void vmReopenSwapFile(void);
 static int vmFreePage(off_t page);
-static void zunionInterBlockClientOnSwappedKeys(redisClient *c);
-static int blockClientOnSwappedKeys(struct redisCommand *cmd, redisClient *c);
+static void zunionInterBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv);
+static void execBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv);
+static int blockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd);
 static int dontWaitForSwappedKey(redisClient *c, robj *key);
 static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key);
 static void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask);
@@ -828,7 +830,7 @@ static struct redisCommand cmdTable[] = {
     {"lastsave",lastsaveCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"type",typeCommand,2,REDIS_CMD_INLINE,NULL,1,1,1},
     {"multi",multiCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
-    {"exec",execCommand,1,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,NULL,0,0,0},
+    {"exec",execCommand,1,REDIS_CMD_INLINE|REDIS_CMD_DENYOOM,execBlockClientOnSwappedKeys,0,0,0},
     {"discard",discardCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"sync",syncCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
     {"flushdb",flushdbCommand,1,REDIS_CMD_INLINE,NULL,0,0,0},
@@ -1913,6 +1915,9 @@ static void loadServerConfig(char *filename) {
             if ((server.appendonly = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"appendfilename") && argc == 2) {
+            zfree(server.appendfilename);
+            server.appendfilename = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"appendfsync") && argc == 2) {
             if (!strcasecmp(argv[1],"no")) {
                 server.appendfsync = APPENDFSYNC_NO;
@@ -2418,7 +2423,7 @@ static int processCommand(redisClient *c) {
         addReply(c,shared.queued);
     } else {
         if (server.vm_enabled && server.vm_max_threads > 0 &&
-            blockClientOnSwappedKeys(cmd,c)) return 1;
+            blockClientOnSwappedKeys(c,cmd)) return 1;
         call(c,cmd);
     }
 
@@ -4463,7 +4468,12 @@ static void delCommand(redisClient *c) {
 }
 
 static void existsCommand(redisClient *c) {
-    addReply(c,lookupKeyRead(c->db,c->argv[1]) ? shared.cone : shared.czero);
+    expireIfNeeded(c->db,c->argv[1]);
+    if (dictFind(c->db->dict,c->argv[1])) {
+        addReply(c, shared.cone);
+    } else {
+        addReply(c, shared.czero);
+    }
 }
 
 static void selectCommand(redisClient *c) {
@@ -8178,9 +8188,41 @@ static void flushAppendOnlyFile(void) {
     }
 }
 
+static sds catAppendOnlyGenericCommand(sds buf, int argc, robj **argv) {
+    int j;
+    buf = sdscatprintf(buf,"*%d\r\n",argc);
+    for (j = 0; j < argc; j++) {
+        robj *o = getDecodedObject(argv[j]);
+        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
+        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
+        buf = sdscatlen(buf,"\r\n",2);
+        decrRefCount(o);
+    }
+    return buf;
+}
+
+static sds catAppendOnlyExpireAtCommand(sds buf, robj *key, robj *seconds) {
+    int argc = 3;
+    long when;
+    robj *argv[3];
+
+    /* Make sure we can use strtol */
+    seconds = getDecodedObject(seconds);
+    when = time(NULL)+strtol(seconds->ptr,NULL,10);
+    decrRefCount(seconds);
+
+    argv[0] = createStringObject("EXPIREAT",8);
+    argv[1] = key;
+    argv[2] = createObject(REDIS_STRING,
+        sdscatprintf(sdsempty(),"%ld",when));
+    buf = catAppendOnlyGenericCommand(buf, argc, argv);
+    decrRefCount(argv[0]);
+    decrRefCount(argv[2]);
+    return buf;
+}
+
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
     sds buf = sdsempty();
-    int j;
     robj *tmpargv[3];
 
     /* The DB this command was targetting is not the same as the last command
@@ -8194,36 +8236,19 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         server.appendseldb = dictid;
     }
 
-    /* "Fix" the argv vector if the command is EXPIRE. We want to translate
-     * EXPIREs into EXPIREATs calls */
     if (cmd->proc == expireCommand) {
-        long when;
-
-        tmpargv[0] = createStringObject("EXPIREAT",8);
+        /* Translate EXPIRE into EXPIREAT */
+        buf = catAppendOnlyExpireAtCommand(buf,argv[1],argv[2]);
+    } else if (cmd->proc == setexCommand) {
+        /* Translate SETEX to SET and EXPIREAT */
+        tmpargv[0] = createStringObject("SET",3);
         tmpargv[1] = argv[1];
-        incrRefCount(argv[1]);
-        when = time(NULL)+strtol(argv[2]->ptr,NULL,10);
-        tmpargv[2] = createObject(REDIS_STRING,
-            sdscatprintf(sdsempty(),"%ld",when));
-        argv = tmpargv;
-    }
-
-    /* Append the actual command */
-    buf = sdscatprintf(buf,"*%d\r\n",argc);
-    for (j = 0; j < argc; j++) {
-        robj *o = argv[j];
-
-        o = getDecodedObject(o);
-        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
-        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
-        buf = sdscatlen(buf,"\r\n",2);
-        decrRefCount(o);
-    }
-
-    /* Free the objects from the modified argv for EXPIREAT */
-    if (cmd->proc == expireCommand) {
-        for (j = 0; j < 3; j++)
-            decrRefCount(argv[j]);
+        tmpargv[2] = argv[3];
+        buf = catAppendOnlyGenericCommand(buf,3,tmpargv);
+        decrRefCount(tmpargv[0]);
+        buf = catAppendOnlyExpireAtCommand(buf,argv[1],argv[2]);
+    } else {
+        buf = catAppendOnlyGenericCommand(buf,argc,argv);
     }
 
     /* Append to the AOF buffer. This will be flushed on disk just before
@@ -9660,12 +9685,56 @@ static int waitForSwappedKey(redisClient *c, robj *key) {
     return 1;
 }
 
-/* Preload keys needed for the ZUNION and ZINTER commands. */
-static void zunionInterBlockClientOnSwappedKeys(redisClient *c) {
+/* Preload keys for any command with first, last and step values for
+ * the command keys prototype, as defined in the command table. */
+static void waitForMultipleSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
+    int j, last;
+    if (cmd->vm_firstkey == 0) return;
+    last = cmd->vm_lastkey;
+    if (last < 0) last = argc+last;
+    for (j = cmd->vm_firstkey; j <= last; j += cmd->vm_keystep) {
+        redisAssert(j < argc);
+        waitForSwappedKey(c,argv[j]);
+    }
+}
+
+/* Preload keys needed for the ZUNION and ZINTER commands.
+ * Note that the number of keys to preload is user-defined, so we need to
+ * apply a sanity check against argc. */
+static void zunionInterBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
     int i, num;
-    num = atoi(c->argv[2]->ptr);
+    REDIS_NOTUSED(cmd);
+
+    num = atoi(argv[2]->ptr);
+    if (num > (argc-3)) return;
     for (i = 0; i < num; i++) {
-        waitForSwappedKey(c,c->argv[3+i]);
+        waitForSwappedKey(c,argv[3+i]);
+    }
+}
+
+/* Preload keys needed to execute the entire MULTI/EXEC block.
+ *
+ * This function is called by blockClientOnSwappedKeys when EXEC is issued,
+ * and will block the client when any command requires a swapped out value. */
+static void execBlockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd, int argc, robj **argv) {
+    int i, margc;
+    struct redisCommand *mcmd;
+    robj **margv;
+    REDIS_NOTUSED(cmd);
+    REDIS_NOTUSED(argc);
+    REDIS_NOTUSED(argv);
+
+    if (!(c->flags & REDIS_MULTI)) return;
+    for (i = 0; i < c->mstate.count; i++) {
+        mcmd = c->mstate.commands[i].cmd;
+        margc = c->mstate.commands[i].argc;
+        margv = c->mstate.commands[i].argv;
+
+        if (mcmd->vm_preload_proc != NULL) {
+            mcmd->vm_preload_proc(c,mcmd,margc,margv);
+        } else {
+            waitForMultipleSwappedKeys(c,mcmd,margc,margv);
+        }
     }
 }
 
@@ -9679,17 +9748,11 @@ static void zunionInterBlockClientOnSwappedKeys(redisClient *c) {
  *
  * Return 1 if the client is marked as blocked, 0 if the client can
  * continue as the keys it is going to access appear to be in memory. */
-static int blockClientOnSwappedKeys(struct redisCommand *cmd, redisClient *c) {
-    int j, last;
-
+static int blockClientOnSwappedKeys(redisClient *c, struct redisCommand *cmd) {
     if (cmd->vm_preload_proc != NULL) {
-        cmd->vm_preload_proc(c);
+        cmd->vm_preload_proc(c,cmd,c->argc,c->argv);
     } else {
-        if (cmd->vm_firstkey == 0) return 0;
-        last = cmd->vm_lastkey;
-        if (last < 0) last = c->argc+last;
-        for (j = cmd->vm_firstkey; j <= last; j += cmd->vm_keystep)
-            waitForSwappedKey(c,c->argv[j]);
+        waitForMultipleSwappedKeys(c,cmd,c->argc,c->argv);
     }
 
     /* If the client was blocked for at least one key, mark it as blocked. */