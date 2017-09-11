@@ -753,9 +753,36 @@ void nodeIp2String(char *buf, clusterLink *link) {
 
 
 /* Update the node address to the IP address that can be extracted
- * from link->fd, and at the specified port. */
-void nodeUpdateAddress(clusterNode *node, clusterLink *link, int port) {
-    /* TODO */
+ * from link->fd, and at the specified port.
+ * Also disconnect the node link so that we'll connect again to the new
+ * address.
+ *
+ * If the ip/port pair are already correct no operation is performed at
+ * all.
+ *
+ * The function returns 0 if the node address is still the same,
+ * otherwise 1 is returned. */
+int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
+    char ip[REDIS_IP_STR_LEN];
+
+    /* We don't proceed if the link is the same as the sender link, as this
+     * function is designed to see if the node link is consistent with the
+     * symmetric link that is used to receive PINGs from the node.
+     *
+     * As a side effect this function never frees the passed 'link', so
+     * it is safe to call during packet processing. */
+    if (link == node->link) return 0;
+
+    nodeIp2String(ip,link);
+    if (node->port == port && strcmp(ip,node->ip) == 0) return 0;
+
+    /* IP / port is different, update it. */
+    memcpy(node->ip,ip,sizeof(ip));
+    node->port = port;
+    if (node->link) freeClusterLink(node->link);
+    redisLog(REDIS_WARNING,"Address updated for node %.40s, now %s:%d",
+        node->name, node->ip, node->port);
+    return 1;
 }
 
 /* When this function is called, there is a packet to process starting
@@ -854,8 +881,14 @@ int clusterProcessPacket(clusterLink *link) {
                 if (sender) {
                     redisLog(REDIS_WARNING,
                         "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
-                    nodeUpdateAddress(sender,link,ntohs(hdr->port));
-                    freeClusterNode(link->node); /* will free the link too */
+                    if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
+                    {
+                        clusterUpdateState();
+                        clusterSaveConfigOrDie();
+                    }
+                    /* Free this node as we alrady have it. This will
+                     * cause the link to be freed as well. */
+                    freeClusterNode(link->node);
                     return 0;
                 }
 
@@ -888,6 +921,15 @@ int clusterProcessPacket(clusterLink *link) {
             }
         }
 
+        /* Update the node address if it changed. */
+        if (sender && type == CLUSTERMSG_TYPE_PING &&
+            !(sender->flags & REDIS_NODE_HANDSHAKE) &&
+            nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
+        {
+            update_state = 1;
+            update_config = 1;
+        }
+
         /* Update our info about the node */
         if (link->node && type == CLUSTERMSG_TYPE_PONG) {
             link->node->pong_received = time(NULL);
@@ -1049,12 +1091,12 @@ int clusterProcessPacket(clusterLink *link) {
             decrRefCount(message);
         }
     } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST) {
-        if (!sender) return 0;  /* We don't know that node. */
+        if (!sender) return 1;  /* We don't know that node. */
         /* If we are not a master, ignore that message at all. */
         if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return 0;
         clusterSendFailoverAuthIfNeeded(sender);
     } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK) {
-        if (!sender) return 0;  /* We don't know that node. */
+        if (!sender) return 1;  /* We don't know that node. */
         /* If this is a master, increment the number of acknowledges
          * we received so far. */
         if (sender->flags & REDIS_NODE_MASTER)