@@ -1827,13 +1827,13 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
         if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
             char payload[REDIS_IP_STR_LEN+1024];
             sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
-                                             NULL : ri->master;
+                                             ri : ri->master;
 
             snprintf(payload,sizeof(payload),
                 "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
                 "%s,%s,%d,%lld",    /* Info about current master. */
                 ip, server.port, server.runid,
-                (ri->flags & SRI_CAN_FAILOVER) != 0,
+                (master->flags & SRI_CAN_FAILOVER) != 0,
                 (unsigned long long) sentinel.current_epoch,
                 /* --- */
                 master->name,master->addr->ip,master->addr->port,