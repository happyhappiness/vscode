@@ -1241,6 +1241,7 @@ void clusterCommand(redisClient *c) {
             server.cluster.importing_slots_from[slot] = NULL;
         } else {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
+            return;
         }
         clusterSaveConfigOrDie();
         addReply(c,shared.ok);