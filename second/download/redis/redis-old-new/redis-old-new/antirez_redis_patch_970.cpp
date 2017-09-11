@@ -2503,6 +2503,7 @@ void sentinelCommand(redisClient *c) {
         sentinelPendingScriptsCommand(c);
     } else if (!strcasecmp(c->argv[1]->ptr,"monitor")) {
         /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
+        sentinelRedisInstance *ri;
         long quorum, port;
         char buf[32];
 
@@ -2518,9 +2519,11 @@ void sentinelCommand(redisClient *c) {
             addReplyError(c,"Invalid IP address specified");
             return;
         }
-        if (createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
-                c->argv[3]->ptr,port,quorum,NULL) == NULL)
-        {
+
+        /* Parameters are valid. Try to create the master instance. */
+        ri = createSentinelRedisInstance(c->argv[2]->ptr,SRI_MASTER,
+                c->argv[3]->ptr,port,quorum,NULL);
+        if (ri == NULL) {
             switch(errno) {
             case EBUSY:
                 addReplyError(c,"Duplicated master name");
@@ -2534,6 +2537,7 @@ void sentinelCommand(redisClient *c) {
             }
         } else {
             sentinelFlushConfig();
+            sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@");
             addReply(c,shared.ok);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"remove")) {
@@ -2542,6 +2546,7 @@ void sentinelCommand(redisClient *c) {
 
         if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
             == NULL) return;
+        sentinelEvent(REDIS_WARNING,"-monitor",ri,"%@");
         dictDelete(sentinel.masters,c->argv[2]->ptr);
         sentinelFlushConfig();
         addReply(c,shared.ok);
@@ -2693,6 +2698,7 @@ void sentinelSetCommand(redisClient *c) {
             if (changes) sentinelFlushConfig();
             return;
         }
+        sentinelEvent(REDIS_WARNING,"+set",ri,"%@ %s %s",option,value);
     }
 
     if (changes) sentinelFlushConfig();