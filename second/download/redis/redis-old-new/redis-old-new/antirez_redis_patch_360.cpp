@@ -2490,6 +2490,7 @@ int prepareForShutdown(int flags) {
     int nosave = flags & SHUTDOWN_NOSAVE;
 
     serverLog(LL_WARNING,"User requested shutdown...");
+
     /* Kill the saving child if there is a background saving in progress.
        We want to avoid race conditions, for instance our saving child may
        overwrite the synchronous saving did by SHUTDOWN. */
@@ -2498,6 +2499,7 @@ int prepareForShutdown(int flags) {
         kill(server.rdb_child_pid,SIGUSR1);
         rdbRemoveTempFile(server.rdb_child_pid);
     }
+
     if (server.aof_state != AOF_OFF) {
         /* Kill the AOF saving child as the AOF we already have may be longer
          * but contains the full dataset anyway. */
@@ -2516,6 +2518,8 @@ int prepareForShutdown(int flags) {
         serverLog(LL_NOTICE,"Calling fsync() on the AOF file.");
         aof_fsync(server.aof_fd);
     }
+
+    /* Create a new RDB file before exiting. */
     if ((server.saveparamslen > 0 && !nosave) || save) {
         serverLog(LL_NOTICE,"Saving the final RDB snapshot before exiting.");
         /* Snapshotting. Perform a SYNC SAVE and exit */
@@ -2529,10 +2533,17 @@ int prepareForShutdown(int flags) {
             return C_ERR;
         }
     }
+
+    /* Remove the pid file if possible and needed. */
     if (server.daemonize || server.pidfile) {
         serverLog(LL_NOTICE,"Removing the pid file.");
         unlink(server.pidfile);
     }
+
+    /* Best effort flush of slave output buffers, so that we hopefully
+     * send them pending writes. */
+    flushSlavesOutputBuffers();
+
     /* Close the listening sockets. Apparently this allows faster restarts. */
     closeListeningSockets(1);
     serverLog(LL_WARNING,"%s is now ready to exit, bye bye...",