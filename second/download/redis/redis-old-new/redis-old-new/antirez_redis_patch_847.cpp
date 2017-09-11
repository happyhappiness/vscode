@@ -50,7 +50,7 @@ static struct {
     {NULL, 0}
 };
 
-clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_LIMIT_NUM_CLASSES] = {
+clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_TYPE_COUNT] = {
     {0, 0, 0}, /* normal */
     {1024*1024*256, 1024*1024*64, 60}, /* slave */
     {1024*1024*32, 1024*1024*8, 60}  /* pubsub */
@@ -456,7 +456,7 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"client-output-buffer-limit") &&
                    argc == 5)
         {
-            int class = getClientLimitClassByName(argv[1]);
+            int class = getClientTypeByName(argv[1]);
             unsigned long long hard, soft;
             int soft_seconds;
 
@@ -817,7 +817,7 @@ void configSetCommand(redisClient *c) {
             long val;
 
             if ((j % 4) == 0) {
-                if (getClientLimitClassByName(v[j]) == -1) {
+                if (getClientTypeByName(v[j]) == -1) {
                     sdsfreesplitres(v,vlen);
                     goto badfmt;
                 }
@@ -835,7 +835,7 @@ void configSetCommand(redisClient *c) {
             unsigned long long hard, soft;
             int soft_seconds;
 
-            class = getClientLimitClassByName(v[j]);
+            class = getClientTypeByName(v[j]);
             hard = strtoll(v[j+1],NULL,10);
             soft = strtoll(v[j+2],NULL,10);
             soft_seconds = strtoll(v[j+3],NULL,10);
@@ -1113,13 +1113,13 @@ void configGetCommand(redisClient *c) {
         sds buf = sdsempty();
         int j;
 
-        for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
+        for (j = 0; j < REDIS_CLIENT_TYPE_COUNT; j++) {
             buf = sdscatprintf(buf,"%s %llu %llu %ld",
-                    getClientLimitClassName(j),
+                    getClientTypeName(j),
                     server.client_obuf_limits[j].hard_limit_bytes,
                     server.client_obuf_limits[j].soft_limit_bytes,
                     (long) server.client_obuf_limits[j].soft_limit_seconds);
-            if (j != REDIS_CLIENT_LIMIT_NUM_CLASSES-1)
+            if (j != REDIS_CLIENT_TYPE_COUNT-1)
                 buf = sdscatlen(buf," ",1);
         }
         addReplyBulkCString(c,"client-output-buffer-limit");
@@ -1535,7 +1535,7 @@ void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state
     int j;
     char *option = "client-output-buffer-limit";
 
-    for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
+    for (j = 0; j < REDIS_CLIENT_TYPE_COUNT; j++) {
         int force = (server.client_obuf_limits[j].hard_limit_bytes !=
                     clientBufferLimitsDefaults[j].hard_limit_bytes) ||
                     (server.client_obuf_limits[j].soft_limit_bytes !=
@@ -1551,7 +1551,7 @@ void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state
                 server.client_obuf_limits[j].soft_limit_bytes);
 
         line = sdscatprintf(sdsempty(),"%s %s %s %s %ld",
-                option, getClientLimitClassName(j), hard, soft,
+                option, getClientTypeName(j), hard, soft,
                 (long) server.client_obuf_limits[j].soft_limit_seconds);
         rewriteConfigRewriteLine(state,option,line,force);
     }