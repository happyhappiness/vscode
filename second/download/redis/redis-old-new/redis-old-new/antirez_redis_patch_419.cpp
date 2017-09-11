@@ -1621,7 +1621,7 @@ void adjustOpenFilesLimit(void) {
                 server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS;
                 if (server.maxclients < 1) {
                     serverLog(LL_WARNING,"Your current 'ulimit -n' "
-                        "of %llu is not enough for Redis to start. "
+                        "of %llu is not enough for the server to start. "
                         "Please increase your open file limit to at least "
                         "%llu. Exiting.",
                         (unsigned long long) oldlimit,
@@ -1632,7 +1632,7 @@ void adjustOpenFilesLimit(void) {
                     "requiring at least %llu max file descriptors.",
                     old_maxclients,
                     (unsigned long long) maxfiles);
-                serverLog(LL_WARNING,"Redis can't set maximum open files "
+                serverLog(LL_WARNING,"Server can't set maximum open files "
                     "to %llu because of OS error: %s.",
                     (unsigned long long) maxfiles, strerror(setrlimit_error));
                 serverLog(LL_WARNING,"Current maximum open files is %llu. "