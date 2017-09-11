@@ -743,7 +743,7 @@ void moveCommand(client *c) {
     robj *o;
     redisDb *src, *dst;
     int srcid;
-    long long dbid;
+    long long dbid, expire;
 
     if (server.cluster_enabled) {
         addReplyError(c,"MOVE is not allowed in cluster mode");
@@ -777,13 +777,15 @@ void moveCommand(client *c) {
         addReply(c,shared.czero);
         return;
     }
+    expire = getExpire(c->db,c->argv[1]);
 
     /* Return zero if the key already exists in the target DB */
     if (lookupKeyWrite(dst,c->argv[1]) != NULL) {
         addReply(c,shared.czero);
         return;
     }
     dbAdd(dst,c->argv[1],o);
+    if (expire) setExpire(dst,c->argv[1],expire);
     incrRefCount(o);
 
     /* OK! key moved, free the entry in the source DB */