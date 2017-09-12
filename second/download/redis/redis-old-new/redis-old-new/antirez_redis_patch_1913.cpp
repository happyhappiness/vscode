@@ -342,7 +342,7 @@ void pushxGenericCommand(redisClient *c, robj *refval, robj *val, int where) {
         server.dirty++;
     }
 
-    addReplyUlong(c,listTypeLength(subject));
+    addReplyLongLong(c,listTypeLength(subject));
 }
 
 void lpushxCommand(redisClient *c) {
@@ -366,7 +366,7 @@ void linsertCommand(redisClient *c) {
 void llenCommand(redisClient *c) {
     robj *o = lookupKeyReadOrReply(c,c->argv[1],shared.czero);
     if (o == NULL || checkType(c,o,REDIS_LIST)) return;
-    addReplyUlong(c,listTypeLength(o));
+    addReplyLongLong(c,listTypeLength(o));
 }
 
 void lindexCommand(redisClient *c) {
@@ -494,7 +494,7 @@ void lrangeCommand(redisClient *c) {
     rangelen = (end-start)+1;
 
     /* Return the result in form of a multi-bulk reply */
-    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
+    addReplyMultiBulkLen(c,rangelen);
     listTypeIterator *li = listTypeInitIterator(o,start,REDIS_TAIL);
     for (j = 0; j < rangelen; j++) {
         redisAssert(listTypeNext(li,&entry));
@@ -594,7 +594,7 @@ void lremCommand(redisClient *c) {
         decrRefCount(obj);
 
     if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
+    addReplyLongLong(c,removed);
     if (removed) touchWatchedKey(c->db,c->argv[1]);
 }
 
@@ -772,7 +772,7 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     redisAssert(ln != NULL);
     receiver = ln->value;
 
-    addReplySds(receiver,sdsnew("*2\r\n"));
+    addReplyMultiBulkLen(receiver,2);
     addReplyBulk(receiver,key);
     addReplyBulk(receiver,ele);
     unblockClientWaitingData(receiver);
@@ -782,9 +782,20 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
 /* Blocking RPOP/LPOP */
 void blockingPopGenericCommand(redisClient *c, int where) {
     robj *o;
+    long long lltimeout;
     time_t timeout;
     int j;
 
+    /* Make sure timeout is an integer value */
+    if (getLongLongFromObjectOrReply(c,c->argv[c->argc-1],&lltimeout,
+            "timeout is not an integer") != REDIS_OK) return;
+
+    /* Make sure the timeout is not negative */
+    if (lltimeout < 0) {
+        addReplyError(c,"timeout is negative");
+        return;
+    }
+
     for (j = 1; j < c->argc-1; j++) {
         o = lookupKeyWrite(c->db,c->argv[j]);
         if (o != NULL) {
@@ -811,7 +822,7 @@ void blockingPopGenericCommand(redisClient *c, int where) {
                      * "real" command will add the last element (the value)
                      * for us. If this souds like an hack to you it's just
                      * because it is... */
-                    addReplySds(c,sdsnew("*2\r\n"));
+                    addReplyMultiBulkLen(c,2);
                     addReplyBulk(c,argv[1]);
                     popGenericCommand(c,where);
 
@@ -823,8 +834,16 @@ void blockingPopGenericCommand(redisClient *c, int where) {
             }
         }
     }
+
+    /* If we are inside a MULTI/EXEC and the list is empty the only thing
+     * we can do is treating it as a timeout (even with timeout 0). */
+    if (c->flags & REDIS_MULTI) {
+        addReply(c,shared.nullmultibulk);
+        return;
+    }
+
     /* If the list is empty or the key does not exists we must block */
-    timeout = strtol(c->argv[c->argc-1]->ptr,NULL,10);
+    timeout = lltimeout;
     if (timeout > 0) timeout += time(NULL);
     blockForKeys(c,c->argv+1,c->argc-2,timeout);
 }