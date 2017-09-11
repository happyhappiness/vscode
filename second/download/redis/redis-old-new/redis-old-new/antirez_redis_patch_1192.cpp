@@ -1440,6 +1440,7 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;
         }
+        clusterUpdateState();
         clusterSaveConfigOrDie();
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {