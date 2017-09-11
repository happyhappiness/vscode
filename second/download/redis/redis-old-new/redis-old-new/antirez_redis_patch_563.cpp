@@ -139,10 +139,15 @@ typedef struct instanceLink {
     mstime_t pc_last_activity; /* Last time we received any message. */
     mstime_t last_avail_time; /* Last time the instance replied to ping with
                                  a reply we consider valid. */
-    mstime_t last_ping_time;  /* Last time a pending ping was sent in the
-                                 context of the current command connection
-                                 with the instance. 0 if still not sent or
-                                 if pong already received. */
+    mstime_t act_ping_time;   /* Time at which the last pending ping (no pong
+                                 received after it) was sent. This field is
+                                 set to 0 when a pong is received, and set again
+                                 to the current time if the value is 0 and a new
+                                 ping is sent. */
+    mstime_t last_ping_time;  /* Time at which we sent the last ping. This is
+                                 only used to avoid sending too many pings
+                                 during failure. Idle time is computed using
+                                 the act_ping_time field. */
     mstime_t last_pong_time;  /* Last time the instance replied to ping,
                                  whatever the reply was. That's used to check
                                  if the link is idle and must be reconnected. */
@@ -925,11 +930,12 @@ instanceLink *createInstanceLink(void) {
     link->pc_conn_time = 0;
     link->last_reconn_time = 0;
     link->pc_last_activity = 0;
-    /* We set the last_ping_time to "now" even if we actually don't have yet
+    /* We set the act_ping_time to "now" even if we actually don't have yet
      * a connection with the node, nor we sent a ping.
      * This is useful to detect a timeout in case we'll not be able to connect
      * with the node at all. */
-    link->last_ping_time = mstime();
+    link->act_ping_time = mstime();
+    link->last_ping_time = 0;
     link->last_avail_time = mstime();
     link->last_pong_time = mstime();
     return link;
@@ -1344,7 +1350,8 @@ void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
     sdsfree(ri->slave_master_host);
     ri->runid = NULL;
     ri->slave_master_host = NULL;
-    ri->link->last_ping_time = mstime();
+    ri->link->act_ping_time = mstime();
+    ri->link->last_ping_time = 0;
     ri->link->last_avail_time = mstime();
     ri->link->last_pong_time = mstime();
     ri->role_reported_time = mstime();
@@ -2199,7 +2206,7 @@ void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata
             strncmp(r->str,"MASTERDOWN",10) == 0)
         {
             link->last_avail_time = mstime();
-            link->last_ping_time = 0; /* Flag the pong as received. */
+            link->act_ping_time = 0; /* Flag the pong as received. */
         } else {
             /* Send a SCRIPT KILL command if the instance appears to be
              * down because of a busy script. */
@@ -2440,20 +2447,31 @@ int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master) {
     return REDIS_OK;
 }
 
-/* Send a PING to the specified instance and refresh the last_ping_time
+/* Send a PING to the specified instance and refresh the act_ping_time
  * if it is zero (that is, if we received a pong for the previous ping).
  *
  * On error zero is returned, and we can't consider the PING command
  * queued in the connection. */
 int sentinelSendPing(sentinelRedisInstance *ri) {
+    static unsigned long long counters[256];
+    static time_t last;
+    // printf("(%lld) PING %s\n", mstime(), sentinelGetInstanceTypeString(ri));
+    counters[ri->flags & (SRI_SLAVE|SRI_MASTER|SRI_SENTINEL)]++;
+    if (time(NULL)-last >= 5) {
+        printf("slave: %llu master: %llu sentinel: %llu\n",
+            counters[SRI_SLAVE], counters[SRI_MASTER], counters[SRI_SENTINEL]);
+        last = time(NULL);
+    }
     int retval = redisAsyncCommand(ri->link->cc,
         sentinelPingReplyCallback, ri, "PING");
     if (retval == REDIS_OK) {
         ri->link->pending_commands++;
-        /* We update the ping time only if we received the pong for
-         * the previous ping, otherwise we are technically waiting
-         * since the first ping that did not received a reply. */
-        if (ri->link->last_ping_time == 0) ri->link->last_ping_time = mstime();
+        ri->link->last_ping_time = mstime();
+        /* We update the active ping time only if we received the pong for
+         * the previous ping, otherwise we are technically waiting since the
+         * first ping that did not received a reply. */
+        if (ri->link->act_ping_time == 0)
+            ri->link->act_ping_time = ri->link->last_ping_time;
         return 1;
     } else {
         return 0;
@@ -2506,9 +2524,7 @@ void sentinelSendPeriodicCommands(sentinelRedisInstance *ri) {
             sentinelInfoReplyCallback, ri, "INFO");
         if (retval == REDIS_OK) ri->link->pending_commands++;
     } else if ((now - ri->link->last_pong_time) > ping_period &&
-                (ri->link->last_ping_time == 0 ||
-                 now - ri->link->last_ping_time > ping_period*2))
-    {
+               (now - ri->link->last_ping_time) > ping_period/2) {
         /* Send PING to all the three kinds of instances. */
         sentinelSendPing(ri);
     } else if ((now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD) {
@@ -2592,7 +2608,7 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
 
     addReplyBulkCString(c,"last-ping-sent");
     addReplyBulkLongLong(c,
-        ri->link->last_ping_time ? (mstime() - ri->link->last_ping_time) : 0);
+        ri->link->act_ping_time ? (mstime() - ri->link->act_ping_time) : 0);
     fields++;
 
     addReplyBulkCString(c,"last-ok-ping-reply");
@@ -3202,8 +3218,8 @@ void sentinelPublishCommand(redisClient *c) {
 void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
     mstime_t elapsed = 0;
 
-    if (ri->link->last_ping_time)
-        elapsed = mstime() - ri->link->last_ping_time;
+    if (ri->link->act_ping_time)
+        elapsed = mstime() - ri->link->act_ping_time;
 
     /* Check if we are in need for a reconnection of one of the
      * links, because we are detecting low activity.
@@ -3214,10 +3230,10 @@ void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
     if (ri->link->cc &&
         (mstime() - ri->link->cc_conn_time) >
         SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
-        ri->link->last_ping_time != 0 && /* Ther is a pending ping... */
+        ri->link->act_ping_time != 0 && /* Ther is a pending ping... */
         /* The pending ping is delayed, and we did not received
          * error replies as well. */
-        (mstime() - ri->link->last_ping_time) > (ri->down_after_period/2) &&
+        (mstime() - ri->link->act_ping_time) > (ri->down_after_period/2) &&
         (mstime() - ri->link->last_pong_time) > (ri->down_after_period/2))
     {
         instanceLinkCloseConnection(ri->link,ri->link->cc);