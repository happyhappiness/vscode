@@ -3041,6 +3041,7 @@ void sentinelCommand(redisClient *c) {
         sentinelRedisInstance *ri;
         int usable;
 
+        if (c->argc != 3) goto numargserr;
         if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
             == NULL) return;
         int result = sentinelIsQuorumReachable(ri,&usable);