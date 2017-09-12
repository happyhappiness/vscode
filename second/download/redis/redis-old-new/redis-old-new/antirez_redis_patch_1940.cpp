@@ -179,7 +179,7 @@ void syncCommand(redisClient *c) {
     /* Refuse SYNC requests if we are a slave but the link with our master
      * is not ok... */
     if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED) {
-        addReplySds(c,sdsnew("-ERR Can't SYNC while not connected with my master\r\n"));
+        addReplyError(c,"Can't SYNC while not connected with my master");
         return;
     }
 
@@ -188,7 +188,7 @@ void syncCommand(redisClient *c) {
      * buffer registering the differences between the BGSAVE and the current
      * dataset, so that we can copy to other slaves if needed. */
     if (listLength(c->reply) != 0) {
-        addReplySds(c,sdsnew("-ERR SYNC is invalid with pending input\r\n"));
+        addReplyError(c,"SYNC is invalid with pending input");
         return;
     }
 
@@ -226,7 +226,7 @@ void syncCommand(redisClient *c) {
         redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
         if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
             redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
-            addReplySds(c,sdsnew("-ERR Unalbe to perform background save\r\n"));
+            addReplyError(c,"Unable to perform background save");
             return;
         }
         c->replstate = REDIS_REPL_WAIT_BGSAVE_END;