     }
 
     /* PING, PONG, MEET: process config information. */
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
         type == CLUSTERMSG_TYPE_MEET)
     {
-        redisLog(REDIS_DEBUG,"%s packet received: %p",
+        serverLog(LL_DEBUG,"%s packet received: %p",
             type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
             (void*)link->node);
         if (link->node) {
             if (nodeInHandshake(link->node)) {
                 /* If we already have this node, try to change the
                  * IP/port of the node with the new one. */
                 if (sender) {
-                    redisLog(REDIS_VERBOSE,
+                    serverLog(LL_VERBOSE,
                         "Handshake: we already know node %.40s, "
                         "updating the address if needed.", sender->name);
                     if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
                     {
                         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                              CLUSTER_TODO_UPDATE_STATE);
