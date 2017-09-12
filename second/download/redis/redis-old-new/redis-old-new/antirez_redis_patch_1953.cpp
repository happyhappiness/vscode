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