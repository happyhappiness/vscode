@@ -2216,9 +2216,10 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
     sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
+    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
+
     /* Try to obtain our own IP address. */
     if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
-    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
 
     /* Format and send the Hello message. */
     snprintf(payload,sizeof(payload),