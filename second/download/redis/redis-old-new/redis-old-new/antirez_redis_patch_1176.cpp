@@ -107,6 +107,7 @@ int clusterLoadConfig(char *filename) {
                 n->flags |= REDIS_NODE_PFAIL;
             } else if (!strcasecmp(s,"fail")) {
                 n->flags |= REDIS_NODE_FAIL;
+                n->fail_time = time(NULL);
             } else if (!strcasecmp(s,"handshake")) {
                 n->flags |= REDIS_NODE_HANDSHAKE;
             } else if (!strcasecmp(s,"noaddr")) {
@@ -341,6 +342,7 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     node->slaves = NULL;
     node->slaveof = NULL;
     node->ping_sent = node->pong_received = 0;
+    node->fail_time = 0;
     node->configdigest = NULL;
     node->configdigest_ts = 0;
     node->link = NULL;
@@ -594,6 +596,7 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
     /* Mark the node as failing. */
     node->flags &= ~REDIS_NODE_PFAIL;
     node->flags |= REDIS_NODE_FAIL;
+    node->fail_time = time(NULL);
 
     /* Broadcast the failing node name to everybody */
     clusterSendFail(node->name);
@@ -907,6 +910,7 @@ int clusterProcessPacket(clusterLink *link) {
                 "FAIL message received from %.40s about %.40s",
                 hdr->sender, hdr->data.fail.about.nodename);
             failing->flags |= REDIS_NODE_FAIL;
+            failing->fail_time = time(NULL);
             failing->flags &= ~REDIS_NODE_PFAIL;
             clusterUpdateState();
             clusterSaveConfigOrDie();