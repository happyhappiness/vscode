@@ -4174,18 +4174,22 @@ void clusterCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"failover") &&
                (c->argc == 2 || c->argc == 3))
     {
-        /* CLUSTER FAILOVER [FORCE] */
-        int force = 0;
+        /* CLUSTER FAILOVER [FORCE|TAKEOVER] */
+        int force = 0, takeover = 0;
 
         if (c->argc == 3) {
             if (!strcasecmp(c->argv[2]->ptr,"force")) {
                 force = 1;
+            } else if (!strcasecmp(c->argv[2]->ptr,"takeover")) {
+                takeover = 1;
+                force = 1; /* Takeover also implies force. */
             } else {
                 addReply(c,shared.syntaxerr);
                 return;
             }
         }
 
+        /* Check preconditions. */
         if (nodeIsMaster(myself)) {
             addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
             return;
@@ -4203,15 +4207,24 @@ void clusterCommand(redisClient *c) {
         resetManualFailover();
         server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
 
-        /* If this is a forced failover, we don't need to talk with our master
-         * to agree about the offset. We just failover taking over it without
-         * coordination. */
-        if (force) {
+        if (takeover) {
+            /* A takeover does not perform any initial check. It just
+             * generates a new configuration epoch for this node without
+             * consensus, claims the master's slots, and broadcast the new
+             * configuration. */
+            redisLog(REDIS_WARNING,"Taking over the master (user request).");
+            clusterBumpConfigEpochWithoutConsensus();
+            clusterFailoverReplaceYourMaster();
+        } else if (force) {
+            /* If this is a forced failover, we don't need to talk with our
+             * master to agree about the offset. We just failover taking over
+             * it without coordination. */
+            redisLog(REDIS_WARNING,"Forced failover user request accepted.");
             server.cluster->mf_can_start = 1;
         } else {
+            redisLog(REDIS_WARNING,"Manual failover user request accepted.");
             clusterSendMFStart(myself->slaveof);
         }
-        redisLog(REDIS_WARNING,"Manual failover user request accepted.");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"set-config-epoch") && c->argc == 3)
     {