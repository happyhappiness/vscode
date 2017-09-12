@@ -245,13 +245,11 @@ void keysCommand(redisClient *c) {
 }
 
 void dbsizeCommand(redisClient *c) {
-    addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",dictSize(c->db->dict)));
+    addReplyLongLong(c,dictSize(c->db->dict));
 }
 
 void lastsaveCommand(redisClient *c) {
-    addReplySds(c,
-        sdscatprintf(sdsempty(),":%lu\r\n",server.lastsave));
+    addReplyLongLong(c,server.lastsave);
 }
 
 void typeCommand(redisClient *c) {