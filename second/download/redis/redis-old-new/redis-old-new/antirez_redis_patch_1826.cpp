@@ -817,20 +817,20 @@ int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
     return 1;
 }
 
-int checkTimeout(redisClient *c, robj *object, time_t *timeout) {
-    long long lltimeout;
+int getTimeoutFromObjectOrReply(redisClient *c, robj *object, time_t *timeout) {
+    long tval;
 
-    if (getLongLongFromObject(object, &lltimeout) != REDIS_OK) {
-        addReplyError(c, "timeout is not an integer");
+    if (getLongFromObjectOrReply(c,object,&tval,
+        "timeout is not an integer or out of range") != REDIS_OK)
         return REDIS_ERR;
-    }
 
-    if (lltimeout < 0) {
-        addReplyError(c, "timeout is negative");
+    if (tval < 0) {
+        addReplyError(c,"timeout is negative");
         return REDIS_ERR;
     }
 
-    *timeout = lltimeout;
+    if (tval > 0) tval += time(NULL);
+    *timeout = tval;
 
     return REDIS_OK;
 }
@@ -841,9 +841,8 @@ void blockingPopGenericCommand(redisClient *c, int where) {
     time_t timeout;
     int j;
 
-    if (checkTimeout(c, c->argv[c->argc - 1], &timeout) != REDIS_OK) {
+    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout) != REDIS_OK)
         return;
-    }
 
     for (j = 1; j < c->argc-1; j++) {
         o = lookupKeyWrite(c->db,c->argv[j]);
@@ -894,7 +893,6 @@ void blockingPopGenericCommand(redisClient *c, int where) {
     }
 
     /* If the list is empty or the key does not exists we must block */
-    if (timeout > 0) timeout += time(NULL);
     blockForKeys(c, c->argv + 1, c->argc - 2, timeout, NULL);
 }
 
@@ -909,9 +907,8 @@ void brpopCommand(redisClient *c) {
 void brpoplpushCommand(redisClient *c) {
     time_t timeout;
 
-    if (checkTimeout(c, c->argv[3], &timeout) != REDIS_OK) {
+    if (getTimeoutFromObjectOrReply(c,c->argv[3],&timeout) != REDIS_OK)
         return;
-    }
 
     robj *key = lookupKeyWrite(c->db, c->argv[1]);
 
@@ -922,8 +919,6 @@ void brpoplpushCommand(redisClient *c) {
              * returns immediately. */
             addReply(c, shared.nullmultibulk);
         } else {
-            if (timeout > 0) timeout += time(NULL);
-
             /* The list is empty and the client blocks. */
             blockForKeys(c, c->argv + 1, 1, timeout, c->argv[2]);
         }