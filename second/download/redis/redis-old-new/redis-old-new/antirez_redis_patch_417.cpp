@@ -3869,14 +3869,14 @@ int main(int argc, char **argv) {
     if (background || server.pidfile) createPidFile();
     redisSetProcTitle(argv[0]);
     redisAsciiArt();
+    checkTcpBacklogSettings();
 
     if (!server.sentinel_mode) {
         /* Things not needed when running in Sentinel mode. */
         serverLog(LL_WARNING,"Server started, Redis version " REDIS_VERSION);
     #ifdef __linux__
         linuxMemoryWarnings();
     #endif
-        checkTcpBacklogSettings();
         loadDataFromDisk();
         if (server.cluster_enabled) {
             if (verifyClusterConfigWithData() == C_ERR) {