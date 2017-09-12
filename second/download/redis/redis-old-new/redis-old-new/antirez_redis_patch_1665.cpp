@@ -1086,6 +1086,21 @@ sds clusterGenNodesDescription(void) {
                 start = -1;
             }
         }
+
+        /* Just for MYSELF node we also dump info about slots that
+         * we are migrating to other instances or importing from other
+         * instances. */
+        if (node->flags & REDIS_NODE_MYSELF) {
+            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+                if (server.cluster.migrating_slots_to[j]) {
+                    ci = sdscatprintf(ci," [%d->%.40s]",j,
+                        server.cluster.migrating_slots_to[j]->name);
+                } else if (server.cluster.importing_slots_from[j]) {
+                    ci = sdscatprintf(ci," [%d<-%.40s]",j,
+                        server.cluster.importing_slots_from[j]->name);
+                }
+            }
+        }
         ci = sdscatlen(ci,"\n",1);
     }
     dictReleaseIterator(di);
@@ -1206,6 +1221,7 @@ void clusterCommand(redisClient *c) {
         } else {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
         }
+        addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         char *statestr[] = {"ok","fail","needhelp"};
         int slots_assigned = 0, slots_ok = 0, slots_pfail = 0, slots_fail = 0;