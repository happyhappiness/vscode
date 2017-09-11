@@ -1570,9 +1570,9 @@ void adjustOpenFilesLimit(void) {
             if (bestlimit < oldlimit) bestlimit = oldlimit;
 
             if (bestlimit < maxfiles) {
-                int old_maxclients = server.maxclients;
-                server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS;
-                if (server.maxclients < 1) {
+                unsigned int old_maxclients = server.maxclients;
+                server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS; /* NOTICE: server.maxclients is unsigned */
+                if (bestlimit <= CONFIG_MIN_RESERVED_FDS) {
                     serverLog(LL_WARNING,"Your current 'ulimit -n' "
                         "of %llu is not enough for the server to start. "
                         "Please increase your open file limit to at least "