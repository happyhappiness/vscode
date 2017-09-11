@@ -669,56 +669,119 @@ void aofUpdateCurrentSize(void) {
  * Handle this. */
 void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
-        int fd;
+        int newfd, oldfd;
+        int nwritten;
         char tmpfile[256];
+        long long now = ustime();
 
         redisLog(REDIS_NOTICE,
-            "Background append only file rewriting terminated with success");
-        /* Now it's time to flush the differences accumulated by the parent */
-        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) server.bgrewritechildpid);
-        fd = open(tmpfile,O_WRONLY|O_APPEND);
-        if (fd == -1) {
-            redisLog(REDIS_WARNING, "Not able to open the temp append only file produced by the child: %s", strerror(errno));
+            "Background AOF rewrite terminated with success");
+
+        /* Flush the differences accumulated by the parent to the rewritten AOF. */
+        snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int)server.bgrewritechildpid);
+        newfd = open(tmpfile,O_WRONLY|O_APPEND);
+        if (newfd == -1) {
+            redisLog(REDIS_WARNING,
+                "Unable to open the temporary AOF produced by the child: %s", strerror(errno));
             goto cleanup;
         }
-        /* Flush our data... */
-        if (write(fd,server.bgrewritebuf,sdslen(server.bgrewritebuf)) !=
-                (signed) sdslen(server.bgrewritebuf)) {
-            redisLog(REDIS_WARNING, "Error or short write trying to flush the parent diff of the append log file in the child temp file: %s", strerror(errno));
-            close(fd);
+
+        nwritten = write(newfd,server.bgrewritebuf,sdslen(server.bgrewritebuf));
+        if (nwritten != (signed)sdslen(server.bgrewritebuf)) {
+            if (nwritten == -1) {
+                redisLog(REDIS_WARNING,
+                    "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
+            } else {
+                redisLog(REDIS_WARNING,
+                    "Short write trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
+            }
+            close(newfd);
             goto cleanup;
         }
-        redisLog(REDIS_NOTICE,"Parent diff flushed into the new append log file with success (%lu bytes)",sdslen(server.bgrewritebuf));
-        /* Now our work is to rename the temp file into the stable file. And
-         * switch the file descriptor used by the server for append only. */
+
+        redisLog(REDIS_NOTICE,
+            "Parent diff successfully flushed to the rewritten AOF (%lu bytes)", nwritten);
+
+        /* The only remaining thing to do is to rename the temporary file to
+         * the configured file and switch the file descriptor used to do AOF
+         * writes. There are two possible scenarios:
+         *
+         * 1) AOF is DISABLED and this was a one time rewrite. The temporary
+         * file will be renamed to the configured file. When this file already
+         * exists, it will be unlinked, which may block the server.
+         *
+         * 2) AOF is ENABLED and the rewritten AOF will immediately start
+         * receiving writes. After the temporary file is renamed to the
+         * configured file, the original AOF file descriptor will be closed.
+         * Since this will be the last reference to that file, closing it
+         * causes the underlying file to be unlinked, which may block the
+         * server.
+         *
+         * To mitigate the blocking effect of the unlink operation (either
+         * caused by rename(2) in scenario 1, or by close(2) in scenario 2), we
+         * use a background thread in libeio to take care of this. First, we
+         * make scenario 1 identical to scenario 2 by opening the target file
+         * when it exists. The unlink operation after the rename(2) will then
+         * be executed upon calling close(2) for its descriptor. Everything to
+         * guarantee atomicity for this switch has already happened by then, so
+         * we don't care what the outcome or duration of that close operation
+         * is, as long as the file descriptor is released again. */
+        if (server.appendfd == -1) {
+            /* AOF disabled */
+            struct stat st;
+
+            /* Check if the configured filename exists. If so, we need to open
+             * it to prevent rename(2) from unlinking it. */
+            if (stat(server.appendfilename, &st) == ENOENT) {
+                oldfd = -1;
+            } else {
+                /* Don't care if this fails: oldfd will be -1. */
+                oldfd = open(server.appendfilename,O_RDONLY|O_NONBLOCK);
+            }
+        } else {
+            /* AOF enabled */
+            oldfd = -1;
+        }
+
+        /* Rename the temporary file. This will not unlink the target file if
+         * it exists, because we reference it with "oldfd". */
         if (rename(tmpfile,server.appendfilename) == -1) {
-            redisLog(REDIS_WARNING,"Can't rename the temp append only file into the stable one: %s", strerror(errno));
-            close(fd);
+            redisLog(REDIS_WARNING,
+                "Error trying to rename the temporary AOF: %s", strerror(errno));
+            close(newfd);
+            if (oldfd != -1)
+                close(oldfd);
             goto cleanup;
         }
-        /* Mission completed... almost */
-        redisLog(REDIS_NOTICE,"Append only file successfully rewritten.");
-        if (server.appendfd != -1) {
-            /* If append only is actually enabled... */
-            close(server.appendfd);
-            server.appendfd = fd;
-            if (server.appendfsync != APPENDFSYNC_NO) aof_fsync(fd);
-            server.appendseldb = -1; /* Make sure it will issue SELECT */
-            redisLog(REDIS_NOTICE,"The new append only file was selected for future appends.");
+
+        if (server.appendfd == -1) {
+            /* AOF disabled */
+            close(newfd);
+        } else {
+            /* AOF enabled */
+            oldfd = server.appendfd;
+            server.appendfd = newfd;
+            if (server.appendfsync != APPENDFSYNC_NO) aof_fsync(newfd);
+            server.appendseldb = -1; /* Make sure SELECT is re-issued */
             aofUpdateCurrentSize();
             server.auto_aofrewrite_base_size = server.appendonly_current_size;
-        } else {
-            /* If append only is disabled we just generate a dump in this
-             * format. Why not? */
-            close(fd);
         }
+
+        redisLog(REDIS_NOTICE, "Background AOF rewrite successful");
+
+        /* Asynchronously close the overwritten AOF. */
+        if (oldfd != -1) eio_close(oldfd, 0, NULL, 0);
+
+        redisLog(REDIS_VERBOSE,
+            "Background AOF rewrite signal handler took %lldus", ustime()-now);
     } else if (!bysignal && exitcode != 0) {
-        redisLog(REDIS_WARNING, "Background append only file rewriting error");
+        redisLog(REDIS_WARNING,
+            "Background AOF rewrite terminated with error");
     } else {
         redisLog(REDIS_WARNING,
-            "Background append only file rewriting terminated by signal %d",
-            bysignal);
+            "Background AOF rewrite terminated by signal %d", bysignal);
     }
+
 cleanup:
     sdsfree(server.bgrewritebuf);
     server.bgrewritebuf = sdsempty();