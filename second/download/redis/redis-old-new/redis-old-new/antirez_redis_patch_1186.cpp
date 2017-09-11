@@ -1659,8 +1659,7 @@ void clusterCommand(redisClient *c) {
             return;
         if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL) != REDIS_OK)
             return;
-        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0 ||
-            maxkeys > 1024*1024) {
+        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0) {
             addReplyError(c,"Invalid slot or number of keys");
             return;
         }