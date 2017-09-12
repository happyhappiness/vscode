@@ -790,23 +790,28 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     receiver = ln->value;
 
     if (receiver->bstate.target == NULL) {
-      addReplyMultiBulkLen(receiver,2);
-      addReplyBulk(receiver,key);
-      addReplyBulk(receiver,ele);
+        /* BRPOP/BLPOP return a multi-bulk with the name
+         * of the popped list */
+        addReplyMultiBulkLen(receiver,2);
+        addReplyBulk(receiver,key);
+        addReplyBulk(receiver,ele);
     }
     else {
-      robj *dobj = lookupKeyWrite(receiver->db,receiver->bstate.target);
-      if (dobj && checkType(receiver,dobj,REDIS_LIST)) return 0;
+        /* BRPOPLPUSH */
+        robj *dobj = lookupKeyWrite(receiver->db,receiver->bstate.target);
+        if (dobj && checkType(receiver,dobj,REDIS_LIST)) return 0;
 
-      addReplyBulk(receiver,ele);
+        addReplyBulk(receiver,ele);
 
-      /* Create the list if the key does not exist */
-      if (!dobj) {
-          dobj = createZiplistObject();
-          dbAdd(receiver->db,receiver->bstate.target,dobj);
-      }
+        if (!handleClientsWaitingListPush(receiver, receiver->bstate.target, ele)) {
+            /* Create the list if the key does not exist */
+            if (!dobj) {
+                dobj = createZiplistObject();
+                dbAdd(receiver->db, receiver->bstate.target, dobj);
+            }
 
-      listTypePush(dobj,ele,REDIS_HEAD);
+            listTypePush(dobj, ele, REDIS_HEAD);
+        }
     }
 
     unblockClientWaitingData(receiver);
@@ -880,13 +885,13 @@ int checkTimeout(redisClient *c, robj *object, time_t *timeout) {
     long long lltimeout;
 
     if (getLongLongFromObject(object, &lltimeout) != REDIS_OK) {
-      addReplyError(c, "timeout is not an integer");
-      return REDIS_ERR;
+        addReplyError(c, "timeout is not an integer");
+        return REDIS_ERR;
     }
-    
+
     if (lltimeout < 0) {
-      addReplyError(c, "timeout is negative");
-      return REDIS_ERR;
+        addReplyError(c, "timeout is negative");
+        return REDIS_ERR;
     }
 
     *timeout = lltimeout;
@@ -911,20 +916,27 @@ void brpoplpushCommand(redisClient *c) {
 
     robj *key = lookupKeyWrite(c->db, c->argv[1]);
 
-
     if (key == NULL) {
-        // block
         if (c->flags & REDIS_MULTI) {
-            addReply(c,shared.nullmultibulk);
+
+            /* Blocking against an empty list in a multi state
+             * returns immediately. */
+            addReply(c, shared.nullmultibulk);
         } else {
             if (timeout > 0) timeout += time(NULL);
+
+            /* The list is empty and the client blocks. */
             blockForKeys(c, c->argv + 1, 1, timeout, c->argv[2]);
         }
-    } else if (key->type != REDIS_LIST) {
-        addReply(c, shared.wrongtypeerr);
     } else {
-        // The list exists and has elements.
-        redisAssert(listTypeLength(key) > 0);
-        rpoplpushCommand(c);
+        if (key->type != REDIS_LIST) {
+            addReply(c, shared.wrongtypeerr);
+        } else {
+
+            /* The list exists and has elements, so
+             * the regular rpoplpushCommand is executed. */
+            redisAssert(listTypeLength(key) > 0);
+            rpoplpushCommand(c);
+        }
     }
 }