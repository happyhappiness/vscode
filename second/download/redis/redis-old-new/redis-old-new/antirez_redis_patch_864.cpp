@@ -3287,17 +3287,19 @@ void clusterCommand(redisClient *c) {
     }
 
     if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
-        long port;
+        long long port;
 
-        if (getLongFromObjectOrReply(c, c->argv[3], &port, NULL) != REDIS_OK) {
-            addReplyError(c,"Invalid TCP port specified");
+        if (getLongLongFromObject(c->argv[3], &port) != REDIS_OK) {
+            addReplyErrorFormat(c,"Invalid TCP port specified: %s",
+                                (char*)c->argv[3]->ptr);
             return;
         }
 
         if (clusterStartHandshake(c->argv[2]->ptr,port) == 0 &&
             errno == EINVAL)
         {
-            addReplyError(c,"Invalid node address specified");
+            addReplyErrorFormat(c,"Invalid node address specified: %s:%s",
+                            (char*)c->argv[2]->ptr, (char*)c->argv[3]->ptr);
         } else {
             addReply(c,shared.ok);
         }