@@ -1400,6 +1400,7 @@ void initServerConfig(void) {
     server.lazyfree_lazy_eviction = CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION;
     server.lazyfree_lazy_expire = CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE;
     server.lazyfree_lazy_server_del = CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL;
+    server.always_show_logo = CONFIG_DEFAULT_ALWAYS_SHOW_LOGO;
 
     server.lruclock = getLRUClock();
     resetServerSaveParams();
@@ -3335,15 +3336,18 @@ void redisAsciiArt(void) {
     else if (server.sentinel_mode) mode = "sentinel";
     else mode = "standalone";
 
-    if (server.syslog_enabled) {
+    /* Show the ASCII logo if: log file is stdout AND stdout is a
+     * tty AND syslog logging is disabled. Also show logo if the user
+     * forced us to do so via redis.conf. */
+    int show_logo = ((!server.syslog_enabled &&
+                      server.logfile[0] == '\0' &&
+                      isatty(fileno(stdout))) ||
+                     server.always_show_logo);
+
+    if (!show_logo) {
         serverLog(LL_NOTICE,
-            "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
-            REDIS_VERSION,
-            redisGitSHA1(),
-            strtol(redisGitDirty(),NULL,10) > 0,
-            (sizeof(long) == 8) ? "64" : "32",
-            mode, server.port,
-            (long) getpid()
+            "Running mode=%s, port=%d.",
+            mode, server.port
         );
     } else {
         snprintf(buf,1024*16,ascii_logo,
@@ -3700,8 +3704,23 @@ int main(int argc, char **argv) {
         resetServerSaveParams();
         loadServerConfig(configfile,options);
         sdsfree(options);
-    } else {
+    }
+
+//    serverLog(LL_WARNING, "_.~\"(_.~\"(_.~\"(_.~\"(_.~\"( Redis is starting...");
+    serverLog(LL_WARNING, "oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo");
+
+    serverLog(LL_WARNING,
+        "Redis version=%s, bits=%d, commit=%s, modified=%d, pid=%d, just started",
+            REDIS_VERSION,
+            (sizeof(long) == 8) ? 64 : 32,
+            redisGitSHA1(),
+            strtol(redisGitDirty(),NULL,10) > 0,
+            (int)getpid());
+
+    if (argc == 1) {
         serverLog(LL_WARNING, "Warning: no config file specified, using the default config. In order to specify a config file use %s /path/to/%s.conf", argv[0], server.sentinel_mode ? "sentinel" : "redis");
+    } else {
+        serverLog(LL_WARNING, "Configuration loaded");
     }
 
     server.supervised = redisIsSupervised(server.supervised_mode);
@@ -3716,7 +3735,7 @@ int main(int argc, char **argv) {
 
     if (!server.sentinel_mode) {
         /* Things not needed when running in Sentinel mode. */
-        serverLog(LL_WARNING,"Server started, Redis version " REDIS_VERSION);
+        serverLog(LL_WARNING,"Server initialized");
     #ifdef __linux__
         linuxMemoryWarnings();
     #endif
@@ -3731,7 +3750,7 @@ int main(int argc, char **argv) {
             }
         }
         if (server.ipfd_count > 0)
-            serverLog(LL_NOTICE,"The server is now ready to accept connections on port %d", server.port);
+            serverLog(LL_NOTICE,"Ready to accept connections");
         if (server.sofd > 0)
             serverLog(LL_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
     } else {