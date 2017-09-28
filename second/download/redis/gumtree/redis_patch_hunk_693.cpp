              * is a well known node in our cluster, otherwise we risk
              * joining another cluster. */
             if (sender &&
                 !(flags & CLUSTER_NODE_NOADDR) &&
                 !clusterBlacklistExists(g->nodename))
             {
-                clusterStartHandshake(g->ip,ntohs(g->port));
+                clusterStartHandshake(g->ip,ntohs(g->port),ntohs(g->cport));
             }
         }
 
         /* Next node */
         g++;
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
      * symmetric link that is used to receive PINGs from the node.
      *
      * As a side effect this function never frees the passed 'link', so
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
         node->name, node->ip, node->port);
 
     /* Check if this is our master and we have to change the
