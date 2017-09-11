@@ -1239,6 +1239,7 @@ void clusterCommand(redisClient *c) {
             server.cluster.importing_slots_from[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
             server.cluster.importing_slots_from[slot] = NULL;
+            server.cluster.migrating_slots_to[slot] = NULL;
         } else {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;