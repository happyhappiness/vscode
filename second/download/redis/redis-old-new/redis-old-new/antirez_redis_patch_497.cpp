@@ -236,7 +236,7 @@ void loadServerConfigFromString(char *config) {
             }
         } else if (!strcasecmp(argv[0],"dir") && argc == 2) {
             if (chdir(argv[1]) == -1) {
-                redisLog(REDIS_WARNING,"Can't chdir to '%s': %s",
+                serverLog(REDIS_WARNING,"Can't chdir to '%s': %s",
                     argv[1], strerror(errno));
                 exit(1);
             }
@@ -647,7 +647,7 @@ void loadServerConfig(char *filename, char *options) {
             fp = stdin;
         } else {
             if ((fp = fopen(filename,"r")) == NULL) {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "Fatal error, can't open config file '%s'", filename);
                 exit(1);
             }
@@ -954,7 +954,7 @@ void configSetCommand(redisClient *c) {
     } config_set_memory_field("maxmemory",server.maxmemory) {
         if (server.maxmemory) {
             if (server.maxmemory < zmalloc_used_memory()) {
-                redisLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
+                serverLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
             }
             freeMemoryIfNeeded();
         }
@@ -1657,7 +1657,7 @@ void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
         /* Don't blank lines about options the rewrite process
          * don't understand. */
         if (dictFind(state->rewritten,option) == NULL) {
-            redisLog(REDIS_DEBUG,"Not rewritten option: %s", option);
+            serverLog(REDIS_DEBUG,"Not rewritten option: %s", option);
             continue;
         }
 
@@ -1862,10 +1862,10 @@ void configCommand(redisClient *c) {
             return;
         }
         if (rewriteConfig(server.configfile) == -1) {
-            redisLog(REDIS_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
+            serverLog(REDIS_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
             addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
         } else {
-            redisLog(REDIS_WARNING,"CONFIG REWRITE executed with success.");
+            serverLog(REDIS_WARNING,"CONFIG REWRITE executed with success.");
             addReply(c,shared.ok);
         }
     } else {