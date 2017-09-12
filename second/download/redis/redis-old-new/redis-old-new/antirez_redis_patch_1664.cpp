@@ -115,7 +115,30 @@ int clusterLoadConfig(char *filename) {
         for (j = 7; j < argc; j++) {
             int start, stop;
 
-            if ((p = strchr(argv[j],'-')) != NULL) {
+            if (argv[j][0] == '[') {
+                /* Here we handle migrating / importing slots */
+                int slot;
+                char direction;
+                clusterNode *cn;
+
+                p = strchr(argv[j],'-');
+                redisAssert(p != NULL);
+                *p = '\0';
+                direction = p[1]; /* Either '>' or '<' */
+                slot = atoi(argv[j]+1);
+                p += 3;
+                cn = clusterLookupNode(p);
+                if (!cn) {
+                    cn = createClusterNode(p,0);
+                    clusterAddNode(cn);
+                }
+                if (direction == '>') {
+                    server.cluster.migrating_slots_to[slot] = cn;
+                } else {
+                    server.cluster.importing_slots_from[slot] = cn;
+                }
+                continue;
+            } else if ((p = strchr(argv[j],'-')) != NULL) {
                 *p = '\0';
                 start = atoi(argv[j]);
                 stop = atoi(p+1);
@@ -1093,10 +1116,10 @@ sds clusterGenNodesDescription(void) {
         if (node->flags & REDIS_NODE_MYSELF) {
             for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                 if (server.cluster.migrating_slots_to[j]) {
-                    ci = sdscatprintf(ci," [%d->%.40s]",j,
+                    ci = sdscatprintf(ci," [%d->-%.40s]",j,
                         server.cluster.migrating_slots_to[j]->name);
                 } else if (server.cluster.importing_slots_from[j]) {
-                    ci = sdscatprintf(ci," [%d<-%.40s]",j,
+                    ci = sdscatprintf(ci," [%d-<-%.40s]",j,
                         server.cluster.importing_slots_from[j]->name);
                 }
             }
@@ -1221,6 +1244,7 @@ void clusterCommand(redisClient *c) {
         } else {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
         }
+        clusterSaveConfigOrDie();
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         char *statestr[] = {"ok","fail","needhelp"};