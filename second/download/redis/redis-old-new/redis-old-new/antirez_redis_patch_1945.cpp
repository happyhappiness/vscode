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
@@ -792,7 +792,7 @@ void blockingPopGenericCommand(redisClient *c, int where) {
 
     /* Make sure the timeout is not negative */
     if (lltimeout < 0) {
-        addReplySds(c,sdsnew("-ERR timeout is negative\r\n"));
+        addReplyError(c,"timeout is negative");
         return;
     }
 
@@ -822,7 +822,7 @@ void blockingPopGenericCommand(redisClient *c, int where) {
                      * "real" command will add the last element (the value)
                      * for us. If this souds like an hack to you it's just
                      * because it is... */
-                    addReplySds(c,sdsnew("*2\r\n"));
+                    addReplyMultiBulkLen(c,2);
                     addReplyBulk(c,argv[1]);
                     popGenericCommand(c,where);
 