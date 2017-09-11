@@ -133,6 +133,7 @@ typedef struct sentinelRedisInstance {
     int flags;      /* See SRI_... defines */
     char *name;     /* Master name from the point of view of this sentinel. */
     char *runid;    /* run ID of this instance. */
+    uint64_t config_epoch;  /* Configuration epoch. */
     sentinelAddr *addr; /* Master host. */
     redisAsyncContext *cc; /* Hiredis context for commands. */
     redisAsyncContext *pc; /* Hiredis context for Pub / Sub. */
@@ -191,13 +192,14 @@ typedef struct sentinelRedisInstance {
 
 /* Main state. */
 struct sentinelState {
+    uint64_t current_epoch;     /* Current epoch. */
     dict *masters;      /* Dictionary of master sentinelRedisInstances.
                            Key is the instance name, value is the
                            sentinelRedisInstance structure pointer. */
     int tilt;           /* Are we in TILT mode? */
     int running_scripts;    /* Number of scripts in execution right now. */
     mstime_t tilt_start_time;   /* When TITL started. */
-    mstime_t previous_time;     /* Time last time we ran the time handler. */
+    mstime_t previous_time;     /* Last time we ran the time handler. */
     list *scripts_queue;    /* Queue of user scripts to execute. */
 } sentinel;
 
@@ -402,6 +404,7 @@ void initSentinel(void) {
     }
 
     /* Initialize various data structures. */
+    sentinel.current_epoch = 0;
     sentinel.masters = dictCreate(&instancesDictType,NULL);
     sentinel.tilt = 0;
     sentinel.tilt_start_time = 0;
@@ -861,6 +864,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->flags = flags | SRI_DISCONNECTED;
     ri->name = sdsname;
     ri->runid = NULL;
+    ri->config_epoch = 0;
     ri->addr = addr;
     ri->cc = NULL;
     ri->pc = NULL;
@@ -1745,24 +1749,28 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
     if (strstr(r->element[2]->str,server.runid) != NULL) return;
 
     {
-        int numtokens, port, removed, canfailover;
-        /* Separator changed from ":" to "," in recent versions in order to
-         * play well with IPv6 addresses. For now we make sure to parse both
-         * correctly detecting if there is "," inside the string. */
-        char *sep = strchr(r->element[2]->str,',') ? "," : ":";
+        /* Format is composed of 9 tokens:
+         * 0=ip,1=port,2=runid,3=can_failover,4=current_epoch,
+         * 5=master_name,6=master_ip,7=master_port,8=master_config_epoch. */
+        int numtokens, port, removed, canfailover, master_port;
+        uint64_t current_epoch, master_config_epoch;
         char **token = sdssplitlen(r->element[2]->str,
                                    r->element[2]->len,
-                                   sep,1,&numtokens);
-        sentinelRedisInstance *sentinel;
+                                   ",",1,&numtokens);
+        sentinelRedisInstance *si;
 
-        if (numtokens == 4) {
+        if (numtokens == 9) {
             /* First, try to see if we already have this sentinel. */
             port = atoi(token[1]);
+            master_port = atoi(token[7]);
             canfailover = atoi(token[3]);
-            sentinel = getSentinelRedisInstanceByAddrAndRunID(
+            si = getSentinelRedisInstanceByAddrAndRunID(
                             ri->sentinels,token[0],port,token[2]);
+            current_epoch = strtoull(token[4],NULL,10);
+            master_config_epoch = strtoull(token[8],NULL,10);
+            sentinelRedisInstance *master;
 
-            if (!sentinel) {
+            if (!si) {
                 /* If not, remove all the sentinels that have the same runid
                  * OR the same ip/port, because it's either a restart or a
                  * network topology change. */
@@ -1775,24 +1783,45 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
                 }
 
                 /* Add the new sentinel. */
-                sentinel = createSentinelRedisInstance(NULL,SRI_SENTINEL,
+                si = createSentinelRedisInstance(NULL,SRI_SENTINEL,
                                 token[0],port,ri->quorum,ri);
-                if (sentinel) {
-                    sentinelEvent(REDIS_NOTICE,"+sentinel",sentinel,"%@");
+                if (si) {
+                    sentinelEvent(REDIS_NOTICE,"+sentinel",si,"%@");
                     /* The runid is NULL after a new instance creation and
                      * for Sentinels we don't have a later chance to fill it,
                      * so do it now. */
-                    sentinel->runid = sdsnew(token[2]);
+                    si->runid = sdsnew(token[2]);
+                }
+            }
+
+            /* Update local current_epoch if received current_epoch is greater. */
+            if (current_epoch > sentinel.current_epoch)
+                sentinel.current_epoch = current_epoch;
+
+            /* Update master info if received configuration is newer. */
+            if ((master = sentinelGetMasterByName(token[5])) != NULL) {
+                if (master->config_epoch < master_config_epoch) {
+                    master->config_epoch = master_config_epoch;
+                    if (master_port != master->addr->port ||
+                        !strcmp(master->addr->ip, token[6]))
+                    {
+                        sentinelEvent(REDIS_WARNING,"+switch-master",
+                            master,"%s %s %d %s %d",
+                            master->name, master->addr->ip, master->addr->port,
+                            token[6], master_port);
+                        sentinelResetMasterAndChangeAddress(ri,
+                                                    token[6], master_port);
+                    }
                 }
             }
 
             /* Update the state of the Sentinel. */
-            if (sentinel) {
-                sentinel->last_hello_time = mstime();
+            if (si) {
+                si->last_hello_time = mstime();
                 if (canfailover)
-                    sentinel->flags |= SRI_CAN_FAILOVER;
+                    si->flags |= SRI_CAN_FAILOVER;
                 else
-                    sentinel->flags &= ~SRI_CAN_FAILOVER;
+                    si->flags &= ~SRI_CAN_FAILOVER;
             }
         }
         sdsfreesplitres(token,numtokens);
@@ -1842,20 +1871,28 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
             sentinelPingReplyCallback, NULL, "PING");
         if (retval != REDIS_OK) return;
         ri->pending_commands++;
-    } else if ((ri->flags & SRI_MASTER) &&
+    } else if ((ri->flags & SRI_SENTINEL) == 0 &&
                (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
     {
-        /* PUBLISH hello messages only to masters. */
+        /* PUBLISH hello messages to masters and slaves. */
         char ip[REDIS_IP_STR_LEN];
         if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
-            char myaddr[REDIS_IP_STR_LEN+128];
+            char payload[REDIS_IP_STR_LEN+1024];
+            sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
+                                             NULL : ri->master;
 
-            snprintf(myaddr,sizeof(myaddr),"%s,%d,%s,%d",
+            snprintf(payload,sizeof(payload),
+                "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
+                "%s,%s,%d,%lld",    /* Info about current master. */
                 ip, server.port, server.runid,
-                (ri->flags & SRI_CAN_FAILOVER) != 0);
+                (ri->flags & SRI_CAN_FAILOVER) != 0,
+                (unsigned long long) sentinel.current_epoch,
+                /* --- */
+                master->name,master->addr->ip,master->addr->port,
+                master->config_epoch);
             retval = redisAsyncCommand(ri->cc,
                 sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
-                    SENTINEL_HELLO_CHANNEL,myaddr);
+                    SENTINEL_HELLO_CHANNEL,payload);
             if (retval != REDIS_OK) return;
             ri->pending_commands++;
         }