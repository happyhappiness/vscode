@@ -47,6 +47,12 @@ static struct {
     {NULL, 0}
 };
 
+clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_LIMIT_NUM_CLASSES] = {
+    {0, 0, 0}, /* normal */
+    {1024*1024*256, 1024*1024*64, 60}, /* slave */
+    {1024*1024*32, 1024*1024*8, 60}  /* pubsub */
+};
+
 /*-----------------------------------------------------------------------------
  * Config file parsing
  *----------------------------------------------------------------------------*/
@@ -1336,23 +1342,59 @@ void rewriteConfigDirOption(struct rewriteConfigState *state) {
 }
 
 void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
+    char *option = "slaveof";
     sds line;
 
     /* If this is a master, we want all the slaveof config options
      * in the file to be removed. */
     if (server.masterhost == NULL) return;
-    line = sdscatprintf(sdsempty(),"slaveof %s %d",
+    line = sdscatprintf(sdsempty(),"%s %s %d", option,
         server.masterhost, server.masterport);
-    rewriteConfigRewriteLine(state,"slaveof",line,1);
+    rewriteConfigRewriteLine(state,option,line,1);
 }
 
 void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
+    int force = server.aof_state != REDIS_AOF_OFF;
+    char *option = "appendonly";
+    sds line;
+    
+    line = sdscatprintf(sdsempty(),"%s %s", option,
+        (server.aof_state == REDIS_AOF_OFF) ? "no" : "yes");
+    rewriteConfigRewriteLine(state,option,line,force);
 }
 
 void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
+    int force = server.notify_keyspace_events != 0;
+    char *option = "notify-keyspace-events";
+    sds line, flags;
+
+    flags = keyspaceEventsFlagsToString(server.notify_keyspace_events);
+    line = sdscatprintf(sdsempty(),"%s %s", option, flags);
+    sdsfree(flags);
+    rewriteConfigRewriteLine(state,option,line,force);
 }
 
 void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state) {
+    int j;
+    char *option = "client-output-buffer-limit";
+
+    for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
+        int force = (server.client_obuf_limits[j].hard_limit_bytes !=
+                    clientBufferLimitsDefaults[j].hard_limit_bytes) ||
+                    (server.client_obuf_limits[j].soft_limit_bytes !=
+                    clientBufferLimitsDefaults[j].soft_limit_bytes) ||
+                    (server.client_obuf_limits[j].soft_limit_seconds !=
+                    clientBufferLimitsDefaults[j].soft_limit_seconds);
+        sds line;
+
+        line = sdscatprintf(sdsempty(),"%s %s %llu %llu %ld",
+                option,
+                getClientLimitClassName(j),
+                server.client_obuf_limits[j].hard_limit_bytes,
+                server.client_obuf_limits[j].soft_limit_bytes,
+                (long) server.client_obuf_limits[j].soft_limit_seconds);
+        rewriteConfigRewriteLine(state,option,line,force);
+    }
 }
 
 sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) {