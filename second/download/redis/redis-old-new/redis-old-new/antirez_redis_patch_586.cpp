@@ -770,9 +770,6 @@ void configSetCommand(redisClient *c) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.slowlog_max_len = (unsigned)ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
         if (!strcasecmp(o->ptr,"warning")) {
             server.verbosity = REDIS_WARNING;
@@ -834,12 +831,6 @@ void configSetCommand(redisClient *c) {
         ll = memtoll(o->ptr,&err);
         if (err || ll < 0) goto badfmt;
         resizeReplicationBacklog(ll);
-    } else if (!strcasecmp(c->argv[2]->ptr,"watchdog-period")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        if (ll)
-            enableWatchdog(ll);
-        else
-            disableWatchdog();
     } else if (!strcasecmp(c->argv[2]->ptr,"notify-keyspace-events")) {
         int flags = keyspaceEventsStringToFlags(o->ptr);
 
@@ -902,6 +893,10 @@ void configSetCommand(redisClient *c) {
     } config_set_numerical_field(
       "slowlog-log-slower-than",server.slowlog_log_slower_than,0,LLONG_MAX) {
     } config_set_numerical_field(
+      "slowlog-max-len",ll,0,LLONG_MAX) {
+      /* Cast to unsigned. */
+        server.slowlog_max_len = (unsigned)ll;
+    } config_set_numerical_field(
       "latency-monitor-threshold",server.latency_monitor_threshold,0,LLONG_MAX){
     } config_set_numerical_field(
       "repl-ping-slave-period",server.repl_ping_slave_period,1,LLONG_MAX) {
@@ -931,6 +926,12 @@ void configSetCommand(redisClient *c) {
          * but cap them to reasonable values. */
         if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
         if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
+    } config_set_numerical_field(
+      "watchdog-period",ll,0,LLONG_MAX) {
+        if (ll)
+            enableWatchdog(ll);
+        else
+            disableWatchdog();
     }
 
     /* Everyhing else is an error... */