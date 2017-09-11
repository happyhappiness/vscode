@@ -2027,6 +2027,7 @@ int processCommand(redisClient *c) {
                 addReplyError(c,"Multi keys request invalid in cluster");
                 return REDIS_OK;
             } else if (n != server.cluster->myself) {
+                flagTransaction(c);
                 addReplySds(c,sdscatprintf(sdsempty(),
                     "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
                     hashslot,n->ip,n->port));