@@ -70,6 +70,8 @@ void clusterDoBeforeSleep(int flags);
 void clusterSendUpdate(clusterLink *link, clusterNode *node);
 void resetManualFailover(void);
 void clusterCloseAllSlots(void);
+void clusterSetNodeAsMaster(clusterNode *n);
+void clusterDelNode(clusterNode *delnode);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -462,6 +464,65 @@ void clusterInit(void) {
     resetManualFailover();
 }
 
+/* Reset a node performing a soft or hard reset:
+ *
+ * 1) All other nodes are forget.
+ * 2) All the assigned / open slots are released.
+ * 3) If the node is a slave, it turns into a master.
+ * 5) Only for hard reset: a new Node ID is generated.
+ * 6) Only for hard reset: currentEpoch and configEpoch are set to 0.
+ * 7) The new configuration is saved and the cluster state updated.  */
+void clusterReset(int hard) {
+    dictIterator *di;
+    dictEntry *de;
+    int j;
+
+    /* Turn into master. */
+    if (nodeIsSlave(myself)) {
+        clusterSetNodeAsMaster(myself);
+        replicationUnsetMaster();
+    }
+
+    /* Close slots, reset manual failover state. */
+    clusterCloseAllSlots();
+    resetManualFailover();
+
+    /* Unassign all the slots. */
+    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) clusterDelSlot(j);
+
+    /* Forget all the nodes, but myself. */
+    di = dictGetSafeIterator(server.cluster->nodes);
+    while((de = dictNext(di)) != NULL) {
+        clusterNode *node = dictGetVal(de);
+
+        if (node == myself) continue;
+        clusterDelNode(node);
+    }
+    dictReleaseIterator(di);
+
+    /* Hard reset only: set epochs to 0, change node ID. */
+    if (hard) {
+        sds oldname;
+
+        server.cluster->currentEpoch = 0;
+        server.cluster->lastVoteEpoch = 0;
+        myself->configEpoch = 0;
+
+        /* To change the Node ID we need to remove the old name from the
+         * nodes table, change the ID, and re-add back with new name. */
+        oldname = sdsnewlen(myself->name, REDIS_CLUSTER_NAMELEN);
+        dictDelete(server.cluster->nodes,oldname);
+        sdsfree(oldname);
+        getRandomHexChars(myself->name, REDIS_CLUSTER_NAMELEN);
+        clusterAddNode(myself);
+    }
+
+    /* Make sure to persist the new config and update the state. */
+    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                         CLUSTER_TODO_UPDATE_STATE|
+                         CLUSTER_TODO_FSYNC_CONFIG);
+}
+
 /* -----------------------------------------------------------------------------
  * CLUSTER communication link
  * -------------------------------------------------------------------------- */
@@ -3728,6 +3789,33 @@ void clusterCommand(redisClient *c) {
                                  CLUSTER_TODO_SAVE_CONFIG);
             addReply(c,shared.ok);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"reset") &&
+               (c->argc == 2 || c->argc == 3))
+    {
+        /* CLUSTER RESET [SOFT|HARD] */
+        int hard = 0;
+
+        /* Parse soft/hard argument. Default is soft. */
+        if (c->argc == 3) {
+            if (!strcasecmp(c->argv[2]->ptr,"hard")) {
+                hard = 1;
+            } else if (!strcasecmp(c->argv[2]->ptr,"hard")) {
+                hard = 0;
+            } else {
+                addReply(c,shared.syntaxerr);
+                return;
+            }
+        }
+
+        /* Slaves can be reset while containing data, but not master nodes
+         * that must be empty. */
+        if (nodeIsMaster(myself) && dictSize(c->db->dict) != 0) {
+            addReplyError(c,"CLUSTER RESET can't be called with "
+                            "master nodes containing keys");
+            return;
+        }
+        clusterReset(hard);
+        addReply(c,shared.ok);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
     }