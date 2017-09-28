     gettimeofday(&tv,NULL);
     addReplyMultiBulkLen(c,2);
     addReplyBulkLongLong(c,tv.tv_sec);
     addReplyBulkLongLong(c,tv.tv_usec);
 }
 
+
+/* Helper function for addReplyCommand() to output flags. */
+int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *reply) {
+    if (cmd->flags & f) {
+        addReplyStatus(c, reply);
+        return 1;
+    }
+    return 0;
+}
+
+/* Output the representation of a Redis command. Used by the COMMAND command. */
+void addReplyCommand(redisClient *c, struct redisCommand *cmd) {
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
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_WRITE, "write");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_READONLY, "readonly");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_DENYOOM, "denyoom");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_ADMIN, "admin");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_PUBSUB, "pubsub");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_NOSCRIPT, "noscript");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_RANDOM, "random");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_SORT_FOR_SCRIPT,"sort_for_script");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_LOADING, "loading");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_STALE, "stale");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_SKIP_MONITOR, "skip_monitor");
+        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_FAST, "fast");
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
+
+/* COMMAND <subcommand> <args> */
+void commandCommand(redisClient *c) {
+    dictIterator *di;
+    dictEntry *de;
+
+    if (c->argc == 1) {
+        addReplyMultiBulkLen(c, dictSize(server.commands));
+        di = dictGetIterator(server.commands);
+        while ((de = dictNext(di)) != NULL) {
+            addReplyCommand(c, dictGetVal(de));
+        }
+        dictReleaseIterator(di);
+    } else if (!strcasecmp(c->argv[1]->ptr, "info")) {
+        int i;
+        addReplyMultiBulkLen(c, c->argc-2);
+        for (i = 2; i < c->argc; i++) {
+            addReplyCommand(c, dictFetchValue(server.commands, c->argv[i]->ptr));
+        }
+    } else if (!strcasecmp(c->argv[1]->ptr, "count") && c->argc == 2) {
+        addReplyLongLong(c, dictSize(server.commands));
+    } else {
+        addReplyError(c, "Unknown subcommand or wrong number of arguments.");
+        return;
+    }
+}
+
 /* Convert an amount of bytes into a human readable string in the form
  * of 100B, 2G, 100M, 4K, and so forth. */
 void bytesToHuman(char *s, unsigned long long n) {
     double d;
 
     if (n < 1024) {
