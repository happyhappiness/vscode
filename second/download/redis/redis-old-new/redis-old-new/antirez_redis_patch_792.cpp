@@ -707,6 +707,7 @@ void moveCommand(redisClient *c) {
     robj *o;
     redisDb *src, *dst;
     int srcid;
+    long long dbid;
 
     if (server.cluster_enabled) {
         addReplyError(c,"MOVE is not allowed in cluster mode");
@@ -716,7 +717,11 @@ void moveCommand(redisClient *c) {
     /* Obtain source and target DB pointers */
     src = c->db;
     srcid = c->db->id;
-    if (selectDb(c,atoi(c->argv[2]->ptr)) == REDIS_ERR) {
+
+    if (getLongLongFromObject(c->argv[2],&dbid) == REDIS_ERR ||
+        dbid < INT_MIN || dbid > INT_MAX ||
+        selectDb(c,dbid) == REDIS_ERR)
+    {
         addReply(c,shared.outofrangeerr);
         return;
     }