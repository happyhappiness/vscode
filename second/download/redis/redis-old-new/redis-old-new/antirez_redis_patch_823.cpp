@@ -273,6 +273,7 @@ struct redisCommand redisCommandTable[] = {
     {"bitcount",bitcountCommand,-2,"r",0,NULL,1,1,1,0,0},
     {"bitpos",bitposCommand,-3,"r",0,NULL,1,1,1,0,0},
     {"wait",waitCommand,3,"rs",0,NULL,0,0,0,0,0},
+    {"commands",commandsCommand,0,"rlt",0,NULL,0,0,0,0,0},
     {"pfselftest",pfselftestCommand,1,"r",0,NULL,0,0,0,0,0},
     {"pfadd",pfaddCommand,-2,"wm",0,NULL,1,1,1,0,0},
     {"pfcount",pfcountCommand,-2,"w",0,NULL,1,1,1,0,0},
@@ -2401,6 +2402,73 @@ void timeCommand(redisClient *c) {
     addReplyBulkLongLong(c,tv.tv_usec);
 }
 
+
+static int replyCmdFlag(redisClient *c,
+                        struct redisCommand *cmd, int f, char *reply) {
+    if (cmd->flags & f) {
+        addReplyStatus(c, reply);
+        return 1;
+    }
+    return 0;
+}
+static void replyCmd(redisClient *c, struct redisCommand *cmd) {
+    if (!cmd) {
+        addReply(c, shared.nullbulk);
+    } else {
+        /* We are adding: command name, arg count, flags, first, last, offset */
+        addReplyMultiBulkLen(c, 6);
+        addReplyBulkCString(c, cmd->name);
+        addReplyLongLong(c, cmd->arity);
+
+        int flagcount = 0;
+        void *flaglen = addDeferredMultiBulkLength(c);
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_WRITE, "write");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_READONLY, "readonly");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_DENYOOM, "denyoom");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_ADMIN, "admin");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_PUBSUB, "pubsub");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_NOSCRIPT, "noscript");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_RANDOM, "random");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_SORT_FOR_SCRIPT,"scriptsort");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_LOADING, "loading");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_STALE, "stale");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_SKIP_MONITOR, "skipmonitor");
+        flagcount += replyCmdFlag(c,cmd,REDIS_CMD_ASKING, "asking");
+        if (cmd->getkeys_proc) {
+            addReplyStatus(c, "movablekeys");
+            flagcount += 1;
+        }
+        setDeferredMultiBulkLength(c, flaglen, flagcount);
+
+        addReplyLongLong(c, cmd->firstkey);
+        addReplyLongLong(c, cmd->lastkey);
+        addReplyLongLong(c, cmd->keystep);
+    }
+}
+void commandsCommand(redisClient *c) {
+    dictIterator *di;
+    dictEntry *de;
+
+    if (c->argc > 2 && !strcasecmp(c->argv[1]->ptr, "info")) {
+        int i;
+        addReplyMultiBulkLen(c, c->argc-2);
+        for (i = 2; i < c->argc; i++) {
+            replyCmd(c, dictFetchValue(server.commands, c->argv[i]->ptr));
+        }
+    } else if (c->argc > 2) {
+        addReplyError(c, "Unknown subcommand.");
+        return;
+    } else {
+        addReplyMultiBulkLen(c, dictSize(server.commands));
+        di = dictGetIterator(server.commands);
+        while ((de = dictNext(di)) != NULL) {
+            replyCmd(c, dictGetVal(de));
+        }
+        dictReleaseIterator(di);
+    }
+}
+
+
 /* Convert an amount of bytes into a human readable string in the form
  * of 100B, 2G, 100M, 4K, and so forth. */
 void bytesToHuman(char *s, unsigned long long n) {