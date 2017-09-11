@@ -45,7 +45,7 @@ void stopAppendOnly(void) {
  * at runtime using the CONFIG command. */
 int startAppendOnly(void) {
     server.lastfsync = time(NULL);
-    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    server.appendfd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
     redisAssert(server.aof_state == REDIS_AOF_OFF);
     if (server.appendfd == -1) {
         redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
@@ -86,10 +86,10 @@ void flushAppendOnlyFile(int force) {
 
     if (sdslen(server.aofbuf) == 0) return;
 
-    if (server.appendfsync == APPENDFSYNC_EVERYSEC)
+    if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
         sync_in_progress = bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC) != 0;
 
-    if (server.appendfsync == APPENDFSYNC_EVERYSEC && !force) {
+    if (server.aof_fsync == AOF_FSYNC_EVERYSEC && !force) {
         /* With this append fsync policy we do background fsyncing.
          * If the fsync is still in progress we can try to delay
          * the write for a couple of seconds. */
@@ -130,7 +130,7 @@ void flushAppendOnlyFile(int force) {
         }
         exit(1);
     }
-    server.appendonly_current_size += nwritten;
+    server.aof_current_size += nwritten;
 
     /* Re-use AOF buffer when it is small enough. The maximum comes from the
      * arena size of 4k minus some overhead (but is otherwise arbitrary). */
@@ -143,17 +143,17 @@ void flushAppendOnlyFile(int force) {
 
     /* Don't fsync if no-appendfsync-on-rewrite is set to yes and there are
      * children doing I/O in the background. */
-    if (server.no_appendfsync_on_rewrite &&
+    if (server.aof_no_fsync_on_rewrite &&
         (server.bgrewritechildpid != -1 || server.bgsavechildpid != -1))
             return;
 
     /* Perform the fsync if needed. */
-    if (server.appendfsync == APPENDFSYNC_ALWAYS) {
+    if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
         /* aof_fsync is defined as fdatasync() for Linux in order to avoid
          * flushing metadata. */
         aof_fsync(server.appendfd); /* Let's try to get this data on the disk */
         server.lastfsync = server.unixtime;
-    } else if ((server.appendfsync == APPENDFSYNC_EVERYSEC &&
+    } else if ((server.aof_fsync == AOF_FSYNC_EVERYSEC &&
                 server.unixtime > server.lastfsync)) {
         if (!sync_in_progress) aof_background_fsync(server.appendfd);
         server.lastfsync = server.unixtime;
@@ -314,7 +314,7 @@ int loadAppendOnlyFile(char *filename) {
     long loops = 0;
 
     if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
-        server.appendonly_current_size = 0;
+        server.aof_current_size = 0;
         fclose(fp);
         return REDIS_ERR;
     }
@@ -398,7 +398,7 @@ int loadAppendOnlyFile(char *filename) {
     server.aof_state = old_aof_state;
     stopLoading();
     aofUpdateCurrentSize();
-    server.auto_aofrewrite_base_size = server.appendonly_current_size;
+    server.aof_rewrite_base_size = server.aof_current_size;
     return REDIS_OK;
 
 readerr:
@@ -441,8 +441,8 @@ int rewriteListObject(rio *r, robj *key, robj *o) {
 
         while(ziplistGet(p,&vstr,&vlen,&vlong)) {
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"RPUSH",5) == 0) return 0;
@@ -454,7 +454,7 @@ int rewriteListObject(rio *r, robj *key, robj *o) {
                 if (rioWriteBulkLongLong(r,vlong) == 0) return 0;
             }
             p = ziplistNext(zl,p);
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
@@ -467,15 +467,15 @@ int rewriteListObject(rio *r, robj *key, robj *o) {
             robj *eleobj = listNodeValue(ln);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"RPUSH",5) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkObject(r,eleobj) == 0) return 0;
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else {
@@ -495,15 +495,15 @@ int rewriteSetObject(rio *r, robj *key, robj *o) {
 
         while(intsetGet(o->ptr,ii++,&llval)) {
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"SADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkLongLong(r,llval) == 0) return 0;
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else if (o->encoding == REDIS_ENCODING_HT) {
@@ -513,15 +513,15 @@ int rewriteSetObject(rio *r, robj *key, robj *o) {
         while((de = dictNext(di)) != NULL) {
             robj *eleobj = dictGetKey(de);
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"SADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkObject(r,eleobj) == 0) return 0;
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
         dictReleaseIterator(di);
@@ -554,8 +554,8 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
             score = zzlGetScore(sptr);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"ZADD",4) == 0) return 0;
@@ -568,7 +568,7 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
                 if (rioWriteBulkLongLong(r,vll) == 0) return 0;
             }
             zzlNext(zl,&eptr,&sptr);
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else if (o->encoding == REDIS_ENCODING_SKIPLIST) {
@@ -581,16 +581,16 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
             double *score = dictGetVal(de);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"ZADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkDouble(r,*score) == 0) return 0;
             if (rioWriteBulkObject(r,eleobj) == 0) return 0;
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
         dictReleaseIterator(di);
@@ -612,16 +612,16 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
 
         while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"HMSET",5) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkString(r,(char*)field,flen) == 0) return 0;
             if (rioWriteBulkString(r,(char*)val,vlen) == 0) return 0;
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else {
@@ -633,16 +633,16 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
             robj *val = dictGetVal(de);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOFREWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOFREWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
+                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"HMSET",5) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkObject(r,field) == 0) return 0;
             if (rioWriteBulkObject(r,val) == 0) return 0;
-            if (++count == REDIS_AOFREWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
         dictReleaseIterator(di);
@@ -655,7 +655,7 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
  *
  * In order to minimize the number of commands needed in the rewritten
  * log Redis uses variadic commands when possible, such as RPUSH, SADD
- * and ZADD. However at max REDIS_AOFREWRITE_ITEMS_PER_CMD items per time
+ * and ZADD. However at max REDIS_AOF_REWRITE_ITEMS_PER_CMD items per time
  * are inserted using a single command. */
 int rewriteAppendOnlyFile(char *filename) {
     dictIterator *di = NULL;
@@ -799,7 +799,7 @@ int rewriteAppendOnlyFileBackground(void) {
         }
         redisLog(REDIS_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
-        server.aofrewrite_scheduled = 0;
+        server.aof_rewrite_scheduled = 0;
         server.bgrewritechildpid = childpid;
         updateDictResizePolicy();
         /* We set appendseldb to -1 in order to force the next call to the
@@ -816,7 +816,7 @@ void bgrewriteaofCommand(redisClient *c) {
     if (server.bgrewritechildpid != -1) {
         addReplyError(c,"Background append only file rewriting already in progress");
     } else if (server.bgsavechildpid != -1) {
-        server.aofrewrite_scheduled = 1;
+        server.aof_rewrite_scheduled = 1;
         addReplyStatus(c,"Background append only file rewriting scheduled");
     } else if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
         addReplyStatus(c,"Background append only file rewriting started");
@@ -832,7 +832,7 @@ void aofRemoveTempFile(pid_t childpid) {
     unlink(tmpfile);
 }
 
-/* Update the server.appendonly_current_size filed explicitly using stat(2)
+/* Update the server.aof_current_size filed explicitly using stat(2)
  * to check the size of the file. This is useful after a rewrite or after
  * a restart, normally the size is updated just adding the write length
  * to the current lenght, that is much faster. */
@@ -843,7 +843,7 @@ void aofUpdateCurrentSize(void) {
         redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
             strerror(errno));
     } else {
-        server.appendonly_current_size = sb.st_size;
+        server.aof_current_size = sb.st_size;
     }
 }
 
@@ -919,15 +919,15 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
              /* Don't care if this fails: oldfd will be -1 and we handle that.
               * One notable case of -1 return is if the old file does
               * not exist. */
-             oldfd = open(server.appendfilename,O_RDONLY|O_NONBLOCK);
+             oldfd = open(server.aof_filename,O_RDONLY|O_NONBLOCK);
         } else {
             /* AOF enabled */
             oldfd = -1; /* We'll set this to the current AOF filedes later. */
         }
 
         /* Rename the temporary file. This will not unlink the target file if
          * it exists, because we reference it with "oldfd". */
-        if (rename(tmpfile,server.appendfilename) == -1) {
+        if (rename(tmpfile,server.aof_filename) == -1) {
             redisLog(REDIS_WARNING,
                 "Error trying to rename the temporary AOF: %s", strerror(errno));
             close(newfd);
@@ -943,13 +943,13 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             /* AOF enabled, replace the old fd with the new one. */
             oldfd = server.appendfd;
             server.appendfd = newfd;
-            if (server.appendfsync == APPENDFSYNC_ALWAYS)
+            if (server.aof_fsync == AOF_FSYNC_ALWAYS)
                 aof_fsync(newfd);
-            else if (server.appendfsync == APPENDFSYNC_EVERYSEC)
+            else if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
                 aof_background_fsync(newfd);
             server.appendseldb = -1; /* Make sure SELECT is re-issued */
             aofUpdateCurrentSize();
-            server.auto_aofrewrite_base_size = server.appendonly_current_size;
+            server.aof_rewrite_base_size = server.aof_current_size;
 
             /* Clear regular AOF buffer since its contents was just written to
              * the new AOF from the background rewrite buffer. */
@@ -982,5 +982,5 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     server.bgrewritechildpid = -1;
     /* Schedule a new rewrite if we are waiting for it to switch the AOF ON. */
     if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
-        server.aofrewrite_scheduled = 1;
+        server.aof_rewrite_scheduled = 1;
 }