@@ -531,6 +531,7 @@ void clusterReset(int hard) {
         sdsfree(oldname);
         getRandomHexChars(myself->name, CLUSTER_NAMELEN);
         clusterAddNode(myself);
+        serverLog(LL_NOTICE,"Node hard reset, now I'm %.40s", myself->name);
     }
 
     /* Make sure to persist the new config and update the state. */
@@ -1330,14 +1331,19 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
             }
 
             /* If we already know this node, but it is not reachable, and
-             * we see a different address in the gossip section, start an
-             * handshake with the (possibly) new address: this will result
-             * into a node address update if the handshake will be
-             * successful. */
+             * we see a different address in the gossip section of a node that
+             * can talk with this other node, update the address, disconnect
+             * the old link if any, so that we'll attempt to connect with the
+             * new address. */
             if (node->flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL) &&
+                !(flags & CLUSTER_NODE_NOADDR) &&
+                !(flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL)) &&
                 (strcasecmp(node->ip,g->ip) || node->port != ntohs(g->port)))
             {
-                clusterStartHandshake(g->ip,ntohs(g->port));
+                if (node->link) freeClusterLink(node->link);
+                memcpy(node->ip,g->ip,NET_IP_STR_LEN);
+                node->port = g->port;
+                node->flags &= ~CLUSTER_NODE_NOADDR;
             }
         } else {
             /* If it's not in NOADDR state and we don't have it, we
@@ -1710,7 +1716,10 @@ int clusterProcessPacket(clusterLink *link) {
                 /* If the reply has a non matching node ID we
                  * disconnect this node and set it as not having an associated
                  * address. */
-                serverLog(LL_DEBUG,"PONG contains mismatching sender ID");
+                serverLog(LL_WARNING,"PONG contains mismatching sender ID. About node %.40s added %d ms ago, having flags %d",
+                    link->node->name,
+                    (int)(mstime()-(link->node->ctime)),
+                    link->node->flags);
                 link->node->flags |= CLUSTER_NODE_NOADDR;
                 link->node->ip[0] = '\0';
                 link->node->port = 0;