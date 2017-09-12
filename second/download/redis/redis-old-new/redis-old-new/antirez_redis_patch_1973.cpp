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
@@ -594,7 +594,7 @@ void lremCommand(redisClient *c) {
         decrRefCount(obj);
 
     if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
+    addReplyLongLong(c,removed);
     if (removed) touchWatchedKey(c->db,c->argv[1]);
 }
 