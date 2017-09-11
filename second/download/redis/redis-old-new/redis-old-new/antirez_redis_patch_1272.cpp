@@ -228,7 +228,11 @@ void existsCommand(redisClient *c) {
 }
 
 void selectCommand(redisClient *c) {
-    int id = atoi(c->argv[1]->ptr);
+    long id;
+
+    if (getLongFromObjectOrReply(c, c->argv[1], &id,
+        "invalid DB index") != REDIS_OK)
+        return;
 
     if (server.cluster_enabled && id != 0) {
         addReplyError(c,"SELECT is not allowed in cluster mode");