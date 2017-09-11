@@ -4022,6 +4022,13 @@ void clusterCommand(client *c) {
             }
             clusterDelSlot(slot);
             clusterAddSlot(n,slot);
+        } else if (!strcasecmp(c->argv[3]->ptr,"bumpepoch") && c->argc == 2) {
+            /* CLUSTER BUMPEPOCH */
+            int retval = clusterBumpConfigEpochWithoutConsensus();
+            sds reply = sdscatprintf(sdsempty(),"%s %llu\r\n",
+                    (retval == C_OK) ? "BUMPED" : "STILL",
+                    (unsigned long long) myself->configEpoch);
+            addReplySds(c,reply);
         } else {
             addReplyError(c,
                 "Invalid CLUSTER SETSLOT action or number of arguments");