@@ -1576,7 +1576,10 @@ void adjustOpenFilesLimit(void) {
 
             if (bestlimit < maxfiles) {
                 unsigned int old_maxclients = server.maxclients;
-                server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS; /* NOTICE: server.maxclients is unsigned */
+                server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS;
+                /* maxclients is unsigned so may overflow: in order
+                 * to check if maxclients is now logically less than 1
+                 * we test indirectly via bestlimit. */
                 if (bestlimit <= CONFIG_MIN_RESERVED_FDS) {
                     serverLog(LL_WARNING,"Your current 'ulimit -n' "
                         "of %llu is not enough for the server to start. "