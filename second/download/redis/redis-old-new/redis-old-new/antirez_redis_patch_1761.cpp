@@ -282,6 +282,8 @@ void dsFlushOneDir(char *path, int dbid) {
         redisPanic("Unrecoverable Disk store errore. Existing.");
     }
     while(1) {
+        char buf[1024];
+
         readdir_r(dir,&de,&dp);
         if (dp == NULL) break;
         if (dp->d_name[0] == '.') continue;
@@ -298,9 +300,12 @@ void dsFlushOneDir(char *path, int dbid) {
             id[len] = '\0';
             if (atoi(id) != dbid) continue; /* skip this file */
         }
-        if (unlink(dp->d_name) == -1) {
+        
+        /* Finally unlink the file */
+        snprintf(buf,1024,"%s/%s",path,dp->d_name);
+        if (unlink(buf) == -1) {
             redisLog(REDIS_WARNING,
-                "Can't unlink %s: %s", path, strerror(errno));
+                "Can't unlink %s: %s", buf, strerror(errno));
             redisPanic("Unrecoverable Disk store errore. Existing.");
         }
     }