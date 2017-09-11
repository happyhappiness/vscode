@@ -2453,15 +2453,6 @@ int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master) {
  * On error zero is returned, and we can't consider the PING command
  * queued in the connection. */
 int sentinelSendPing(sentinelRedisInstance *ri) {
-    static unsigned long long counters[256];
-    static time_t last;
-    // printf("(%lld) PING %s\n", mstime(), sentinelGetInstanceTypeString(ri));
-    counters[ri->flags & (SRI_SLAVE|SRI_MASTER|SRI_SENTINEL)]++;
-    if (time(NULL)-last >= 5) {
-        printf("slave: %llu master: %llu sentinel: %llu\n",
-            counters[SRI_SLAVE], counters[SRI_MASTER], counters[SRI_SENTINEL]);
-        last = time(NULL);
-    }
     int retval = redisAsyncCommand(ri->link->cc,
         sentinelPingReplyCallback, ri, "PING");
     if (retval == REDIS_OK) {