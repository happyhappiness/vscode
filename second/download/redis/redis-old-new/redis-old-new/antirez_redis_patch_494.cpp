@@ -152,7 +152,7 @@ void aofRewriteBufferAppend(unsigned char *s, unsigned long len) {
             if (((numblocks+1) % 10) == 0) {
                 int level = ((numblocks+1) % 100) == 0 ? REDIS_WARNING :
                                                          REDIS_NOTICE;
-                redisLog(level,"Background AOF buffer size: %lu MB",
+                serverLog(level,"Background AOF buffer size: %lu MB",
                     aofRewriteBufferSize()/(1024*1024));
             }
         }
@@ -216,7 +216,7 @@ void stopAppendOnly(void) {
     if (server.aof_child_pid != -1) {
         int statloc;
 
-        redisLog(REDIS_NOTICE,"Killing running AOF rewrite child: %ld",
+        serverLog(REDIS_NOTICE,"Killing running AOF rewrite child: %ld",
             (long) server.aof_child_pid);
         if (kill(server.aof_child_pid,SIGUSR1) != -1)
             wait3(&statloc,0,NULL);
@@ -237,12 +237,12 @@ int startAppendOnly(void) {
     server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
     redisAssert(server.aof_state == REDIS_AOF_OFF);
     if (server.aof_fd == -1) {
-        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
+        serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
         return REDIS_ERR;
     }
     if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
         close(server.aof_fd);
-        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
+        serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
         return REDIS_ERR;
     }
     /* We correctly switched on AOF, now wait for the rewrite to be complete
@@ -298,7 +298,7 @@ void flushAppendOnlyFile(int force) {
             /* Otherwise fall trough, and go write since we can't wait
              * over two seconds. */
             server.aof_delayed_fsync++;
-            redisLog(REDIS_NOTICE,"Asynchronous AOF fsync is taking too long (disk is busy?). Writing the AOF buffer without waiting for fsync to complete, this may slow down Redis.");
+            serverLog(REDIS_NOTICE,"Asynchronous AOF fsync is taking too long (disk is busy?). Writing the AOF buffer without waiting for fsync to complete, this may slow down Redis.");
         }
     }
     /* We want to perform a single write. This should be guaranteed atomic
@@ -340,13 +340,13 @@ void flushAppendOnlyFile(int force) {
         /* Log the AOF write error and record the error code. */
         if (nwritten == -1) {
             if (can_log) {
-                redisLog(REDIS_WARNING,"Error writing to the AOF file: %s",
+                serverLog(REDIS_WARNING,"Error writing to the AOF file: %s",
                     strerror(errno));
                 server.aof_last_write_errno = errno;
             }
         } else {
             if (can_log) {
-                redisLog(REDIS_WARNING,"Short write while writing to "
+                serverLog(REDIS_WARNING,"Short write while writing to "
                                        "the AOF file: (nwritten=%lld, "
                                        "expected=%lld)",
                                        (long long)nwritten,
@@ -355,7 +355,7 @@ void flushAppendOnlyFile(int force) {
 
             if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
                 if (can_log) {
-                    redisLog(REDIS_WARNING, "Could not remove short write "
+                    serverLog(REDIS_WARNING, "Could not remove short write "
                              "from the append-only file.  Redis may refuse "
                              "to load the AOF the next time it starts.  "
                              "ftruncate: %s", strerror(errno));
@@ -374,7 +374,7 @@ void flushAppendOnlyFile(int force) {
              * reply for the client is already in the output buffers, and we
              * have the contract with the user that on acknowledged write data
              * is synced on disk. */
-            redisLog(REDIS_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
+            serverLog(REDIS_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
             exit(1);
         } else {
             /* Recover from failed write leaving data into the buffer. However
@@ -394,7 +394,7 @@ void flushAppendOnlyFile(int force) {
         /* Successful write(2). If AOF was in error state, restore the
          * OK state and log the event. */
         if (server.aof_last_write_status == REDIS_ERR) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "AOF write error looks solved, Redis can write again.");
             server.aof_last_write_status = REDIS_OK;
         }
@@ -611,7 +611,7 @@ int loadAppendOnlyFile(char *filename) {
     }
 
     if (fp == NULL) {
-        redisLog(REDIS_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
+        serverLog(REDIS_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
         exit(1);
     }
 
@@ -677,7 +677,7 @@ int loadAppendOnlyFile(char *filename) {
         /* Command lookup */
         cmd = lookupCommand(argv[0]->ptr);
         if (!cmd) {
-            redisLog(REDIS_WARNING,"Unknown command '%s' reading the append only file", (char*)argv[0]->ptr);
+            serverLog(REDIS_WARNING,"Unknown command '%s' reading the append only file", (char*)argv[0]->ptr);
             exit(1);
         }
 
@@ -710,40 +710,40 @@ int loadAppendOnlyFile(char *filename) {
 
 readerr: /* Read error. If feof(fp) is true, fall through to unexpected EOF. */
     if (!feof(fp)) {
-        redisLog(REDIS_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
+        serverLog(REDIS_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
         exit(1);
     }
 
 uxeof: /* Unexpected AOF end of file. */
     if (server.aof_load_truncated) {
-        redisLog(REDIS_WARNING,"!!! Warning: short read while loading the AOF file !!!");
-        redisLog(REDIS_WARNING,"!!! Truncating the AOF at offset %llu !!!",
+        serverLog(REDIS_WARNING,"!!! Warning: short read while loading the AOF file !!!");
+        serverLog(REDIS_WARNING,"!!! Truncating the AOF at offset %llu !!!",
             (unsigned long long) valid_up_to);
         if (valid_up_to == -1 || truncate(filename,valid_up_to) == -1) {
             if (valid_up_to == -1) {
-                redisLog(REDIS_WARNING,"Last valid command offset is invalid");
+                serverLog(REDIS_WARNING,"Last valid command offset is invalid");
             } else {
-                redisLog(REDIS_WARNING,"Error truncating the AOF file: %s",
+                serverLog(REDIS_WARNING,"Error truncating the AOF file: %s",
                     strerror(errno));
             }
         } else {
             /* Make sure the AOF file descriptor points to the end of the
              * file after the truncate call. */
             if (server.aof_fd != -1 && lseek(server.aof_fd,0,SEEK_END) == -1) {
-                redisLog(REDIS_WARNING,"Can't seek the end of the AOF file: %s",
+                serverLog(REDIS_WARNING,"Can't seek the end of the AOF file: %s",
                     strerror(errno));
             } else {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "AOF loaded anyway because aof-load-truncated is enabled");
                 goto loaded_ok;
             }
         }
     }
-    redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
+    serverLog(REDIS_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
     exit(1);
 
 fmterr: /* Format error. */
-    redisLog(REDIS_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
+    serverLog(REDIS_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
     exit(1);
 }
 
@@ -1011,7 +1011,7 @@ int rewriteAppendOnlyFile(char *filename) {
     snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        redisLog(REDIS_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
+        serverLog(REDIS_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
         return REDIS_ERR;
     }
 
@@ -1118,13 +1118,13 @@ int rewriteAppendOnlyFile(char *filename) {
      * the child will eventually get terminated. */
     if (syncRead(server.aof_pipe_read_ack_from_parent,&byte,1,5000) != 1 ||
         byte != '!') goto werr;
-    redisLog(REDIS_NOTICE,"Parent agreed to stop sending diffs. Finalizing AOF...");
+    serverLog(REDIS_NOTICE,"Parent agreed to stop sending diffs. Finalizing AOF...");
 
     /* Read the final diff if any. */
     aofReadDiffFromParent();
 
     /* Write the received diff to the file. */
-    redisLog(REDIS_NOTICE,
+    serverLog(REDIS_NOTICE,
         "Concatenating %.2f MB of AOF diff received from parent.",
         (double) sdslen(server.aof_child_diff) / (1024*1024));
     if (rioWrite(&aof,server.aof_child_diff,sdslen(server.aof_child_diff)) == 0)
@@ -1138,15 +1138,15 @@ int rewriteAppendOnlyFile(char *filename) {
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        redisLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
+        serverLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
         return REDIS_ERR;
     }
-    redisLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
+    serverLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
     return REDIS_OK;
 
 werr:
-    redisLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
+    serverLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
     if (di) dictReleaseIterator(di);
@@ -1167,14 +1167,14 @@ void aofChildPipeReadable(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(mask);
 
     if (read(fd,&byte,1) == 1 && byte == '!') {
-        redisLog(REDIS_NOTICE,"AOF rewrite child asks to stop sending diffs.");
+        serverLog(REDIS_NOTICE,"AOF rewrite child asks to stop sending diffs.");
         server.aof_stop_sending_diff = 1;
         if (write(server.aof_pipe_write_ack_to_child,"!",1) != 1) {
             /* If we can't send the ack, inform the user, but don't try again
              * since in the other side the children will use a timeout if the
              * kernel can't buffer our write, or, the children was
              * terminated. */
-            redisLog(REDIS_WARNING,"Can't send ACK to AOF child: %s",
+            serverLog(REDIS_WARNING,"Can't send ACK to AOF child: %s",
                 strerror(errno));
         }
     }
@@ -1210,7 +1210,7 @@ int aofCreatePipes(void) {
     return REDIS_OK;
 
 error:
-    redisLog(REDIS_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
+    serverLog(REDIS_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
         strerror(errno));
     for (j = 0; j < 6; j++) if(fds[j] != -1) close(fds[j]);
     return REDIS_ERR;
@@ -1261,7 +1261,7 @@ int rewriteAppendOnlyFileBackground(void) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                redisLog(REDIS_NOTICE,
+                serverLog(REDIS_NOTICE,
                     "AOF rewrite: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
@@ -1275,12 +1275,12 @@ int rewriteAppendOnlyFileBackground(void) {
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));
             return REDIS_ERR;
         }
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
         server.aof_rewrite_scheduled = 0;
         server.aof_rewrite_time_start = time(NULL);
@@ -1327,7 +1327,7 @@ void aofUpdateCurrentSize(void) {
 
     latencyStartMonitor(latency);
     if (redis_fstat(server.aof_fd,&sb) == -1) {
-        redisLog(REDIS_WARNING,"Unable to obtain the AOF file length. stat: %s",
+        serverLog(REDIS_WARNING,"Unable to obtain the AOF file length. stat: %s",
             strerror(errno));
     } else {
         server.aof_current_size = sb.st_size;
@@ -1345,7 +1345,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         long long now = ustime();
         mstime_t latency;
 
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Background AOF rewrite terminated with success");
 
         /* Flush the differences accumulated by the parent to the
@@ -1355,21 +1355,21 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             (int)server.aof_child_pid);
         newfd = open(tmpfile,O_WRONLY|O_APPEND);
         if (newfd == -1) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Unable to open the temporary AOF produced by the child: %s", strerror(errno));
             goto cleanup;
         }
 
         if (aofRewriteBufferWrite(newfd) == -1) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
             close(newfd);
             goto cleanup;
         }
         latencyEndMonitor(latency);
         latencyAddSampleIfNeeded("aof-rewrite-diff-write",latency);
 
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Residual parent diff successfully flushed to the rewritten AOF (%.2f MB)", (double) aofRewriteBufferSize() / (1024*1024));
 
         /* The only remaining thing to do is to rename the temporary file to
@@ -1415,7 +1415,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
          * it exists, because we reference it with "oldfd". */
         latencyStartMonitor(latency);
         if (rename(tmpfile,server.aof_filename) == -1) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Error trying to rename the temporary AOF file: %s", strerror(errno));
             close(newfd);
             if (oldfd != -1) close(oldfd);
@@ -1448,25 +1448,25 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
 
         server.aof_lastbgrewrite_status = REDIS_OK;
 
-        redisLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
+        serverLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
         /* Change state from WAIT_REWRITE to ON if needed */
         if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
             server.aof_state = REDIS_AOF_ON;
 
         /* Asynchronously close the overwritten AOF. */
         if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);
 
-        redisLog(REDIS_VERBOSE,
+        serverLog(REDIS_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);
     } else if (!bysignal && exitcode != 0) {
         server.aof_lastbgrewrite_status = REDIS_ERR;
 
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Background AOF rewrite terminated with error");
     } else {
         server.aof_lastbgrewrite_status = REDIS_ERR;
 
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Background AOF rewrite terminated by signal %d", bysignal);
     }
 