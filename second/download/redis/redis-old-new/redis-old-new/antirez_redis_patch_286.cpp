@@ -168,7 +168,13 @@ int clusterLoadConfig(char *filename) {
         if ((p = strrchr(argv[1],':')) == NULL) goto fmterr;
         *p = '\0';
         memcpy(n->ip,argv[1],strlen(argv[1])+1);
+        this_is_broken();
+        char *busp = strchr(p+1,':');
+        if (busp) *busp = '\0';
         n->port = atoi(p+1);
+        /* In older versions of nodes.conf the bus port is missing. In this case
+         * we set it to the default offset of 10000 from the base port. */
+        n->cport = busp ? atoi(busp+1) : n->port + CLUSTER_PORT_INCR;
 
         /* Parse flags */
         p = s = argv[2];
@@ -469,9 +475,14 @@ void clusterInit(void) {
     /* The slots -> keys map is a sorted set. Init it. */
     server.cluster->slots_to_keys = zslCreate();
 
-    /* Set myself->port to my listening port, we'll just need to discover
-     * the IP address via MEET messages. */
+    /* Set myself->port / cport to my listening ports, we'll just need to
+     * discover the IP address via MEET messages. */
     myself->port = server.port;
+    myself->cport = server.port+CLUSTER_PORT_INCR;
+    if (server.cluster_announce_port)
+        myself->port = server.cluster_announce_port;
+    if (server.cluster_announce_bus_port)
+        myself->cport = server.cluster_announce_bus_port;
 
     server.cluster->mf_end = 0;
     resetManualFailover();
@@ -670,6 +681,7 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     node->link = NULL;
     memset(node->ip,0,sizeof(node->ip));
     node->port = 0;
+    node->cport = 0;
     node->fail_reports = listCreate();
     node->voted_time = 0;
     node->orphaned_time = 0;
@@ -1212,7 +1224,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
 /* Return true if we already have a node in HANDSHAKE state matching the
  * specified ip address and port number. This function is used in order to
  * avoid adding a new handshake node for the same address multiple times. */
-int clusterHandshakeInProgress(char *ip, int port) {
+int clusterHandshakeInProgress(char *ip, int port, int cport) {
     dictIterator *di;
     dictEntry *de;
 
@@ -1221,7 +1233,9 @@ int clusterHandshakeInProgress(char *ip, int port) {
         clusterNode *node = dictGetVal(de);
 
         if (!nodeInHandshake(node)) continue;
-        if (!strcasecmp(node->ip,ip) && node->port == port) break;
+        if (!strcasecmp(node->ip,ip) &&
+            node->port == port &&
+            node->cport == cport) break;
     }
     dictReleaseIterator(di);
     return de != NULL;
@@ -1234,7 +1248,7 @@ int clusterHandshakeInProgress(char *ip, int port) {
  *
  * EAGAIN - There is already an handshake in progress for this address.
  * EINVAL - IP or port are not valid. */
-int clusterStartHandshake(char *ip, int port) {
+int clusterStartHandshake(char *ip, int port, int cport) {
     clusterNode *n;
     char norm_ip[NET_IP_STR_LEN];
     struct sockaddr_storage sa;
@@ -1254,7 +1268,7 @@ int clusterStartHandshake(char *ip, int port) {
     }
 
     /* Port sanity check */
-    if (port <= 0 || port > (65535-CLUSTER_PORT_INCR)) {
+    if (port <= 0 || port > 65535 || cport <= 0 || cport > 65535) {
         errno = EINVAL;
         return 0;
     }
@@ -1271,7 +1285,7 @@ int clusterStartHandshake(char *ip, int port) {
             (void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),
             norm_ip,NET_IP_STR_LEN);
 
-    if (clusterHandshakeInProgress(norm_ip,port)) {
+    if (clusterHandshakeInProgress(norm_ip,port,cport)) {
         errno = EAGAIN;
         return 0;
     }
@@ -1282,6 +1296,7 @@ int clusterStartHandshake(char *ip, int port) {
     n = createClusterNode(NULL,CLUSTER_NODE_HANDSHAKE|CLUSTER_NODE_MEET);
     memcpy(n->ip,norm_ip,sizeof(n->ip));
     n->port = port;
+    n->cport = cport;
     clusterAddNode(n);
     return 1;
 }
@@ -1301,10 +1316,11 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         sds ci;
 
         ci = representClusterNodeFlags(sdsempty(), flags);
-        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d %s",
+        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d:%d %s",
             g->nodename,
             g->ip,
             ntohs(g->port),
+            ntohs(g->cport),
             ci);
         sdsfree(ci);
 
@@ -1338,11 +1354,14 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
             if (node->flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL) &&
                 !(flags & CLUSTER_NODE_NOADDR) &&
                 !(flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL)) &&
-                (strcasecmp(node->ip,g->ip) || node->port != ntohs(g->port)))
+                (strcasecmp(node->ip,g->ip) ||
+                 node->port != ntohs(g->port) ||
+                 node->cport != ntohs(g->cport)))
             {
                 if (node->link) freeClusterLink(node->link);
                 memcpy(node->ip,g->ip,NET_IP_STR_LEN);
                 node->port = ntohs(g->port);
+                node->cport = ntohs(g->cport);
                 node->flags &= ~CLUSTER_NODE_NOADDR;
             }
         } else {
@@ -1356,7 +1375,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
                 !(flags & CLUSTER_NODE_NOADDR) &&
                 !clusterBlacklistExists(g->nodename))
             {
-                clusterStartHandshake(g->ip,ntohs(g->port));
+                clusterStartHandshake(g->ip,ntohs(g->port),ntohs(g->cport));
             }
         }
 
@@ -1365,23 +1384,36 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
     }
 }
 
-/* IP -> string conversion. 'buf' is supposed to at least be 46 bytes. */
-void nodeIp2String(char *buf, clusterLink *link) {
-    anetPeerToString(link->fd, buf, NET_IP_STR_LEN, NULL);
+/* IP -> string conversion. 'buf' is supposed to at least be 46 bytes.
+ * If 'announced_ip' length is non-zero, it is used instead of extracting
+ * the IP from the socket peer address. */
+void nodeIp2String(char *buf, clusterLink *link, char *announced_ip) {
+    if (announced_ip[0] != '\0') {
+        memcpy(buf,announced_ip,NET_IP_STR_LEN);
+        buf[NET_IP_STR_LEN-1] = '\0'; /* We are not sure the input is sane. */
+    } else {
+        anetPeerToString(link->fd, buf, NET_IP_STR_LEN, NULL);
+    }
 }
 
 /* Update the node address to the IP address that can be extracted
- * from link->fd, and at the specified port.
- * Also disconnect the node link so that we'll connect again to the new
- * address.
+ * from link->fd, or if hdr->myip is non empty, to the address the node
+ * is announcing us. The port is taken from the packet header as well.
+ *
+ * If the address or port changed, disconnect the node link so that we'll
+ * connect again to the new address.
  *
  * If the ip/port pair are already correct no operation is performed at
  * all.
  *
  * The function returns 0 if the node address is still the same,
  * otherwise 1 is returned. */
-int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
+int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link,
+                              clusterMsg *hdr)
+{
     char ip[NET_IP_STR_LEN] = {0};
+    int port = ntohs(hdr->port);
+    int cport = ntohs(hdr->cport);
 
     /* We don't proceed if the link is the same as the sender link, as this
      * function is designed to see if the node link is consistent with the
@@ -1391,12 +1423,14 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
      * it is safe to call during packet processing. */
     if (link == node->link) return 0;
 
-    nodeIp2String(ip,link);
-    if (node->port == port && strcmp(ip,node->ip) == 0) return 0;
+    nodeIp2String(ip,link,hdr->myip);
+    if (node->port == port && node->cport == cport &&
+        strcmp(ip,node->ip) == 0) return 0;
 
     /* IP / port is different, update it. */
     memcpy(node->ip,ip,sizeof(ip));
     node->port = port;
+    node->cport = cport;
     if (node->link) freeClusterLink(node->link);
     node->flags &= ~CLUSTER_NODE_NOADDR;
     serverLog(LL_WARNING,"Address updated for node %.40s, now %s:%d",
@@ -1635,7 +1669,7 @@ int clusterProcessPacket(clusterLink *link) {
 
         /* We use incoming MEET messages in order to set the address
          * for 'myself', since only other cluster nodes will send us
-         * MEET messagses on handshakes, when the cluster joins, or
+         * MEET messages on handshakes, when the cluster joins, or
          * later if we changed address, and those nodes will use our
          * official address to connect to us. So by obtaining this address
          * from the socket is a simple way to discover / update our own
@@ -1644,7 +1678,9 @@ int clusterProcessPacket(clusterLink *link) {
          * However if we don't have an address at all, we update the address
          * even with a normal PING packet. If it's wrong it will be fixed
          * by MEET later. */
-        if (type == CLUSTERMSG_TYPE_MEET || myself->ip[0] == '\0') {
+        if ((type == CLUSTERMSG_TYPE_MEET || myself->ip[0] == '\0') &&
+            server.cluster_announce_ip == NULL)
+        {
             char ip[NET_IP_STR_LEN];
 
             if (anetSockName(link->fd,ip,sizeof(ip),NULL) != -1 &&
@@ -1665,8 +1701,9 @@ int clusterProcessPacket(clusterLink *link) {
             clusterNode *node;
 
             node = createClusterNode(NULL,CLUSTER_NODE_HANDSHAKE);
-            nodeIp2String(node->ip,link);
+            nodeIp2String(node->ip,link,hdr->myip);
             node->port = ntohs(hdr->port);
+            node->cport = ntohs(hdr->cport);
             clusterAddNode(node);
             clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
         }
@@ -1696,7 +1733,7 @@ int clusterProcessPacket(clusterLink *link) {
                     serverLog(LL_VERBOSE,
                         "Handshake: we already know node %.40s, "
                         "updating the address if needed.", sender->name);
-                    if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
+                    if (nodeUpdateAddressIfNeeded(sender,link,hdr))
                     {
                         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                              CLUSTER_TODO_UPDATE_STATE);
@@ -1728,6 +1765,7 @@ int clusterProcessPacket(clusterLink *link) {
                 link->node->flags |= CLUSTER_NODE_NOADDR;
                 link->node->ip[0] = '\0';
                 link->node->port = 0;
+                link->node->cport = 0;
                 freeClusterLink(link);
                 clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                 return 0;
@@ -1737,7 +1775,7 @@ int clusterProcessPacket(clusterLink *link) {
         /* Update the node address if it changed. */
         if (sender && type == CLUSTERMSG_TYPE_PING &&
             !nodeInHandshake(sender) &&
-            nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
+            nodeUpdateAddressIfNeeded(sender,link,hdr))
         {
             clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                  CLUSTER_TODO_UPDATE_STATE);
@@ -2134,11 +2172,28 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     hdr->type = htons(type);
     memcpy(hdr->sender,myself->name,CLUSTER_NAMELEN);
 
+    /* If cluster-announce-ip option is enabled, force the receivers of our
+     * packets to use the specified address for this node. Otherwise if the
+     * first byte is zero, they'll do auto discovery. */
+    memset(hdr->myip,0,NET_IP_STR_LEN);
+    if (server.cluster_announce_ip) {
+        strncpy(hdr->myip,server.cluster_announce_ip,NET_IP_STR_LEN);
+        hdr->myip[NET_IP_STR_LEN-1] = '\0';
+    }
+
+    /* Handle cluster-announce-port as well. */
+    int announced_port = server.cluster_announce_port ?
+                         server.cluster_announce_port : server.port;
+    int announced_cport = server.cluster_announce_bus_port ?
+                          server.cluster_announce_bus_port :
+                          (server.port + CLUSTER_PORT_INCR);
+
     memcpy(hdr->myslots,master->slots,sizeof(hdr->myslots));
     memset(hdr->slaveof,0,CLUSTER_NAMELEN);
     if (myself->slaveof != NULL)
         memcpy(hdr->slaveof,myself->slaveof->name, CLUSTER_NAMELEN);
-    hdr->port = htons(server.port);
+    hdr->port = htons(announced_port);
+    hdr->cport = htons(announced_cport);
     hdr->flags = htons(myself->flags);
     hdr->state = server.cluster->state;
 
@@ -2274,9 +2329,9 @@ void clusterSendPing(clusterLink *link, int type) {
         gossip->pong_received = htonl(this->pong_received);
         memcpy(gossip->ip,this->ip,sizeof(this->ip));
         gossip->port = htons(this->port);
+        gossip->cport = htons(this->cport);
         gossip->flags = htons(this->flags);
         gossip->notused1 = 0;
-        gossip->notused2 = 0;
         gossipcount++;
     }
 
@@ -3073,6 +3128,31 @@ void clusterCron(void) {
 
     iteration++; /* Number of times this function was called so far. */
 
+    /* We want to take myself->ip in sync with the cluster-announce-ip option.
+     * The option can be set at runtime via CONFIG SET, so we periodically check
+     * if the option changed to reflect this into myself->ip. */
+    {
+        static char *prev_ip = NULL;
+        char *curr_ip = server.cluster_announce_ip;
+        int changed = 0;
+
+        if (prev_ip == NULL && curr_ip != NULL) changed = 1;
+        if (prev_ip != NULL && curr_ip == NULL) changed = 1;
+        if (prev_ip && curr_ip && strcmp(prev_ip,curr_ip)) changed = 1;
+
+        if (changed) {
+            prev_ip = curr_ip;
+            if (prev_ip) prev_ip = zstrdup(prev_ip);
+
+            if (curr_ip) {
+                strncpy(myself->ip,server.cluster_announce_ip,NET_IP_STR_LEN);
+                myself->ip[NET_IP_STR_LEN-1] = '\0';
+            } else {
+                myself->ip[0] = '\0'; /* Force autodetection. */
+            }
+        }
+    }
+
     /* The handshake timeout is the time after which a handshake node that was
      * not turned into a normal node is removed from the nodes. Usually it is
      * just the NODE_TIMEOUT value, but when NODE_TIMEOUT is too small we use
@@ -3100,7 +3180,7 @@ void clusterCron(void) {
             clusterLink *link;
 
             fd = anetTcpNonBlockBindConnect(server.neterr, node->ip,
-                node->port+CLUSTER_PORT_INCR, NET_FIRST_BIND_ADDR);
+                node->cport, NET_FIRST_BIND_ADDR);
             if (fd == -1) {
                 /* We got a synchronous error from connect before
                  * clusterSendPing() had a chance to be called.
@@ -3110,8 +3190,7 @@ void clusterCron(void) {
                 if (node->ping_sent == 0) node->ping_sent = mstime();
                 serverLog(LL_DEBUG, "Unable to connect to "
                     "Cluster Node [%s]:%d -> %s", node->ip,
-                    node->port+CLUSTER_PORT_INCR,
-                    server.neterr);
+                    node->cport, server.neterr);
                 continue;
             }
             link = createClusterLink(node);
@@ -3142,7 +3221,7 @@ void clusterCron(void) {
             node->flags &= ~CLUSTER_NODE_MEET;
 
             serverLog(LL_DEBUG,"Connecting with Node %.40s at %s:%d",
-                    node->name, node->ip, node->port+CLUSTER_PORT_INCR);
+                    node->name, node->ip, node->cport);
         }
     }
     dictReleaseIterator(di);
@@ -3663,10 +3742,11 @@ sds clusterGenNodeDescription(clusterNode *node) {
     sds ci;
 
     /* Node coordinates */
-    ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
+    ci = sdscatprintf(sdsempty(),"%.40s %s:%d:%d ",
         node->name,
         node->ip,
-        node->port);
+        node->port,
+        node->cport);
 
     /* Flags */
     ci = representClusterNodeFlags(ci, node->flags);
@@ -3849,16 +3929,27 @@ void clusterCommand(client *c) {
         return;
     }
 
-    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
-        long long port;
+    if (!strcasecmp(c->argv[1]->ptr,"meet") && (c->argc == 4 || c->argc == 5)) {
+        /* CLUSTER MEET <ip> <port> [cport] */
+        long long port, cport;
 
         if (getLongLongFromObject(c->argv[3], &port) != C_OK) {
-            addReplyErrorFormat(c,"Invalid TCP port specified: %s",
+            addReplyErrorFormat(c,"Invalid TCP base port specified: %s",
                                 (char*)c->argv[3]->ptr);
             return;
         }
 
-        if (clusterStartHandshake(c->argv[2]->ptr,port) == 0 &&
+        if (c->argc == 5) {
+            if (getLongLongFromObject(c->argv[4], &cport) != C_OK) {
+                addReplyErrorFormat(c,"Invalid TCP bus port specified: %s",
+                                    (char*)c->argv[4]->ptr);
+                return;
+            }
+        } else {
+            cport = port + CLUSTER_PORT_INCR;
+        }
+
+        if (clusterStartHandshake(c->argv[2]->ptr,port,cport) == 0 &&
             errno == EINVAL)
         {
             addReplyErrorFormat(c,"Invalid node address specified: %s:%s",