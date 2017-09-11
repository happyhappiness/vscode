@@ -280,6 +280,7 @@ void delCommand(redisClient *c) {
     int deleted = 0, j;
 
     for (j = 1; j < c->argc; j++) {
+        expireIfNeeded(c->db,c->argv[j]);
         if (dbDelete(c->db,c->argv[j])) {
             signalModifiedKey(c->db,c->argv[j]);
             notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,