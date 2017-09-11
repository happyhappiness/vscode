@@ -983,7 +983,7 @@ int processInlineBuffer(redisClient *c) {
 /* Helper function. Trims query buffer to make the function that processes
  * multi bulk requests idempotent. */
 static void setProtocolError(redisClient *c, int pos) {
-    if (server.verbosity >= REDIS_VERBOSE) {
+    if (server.verbosity <= REDIS_VERBOSE) {
         sds client = catClientInfoString(sdsempty(),c);
         redisLog(REDIS_VERBOSE,
             "Protocol error from client: %s", client);