@@ -72,6 +72,7 @@ void resetManualFailover(void);
 void clusterCloseAllSlots(void);
 void clusterSetNodeAsMaster(clusterNode *n);
 void clusterDelNode(clusterNode *delnode);
+sds representRedisNodeFlags(sds ci, uint16_t flags);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -163,9 +164,13 @@ int clusterLoadConfig(char *filename) {
                         argv[j]);
                 }
             }
+            sdsfreesplitres(argv,argc);
             continue;
         }
 
+        /* Regular config lines have at least eight fields */
+        if (argc < 8) goto fmterr;
+
         /* Create this node if it does not exist */
         n = clusterLookupNode(argv[0]);
         if (!n) {
@@ -266,11 +271,12 @@ int clusterLoadConfig(char *filename) {
 
         sdsfreesplitres(argv,argc);
     }
+    /* Config sanity check */
+    if (server.cluster->myself == NULL) goto fmterr;
+
     zfree(line);
     fclose(fp);
 
-    /* Config sanity check */
-    redisAssert(server.cluster->myself != NULL);
     redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s", myself->name);
 
     /* Something that should never happen: currentEpoch smaller than
@@ -284,7 +290,8 @@ int clusterLoadConfig(char *filename) {
 fmterr:
     redisLog(REDIS_WARNING,
         "Unrecoverable error: corrupted cluster config file.");
-    fclose(fp);
+    zfree(line);
+    if (fp) fclose(fp);
     exit(1);
 }
 
@@ -321,7 +328,7 @@ int clusterSaveConfig(int do_fsync) {
 
     /* Pad the new payload if the existing file length is greater. */
     if (fstat(fd,&sb) != -1) {
-        if (sb.st_size > content_size) {
+        if (sb.st_size > (off_t)content_size) {
             ci = sdsgrowzero(ci,sb.st_size);
             memset(ci+content_size,'\n',sb.st_size-content_size);
         }
@@ -1144,20 +1151,11 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
     clusterNode *sender = link->node ? link->node : clusterLookupNode(hdr->sender);
 
     while(count--) {
-        sds ci = sdsempty();
         uint16_t flags = ntohs(g->flags);
         clusterNode *node;
+        sds ci;
 
-        if (flags == 0) ci = sdscat(ci,"noflags,");
-        if (flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
-        if (flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
-        if (flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
-        if (flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
-        if (flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
-        if (flags & REDIS_NODE_HANDSHAKE) ci = sdscat(ci,"handshake,");
-        if (flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
-        if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
-
+        ci = representRedisNodeFlags(sdsempty(), flags);
         redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
             g->nodename,
             g->ip,
@@ -1914,7 +1912,7 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     ssize_t nread;
     clusterMsg *hdr;
     clusterLink *link = (clusterLink*) privdata;
-    int readlen, rcvbuflen;
+    unsigned int readlen, rcvbuflen;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
 
@@ -3296,14 +3294,13 @@ int verifyClusterConfigWithData(void) {
         update_config++;
         /* Case A: slot is unassigned. Take responsability for it. */
         if (server.cluster->slots[j] == NULL) {
-            redisLog(REDIS_WARNING, "I've keys about slot %d that is "
-                                    "unassigned. Taking responsability "
-                                    "for it.",j);
+            redisLog(REDIS_WARNING, "I have keys for unassigned slot %d. "
+                                    "Taking responsibility for it.",j);
             clusterAddSlot(myself,j);
         } else {
-            redisLog(REDIS_WARNING, "I've keys about slot %d that is "
-                                    "already assigned to a different node. "
-                                    "Setting it in importing state.",j);
+            redisLog(REDIS_WARNING, "I have keys for slot %d, but the slot is "
+                                    "assigned to another node. "
+                                    "Setting it to importing state.",j);
             server.cluster->importing_slots_from[j] = server.cluster->slots[j];
         }
     }
@@ -3336,9 +3333,40 @@ void clusterSetMaster(clusterNode *n) {
 }
 
 /* -----------------------------------------------------------------------------
- * CLUSTER command
+ * Nodes to string representation functions.
  * -------------------------------------------------------------------------- */
 
+struct redisNodeFlags {
+    uint16_t flag;
+    char *name;
+};
+
+static struct redisNodeFlags redisNodeFlagsTable[] = {
+    {REDIS_NODE_MYSELF,    "myself,"},
+    {REDIS_NODE_MASTER,    "master,"},
+    {REDIS_NODE_SLAVE,     "slave,"},
+    {REDIS_NODE_PFAIL,     "fail?,"},
+    {REDIS_NODE_FAIL,      "fail,"},
+    {REDIS_NODE_HANDSHAKE, "handshake,"},
+    {REDIS_NODE_NOADDR,    "noaddr,"}
+};
+
+/* Concatenate the comma separated list of node flags to the given SDS
+ * string 'ci'. */
+sds representRedisNodeFlags(sds ci, uint16_t flags) {
+    if (flags == 0) {
+        ci = sdscat(ci,"noflags,");
+    } else {
+        int i, size = sizeof(redisNodeFlagsTable)/sizeof(struct redisNodeFlags);
+        for (i = 0; i < size; i++) {
+            struct redisNodeFlags *nodeflag = redisNodeFlagsTable + i;
+            if (flags & nodeflag->flag) ci = sdscat(ci, nodeflag->name);
+        }
+    }
+    sdsIncrLen(ci,-1); /* Remove trailing comma. */
+    return ci;
+}
+
 /* Generate a csv-alike representation of the specified cluster node.
  * See clusterGenNodesDescription() top comment for more information.
  *
@@ -3354,21 +3382,13 @@ sds clusterGenNodeDescription(clusterNode *node) {
         node->port);
 
     /* Flags */
-    if (node->flags == 0) ci = sdscat(ci,"noflags,");
-    if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
-    if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
-    if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
-    if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
-    if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
-    if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
-    if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
-    if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
+    ci = representRedisNodeFlags(ci, node->flags);
 
     /* Slave of... or just "-" */
     if (node->slaveof)
-        ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
+        ci = sdscatprintf(ci," %.40s ",node->slaveof->name);
     else
-        ci = sdscatprintf(ci,"- ");
+        ci = sdscatlen(ci," - ",3);
 
     /* Latency from the POV of this node, link status */
     ci = sdscatprintf(ci,"%lld %lld %llu %s",
@@ -3446,6 +3466,10 @@ sds clusterGenNodesDescription(int filter) {
     return ci;
 }
 
+/* -----------------------------------------------------------------------------
+ * CLUSTER command
+ * -------------------------------------------------------------------------- */
+
 int getSlotOrReply(redisClient *c, robj *o) {
     long long slot;
 
@@ -3962,7 +3986,7 @@ void clusterCommand(redisClient *c) {
                 "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
                 (unsigned long long) myself->configEpoch);
 
-            if (server.cluster->currentEpoch < epoch)
+            if (server.cluster->currentEpoch < (uint64_t)epoch)
                 server.cluster->currentEpoch = epoch;
             /* No need to fsync the config here since in the unlucky event
              * of a failure to persist the config, the conflict resolution code