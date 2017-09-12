@@ -97,7 +97,7 @@ int dsOpen(void) {
     /* New disk store, create the directory structure now, as creating
      * them in a lazy way is not a good idea, after very few insertions
      * we'll need most of the 65536 directories anyway. */
-    if (mkdir(path) == -1) {
+    if (mkdir(path,0644) == -1) {
         redisLog(REDIS_WARNING,"Disk store init failed creating dir %s: %s",
             path, strerror(errno));
         return REDIS_ERR;