@@ -238,17 +238,17 @@ int startAppendOnly(void) {
     serverAssert(server.aof_state == REDIS_AOF_OFF);
     if (server.aof_fd == -1) {
         serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
-    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
+    if (rewriteAppendOnlyFileBackground() == C_ERR) {
         close(server.aof_fd);
         serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
-        return REDIS_ERR;
+        return C_ERR;
     }
     /* We correctly switched on AOF, now wait for the rewrite to be complete
      * in order to append data on disk. */
     server.aof_state = REDIS_AOF_WAIT_REWRITE;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Write the append only file buffer on disk.
@@ -380,7 +380,7 @@ void flushAppendOnlyFile(int force) {
             /* Recover from failed write leaving data into the buffer. However
              * set an error to stop accepting writes as long as the error
              * condition is not cleared. */
-            server.aof_last_write_status = REDIS_ERR;
+            server.aof_last_write_status = C_ERR;
 
             /* Trim the sds buffer if there was a partial write, and there
              * was no way to undo it with ftruncate(2). */
@@ -393,10 +393,10 @@ void flushAppendOnlyFile(int force) {
     } else {
         /* Successful write(2). If AOF was in error state, restore the
          * OK state and log the event. */
-        if (server.aof_last_write_status == REDIS_ERR) {
+        if (server.aof_last_write_status == C_ERR) {
             serverLog(REDIS_WARNING,
                 "AOF write error looks solved, Redis can write again.");
-            server.aof_last_write_status = REDIS_OK;
+            server.aof_last_write_status = C_OK;
         }
     }
     server.aof_current_size += nwritten;
@@ -593,8 +593,8 @@ void freeFakeClient(struct client *c) {
     zfree(c);
 }
 
-/* Replay the append log file. On success REDIS_OK is returned. On non fatal
- * error (the append only file is zero-length) REDIS_ERR is returned. On
+/* Replay the append log file. On success C_OK is returned. On non fatal
+ * error (the append only file is zero-length) C_ERR is returned. On
  * fatal error an error message is logged and the program exists. */
 int loadAppendOnlyFile(char *filename) {
     struct client *fakeClient;
@@ -607,7 +607,7 @@ int loadAppendOnlyFile(char *filename) {
     if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
         server.aof_current_size = 0;
         fclose(fp);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (fp == NULL) {
@@ -699,14 +699,14 @@ int loadAppendOnlyFile(char *filename) {
      * If the client is in the middle of a MULTI/EXEC, log error and quit. */
     if (fakeClient->flags & REDIS_MULTI) goto uxeof;
 
-loaded_ok: /* DB loaded, cleanup and return REDIS_OK to the caller. */
+loaded_ok: /* DB loaded, cleanup and return C_OK to the caller. */
     fclose(fp);
     freeFakeClient(fakeClient);
     server.aof_state = old_aof_state;
     stopLoading();
     aofUpdateCurrentSize();
     server.aof_rewrite_base_size = server.aof_current_size;
-    return REDIS_OK;
+    return C_OK;
 
 readerr: /* Read error. If feof(fp) is true, fall through to unexpected EOF. */
     if (!feof(fp)) {
@@ -952,7 +952,7 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
     long long count = 0, items = hashTypeLength(o);
 
     hi = hashTypeInitIterator(o);
-    while (hashTypeNext(hi) != REDIS_ERR) {
+    while (hashTypeNext(hi) != C_ERR) {
         if (count == 0) {
             int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
                 REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
@@ -1012,7 +1012,7 @@ int rewriteAppendOnlyFile(char *filename) {
     fp = fopen(tmpfile,"w");
     if (!fp) {
         serverLog(REDIS_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     server.aof_child_diff = sdsempty();
@@ -1027,7 +1027,7 @@ int rewriteAppendOnlyFile(char *filename) {
         di = dictGetSafeIterator(d);
         if (!di) {
             fclose(fp);
-            return REDIS_ERR;
+            return C_ERR;
         }
 
         /* SELECT the new DB */
@@ -1140,17 +1140,17 @@ int rewriteAppendOnlyFile(char *filename) {
     if (rename(tmpfile,filename) == -1) {
         serverLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
-        return REDIS_ERR;
+        return C_ERR;
     }
     serverLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
-    return REDIS_OK;
+    return C_OK;
 
 werr:
     serverLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
     if (di) dictReleaseIterator(di);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* ----------------------------------------------------------------------------
@@ -1207,13 +1207,13 @@ int aofCreatePipes(void) {
     server.aof_pipe_write_ack_to_child = fds[5];
     server.aof_pipe_read_ack_from_parent = fds[4];
     server.aof_stop_sending_diff = 0;
-    return REDIS_OK;
+    return C_OK;
 
 error:
     serverLog(REDIS_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
         strerror(errno));
     for (j = 0; j < 6; j++) if(fds[j] != -1) close(fds[j]);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 void aofClosePipes(void) {
@@ -1247,8 +1247,8 @@ int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
     long long start;
 
-    if (server.aof_child_pid != -1) return REDIS_ERR;
-    if (aofCreatePipes() != REDIS_OK) return REDIS_ERR;
+    if (server.aof_child_pid != -1) return C_ERR;
+    if (aofCreatePipes() != C_OK) return C_ERR;
     start = ustime();
     if ((childpid = fork()) == 0) {
         char tmpfile[256];
@@ -1257,7 +1257,7 @@ int rewriteAppendOnlyFileBackground(void) {
         closeListeningSockets(0);
         redisSetProcTitle("redis-aof-rewrite");
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
-        if (rewriteAppendOnlyFile(tmpfile) == REDIS_OK) {
+        if (rewriteAppendOnlyFile(tmpfile) == C_OK) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
@@ -1278,7 +1278,7 @@ int rewriteAppendOnlyFileBackground(void) {
             serverLog(REDIS_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));
-            return REDIS_ERR;
+            return C_ERR;
         }
         serverLog(REDIS_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
@@ -1292,9 +1292,9 @@ int rewriteAppendOnlyFileBackground(void) {
          * with a SELECT statement and it will be safe to merge. */
         server.aof_selected_db = -1;
         replicationScriptCacheFlush();
-        return REDIS_OK;
+        return C_OK;
     }
-    return REDIS_OK; /* unreached */
+    return C_OK; /* unreached */
 }
 
 void bgrewriteaofCommand(client *c) {
@@ -1303,7 +1303,7 @@ void bgrewriteaofCommand(client *c) {
     } else if (server.rdb_child_pid != -1) {
         server.aof_rewrite_scheduled = 1;
         addReplyStatus(c,"Background append only file rewriting scheduled");
-    } else if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
+    } else if (rewriteAppendOnlyFileBackground() == C_OK) {
         addReplyStatus(c,"Background append only file rewriting started");
     } else {
         addReply(c,shared.err);
@@ -1446,7 +1446,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             server.aof_buf = sdsempty();
         }
 
-        server.aof_lastbgrewrite_status = REDIS_OK;
+        server.aof_lastbgrewrite_status = C_OK;
 
         serverLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
         /* Change state from WAIT_REWRITE to ON if needed */
@@ -1459,12 +1459,12 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         serverLog(REDIS_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);
     } else if (!bysignal && exitcode != 0) {
-        server.aof_lastbgrewrite_status = REDIS_ERR;
+        server.aof_lastbgrewrite_status = C_ERR;
 
         serverLog(REDIS_WARNING,
             "Background AOF rewrite terminated with error");
     } else {
-        server.aof_lastbgrewrite_status = REDIS_ERR;
+        server.aof_lastbgrewrite_status = C_ERR;
 
         serverLog(REDIS_WARNING,
             "Background AOF rewrite terminated by signal %d", bysignal);