@@ -307,6 +307,10 @@ void existsCommand(redisClient *c) {
 void selectCommand(redisClient *c) {
     int id = atoi(c->argv[1]->ptr);
 
+    if (server.cluster_enabled) {
+        addReplyError(c,"SELECT is not allowed in cluster mode");
+        return;
+    }
     if (selectDb(c,id) == REDIS_ERR) {
         addReplyError(c,"invalid DB index");
     } else {
@@ -428,6 +432,11 @@ void moveCommand(redisClient *c) {
     redisDb *src, *dst;
     int srcid;
 
+    if (server.cluster_enabled) {
+        addReplyError(c,"MOVE is not allowed in cluster mode");
+        return;
+    }
+
     /* Obtain source and target DB pointers */
     src = c->db;
     srcid = c->db->id;