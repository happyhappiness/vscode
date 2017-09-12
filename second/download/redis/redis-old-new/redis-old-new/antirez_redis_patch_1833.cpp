@@ -689,14 +689,20 @@ void rpoplpushCommand(redisClient *c) {
 
 /* Set a client in blocking mode for the specified key, with the specified
  * timeout */
-void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout) {
+void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout, robj *target) {
     dictEntry *de;
     list *l;
     int j;
 
     c->bstate.keys = zmalloc(sizeof(robj*)*numkeys);
     c->bstate.count = numkeys;
     c->bstate.timeout = timeout;
+    c->bstate.target = target;
+
+    if (target != NULL) {
+      incrRefCount(target);
+    }
+
     for (j = 0; j < numkeys; j++) {
         /* Add the key in the client structure, to map clients -> keys */
         c->bstate.keys[j] = keys[j];
@@ -741,9 +747,15 @@ void unblockClientWaitingData(redisClient *c) {
             dictDelete(c->db->blocking_keys,c->bstate.keys[j]);
         decrRefCount(c->bstate.keys[j]);
     }
+
+    if (c->bstate.target != NULL) {
+        decrRefCount(c->bstate.target);
+    }
+
     /* Cleanup the client structure */
     zfree(c->bstate.keys);
     c->bstate.keys = NULL;
+    c->bstate.target = NULL;
     c->flags &= (~REDIS_BLOCKED);
     server.blpop_blocked_clients--;
     /* We want to process data if there is some command waiting
@@ -783,8 +795,6 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
       addReplyBulk(receiver,ele);
     }
     else {
-      receiver->argc++;
-
       robj *dobj = lookupKeyWrite(receiver->db,receiver->bstate.target);
       if (dobj && checkType(receiver,dobj,REDIS_LIST)) return 0;
 
@@ -806,17 +816,10 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
 /* Blocking RPOP/LPOP */
 void blockingPopGenericCommand(redisClient *c, int where) {
     robj *o;
-    long long lltimeout;
     time_t timeout;
     int j;
 
-    /* Make sure timeout is an integer value */
-    if (getLongLongFromObjectOrReply(c,c->argv[c->argc-1],&lltimeout,
-            "timeout is not an integer") != REDIS_OK) return;
-
-    /* Make sure the timeout is not negative */
-    if (lltimeout < 0) {
-        addReplyError(c,"timeout is negative");
+    if (checkTimeout(c, c->argv[c->argc - 1], &timeout) != REDIS_OK) {
         return;
     }
 
@@ -833,35 +836,27 @@ void blockingPopGenericCommand(redisClient *c, int where) {
                     robj *argv[2], **orig_argv;
                     int orig_argc;
 
-                    if (c->bstate.target == NULL) {
-                      /* We need to alter the command arguments before to call
-                       * popGenericCommand() as the command takes a single key. */
-                      orig_argv = c->argv;
-                      orig_argc = c->argc;
-                      argv[1] = c->argv[j];
-                      c->argv = argv;
-                      c->argc = 2;
-
-                      /* Also the return value is different, we need to output
-                       * the multi bulk reply header and the key name. The
-                       * "real" command will add the last element (the value)
-                       * for us. If this souds like an hack to you it's just
-                       * because it is... */
-                      addReplyMultiBulkLen(c,2);
-                      addReplyBulk(c,argv[1]);
-
-                      popGenericCommand(c,where);
-
-                      /* Fix the client structure with the original stuff */
-                      c->argv = orig_argv;
-                      c->argc = orig_argc;
-                    }
-                    else {
-                      c->argv[2] = c->bstate.target;
-                      c->bstate.target = NULL;
-
-                      rpoplpushCommand(c);
-                    }
+                    /* We need to alter the command arguments before to call
+                     * popGenericCommand() as the command takes a single key. */
+                    orig_argv = c->argv;
+                    orig_argc = c->argc;
+                    argv[1] = c->argv[j];
+                    c->argv = argv;
+                    c->argc = 2;
+
+                    /* Also the return value is different, we need to output
+                     * the multi bulk reply header and the key name. The
+                     * "real" command will add the last element (the value)
+                     * for us. If this souds like an hack to you it's just
+                     * because it is... */
+                    addReplyMultiBulkLen(c,2);
+                    addReplyBulk(c,argv[1]);
+
+                    popGenericCommand(c,where);
+
+                    /* Fix the client structure with the original stuff */
+                    c->argv = orig_argv;
+                    c->argc = orig_argc;
 
                     return;
                 }
@@ -877,9 +872,26 @@ void blockingPopGenericCommand(redisClient *c, int where) {
     }
 
     /* If the list is empty or the key does not exists we must block */
-    timeout = lltimeout;
     if (timeout > 0) timeout += time(NULL);
-    blockForKeys(c,c->argv+1,c->argc-2,timeout);
+    blockForKeys(c, c->argv + 1, c->argc - 2, timeout, NULL);
+}
+
+int checkTimeout(redisClient *c, robj *object, time_t *timeout) {
+    long long lltimeout;
+
+    if (getLongLongFromObject(object, &lltimeout) != REDIS_OK) {
+      addReplyError(c, "timeout is not an integer");
+      return REDIS_ERR;
+    }
+    
+    if (lltimeout < 0) {
+      addReplyError(c, "timeout is negative");
+      return REDIS_ERR;
+    }
+
+    *timeout = lltimeout;
+
+    return REDIS_OK;
 }
 
 void blpopCommand(redisClient *c) {
@@ -891,9 +903,28 @@ void brpopCommand(redisClient *c) {
 }
 
 void brpoplpushCommand(redisClient *c) {
-    c->bstate.target = c->argv[2];
-    c->argv[2] = c->argv[3];
-    c->argc--;
+    time_t timeout;
 
-    blockingPopGenericCommand(c,REDIS_TAIL);
+    if (checkTimeout(c, c->argv[3], &timeout) != REDIS_OK) {
+        return;
+    }
+
+    robj *key = lookupKeyWrite(c->db, c->argv[1]);
+
+
+    if (key == NULL) {
+        // block
+        if (c->flags & REDIS_MULTI) {
+            addReply(c,shared.nullmultibulk);
+        } else {
+            if (timeout > 0) timeout += time(NULL);
+            blockForKeys(c, c->argv + 1, 1, timeout, c->argv[2]);
+        }
+    } else if (key->type != REDIS_LIST) {
+        addReply(c, shared.wrongtypeerr);
+    } else {
+        // The list exists and has elements.
+        redisAssert(listTypeLength(key) > 0);
+        rpoplpushCommand(c);
+    }
 }