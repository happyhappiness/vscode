@@ -1936,6 +1936,7 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
             char payload[REDIS_IP_STR_LEN+1024];
             sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                              ri : ri->master;
+            sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
             snprintf(payload,sizeof(payload),
                 "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
@@ -1944,7 +1945,7 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
                 (master->flags & SRI_CAN_FAILOVER) != 0,
                 (unsigned long long) sentinel.current_epoch,
                 /* --- */
-                master->name,master->addr->ip,master->addr->port,
+                master->name,master_addr->ip,master_addr->port,
                 master->config_epoch);
             retval = redisAsyncCommand(ri->cc,
                 sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",