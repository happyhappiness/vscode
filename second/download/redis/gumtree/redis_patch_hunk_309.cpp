      * at least if the filesystem we are writing is a real physical one.
      * While this will save us against the server being killed I don't think
      * there is much to do about the whole server stopping for power problems
      * or alike */
     nwritten = write(server.aof_fd,server.aof_buf,sdslen(server.aof_buf));
     if (nwritten != (signed)sdslen(server.aof_buf)) {
-        /* Ooops, we are in troubles. The best thing to do for now is
-         * aborting instead of giving the illusion that everything is
-         * working as expected. */
+        static time_t last_write_error_log = 0;
+        int can_log = 0;
+
+        /* Limit logging rate to 1 line per AOF_WRITE_LOG_ERROR_RATE seconds. */
+        if ((server.unixtime - last_write_error_log) > AOF_WRITE_LOG_ERROR_RATE) {
+            can_log = 1;
+            last_write_error_log = server.unixtime;
+        }
+
+        /* Lof the AOF write error and record the error code. */
         if (nwritten == -1) {
-            redisLog(REDIS_WARNING,"Exiting on error writing to the append-only file: %s",strerror(errno));
+            if (can_log) {
+                redisLog(REDIS_WARNING,"Error writing to the AOF file: %s",
+                    strerror(errno));
+                server.aof_last_write_errno = errno;
+            }
         } else {
-            redisLog(REDIS_WARNING,"Exiting on short write while writing to "
-                                   "the append-only file: %s (nwritten=%ld, "
-                                   "expected=%ld)",
-                                   strerror(errno),
-                                   (long)nwritten,
-                                   (long)sdslen(server.aof_buf));
+            if (can_log) {
+                redisLog(REDIS_WARNING,"Short write while writing to "
+                                       "the AOF file: (nwritten=%lld, "
+                                       "expected=%lld)",
+                                       (long long)nwritten,
+                                       (long long)sdslen(server.aof_buf));
+            }
 
             if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
-                redisLog(REDIS_WARNING, "Could not remove short write "
-                         "from the append-only file.  Redis may refuse "
-                         "to load the AOF the next time it starts.  "
-                         "ftruncate: %s", strerror(errno));
+                if (can_log) {
+                    redisLog(REDIS_WARNING, "Could not remove short write "
+                             "from the append-only file.  Redis may refuse "
+                             "to load the AOF the next time it starts.  "
+                             "ftruncate: %s", strerror(errno));
+                }
+            } else {
+                /* If the ftrunacate() succeeded we can set nwritten to
+                 * -1 since there is no longer partial data into the AOF. */
+                nwritten = -1;
             }
+            server.aof_last_write_errno = ENOSPC;
+        }
+
+        /* Handle the AOF write error. */
+        if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
+            /* We can't recover when the fsync policy is ALWAYS since the
+             * reply for the client is already in the output buffers, and we
+             * have the contract with the user that on acknowledged write data
+             * is synched on disk. */
+            redisLog(REDIS_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
+            exit(1);
+        } else {
+            /* Recover from failed write leaving data into the buffer. However
+             * set an error to stop accepting writes as long as the error
+             * condition is not cleared. */
+            server.aof_last_write_status = REDIS_ERR;
+
+            /* Trim the sds buffer if there was a partial write, and there
+             * was no way to undo it with ftruncate(2). */
+            if (nwritten > 0) {
+                server.aof_current_size += nwritten;
+                sdsrange(server.aof_buf,nwritten,-1);
+            }
+            return; /* We'll try again on the next call... */
+        }
+    } else {
+        /* Successful write(2). If AOF was in error state, restore the
+         * OK state and log the event. */
+        if (server.aof_last_write_status == REDIS_ERR) {
+            redisLog(REDIS_WARNING,
+                "AOF write error looks solved, Redis can write again.");
+            server.aof_last_write_status = REDIS_OK;
         }
-        exit(1);
     }
     server.aof_current_size += nwritten;
 
     /* Re-use AOF buffer when it is small enough. The maximum comes from the
      * arena size of 4k minus some overhead (but is otherwise arbitrary). */
     if ((sdslen(server.aof_buf)+sdsavail(server.aof_buf)) < 4000) {
