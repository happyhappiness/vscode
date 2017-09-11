@@ -513,6 +513,8 @@ int clusterProcessPacket(clusterLink *link) {
 
     redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
+
+    /* Perform sanity checks */
     if (totlen < 8) return 1;
     if (totlen > sdslen(link->rcvbuf)) return 1;
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
@@ -531,7 +533,16 @@ int clusterProcessPacket(clusterLink *link) {
         explen += sizeof(clusterMsgDataFail);
         if (totlen != explen) return 1;
     }
+    if (type == CLUSTERMSG_TYPE_PUBLISH) {
+        uint32_t explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
+
+        explen += sizeof(clusterMsgDataPublish) +
+                ntohl(hdr->data.publish.msg.channel_len) +
+                ntohl(hdr->data.publish.msg.message_len);
+        if (totlen != explen) return 1;
+    }
 
+    /* Ready to process the packet. Dispatch by type. */
     sender = clusterLookupNode(hdr->sender);
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
         int update_config = 0;
@@ -665,6 +676,22 @@ int clusterProcessPacket(clusterLink *link) {
             clusterUpdateState();
             clusterSaveConfigOrDie();
         }
+    } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
+        robj *channel, *message;
+        uint32_t channel_len, message_len;
+
+        /* Don't bother creating useless objects if there are no Pub/Sub subscribers. */
+        if (dictSize(server.pubsub_channels) || listLength(server.pubsub_patterns)) {
+            channel_len = ntohl(hdr->data.publish.msg.channel_len);
+            message_len = ntohl(hdr->data.publish.msg.message_len);
+            channel = createStringObject(
+                        (char*)hdr->data.publish.msg.bulk_data,channel_len);
+            message = createStringObject(
+                        (char*)hdr->data.publish.msg.bulk_data+channel_len, message_len);
+            pubsubPublishMessage(channel,message);
+            decrRefCount(channel);
+            decrRefCount(message);
+        }
     } else {
         redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
     }