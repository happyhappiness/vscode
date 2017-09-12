@@ -514,15 +514,14 @@ void expireatCommand(redisClient *c) {
 }
 
 void ttlCommand(redisClient *c) {
-    time_t expire;
-    int ttl = -1;
+    time_t expire, ttl = -1;
 
     expire = getExpire(c->db,c->argv[1]);
     if (expire != -1) {
-        ttl = (int) (expire-time(NULL));
+        ttl = (expire-time(NULL));
         if (ttl < 0) ttl = -1;
     }
-    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
+    addReplyLongLong(c,(long long)ttl);
 }
 
 void persistCommand(redisClient *c) {