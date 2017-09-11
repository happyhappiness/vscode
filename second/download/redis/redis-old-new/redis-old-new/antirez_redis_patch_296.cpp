@@ -4789,8 +4789,6 @@ void migrateCommand(client *c) {
     if (!error_from_target && socket_error && j == 0 && may_retry &&
         errno != ETIMEDOUT)
     {
-        zfree(newargv);
-        newargv = NULL; /* This will get reallocated on retry. */
         goto socket_err; /* A retry is guaranteed because of tested conditions.*/
     }
 
@@ -4816,7 +4814,8 @@ void migrateCommand(client *c) {
     }
 
     if (!error_from_target) {
-        /* Update the last_dbid in migrateCachedSocket and reply +OK. */
+        /* Success! Update the last_dbid in migrateCachedSocket, so that we can
+         * avoid SELECT the next time if the target DB is the same. Reply +OK. */
         cs->last_dbid = dbid;
         addReply(c,shared.ok);
     } else {
@@ -4833,14 +4832,22 @@ void migrateCommand(client *c) {
  * It is very common for the cached socket to get closed, if just reopening
  * it works it's a shame to notify the error to the caller. */
 socket_err:
+    /* Cleanup we want to perform in both the retry and no retry case.
+     * Note: Closing the migrate socket will also force SELECT next time. */
     sdsfree(cmd.io.buffer.ptr);
     migrateCloseSocket(c->argv[1],c->argv[2]);
-    /* Note: Closing the migrate socket will also force SELECT next time. */
+    zfree(newargv);
+    newargv = NULL; /* This will get reallocated on retry. */
+
+    /* Retry only if it's not a timeout and we never attempted a retry
+     * (or the code jumping here did not set may_retry to zero). */
     if (errno != ETIMEDOUT && may_retry) {
         may_retry = 0;
         goto try_again;
     }
-    zfree(ov); zfree(kv); zfree(newargv);
+
+    /* Cleanup we want to do if no retry is attempted. */
+    zfree(ov); zfree(kv);
     addReplySds(c,
         sdscatprintf(sdsempty(),
             "-IOERR error or timeout %s to target instance\r\n",