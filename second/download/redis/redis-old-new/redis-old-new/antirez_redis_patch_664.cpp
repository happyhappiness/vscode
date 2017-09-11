@@ -3886,10 +3886,7 @@ void clusterCommand(redisClient *c) {
             server.cluster->stats_bus_messages_sent,
             server.cluster->stats_bus_messages_received
         );
-        addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
-            (unsigned long)sdslen(info)));
-        addReplySds(c,info);
-        addReply(c,shared.crlf);
+        addReplyBulkSds(c, info);
     } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
         int retval = clusterSaveConfig(1);
 