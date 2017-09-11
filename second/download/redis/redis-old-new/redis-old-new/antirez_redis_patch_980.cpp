@@ -605,11 +605,13 @@ void shutdownCommand(redisClient *c) {
             return;
         }
     }
-    /* SHUTDOWN can be called even while the server is in "loading" state.
-     * When this happens we need to make sure no attempt is performed to save
+    /* When SHUTDOWN is called while the server is loading a dataset in
+     * memory we need to make sure no attempt is performed to save
      * the dataset on shutdown (otherwise it could overwrite the current DB
-     * with half-read data). */
-    if (server.loading)
+     * with half-read data).
+     *
+     * Also when in Sentinel mode clear the SAVE flag and force NOSAVE. */
+    if (server.loading || server.sentinel_mode)
         flags = (flags & ~REDIS_SHUTDOWN_SAVE) | REDIS_SHUTDOWN_NOSAVE;
     if (prepareForShutdown(flags) == REDIS_OK) exit(0);
     addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");