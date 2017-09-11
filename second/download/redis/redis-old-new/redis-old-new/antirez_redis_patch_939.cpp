@@ -2359,15 +2359,22 @@ sds genRedisInfoString(char *section) {
 
     /* Server */
     if (allsections || defsections || !strcasecmp(section,"server")) {
-        struct utsname name;
+        static int call_uname = 1;
+        static struct utsname name;
         char *mode;
 
         if (server.cluster_enabled) mode = "cluster";
         else if (server.sentinel_mode) mode = "sentinel";
         else mode = "standalone";
     
         if (sections++) info = sdscat(info,"\r\n");
-        uname(&name);
+
+        if (call_uname) {
+            /* Uname can be slow and is always the same output. Cache it. */
+            uname(&name);
+            call_uname = 0;
+        }
+
         info = sdscatprintf(info,
             "# Server\r\n"
             "redis_version:%s\r\n"