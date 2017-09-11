@@ -1542,19 +1542,24 @@ int clusterProcessPacket(clusterLink *link) {
     clusterMsg *hdr = (clusterMsg*) link->rcvbuf;
     uint32_t totlen = ntohl(hdr->totlen);
     uint16_t type = ntohs(hdr->type);
-    uint16_t flags = ntohs(hdr->flags);
-    uint64_t senderCurrentEpoch = 0, senderConfigEpoch = 0;
-    clusterNode *sender;
 
     server.cluster->stats_bus_messages_received++;
     serverLog(LL_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
 
     /* Perform sanity checks */
     if (totlen < 16) return 1; /* At least signature, version, totlen, count. */
-    if (ntohs(hdr->ver) != CLUSTER_PROTO_VER)
-        return 1; /* Can't handle versions other than the current one.*/
     if (totlen > sdslen(link->rcvbuf)) return 1;
+
+    if (ntohs(hdr->ver) != CLUSTER_PROTO_VER) {
+        /* Can't handle messages of different versions. */
+        return 1;
+    }
+
+    uint16_t flags = ntohs(hdr->flags);
+    uint64_t senderCurrentEpoch = 0, senderConfigEpoch = 0;
+    clusterNode *sender;
+
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
         type == CLUSTERMSG_TYPE_MEET)
     {