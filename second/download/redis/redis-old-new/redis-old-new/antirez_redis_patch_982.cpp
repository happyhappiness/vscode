@@ -3317,6 +3317,8 @@ void clusterCommand(redisClient *c) {
         resetManualFailover();
         server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
         clusterSendMFStart(myself->slaveof);
+        redisLog(REDIS_WARNING,"Manual failover user request accepted.");
+        addReply(c,shared.ok);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
     }