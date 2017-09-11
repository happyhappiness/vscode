@@ -1824,6 +1824,7 @@ void configCommand(redisClient *c) {
             return;
         }
         if (rewriteConfig(server.configfile) == -1) {
+            redisLog(REDIS_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
             addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
         } else {
             addReply(c,shared.ok);