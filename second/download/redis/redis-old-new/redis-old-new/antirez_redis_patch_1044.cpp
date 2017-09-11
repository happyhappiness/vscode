@@ -59,6 +59,7 @@ void clusterSetMaster(clusterNode *n);
 void clusterHandleSlaveFailover(void);
 int bitmapTestBit(unsigned char *bitmap, int pos);
 void clusterDoBeforeSleep(int flags);
+void clusterSendUpdate(clusterLink *link, clusterNode *node);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -1181,8 +1182,11 @@ int clusterProcessPacket(clusterLink *link) {
                     if (server.cluster->slots[j]->configEpoch >
                         senderConfigEpoch)
                     {
-                        printf("MASTER or SLAVE have old config\n");
-                        break;
+                        redisLog(REDIS_WARNING,
+                            "Node %.40s has old slots configuration, sending "
+                            "an UPDATE message about %.40s\n",
+                                sender->name, server.cluster->slots[j]->name);
+                        clusterSendUpdate(sender->link,server.cluster->slots[j]);
                     }
                 }
             }
@@ -1413,6 +1417,9 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     if (type == CLUSTERMSG_TYPE_FAIL) {
         totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
         totlen += sizeof(clusterMsgDataFail);
+    } else if (type == CLUSTERMSG_TYPE_UPDATE) {
+        totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
+        totlen += sizeof(clusterMsgDataUpdate);
     }
     hdr->totlen = htonl(totlen);
     /* For PING, PONG, and MEET, fixing the totlen field is up to the caller. */
@@ -1562,6 +1569,20 @@ void clusterSendFail(char *nodename) {
     clusterBroadcastMessage(buf,ntohl(hdr->totlen));
 }
 
+/* Send an UPDATE message to the specified link carrying the specified 'node'
+ * slots configuration. The node name, slots bitmap, and configEpoch info
+ * are included. */
+void clusterSendUpdate(clusterLink *link, clusterNode *node) {
+    unsigned char buf[4096];
+    clusterMsg *hdr = (clusterMsg*) buf;
+
+    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_UPDATE);
+    memcpy(hdr->data.update.nodecfg.nodename,node->name,REDIS_CLUSTER_NAMELEN);
+    hdr->data.update.nodecfg.configEpoch = htonu64(node->configEpoch);
+    memcpy(hdr->data.update.nodecfg.slots,node->slots,sizeof(node->slots));
+    clusterSendMessage(link,buf,ntohl(hdr->totlen));
+}
+
 /* -----------------------------------------------------------------------------
  * CLUSTER Pub/Sub support
  *