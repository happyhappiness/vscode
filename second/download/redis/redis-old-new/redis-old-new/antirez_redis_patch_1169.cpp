@@ -115,6 +115,8 @@ int clusterLoadConfig(char *filename) {
                 n->flags |= REDIS_NODE_HANDSHAKE;
             } else if (!strcasecmp(s,"noaddr")) {
                 n->flags |= REDIS_NODE_NOADDR;
+            } else if (!strcasecmp(s,"promoted")) {
+                n->flags |= REDIS_NODE_PROMOTED;
             } else if (!strcasecmp(s,"noflags")) {
                 /* nothing to do */
             } else {
@@ -675,6 +677,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         if (flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
         if (flags & REDIS_NODE_HANDSHAKE) ci = sdscat(ci,"handshake,");
         if (flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
+        if (flags & REDIS_NODE_PROMOTED) ci = sdscat(ci,"promoted,");
         if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
 
         redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
@@ -767,6 +770,7 @@ int clusterProcessPacket(clusterLink *link) {
     clusterMsg *hdr = (clusterMsg*) link->rcvbuf;
     uint32_t totlen = ntohl(hdr->totlen);
     uint16_t type = ntohs(hdr->type);
+    uint16_t flags = ntohs(hdr->flags);
     clusterNode *sender;
 
     redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
@@ -896,10 +900,12 @@ int clusterProcessPacket(clusterLink *link) {
                     sender->flags |= REDIS_NODE_MASTER;
                     sender->slaveof = NULL;
 
-                    /* If this node used to be our slave, it means that
-                     * we were failed over. We'll turn ourself into a slave
+                    /* If this node used to be our slave, and now has the
+                     * PROMOTED flag set. We'll turn ourself into a slave
                      * of the new master. */
-                    if (oldmaster == server.cluster->myself) {
+                    if (flags & REDIS_NODE_PROMOTED &&
+                        oldmaster == server.cluster->myself)
+                    {
                         redisLog(REDIS_WARNING,"One of my slaves took my place. Reconfiguring myself as a replica of %.40s", sender->name);
                         clusterSetMaster(sender);
                     }
@@ -1441,6 +1447,7 @@ void clusterHandleSlaveFailover(void) {
                                server.cluster->myself);
         server.cluster->myself->flags &= ~REDIS_NODE_SLAVE;
         server.cluster->myself->flags |= REDIS_NODE_MASTER;
+        server.cluster->myself->flags |= REDIS_NODE_PROMOTED;
         server.cluster->myself->slaveof = NULL;
         replicationUnsetMaster();
 
@@ -1872,6 +1879,7 @@ sds clusterGenNodesDescription(void) {
         if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
         if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
         if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
+        if (node->flags & REDIS_NODE_PROMOTED) ci = sdscat(ci,"promoted,");
         if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
 
         /* Slave of... or just "-" */
@@ -2236,6 +2244,7 @@ void clusterCommand(redisClient *c) {
         }
 
         /* Set the master. */
+        server.cluster->myself->flags &= ~REDIS_NODE_PROMOTED;
         clusterSetMaster(n);
         clusterUpdateState();
         clusterSaveConfigOrDie();