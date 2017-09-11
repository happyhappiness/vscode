@@ -799,6 +799,64 @@ int clusterHandshakeInProgress(char *ip, int port) {
     return de != NULL;
 }
 
+/* Start an handshake with the specified address if there is not one
+ * already in progress. Returns non-zero if the handshake was actually
+ * started. On error zero is returned and errno is set to one of the
+ * following values:
+ *
+ * EAGAIN - There is already an handshake in progress for this address.
+ * EINVAL - IP or port are not valid. */
+int clusterStartHandshake(char *ip, int port) {
+    clusterNode *n;
+    char norm_ip[REDIS_IP_STR_LEN];
+    struct sockaddr_storage sa;
+
+    /* IP sanity check */
+    if (inet_pton(AF_INET,ip,
+            &(((struct sockaddr_in *)&sa)->sin_addr)))
+    {
+        sa.ss_family = AF_INET;
+    } else if (inet_pton(AF_INET6,ip,
+            &(((struct sockaddr_in6 *)&sa)->sin6_addr)))
+    {
+        sa.ss_family = AF_INET6;
+    } else {
+        errno = EINVAL;
+        return 0;
+    }
+
+    /* Port sanity check */
+    if (port <= 0 || port > (65535-REDIS_CLUSTER_PORT_INCR)) {
+        errno = EINVAL;
+        return 0;
+    }
+
+    /* Set norm_ip as the normalized string representation of the node
+     * IP address. */
+    if (sa.ss_family == AF_INET)
+        inet_ntop(AF_INET,
+            (void*)&(((struct sockaddr_in *)&sa)->sin_addr),
+            norm_ip,REDIS_CLUSTER_IPLEN);
+    else
+        inet_ntop(AF_INET6,
+            (void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),
+            norm_ip,REDIS_CLUSTER_IPLEN);
+
+    if (clusterHandshakeInProgress(norm_ip,port)) {
+        errno = EAGAIN;
+        return 0;
+    }
+
+    /* Add the node with a random address (NULL as first argument to
+     * createClusterNode()). Everything will be fixed during the
+     * handskake. */
+    n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);
+    memcpy(n->ip,norm_ip,sizeof(n->ip));
+    n->port = port;
+    clusterAddNode(n);
+    return 1;
+}
+
 /* Process the gossip section of PING or PONG packets.
  * Note that this function assumes that the packet is already sanity-checked
  * by the caller, not in the content of the gossip section, but in the
@@ -832,7 +890,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
 
         /* Update our state accordingly to the gossip sections */
         node = clusterLookupNode(g->nodename);
-        if (node != NULL) {
+        if (node) {
             /* We already know this node.
                Handle failure reports, only when the sender is a master. */
             if (sender && sender->flags & REDIS_NODE_MASTER &&
@@ -853,24 +911,26 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
                     }
                 }
             }
+
+            /* If we already know this node, but it is not reachable, and
+             * we see a different address in the gossip section, start an
+             * handshake with the (possibly) new address: this will result
+             * into a node address update if the handshake will be
+             * successful. */
+            if (node->flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL) &&
+                (strcasecmp(node->ip,g->ip) || node->port != ntohs(g->port)))
+            {
+                clusterStartHandshake(g->ip,ntohs(g->port));
+            }
         } else {
             /* If it's not in NOADDR state and we don't have it, we
              * start a handshake process against this IP/PORT pairs.
              *
              * Note that we require that the sender of this gossip message
              * is a well known node in our cluster, otherwise we risk
              * joining another cluster. */
-            if (sender && !(flags & REDIS_NODE_NOADDR) &&
-                !clusterHandshakeInProgress(g->ip,ntohs(g->port)))
-            {
-                clusterNode *newnode;
-
-                redisLog(REDIS_DEBUG,"Adding the new node");
-                newnode = createClusterNode(NULL,REDIS_NODE_HANDSHAKE);
-                memcpy(newnode->ip,g->ip,sizeof(g->ip));
-                newnode->port = ntohs(g->port);
-                clusterAddNode(newnode);
-            }
+            if (sender && !(flags & REDIS_NODE_NOADDR))
+                clusterStartHandshake(g->ip,ntohs(g->port));
         }
 
         /* Next node */
@@ -2492,48 +2552,20 @@ void clusterCommand(redisClient *c) {
     }
 
     if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
-        /* CLUSTER MEET <ip> <port> */
-        clusterNode *n;
-        struct sockaddr_storage sa;
         long port;
 
-        /* Perform sanity checks on IP/port */
-        if (inet_pton(AF_INET,c->argv[2]->ptr,
-            &(((struct sockaddr_in *)&sa)->sin_addr)))
-        {
-            sa.ss_family = AF_INET;
-        } else if (inet_pton(AF_INET6,c->argv[2]->ptr,
-            &(((struct sockaddr_in6 *)&sa)->sin6_addr)))
-        {
-            sa.ss_family = AF_INET6;
-        } else {
-            addReplyError(c,"Invalid IP address in MEET");
-            return;
-        }
-        if (getLongFromObjectOrReply(c, c->argv[3], &port, NULL) != REDIS_OK ||
-                    port < 0 || port > (65535-REDIS_CLUSTER_PORT_INCR))
-        {
+        if (getLongFromObjectOrReply(c, c->argv[3], &port, NULL) != REDIS_OK) {
             addReplyError(c,"Invalid TCP port specified");
             return;
         }
 
-        /* Finally add the node to the cluster with a random name, this 
-         * will get fixed in the first handshake (ping/pong). */
-        n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);
-
-        /* Set node->ip as the normalized string representation of the node
-         * IP address. */
-        if (sa.ss_family == AF_INET)
-            inet_ntop(AF_INET,
-                (void*)&(((struct sockaddr_in *)&sa)->sin_addr),
-                n->ip,REDIS_CLUSTER_IPLEN);
-        else
-            inet_ntop(AF_INET6,
-                (void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),
-                n->ip,REDIS_CLUSTER_IPLEN);
-        n->port = port;
-        clusterAddNode(n);
-        addReply(c,shared.ok);
+        if (clusterStartHandshake(c->argv[2]->ptr,port) == 0 &&
+            errno == EINVAL)
+        {
+            addReplyError(c,"Invalid node address specified");
+        } else {
+            addReply(c,shared.ok);
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
         /* CLUSTER NODES */
         robj *o;