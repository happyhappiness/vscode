@@ -102,7 +102,10 @@ int dsOpen(void) {
     }
 
     /* Directory already in place. Assume everything is ok. */
-    if (retval == 0 && S_ISDIR(sb.st_mode)) return REDIS_OK;
+    if (retval == 0 && S_ISDIR(sb.st_mode)) {
+        redisLog(REDIS_NOTICE,"Disk store %s exists", path);
+        return REDIS_OK;
+    }
 
     /* File exists but it's not a directory */
     if (retval == 0 && !S_ISDIR(sb.st_mode)) {
@@ -113,6 +116,7 @@ int dsOpen(void) {
     /* New disk store, create the directory structure now, as creating
      * them in a lazy way is not a good idea, after very few insertions
      * we'll need most of the 65536 directories anyway. */
+    redisLog(REDIS_NOTICE,"Disk store %s does not exist: creating", path);
     if (mkdir(path,0755) == -1) {
         redisLog(REDIS_WARNING,"Disk store init failed creating dir %s: %s",
             path, strerror(errno));