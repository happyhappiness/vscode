@@ -211,7 +211,7 @@ void appendCommand(redisClient *c) {
     }
     touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
-    addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",(unsigned long)totlen));
+    addReplyLongLong(c,totlen);
 }
 
 void substrCommand(redisClient *c) {