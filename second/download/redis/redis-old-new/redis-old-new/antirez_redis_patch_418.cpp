@@ -90,7 +90,7 @@ configEnum aof_fsync_enum[] = {
 };
 
 /* Output buffer limits presets. */
-clientBufferLimitsConfig clientBufferLimitsDefaults[CLIENT_TYPE_COUNT] = {
+clientBufferLimitsConfig clientBufferLimitsDefaults[CLIENT_TYPE_OBUF_COUNT] = {
     {0, 0, 0}, /* normal */
     {1024*1024*256, 1024*1024*64, 60}, /* slave */
     {1024*1024*32, 1024*1024*8, 60}  /* pubsub */
@@ -1163,13 +1163,13 @@ void configGetCommand(client *c) {
         sds buf = sdsempty();
         int j;
 
-        for (j = 0; j < CLIENT_TYPE_COUNT; j++) {
+        for (j = 0; j < CLIENT_TYPE_OBUF_COUNT; j++) {
             buf = sdscatprintf(buf,"%s %llu %llu %ld",
                     getClientTypeName(j),
                     server.client_obuf_limits[j].hard_limit_bytes,
                     server.client_obuf_limits[j].soft_limit_bytes,
                     (long) server.client_obuf_limits[j].soft_limit_seconds);
-            if (j != CLIENT_TYPE_COUNT-1)
+            if (j != CLIENT_TYPE_OBUF_COUNT-1)
                 buf = sdscatlen(buf," ",1);
         }
         addReplyBulkCString(c,"client-output-buffer-limit");
@@ -1566,7 +1566,7 @@ void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state
     int j;
     char *option = "client-output-buffer-limit";
 
-    for (j = 0; j < CLIENT_TYPE_COUNT; j++) {
+    for (j = 0; j < CLIENT_TYPE_OBUF_COUNT; j++) {
         int force = (server.client_obuf_limits[j].hard_limit_bytes !=
                     clientBufferLimitsDefaults[j].hard_limit_bytes) ||
                     (server.client_obuf_limits[j].soft_limit_bytes !=