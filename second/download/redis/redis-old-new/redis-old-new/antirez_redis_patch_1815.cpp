@@ -621,20 +621,38 @@ void lremCommand(redisClient *c) {
 
 /* This is the semantic of this command:
  *  RPOPLPUSH srclist dstlist:
- *   IF LLEN(srclist) > 0
- *     element = RPOP srclist
- *     LPUSH dstlist element
- *     RETURN element
- *   ELSE
- *     RETURN nil
- *   END
+ *    IF LLEN(srclist) > 0
+ *      element = RPOP srclist
+ *      LPUSH dstlist element
+ *      RETURN element
+ *    ELSE
+ *      RETURN nil
+ *    END
  *  END
  *
  * The idea is to be able to get an element from a list in a reliable way
  * since the element is not just returned but pushed against another list
  * as well. This command was originally proposed by Ezra Zygmuntowicz.
  */
-void rpoplpushcommand(redisClient *c) {
+
+void rpoplpushHandlePush(redisClient *c, robj *dstkey, robj *dstobj, robj *value) {
+    if (!handleClientsWaitingListPush(c,dstkey,value)) {
+        /* Create the list if the key does not exist */
+        if (!dstobj) {
+            dstobj = createZiplistObject();
+            dbAdd(c->db,dstkey,dstobj);
+        } else {
+            touchWatchedKey(c->db,dstkey);
+            server.dirty++;
+        }
+        listTypePush(dstobj,value,REDIS_HEAD);
+    }
+
+    /* Always send the pushed value to the client. */
+    addReplyBulk(c,value);
+}
+
+void rpoplpushCommand(redisClient *c) {
     robj *sobj, *value;
     if ((sobj = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
         checkType(c,sobj,REDIS_LIST)) return;
@@ -645,20 +663,7 @@ void rpoplpushcommand(redisClient *c) {
         robj *dobj = lookupKeyWrite(c->db,c->argv[2]);
         if (dobj && checkType(c,dobj,REDIS_LIST)) return;
         value = listTypePop(sobj,REDIS_TAIL);
-
-        /* Add the element to the target list (unless it's directly
-         * passed to some BLPOP-ing client */
-        if (!handleClientsWaitingListPush(c,c->argv[2],value)) {
-            /* Create the list if the key does not exist */
-            if (!dobj) {
-                dobj = createZiplistObject();
-                dbAdd(c->db,c->argv[2],dobj);
-            }
-            listTypePush(dobj,value,REDIS_HEAD);
-        }
-
-        /* Send the element to the client as reply as well */
-        addReplyBulk(c,value);
+        rpoplpushHandlePush(c,c->argv[2],dobj,value);
 
         /* listTypePop returns an object with its refcount incremented */
         decrRefCount(value);
@@ -705,17 +710,23 @@ void rpoplpushcommand(redisClient *c) {
 
 /* Set a client in blocking mode for the specified key, with the specified
  * timeout */
-void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout) {
+void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout, robj *target) {
     dictEntry *de;
     list *l;
     int j;
 
-    c->blocking_keys = zmalloc(sizeof(robj*)*numkeys);
-    c->blocking_keys_num = numkeys;
-    c->blockingto = timeout;
+    c->bpop.keys = zmalloc(sizeof(robj*)*numkeys);
+    c->bpop.count = numkeys;
+    c->bpop.timeout = timeout;
+    c->bpop.target = target;
+
+    if (target != NULL) {
+        incrRefCount(target);
+    }
+
     for (j = 0; j < numkeys; j++) {
         /* Add the key in the client structure, to map clients -> keys */
-        c->blocking_keys[j] = keys[j];
+        c->bpop.keys[j] = keys[j];
         incrRefCount(keys[j]);
 
         /* And in the other "side", to map keys -> clients */
@@ -735,7 +746,7 @@ void blockForKeys(redisClient *c, robj **keys, int numkeys, time_t timeout) {
     }
     /* Mark the client as a blocked client */
     c->flags |= REDIS_BLOCKED;
-    server.blpop_blocked_clients++;
+    server.bpop_blocked_clients++;
 }
 
 /* Unblock a client that's waiting in a blocking operation such as BLPOP */
@@ -744,30 +755,27 @@ void unblockClientWaitingData(redisClient *c) {
     list *l;
     int j;
 
-    redisAssert(c->blocking_keys != NULL);
+    redisAssert(c->bpop.keys != NULL);
     /* The client may wait for multiple keys, so unblock it for every key. */
-    for (j = 0; j < c->blocking_keys_num; j++) {
+    for (j = 0; j < c->bpop.count; j++) {
         /* Remove this client from the list of clients waiting for this key. */
-        de = dictFind(c->db->blocking_keys,c->blocking_keys[j]);
+        de = dictFind(c->db->blocking_keys,c->bpop.keys[j]);
         redisAssert(de != NULL);
         l = dictGetEntryVal(de);
         listDelNode(l,listSearchKey(l,c));
         /* If the list is empty we need to remove it to avoid wasting memory */
         if (listLength(l) == 0)
-            dictDelete(c->db->blocking_keys,c->blocking_keys[j]);
-        decrRefCount(c->blocking_keys[j]);
+            dictDelete(c->db->blocking_keys,c->bpop.keys[j]);
+        decrRefCount(c->bpop.keys[j]);
     }
+
     /* Cleanup the client structure */
-    zfree(c->blocking_keys);
-    c->blocking_keys = NULL;
+    zfree(c->bpop.keys);
+    c->bpop.keys = NULL;
+    c->bpop.target = NULL;
     c->flags &= (~REDIS_BLOCKED);
-    server.blpop_blocked_clients--;
-    /* We want to process data if there is some command waiting
-     * in the input buffer. Note that this is safe even if
-     * unblockClientWaitingData() gets called from freeClient() because
-     * freeClient() will be smart enough to call this function
-     * *after* c->querybuf was set to NULL. */
-    if (c->querybuf && sdslen(c->querybuf) > 0) processInputBuffer(c);
+    server.bpop_blocked_clients--;
+    listAddNodeTail(server.unblocked_clients,c);
 }
 
 /* This should be called from any function PUSHing into lists.
@@ -783,39 +791,81 @@ void unblockClientWaitingData(redisClient *c) {
 int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     struct dictEntry *de;
     redisClient *receiver;
-    list *l;
+    int numclients;
+    list *clients;
     listNode *ln;
+    robj *dstkey, *dstobj;
 
     de = dictFind(c->db->blocking_keys,key);
     if (de == NULL) return 0;
-    l = dictGetEntryVal(de);
-    ln = listFirst(l);
-    redisAssert(ln != NULL);
-    receiver = ln->value;
+    clients = dictGetEntryVal(de);
+    numclients = listLength(clients);
+
+    /* Try to handle the push as long as there are clients waiting for a push.
+     * Note that "numclients" is used because the list of clients waiting for a
+     * push on "key" is deleted by unblockClient() when empty.
+     *
+     * This loop will have more than 1 iteration when there is a BRPOPLPUSH
+     * that cannot push the target list because it does not contain a list. If
+     * this happens, it simply tries the next client waiting for a push. */
+    while (numclients--) {
+        ln = listFirst(clients);
+        redisAssert(ln != NULL);
+        receiver = ln->value;
+        dstkey = receiver->bpop.target;
+
+        /* This should remove the first element of the "clients" list. */
+        unblockClientWaitingData(receiver);
+        redisAssert(ln != listFirst(clients));
+
+        if (dstkey == NULL) {
+            /* BRPOP/BLPOP */
+            addReplyMultiBulkLen(receiver,2);
+            addReplyBulk(receiver,key);
+            addReplyBulk(receiver,ele);
+            return 1;
+        } else {
+            /* BRPOPLPUSH */
+            dstobj = lookupKeyWrite(receiver->db,dstkey);
+            if (dstobj && checkType(receiver,dstobj,REDIS_LIST)) {
+                decrRefCount(dstkey);
+            } else {
+                rpoplpushHandlePush(receiver,dstkey,dstobj,ele);
+                decrRefCount(dstkey);
+                return 1;
+            }
+        }
+    }
 
-    addReplyMultiBulkLen(receiver,2);
-    addReplyBulk(receiver,key);
-    addReplyBulk(receiver,ele);
-    unblockClientWaitingData(receiver);
-    return 1;
+    return 0;
+}
+
+int getTimeoutFromObjectOrReply(redisClient *c, robj *object, time_t *timeout) {
+    long tval;
+
+    if (getLongFromObjectOrReply(c,object,&tval,
+        "timeout is not an integer or out of range") != REDIS_OK)
+        return REDIS_ERR;
+
+    if (tval < 0) {
+        addReplyError(c,"timeout is negative");
+        return REDIS_ERR;
+    }
+
+    if (tval > 0) tval += time(NULL);
+    *timeout = tval;
+
+    return REDIS_OK;
 }
 
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
+    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout) != REDIS_OK)
         return;
-    }
 
     for (j = 1; j < c->argc-1; j++) {
         o = lookupKeyWrite(c->db,c->argv[j]);
@@ -845,11 +895,13 @@ void blockingPopGenericCommand(redisClient *c, int where) {
                      * because it is... */
                     addReplyMultiBulkLen(c,2);
                     addReplyBulk(c,argv[1]);
+
                     popGenericCommand(c,where);
 
                     /* Fix the client structure with the original stuff */
                     c->argv = orig_argv;
                     c->argc = orig_argc;
+
                     return;
                 }
             }
@@ -864,9 +916,7 @@ void blockingPopGenericCommand(redisClient *c, int where) {
     }
 
     /* If the list is empty or the key does not exists we must block */
-    timeout = lltimeout;
-    if (timeout > 0) timeout += time(NULL);
-    blockForKeys(c,c->argv+1,c->argc-2,timeout);
+    blockForKeys(c, c->argv + 1, c->argc - 2, timeout, NULL);
 }
 
 void blpopCommand(redisClient *c) {
@@ -876,3 +926,34 @@ void blpopCommand(redisClient *c) {
 void brpopCommand(redisClient *c) {
     blockingPopGenericCommand(c,REDIS_TAIL);
 }
+
+void brpoplpushCommand(redisClient *c) {
+    time_t timeout;
+
+    if (getTimeoutFromObjectOrReply(c,c->argv[3],&timeout) != REDIS_OK)
+        return;
+
+    robj *key = lookupKeyWrite(c->db, c->argv[1]);
+
+    if (key == NULL) {
+        if (c->flags & REDIS_MULTI) {
+
+            /* Blocking against an empty list in a multi state
+             * returns immediately. */
+            addReply(c, shared.nullmultibulk);
+        } else {
+            /* The list is empty and the client blocks. */
+            blockForKeys(c, c->argv + 1, 1, timeout, c->argv[2]);
+        }
+    } else {
+        if (key->type != REDIS_LIST) {
+            addReply(c, shared.wrongtypeerr);
+        } else {
+
+            /* The list exists and has elements, so
+             * the regular rpoplpushCommand is executed. */
+            redisAssert(listTypeLength(key) > 0);
+            rpoplpushCommand(c);
+        }
+    }
+}