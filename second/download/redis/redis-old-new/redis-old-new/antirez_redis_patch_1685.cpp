@@ -86,6 +86,8 @@ int clusterLoadConfig(char *filename) {
                 n->flags |= REDIS_NODE_HANDSHAKE;
             } else if (!strcasecmp(s,"noaddr")) {
                 n->flags |= REDIS_NODE_NOADDR;
+            } else if (!strcasecmp(s,"noflags")) {
+                /* nothing to do */
             } else {
                 redisPanic("Unknown flag in redis cluster config file");
             }
@@ -524,7 +526,8 @@ int clusterProcessPacket(clusterLink *link) {
         /* Anyway reply with a PONG */
         clusterSendPing(link,CLUSTERMSG_TYPE_PONG);
     } else if (type == CLUSTERMSG_TYPE_PONG) {
-        int update = 0;
+        int update_state = 0;
+        int update_config = 0;
 
         redisLog(REDIS_DEBUG,"Pong packet received: %p", link->node);
         if (link->node) {
@@ -545,6 +548,7 @@ int clusterProcessPacket(clusterLink *link) {
                 redisLog(REDIS_DEBUG,"Handshake with node %.40s completed.",
                     link->node->name);
                 link->node->flags &= ~REDIS_NODE_HANDSHAKE;
+                update_config = 1;
             } else if (memcmp(link->node->name,hdr->sender,
                         REDIS_CLUSTER_NAMELEN) != 0)
             {
@@ -554,6 +558,7 @@ int clusterProcessPacket(clusterLink *link) {
                 redisLog(REDIS_DEBUG,"PONG contains mismatching sender ID");
                 link->node->flags |= REDIS_NODE_NOADDR;
                 freeClusterLink(link);
+                update_config = 1;
                 /* FIXME: remove this node if we already have it.
                  *
                  * If we already have it but the IP is different, use
@@ -599,7 +604,7 @@ int clusterProcessPacket(clusterLink *link) {
                             server.cluster.slots[j]->flags & REDIS_NODE_FAIL)
                         {
                             server.cluster.slots[j] = sender;
-                            update = 1;
+                            update_state = update_config = 1;
                         }
                     }
                 }
@@ -610,10 +615,8 @@ int clusterProcessPacket(clusterLink *link) {
         clusterProcessGossipSection(hdr,link);
 
         /* Update the cluster state if needed */
-        if (update) {
-            clusterUpdateState();
-            clusterSaveConfigOrDie();
-        }
+        if (update_state) clusterUpdateState();
+        if (update_config) clusterSaveConfigOrDie();
     } else if (type == CLUSTERMSG_TYPE_FAIL && sender) {
         clusterNode *failing;
 
@@ -1059,8 +1062,8 @@ sds clusterGenNodesDescription(void) {
                 start = -1;
             }
         }
+        ci = sdscatlen(ci,"\n",1);
     }
-    ci = sdscatlen(ci,"\n",1);
     dictReleaseIterator(di);
     return ci;
 }