@@ -3866,7 +3866,7 @@ int redisSupervisedUpstart(void) {
         return 0;
     }
 
-    serverLog(LL_NOTICE, "supervised by upstart, will stop to signal readyness");
+    serverLog(LL_NOTICE, "supervised by upstart, will stop to signal readiness");
     raise(SIGSTOP);
     unsetenv("UPSTART_JOB");
     return 1;
@@ -3890,7 +3890,7 @@ int redisSupervisedSystemd(void) {
         return 0;
     }
 
-    serverLog(LL_NOTICE, "supervised by systemd, will signal readyness");
+    serverLog(LL_NOTICE, "supervised by systemd, will signal readiness");
     if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
         serverLog(LL_WARNING,
                 "Can't connect to systemd socket %s", notify_socket);