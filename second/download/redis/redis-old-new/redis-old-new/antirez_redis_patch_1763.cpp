@@ -74,6 +74,7 @@
 
 #include <fcntl.h>
 #include <sys/stat.h>
+#include <dirent.h>
 
 int create256dir(char *prefix) {
     char buf[1024];
@@ -270,5 +271,51 @@ int dsExists(redisDb *db, robj *key) {
     return access(buf,R_OK) == 0;
 }
 
-int dsFlushDb(int dbid) {
+void dsFlushOneDir(char *path, int dbid) {
+    DIR *dir;
+    struct dirent *dp, de;
+
+    dir = opendir(path);
+    if (dir == NULL) {
+        redisLog(REDIS_WARNING,"Disk store can't open dir %s: %s",
+            path, strerror(errno));
+        redisPanic("Unrecoverable Disk store errore. Existing.");
+    }
+    while(1) {
+        readdir_r(dir,&de,&dp);
+        if (dp == NULL) break;
+        if (dp->d_name[0] == '.') continue;
+
+        /* Check if we need to remove this entry accordingly to the
+         * DB number */
+        if (dbid != -1) {
+            char id[64];
+            char *p = strchr(dp->d_name,'_');
+            int len = (p - dp->d_name);
+
+            redisAssert(p != NULL && len < 64);
+            memcpy(id,dp->d_name,len);
+            id[len] = '\0';
+            if (atoi(id) != dbid) continue; /* skip this file */
+        }
+        if (unlink(path) == -1) {
+            redisLog(REDIS_WARNING,
+                "Can't unlink %s: %s", path, strerror(errno));
+            redisPanic("Unrecoverable Disk store errore. Existing.");
+        }
+    }
+    closedir(dir);
+}
+
+void dsFlushDb(int dbid) {
+    char buf[1024];
+    int j, i;
+
+    redisLog(REDIS_NOTICE,"Flushing diskstore DB (%d)",dbid);
+    for (j = 0; j < 256; j++) {
+        for (i = 0; i < 256; i++) {
+            snprintf(buf,1024,"%s/%02x/%02x",server.ds_path,j,i);
+            dsFlushOneDir(buf,dbid);
+        }
+    }
 }