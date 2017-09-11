@@ -531,7 +531,6 @@ void syncCommand(redisClient *c) {
             redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
             /* Ok we don't have a BGSAVE in progress, let's start one. */
-            redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
             if (startBgsaveForReplication() != REDIS_OK) {
                 redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
                 addReplyError(c,"Unable to perform background save");