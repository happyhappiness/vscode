@@ -307,6 +307,10 @@ void existsCommand(redisClient *c) {
 void selectCommand(redisClient *c) {
     int id = atoi(c->argv[1]->ptr);
 
+    if (server.cluster_enabled) {
+        addReplyError(c,"SELECT is not allowed in cluster mode");
+        return;
+    }
     if (selectDb(c,id) == REDIS_ERR) {
         addReplyError(c,"invalid DB index");
     } else {
@@ -428,6 +432,11 @@ void moveCommand(redisClient *c) {
     redisDb *src, *dst;
     int srcid;
 
+    if (server.cluster_enabled) {
+        addReplyError(c,"MOVE is not allowed in cluster mode");
+        return;
+    }
+
     /* Obtain source and target DB pointers */
     src = c->db;
     srcid = c->db->id;
@@ -616,3 +625,76 @@ void persistCommand(redisClient *c) {
         }
     }
 }
+
+/* -----------------------------------------------------------------------------
+ * API to get key arguments from commands
+ * ---------------------------------------------------------------------------*/
+
+int *getKeysUsingCommandTable(struct redisCommand *cmd,robj **argv, int argc, int *numkeys) {
+    int j, i = 0, last, *keys;
+    REDIS_NOTUSED(argv);
+
+    if (cmd->firstkey == 0) {
+        *numkeys = 0;
+        return NULL;
+    }
+    last = cmd->lastkey;
+    if (last < 0) last = argc+last;
+    keys = zmalloc(sizeof(int)*((last - cmd->firstkey)+1));
+    for (j = cmd->firstkey; j <= last; j += cmd->keystep) {
+        redisAssert(j < argc);
+        keys[i++] = j;
+    }
+    *numkeys = i;
+    return keys;
+}
+
+int *getKeysFromCommand(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    if (cmd->getkeys_proc) {
+        return cmd->getkeys_proc(cmd,argv,argc,numkeys,flags);
+    } else {
+        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
+    }
+}
+
+void getKeysFreeResult(int *result) {
+    zfree(result);
+}
+
+int *noPreloadGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    if (flags & REDIS_GETKEYS_PRELOAD) {
+        *numkeys = 0;
+        return NULL;
+    } else {
+        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
+    }
+}
+
+int *renameGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    if (flags & REDIS_GETKEYS_PRELOAD) {
+        int *keys = zmalloc(sizeof(int));
+        *numkeys = 1;
+        keys[0] = 1;
+        return keys;
+    } else {
+        return getKeysUsingCommandTable(cmd,argv,argc,numkeys);
+    }
+}
+
+int *zunionInterGetKeys(struct redisCommand *cmd,robj **argv, int argc, int *numkeys, int flags) {
+    int i, num, *keys;
+    REDIS_NOTUSED(cmd);
+    REDIS_NOTUSED(flags);
+
+    num = atoi(argv[2]->ptr);
+    /* Sanity check. Don't return any key if the command is going to
+     * reply with syntax error. */
+    if (num > (argc-3)) {
+        *numkeys = 0;
+        return NULL;
+    }
+    keys = zmalloc(sizeof(int)*num);
+    for (i = 0; i < num; i++) keys[i] = 3+i;
+    *numkeys = num;
+    return keys;
+}