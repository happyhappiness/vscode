@@ -95,10 +95,10 @@ void aofChildWriteDiffData(aeEventLoop *el, int fd, void *privdata, int mask) {
     listNode *ln;
     aofrwblock *block;
     ssize_t nwritten;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(fd);
-    REDIS_NOTUSED(privdata);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(fd);
+    UNUSED(privdata);
+    UNUSED(mask);
 
     while(1) {
         ln = listFirst(server.aof_rewrite_buf_blocks);
@@ -150,8 +150,8 @@ void aofRewriteBufferAppend(unsigned char *s, unsigned long len) {
              * as a notice or warning. */
             numblocks = listLength(server.aof_rewrite_buf_blocks);
             if (((numblocks+1) % 10) == 0) {
-                int level = ((numblocks+1) % 100) == 0 ? REDIS_WARNING :
-                                                         REDIS_NOTICE;
+                int level = ((numblocks+1) % 100) == 0 ? LL_WARNING :
+                                                         LL_NOTICE;
                 serverLog(level,"Background AOF buffer size: %lu MB",
                     aofRewriteBufferSize()/(1024*1024));
             }
@@ -204,19 +204,19 @@ void aof_background_fsync(int fd) {
 /* Called when the user switches from "appendonly yes" to "appendonly no"
  * at runtime using the CONFIG command. */
 void stopAppendOnly(void) {
-    serverAssert(server.aof_state != REDIS_AOF_OFF);
+    serverAssert(server.aof_state != AOF_OFF);
     flushAppendOnlyFile(1);
     aof_fsync(server.aof_fd);
     close(server.aof_fd);
 
     server.aof_fd = -1;
     server.aof_selected_db = -1;
-    server.aof_state = REDIS_AOF_OFF;
+    server.aof_state = AOF_OFF;
     /* rewrite operation in progress? kill it, wait child exit */
     if (server.aof_child_pid != -1) {
         int statloc;
 
-        serverLog(REDIS_NOTICE,"Killing running AOF rewrite child: %ld",
+        serverLog(LL_NOTICE,"Killing running AOF rewrite child: %ld",
             (long) server.aof_child_pid);
         if (kill(server.aof_child_pid,SIGUSR1) != -1)
             wait3(&statloc,0,NULL);
@@ -235,19 +235,19 @@ void stopAppendOnly(void) {
 int startAppendOnly(void) {
     server.aof_last_fsync = server.unixtime;
     server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
-    serverAssert(server.aof_state == REDIS_AOF_OFF);
+    serverAssert(server.aof_state == AOF_OFF);
     if (server.aof_fd == -1) {
-        serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
+        serverLog(LL_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
         return C_ERR;
     }
     if (rewriteAppendOnlyFileBackground() == C_ERR) {
         close(server.aof_fd);
-        serverLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
+        serverLog(LL_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
         return C_ERR;
     }
     /* We correctly switched on AOF, now wait for the rewrite to be complete
      * in order to append data on disk. */
-    server.aof_state = REDIS_AOF_WAIT_REWRITE;
+    server.aof_state = AOF_WAIT_REWRITE;
     return C_OK;
 }
 
@@ -298,7 +298,7 @@ void flushAppendOnlyFile(int force) {
             /* Otherwise fall trough, and go write since we can't wait
              * over two seconds. */
             server.aof_delayed_fsync++;
-            serverLog(REDIS_NOTICE,"Asynchronous AOF fsync is taking too long (disk is busy?). Writing the AOF buffer without waiting for fsync to complete, this may slow down Redis.");
+            serverLog(LL_NOTICE,"Asynchronous AOF fsync is taking too long (disk is busy?). Writing the AOF buffer without waiting for fsync to complete, this may slow down Redis.");
         }
     }
     /* We want to perform a single write. This should be guaranteed atomic
@@ -340,13 +340,13 @@ void flushAppendOnlyFile(int force) {
         /* Log the AOF write error and record the error code. */
         if (nwritten == -1) {
             if (can_log) {
-                serverLog(REDIS_WARNING,"Error writing to the AOF file: %s",
+                serverLog(LL_WARNING,"Error writing to the AOF file: %s",
                     strerror(errno));
                 server.aof_last_write_errno = errno;
             }
         } else {
             if (can_log) {
-                serverLog(REDIS_WARNING,"Short write while writing to "
+                serverLog(LL_WARNING,"Short write while writing to "
                                        "the AOF file: (nwritten=%lld, "
                                        "expected=%lld)",
                                        (long long)nwritten,
@@ -355,7 +355,7 @@ void flushAppendOnlyFile(int force) {
 
             if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
                 if (can_log) {
-                    serverLog(REDIS_WARNING, "Could not remove short write "
+                    serverLog(LL_WARNING, "Could not remove short write "
                              "from the append-only file.  Redis may refuse "
                              "to load the AOF the next time it starts.  "
                              "ftruncate: %s", strerror(errno));
@@ -374,7 +374,7 @@ void flushAppendOnlyFile(int force) {
              * reply for the client is already in the output buffers, and we
              * have the contract with the user that on acknowledged write data
              * is synced on disk. */
-            serverLog(REDIS_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
+            serverLog(LL_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
             exit(1);
         } else {
             /* Recover from failed write leaving data into the buffer. However
@@ -394,7 +394,7 @@ void flushAppendOnlyFile(int force) {
         /* Successful write(2). If AOF was in error state, restore the
          * OK state and log the event. */
         if (server.aof_last_write_status == C_ERR) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "AOF write error looks solved, Redis can write again.");
             server.aof_last_write_status = C_OK;
         }
@@ -531,7 +531,7 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
     /* Append to the AOF buffer. This will be flushed on disk just before
      * of re-entering the event loop, so before the client will get a
      * positive reply about the operation performed. */
-    if (server.aof_state == REDIS_AOF_ON)
+    if (server.aof_state == AOF_ON)
         server.aof_buf = sdscatlen(server.aof_buf,buf,sdslen(buf));
 
     /* If a background append only file rewriting is in progress we want to
@@ -562,10 +562,10 @@ struct client *createFakeClient(void) {
     c->argv = NULL;
     c->bufpos = 0;
     c->flags = 0;
-    c->btype = REDIS_BLOCKED_NONE;
+    c->btype = BLOCKED_NONE;
     /* We set the fake client as a slave waiting for the synchronization
      * so that Redis will not try to send replies to this client. */
-    c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+    c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
     c->reply = listCreate();
     c->reply_bytes = 0;
     c->obuf_soft_limit_reached_time = 0;
@@ -611,13 +611,13 @@ int loadAppendOnlyFile(char *filename) {
     }
 
     if (fp == NULL) {
-        serverLog(REDIS_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
+        serverLog(LL_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
         exit(1);
     }
 
     /* Temporarily disable AOF, to prevent EXEC from feeding a MULTI
      * to the same file we're about to read. */
-    server.aof_state = REDIS_AOF_OFF;
+    server.aof_state = AOF_OFF;
 
     fakeClient = createFakeClient();
     startLoading(fp);
@@ -677,7 +677,7 @@ int loadAppendOnlyFile(char *filename) {
         /* Command lookup */
         cmd = lookupCommand(argv[0]->ptr);
         if (!cmd) {
-            serverLog(REDIS_WARNING,"Unknown command '%s' reading the append only file", (char*)argv[0]->ptr);
+            serverLog(LL_WARNING,"Unknown command '%s' reading the append only file", (char*)argv[0]->ptr);
             exit(1);
         }
 
@@ -687,7 +687,7 @@ int loadAppendOnlyFile(char *filename) {
         /* The fake client should not have a reply */
         serverAssert(fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0);
         /* The fake client should never get blocked */
-        serverAssert((fakeClient->flags & REDIS_BLOCKED) == 0);
+        serverAssert((fakeClient->flags & CLIENT_BLOCKED) == 0);
 
         /* Clean up. Command code may have changed argv/argc so we use the
          * argv/argc of the client instead of the local variables. */
@@ -697,7 +697,7 @@ int loadAppendOnlyFile(char *filename) {
 
     /* This point can only be reached when EOF is reached without errors.
      * If the client is in the middle of a MULTI/EXEC, log error and quit. */
-    if (fakeClient->flags & REDIS_MULTI) goto uxeof;
+    if (fakeClient->flags & CLIENT_MULTI) goto uxeof;
 
 loaded_ok: /* DB loaded, cleanup and return C_OK to the caller. */
     fclose(fp);
@@ -710,40 +710,40 @@ int loadAppendOnlyFile(char *filename) {
 
 readerr: /* Read error. If feof(fp) is true, fall through to unexpected EOF. */
     if (!feof(fp)) {
-        serverLog(REDIS_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
+        serverLog(LL_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
         exit(1);
     }
 
 uxeof: /* Unexpected AOF end of file. */
     if (server.aof_load_truncated) {
-        serverLog(REDIS_WARNING,"!!! Warning: short read while loading the AOF file !!!");
-        serverLog(REDIS_WARNING,"!!! Truncating the AOF at offset %llu !!!",
+        serverLog(LL_WARNING,"!!! Warning: short read while loading the AOF file !!!");
+        serverLog(LL_WARNING,"!!! Truncating the AOF at offset %llu !!!",
             (unsigned long long) valid_up_to);
         if (valid_up_to == -1 || truncate(filename,valid_up_to) == -1) {
             if (valid_up_to == -1) {
-                serverLog(REDIS_WARNING,"Last valid command offset is invalid");
+                serverLog(LL_WARNING,"Last valid command offset is invalid");
             } else {
-                serverLog(REDIS_WARNING,"Error truncating the AOF file: %s",
+                serverLog(LL_WARNING,"Error truncating the AOF file: %s",
                     strerror(errno));
             }
         } else {
             /* Make sure the AOF file descriptor points to the end of the
              * file after the truncate call. */
             if (server.aof_fd != -1 && lseek(server.aof_fd,0,SEEK_END) == -1) {
-                serverLog(REDIS_WARNING,"Can't seek the end of the AOF file: %s",
+                serverLog(LL_WARNING,"Can't seek the end of the AOF file: %s",
                     strerror(errno));
             } else {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "AOF loaded anyway because aof-load-truncated is enabled");
                 goto loaded_ok;
             }
         }
     }
-    serverLog(REDIS_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
+    serverLog(LL_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
     exit(1);
 
 fmterr: /* Format error. */
-    serverLog(REDIS_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
+    serverLog(LL_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
     exit(1);
 }
 
@@ -761,7 +761,7 @@ int rioWriteBulkObject(rio *r, robj *obj) {
     } else if (sdsEncodedObject(obj)) {
         return rioWriteBulkString(r,obj->ptr,sdslen(obj->ptr));
     } else {
-        redisPanic("Unknown string encoding");
+        serverPanic("Unknown string encoding");
     }
 }
 
@@ -777,8 +777,8 @@ int rewriteListObject(rio *r, robj *key, robj *o) {
 
         while (quicklistNext(li,&entry)) {
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"RPUSH",5) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
@@ -789,12 +789,12 @@ int rewriteListObject(rio *r, robj *key, robj *o) {
             } else {
                 if (rioWriteBulkLongLong(r,entry.longval) == 0) return 0;
             }
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
         quicklistReleaseIterator(li);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return 1;
 }
@@ -810,15 +810,15 @@ int rewriteSetObject(rio *r, robj *key, robj *o) {
 
         while(intsetGet(o->ptr,ii++,&llval)) {
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"SADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkLongLong(r,llval) == 0) return 0;
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else if (o->encoding == OBJ_ENCODING_HT) {
@@ -828,20 +828,20 @@ int rewriteSetObject(rio *r, robj *key, robj *o) {
         while((de = dictNext(di)) != NULL) {
             robj *eleobj = dictGetKey(de);
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"SADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkObject(r,eleobj) == 0) return 0;
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
         dictReleaseIterator(di);
     } else {
-        redisPanic("Unknown set encoding");
+        serverPanic("Unknown set encoding");
     }
     return 1;
 }
@@ -869,8 +869,8 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
             score = zzlGetScore(sptr);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"ZADD",4) == 0) return 0;
@@ -883,7 +883,7 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
                 if (rioWriteBulkLongLong(r,vll) == 0) return 0;
             }
             zzlNext(zl,&eptr,&sptr);
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
     } else if (o->encoding == OBJ_ENCODING_SKIPLIST) {
@@ -896,21 +896,21 @@ int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
             double *score = dictGetVal(de);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"ZADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkDouble(r,*score) == 0) return 0;
             if (rioWriteBulkObject(r,eleobj) == 0) return 0;
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
         dictReleaseIterator(di);
     } else {
-        redisPanic("Unknown sorted zset encoding");
+        serverPanic("Unknown sorted zset encoding");
     }
     return 1;
 }
@@ -941,7 +941,7 @@ static int rioWriteHashIteratorCursor(rio *r, hashTypeIterator *hi, int what) {
         return rioWriteBulkObject(r, value);
     }
 
-    redisPanic("Unknown hash encoding");
+    serverPanic("Unknown hash encoding");
     return 0;
 }
 
@@ -954,8 +954,8 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
     hi = hashTypeInitIterator(o);
     while (hashTypeNext(hi) != C_ERR) {
         if (count == 0) {
-            int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+            int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                AOF_REWRITE_ITEMS_PER_CMD : items;
 
             if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
             if (rioWriteBulkString(r,"HMSET",5) == 0) return 0;
@@ -964,7 +964,7 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
 
         if (rioWriteHashIteratorCursor(r, hi, OBJ_HASH_KEY) == 0) return 0;
         if (rioWriteHashIteratorCursor(r, hi, OBJ_HASH_VALUE) == 0) return 0;
-        if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+        if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
         items--;
     }
 
@@ -993,7 +993,7 @@ ssize_t aofReadDiffFromParent(void) {
  *
  * In order to minimize the number of commands needed in the rewritten
  * log Redis uses variadic commands when possible, such as RPUSH, SADD
- * and ZADD. However at max REDIS_AOF_REWRITE_ITEMS_PER_CMD items per time
+ * and ZADD. However at max AOF_REWRITE_ITEMS_PER_CMD items per time
  * are inserted using a single command. */
 int rewriteAppendOnlyFile(char *filename) {
     dictIterator *di = NULL;
@@ -1011,14 +1011,14 @@ int rewriteAppendOnlyFile(char *filename) {
     snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        serverLog(REDIS_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
+        serverLog(LL_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
         return C_ERR;
     }
 
     server.aof_child_diff = sdsempty();
     rioInitWithFile(&aof,fp);
     if (server.aof_rewrite_incremental_fsync)
-        rioSetAutoSync(&aof,REDIS_AOF_AUTOSYNC_BYTES);
+        rioSetAutoSync(&aof,AOF_AUTOSYNC_BYTES);
     for (j = 0; j < server.dbnum; j++) {
         char selectcmd[] = "*2\r\n$6\r\nSELECT\r\n";
         redisDb *db = server.db+j;
@@ -1066,7 +1066,7 @@ int rewriteAppendOnlyFile(char *filename) {
             } else if (o->type == OBJ_HASH) {
                 if (rewriteHashObject(&aof,&key,o) == 0) goto werr;
             } else {
-                redisPanic("Unknown object type");
+                serverPanic("Unknown object type");
             }
             /* Save the expire time */
             if (expiretime != -1) {
@@ -1118,13 +1118,13 @@ int rewriteAppendOnlyFile(char *filename) {
      * the child will eventually get terminated. */
     if (syncRead(server.aof_pipe_read_ack_from_parent,&byte,1,5000) != 1 ||
         byte != '!') goto werr;
-    serverLog(REDIS_NOTICE,"Parent agreed to stop sending diffs. Finalizing AOF...");
+    serverLog(LL_NOTICE,"Parent agreed to stop sending diffs. Finalizing AOF...");
 
     /* Read the final diff if any. */
     aofReadDiffFromParent();
 
     /* Write the received diff to the file. */
-    serverLog(REDIS_NOTICE,
+    serverLog(LL_NOTICE,
         "Concatenating %.2f MB of AOF diff received from parent.",
         (double) sdslen(server.aof_child_diff) / (1024*1024));
     if (rioWrite(&aof,server.aof_child_diff,sdslen(server.aof_child_diff)) == 0)
@@ -1138,15 +1138,15 @@ int rewriteAppendOnlyFile(char *filename) {
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        serverLog(REDIS_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
+        serverLog(LL_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
         return C_ERR;
     }
-    serverLog(REDIS_NOTICE,"SYNC append only file rewrite performed");
+    serverLog(LL_NOTICE,"SYNC append only file rewrite performed");
     return C_OK;
 
 werr:
-    serverLog(REDIS_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
+    serverLog(LL_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
     if (di) dictReleaseIterator(di);
@@ -1162,19 +1162,19 @@ int rewriteAppendOnlyFile(char *filename) {
  * parent sends a '!' as well to acknowledge. */
 void aofChildPipeReadable(aeEventLoop *el, int fd, void *privdata, int mask) {
     char byte;
-    REDIS_NOTUSED(el);
-    REDIS_NOTUSED(privdata);
-    REDIS_NOTUSED(mask);
+    UNUSED(el);
+    UNUSED(privdata);
+    UNUSED(mask);
 
     if (read(fd,&byte,1) == 1 && byte == '!') {
-        serverLog(REDIS_NOTICE,"AOF rewrite child asks to stop sending diffs.");
+        serverLog(LL_NOTICE,"AOF rewrite child asks to stop sending diffs.");
         server.aof_stop_sending_diff = 1;
         if (write(server.aof_pipe_write_ack_to_child,"!",1) != 1) {
             /* If we can't send the ack, inform the user, but don't try again
              * since in the other side the children will use a timeout if the
              * kernel can't buffer our write, or, the children was
              * terminated. */
-            serverLog(REDIS_WARNING,"Can't send ACK to AOF child: %s",
+            serverLog(LL_WARNING,"Can't send ACK to AOF child: %s",
                 strerror(errno));
         }
     }
@@ -1210,7 +1210,7 @@ int aofCreatePipes(void) {
     return C_OK;
 
 error:
-    serverLog(REDIS_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
+    serverLog(LL_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
         strerror(errno));
     for (j = 0; j < 6; j++) if(fds[j] != -1) close(fds[j]);
     return C_ERR;
@@ -1261,7 +1261,7 @@ int rewriteAppendOnlyFileBackground(void) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                serverLog(REDIS_NOTICE,
+                serverLog(LL_NOTICE,
                     "AOF rewrite: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
@@ -1275,12 +1275,12 @@ int rewriteAppendOnlyFileBackground(void) {
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));
             return C_ERR;
         }
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
         server.aof_rewrite_scheduled = 0;
         server.aof_rewrite_time_start = time(NULL);
@@ -1327,7 +1327,7 @@ void aofUpdateCurrentSize(void) {
 
     latencyStartMonitor(latency);
     if (redis_fstat(server.aof_fd,&sb) == -1) {
-        serverLog(REDIS_WARNING,"Unable to obtain the AOF file length. stat: %s",
+        serverLog(LL_WARNING,"Unable to obtain the AOF file length. stat: %s",
             strerror(errno));
     } else {
         server.aof_current_size = sb.st_size;
@@ -1345,7 +1345,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         long long now = ustime();
         mstime_t latency;
 
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Background AOF rewrite terminated with success");
 
         /* Flush the differences accumulated by the parent to the
@@ -1355,21 +1355,21 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             (int)server.aof_child_pid);
         newfd = open(tmpfile,O_WRONLY|O_APPEND);
         if (newfd == -1) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Unable to open the temporary AOF produced by the child: %s", strerror(errno));
             goto cleanup;
         }
 
         if (aofRewriteBufferWrite(newfd) == -1) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
             close(newfd);
             goto cleanup;
         }
         latencyEndMonitor(latency);
         latencyAddSampleIfNeeded("aof-rewrite-diff-write",latency);
 
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Residual parent diff successfully flushed to the rewritten AOF (%.2f MB)", (double) aofRewriteBufferSize() / (1024*1024));
 
         /* The only remaining thing to do is to rename the temporary file to
@@ -1415,7 +1415,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
          * it exists, because we reference it with "oldfd". */
         latencyStartMonitor(latency);
         if (rename(tmpfile,server.aof_filename) == -1) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Error trying to rename the temporary AOF file: %s", strerror(errno));
             close(newfd);
             if (oldfd != -1) close(oldfd);
@@ -1448,25 +1448,25 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
 
         server.aof_lastbgrewrite_status = C_OK;
 
-        serverLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
+        serverLog(LL_NOTICE, "Background AOF rewrite finished successfully");
         /* Change state from WAIT_REWRITE to ON if needed */
-        if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
-            server.aof_state = REDIS_AOF_ON;
+        if (server.aof_state == AOF_WAIT_REWRITE)
+            server.aof_state = AOF_ON;
 
         /* Asynchronously close the overwritten AOF. */
         if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);
 
-        serverLog(REDIS_VERBOSE,
+        serverLog(LL_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);
     } else if (!bysignal && exitcode != 0) {
         server.aof_lastbgrewrite_status = C_ERR;
 
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Background AOF rewrite terminated with error");
     } else {
         server.aof_lastbgrewrite_status = C_ERR;
 
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Background AOF rewrite terminated by signal %d", bysignal);
     }
 
@@ -1478,6 +1478,6 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     server.aof_rewrite_time_last = time(NULL)-server.aof_rewrite_time_start;
     server.aof_rewrite_time_start = -1;
     /* Schedule a new rewrite if we are waiting for it to switch the AOF ON. */
-    if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
+    if (server.aof_state == AOF_WAIT_REWRITE)
         server.aof_rewrite_scheduled = 1;
 }