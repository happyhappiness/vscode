@@ -1469,17 +1469,6 @@ void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
     rewriteConfigRewriteLine(state,option,line,1);
 }
 
-/* Rewrite the appendonly option. */
-void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
-    int force = server.aof_state != REDIS_AOF_OFF;
-    char *option = "appendonly";
-    sds line;
-    
-    line = sdscatprintf(sdsempty(),"%s %s", option,
-        (server.aof_state == REDIS_AOF_OFF) ? "no" : "yes");
-    rewriteConfigRewriteLine(state,option,line,force);
-}
-
 /* Rewrite the notify-keyspace-events option. */
 void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
     int force = server.notify_keyspace_events != 0;
@@ -1578,12 +1567,23 @@ void rewriteConfigReleaseState(struct rewriteConfigState *state) {
  * should be replaced by empty lines.
  *
  * This function does just this, iterating all the option names and
- * blanking all the lines still associated. */
+ * blanking all the lines still associated.
+ *
+ * Two options "include" and "rename-command" are special, they are
+ * just kept because struct RedisServer doesn't record them. Notice
+ * this also means the included config file isn't rewritten, you'd
+ * better put "include" at the beginning of Redis main config file
+ * so that runtime config change won't be canceled by conflicted
+ * options in the included config file. */
 void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
     dictIterator *di = dictGetIterator(state->option_to_line);
     dictEntry *de;
 
     while((de = dictNext(di)) != NULL) {
+        sds option = dictGetKey(de);
+        if (!strcmp(option, "include") || !strcmp(option, "rename-command"))
+            continue;
+
         list *l = dictGetVal(de);
         sds option = dictGetKey(de);
 
@@ -1717,6 +1717,8 @@ int rewriteConfig(char *path) {
     rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
     rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
     rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
+    rewriteConfigNumericalOption(state,"min-slaves-to-write",server.repl_min_slaves_to_write,REDIS_DEFAULT_MIN_SLAVES_TO_WRITE);
+    rewriteConfigNumericalOption(state,"min-slaves-max-lag",server.repl_min_slaves_max_lag,REDIS_DEFAULT_MIN_SLAVES_MAX_LAG);
     rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
     rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
     rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
@@ -1729,7 +1731,8 @@ int rewriteConfig(char *path) {
         "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
         NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
     rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
-    rewriteConfigAppendonlyOption(state);
+    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != REDIS_AOF_OFF,0);
+    rewriteConfigStringOption(state,"appendfilename",server.aof_filename,REDIS_DEFAULT_AOF_FILENAME);
     rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
         "everysec", AOF_FSYNC_EVERYSEC,
         "always", AOF_FSYNC_ALWAYS,