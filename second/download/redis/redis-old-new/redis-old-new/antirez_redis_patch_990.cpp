@@ -2384,6 +2384,7 @@ void sentinelCommand(redisClient *c) {
         /* SENTINEL MASTER <name> */
         sentinelRedisInstance *ri;
 
+        if (c->argc != 3) goto numargserr;
         if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
             == NULL) return;
         addReplySentinelRedisInstance(c,ri);