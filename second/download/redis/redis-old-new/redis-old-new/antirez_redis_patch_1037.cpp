@@ -1303,21 +1303,21 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         ri->config_epoch = strtoull(argv[2],NULL,10);
         if (ri->config_epoch > sentinel.current_epoch)
             sentinel.current_epoch = ri->config_epoch;
-    } else if (!strcasecmp(argv[0],"slave") && argc == 3) {
+    } else if (!strcasecmp(argv[0],"known-slave") && argc == 3) {
         sentinelRedisInstance *slave;
 
-        /* slave <name> <ip> <port> */
+        /* known-slave <name> <ip> <port> */
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         if ((slave = createSentinelRedisInstance(NULL,SRI_SLAVE,argv[2],
                     atoi(argv[3]), ri->quorum, ri)) == NULL)
         {
             return "Wrong hostname or port for slave.";
         }
-    } else if (!strcasecmp(argv[0],"sentinel") && argc == 3) {
+    } else if (!strcasecmp(argv[0],"known-sentinel") && argc == 3) {
         sentinelRedisInstance *si;
 
-        /* sentinel <name> <ip> <port> */
+        /* known-sentinel <name> <ip> <port> */
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         if ((si = createSentinelRedisInstance(NULL,SRI_SENTINEL,argv[2],
@@ -1331,6 +1331,107 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
     return NULL;
 }
 
+/* Implements CONFIG REWRITE for "sentinel" option.
+ * This is used not just to rewrite the configuration given by the user
+ * (the configured masters) but also in order to retain the state of
+ * Sentinel across restarts: config epoch of masters, associated slaves
+ * and sentinel instances, and so forth. */
+void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
+    dictIterator *di, *di2;
+    dictEntry *de;
+
+    /* For every master emit a "sentinel monitor" config entry. */
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *master, *ri;
+        sds line;
+
+        /* sentinel monitor */
+        master = dictGetVal(de);
+        line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
+            master->name, master->addr->ip, master->addr->port,
+            master->quorum);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+
+        /* sentinel down-after-milliseconds */
+        if (master->down_after_period != SENTINEL_DEFAULT_DOWN_AFTER) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel down-after-milliseconds %s %ld",
+                master->name, (long) master->down_after_period);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel failover-timeout */
+        if (master->failover_timeout != SENTINEL_DEFAULT_FAILOVER_TIMEOUT) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel failover-timeout %s %ld",
+                master->name, (long) master->failover_timeout);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel parallel-syncs */
+        if (master->parallel_syncs != SENTINEL_DEFAULT_PARALLEL_SYNCS) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel parallel-syncs %s %d",
+                master->name, master->parallel_syncs);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel notification-script */
+        if (master->notification_script) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel notification-script %s %s",
+                master->name, master->notification_script);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel client-reconfig-script */
+        if (master->client_reconfig_script) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel client-reconfig-script %s %s",
+                master->name, master->client_reconfig_script);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel auth-pass */
+        if (master->auth_pass) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel auth-pass %s %s",
+                master->name, master->auth_pass);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel config-epoch */
+        line = sdscatprintf(sdsempty(),
+            "sentinel config-epoch %s %llu",
+            master->name, (unsigned long long) master->config_epoch);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+
+        /* sentinel known-slave */
+        di2 = dictGetIterator(master->slaves);
+        while((de = dictNext(di)) != NULL) {
+            ri = dictGetVal(de);
+            line = sdscatprintf(sdsempty(),
+                "sentinel known-slave %s %s %d",
+                master->name, ri->addr->ip, ri->addr->port);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+        dictReleaseIterator(di2);
+
+        /* sentinel known-sentinel */
+        di2 = dictGetIterator(master->sentinels);
+        while((de = dictNext(di)) != NULL) {
+            ri = dictGetVal(de);
+            line = sdscatprintf(sdsempty(),
+                "sentinel known-sentinel %s %s %d",
+                master->name, ri->addr->ip, ri->addr->port);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+        dictReleaseIterator(di2);
+    }
+    dictReleaseIterator(di);
+}
+
 /* ====================== hiredis connection handling ======================= */
 
 /* Completely disconnect an hiredis link from an instance. */