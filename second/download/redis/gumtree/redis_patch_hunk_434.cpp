 int clusterProcessPacket(clusterLink *link) {
     clusterMsg *hdr = (clusterMsg*) link->rcvbuf;
     uint32_t totlen = ntohl(hdr->totlen);
     uint16_t type = ntohs(hdr->type);
 
     server.cluster->stats_bus_messages_received++;
-    redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
+    serverLog(LL_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
 
     /* Perform sanity checks */
     if (totlen < 16) return 1; /* At least signature, version, totlen, count. */
     if (totlen > sdslen(link->rcvbuf)) return 1;
 
