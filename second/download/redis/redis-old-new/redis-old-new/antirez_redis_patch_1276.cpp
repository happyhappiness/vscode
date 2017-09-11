@@ -1849,7 +1849,7 @@ sds genRedisInfoString(char *section) {
     unsigned long lol, bib;
     int allsections = 0, defsections = 0;
     int sections = 0;
-    
+
     if (section) {
         allsections = strcasecmp(section,"all") == 0;
         defsections = strcasecmp(section,"default") == 0;
@@ -1862,14 +1862,20 @@ sds genRedisInfoString(char *section) {
     /* Server */
     if (allsections || defsections || !strcasecmp(section,"server")) {
         struct utsname name;
+        char *mode;
 
+        if (server.cluster_enabled) mode = "cluster";
+        else if (server.sentinel_mode) mode = "sentinel";
+        else mode = "standalone";
+    
         if (sections++) info = sdscat(info,"\r\n");
         uname(&name);
         info = sdscatprintf(info,
             "# Server\r\n"
             "redis_version:%s\r\n"
             "redis_git_sha1:%s\r\n"
             "redis_git_dirty:%d\r\n"
+            "redis_mode:%s\r\n"
             "os:%s %s %s\r\n"
             "arch_bits:%d\r\n"
             "multiplexing_api:%s\r\n"
@@ -1883,6 +1889,7 @@ sds genRedisInfoString(char *section) {
             REDIS_VERSION,
             redisGitSHA1(),
             strtol(redisGitDirty(),NULL,10) > 0,
+            mode,
             name.sysname, name.release, name.machine,
             server.arch_bits,
             aeGetApiName(),