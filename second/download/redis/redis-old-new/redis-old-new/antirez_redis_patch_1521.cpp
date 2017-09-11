@@ -666,7 +666,7 @@ int clusterProcessPacket(clusterLink *link) {
             clusterSaveConfigOrDie();
         }
     } else {
-        redisLog(REDIS_NOTICE,"Received unknown packet type: %d", type);
+        redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
     }
     return 1;
 }
@@ -759,6 +759,22 @@ void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
     link->sndbuf = sdscatlen(link->sndbuf, msg, msglen);
 }
 
+/* Send a message to all the nodes with a reliable link */
+void clusterBroadcastMessage(void *buf, size_t len) {
+    dictIterator *di;
+    dictEntry *de;
+
+    di = dictGetIterator(server.cluster.nodes);
+    while((de = dictNext(di)) != NULL) {
+        clusterNode *node = dictGetEntryVal(de);
+
+        if (!node->link) continue;
+        if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR)) continue;
+        clusterSendMessage(node->link,buf,len);
+    }
+    dictReleaseIterator(di);
+}
+
 /* Build the message header */
 void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     int totlen;
@@ -843,20 +859,48 @@ void clusterSendPing(clusterLink *link, int type) {
     clusterSendMessage(link,buf,totlen);
 }
 
-/* Send a message to all the nodes with a reliable link */
-void clusterBroadcastMessage(void *buf, size_t len) {
-    dictIterator *di;
-    dictEntry *de;
+/* Send a PUBLISH message.
+ *
+ * If link is NULL, then the message is broadcasted to the whole cluster. */
+void clusterSendPublish(clusterLink *link, robj *channel, robj *message) {
+    unsigned char buf[4096], *payload;
+    clusterMsg *hdr = (clusterMsg*) buf;
+    uint32_t totlen;
+    uint32_t channel_len, message_len;
 
-    di = dictGetIterator(server.cluster.nodes);
-    while((de = dictNext(di)) != NULL) {
-        clusterNode *node = dictGetEntryVal(de);
+    channel = getDecodedObject(channel);
+    message = getDecodedObject(message);
+    channel_len = sdslen(channel->ptr);
+    message_len = sdslen(message->ptr);
 
-        if (!node->link) continue;
-        if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR)) continue;
-        clusterSendMessage(node->link,buf,len);
+    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_PUBLISH);
+    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
+    totlen += sizeof(clusterMsgDataPublish) + channel_len + message_len;
+
+    hdr->data.publish.msg.channel_len = htonl(channel_len);
+    hdr->data.publish.msg.message_len = htonl(message_len);
+    hdr->totlen = htonl(totlen);
+
+    /* Try to use the local buffer if possible */
+    if (totlen < sizeof(buf)) {
+        payload = buf;
+    } else {
+        payload = zmalloc(totlen);
+        hdr = (clusterMsg*) payload;
+        memcpy(payload,hdr,sizeof(hdr));
     }
-    dictReleaseIterator(di);
+    memcpy(hdr->data.publish.msg.bulk_data,channel->ptr,sdslen(channel->ptr));
+    memcpy(hdr->data.publish.msg.bulk_data+sdslen(channel->ptr),
+        message->ptr,sdslen(message->ptr));
+
+    if (link)
+        clusterSendMessage(link,payload,totlen);
+    else
+        clusterBroadcastMessage(payload,totlen);
+
+    decrRefCount(channel);
+    decrRefCount(message);
+    if (payload != buf) zfree(payload);
 }
 
 /* Send a FAIL message to all the nodes we are able to contact.
@@ -874,6 +918,17 @@ void clusterSendFail(char *nodename) {
 }
 
 /* -----------------------------------------------------------------------------
+ * CLUSTER Pub/Sub support
+ *
+ * For now we do very little, just propagating PUBLISH messages across the whole
+ * cluster. In the future we'll try to get smarter and avoiding propagating those
+ * messages to hosts without receives for a given channel.
+ * -------------------------------------------------------------------------- */
+void clusterPropagatePublish(robj *channel, robj *message) {
+    clusterSendPublish(NULL, channel, message);
+}
+
+/* -----------------------------------------------------------------------------
  * CLUSTER cron job
  * -------------------------------------------------------------------------- */
 