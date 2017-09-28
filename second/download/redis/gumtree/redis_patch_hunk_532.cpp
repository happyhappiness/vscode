         }
         dictReleaseIterator(di);
     }
     di = NULL; /* So that we don't release it again on error. */
 
     /* EOF opcode */
-    if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
+    if (rdbSaveType(rdb,RDB_OPCODE_EOF) == -1) goto werr;
 
     /* CRC64 checksum. It will be zero if checksum computation is disabled, the
      * loading code skips the check in this case. */
     cksum = rdb->cksum;
     memrev64ifbe(&cksum);
     if (rioWrite(rdb,&cksum,8) == 0) goto werr;
-    return REDIS_OK;
+    return C_OK;
 
 werr:
     if (error) *error = errno;
     if (di) dictReleaseIterator(di);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* This is just a wrapper to rdbSaveRio() that additionally adds a prefix
  * and a suffix to the generated RDB dump. The prefix is:
  *
  * $EOF:<40 bytes unguessable hex string>\r\n
  *
  * While the suffix is the 40 bytes hex string we announced in the prefix.
  * This way processes receiving the payload can understand when it ends
  * without doing any processing of the content. */
 int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
-    char eofmark[REDIS_EOF_MARK_SIZE];
+    char eofmark[RDB_EOF_MARK_SIZE];
 
-    getRandomHexChars(eofmark,REDIS_EOF_MARK_SIZE);
+    getRandomHexChars(eofmark,RDB_EOF_MARK_SIZE);
     if (error) *error = 0;
     if (rioWrite(rdb,"$EOF:",5) == 0) goto werr;
-    if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
+    if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     if (rioWrite(rdb,"\r\n",2) == 0) goto werr;
-    if (rdbSaveRio(rdb,error) == REDIS_ERR) goto werr;
-    if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
-    return REDIS_OK;
+    if (rdbSaveRio(rdb,error) == C_ERR) goto werr;
+    if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
+    return C_OK;
 
 werr: /* Write error. */
     /* Set 'error' only if not already set by rdbSaveRio() call. */
     if (error && *error == 0) *error = errno;
-    return REDIS_ERR;
+    return C_ERR;
 }
 
-/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success. */
+/* Save the DB on disk. Return C_ERR on error, C_OK on success. */
 int rdbSave(char *filename) {
     char tmpfile[256];
+    char cwd[MAXPATHLEN]; /* Current working dir path for error messages. */
     FILE *fp;
     rio rdb;
-    int error;
+    int error = 0;
 
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+        char *cwdp = getcwd(cwd,MAXPATHLEN);
+        serverLog(LL_WARNING,
+            "Failed opening the RDB file %s (in server root dir %s) "
+            "for saving: %s",
+            filename,
+            cwdp ? cwdp : "unknown",
             strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     rioInitWithFile(&rdb,fp);
-    if (rdbSaveRio(&rdb,&error) == REDIS_ERR) {
+    if (rdbSaveRio(&rdb,&error) == C_ERR) {
         errno = error;
         goto werr;
     }
 
     /* Make sure data will not remain on the OS's output buffers */
     if (fflush(fp) == EOF) goto werr;
     if (fsync(fileno(fp)) == -1) goto werr;
     if (fclose(fp) == EOF) goto werr;
 
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
+        char *cwdp = getcwd(cwd,MAXPATHLEN);
+        serverLog(LL_WARNING,
+            "Error moving temp DB file %s on the final "
+            "destination %s (in server root dir %s): %s",
+            tmpfile,
+            filename,
+            cwdp ? cwdp : "unknown",
+            strerror(errno));
         unlink(tmpfile);
-        return REDIS_ERR;
+        return C_ERR;
     }
-    redisLog(REDIS_NOTICE,"DB saved on disk");
+
+    serverLog(LL_NOTICE,"DB saved on disk");
     server.dirty = 0;
     server.lastsave = time(NULL);
-    server.lastbgsave_status = REDIS_OK;
-    return REDIS_OK;
+    server.lastbgsave_status = C_OK;
+    return C_OK;
 
 werr:
-    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
+    serverLog(LL_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 int rdbSaveBackground(char *filename) {
     pid_t childpid;
     long long start;
 
-    if (server.rdb_child_pid != -1) return REDIS_ERR;
+    if (server.rdb_child_pid != -1) return C_ERR;
 
     server.dirty_before_bgsave = server.dirty;
     server.lastbgsave_try = time(NULL);
 
     start = ustime();
     if ((childpid = fork()) == 0) {
         int retval;
 
         /* Child */
         closeListeningSockets(0);
         redisSetProcTitle("redis-rdb-bgsave");
         retval = rdbSave(filename);
-        if (retval == REDIS_OK) {
+        if (retval == C_OK) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                redisLog(REDIS_NOTICE,
+                serverLog(LL_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
         }
-        exitFromChild((retval == REDIS_OK) ? 0 : 1);
+        exitFromChild((retval == C_OK) ? 0 : 1);
     } else {
         /* Parent */
         server.stat_fork_time = ustime()-start;
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            server.lastbgsave_status = REDIS_ERR;
-            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
+            server.lastbgsave_status = C_ERR;
+            serverLog(LL_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
-            return REDIS_ERR;
+            return C_ERR;
         }
-        redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
+        serverLog(LL_NOTICE,"Background saving started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
-        server.rdb_child_type = REDIS_RDB_CHILD_TYPE_DISK;
+        server.rdb_child_type = RDB_CHILD_TYPE_DISK;
         updateDictResizePolicy();
-        return REDIS_OK;
+        return C_OK;
     }
-    return REDIS_OK; /* unreached */
+    return C_OK; /* unreached */
 }
 
 void rdbRemoveTempFile(pid_t childpid) {
     char tmpfile[256];
 
     snprintf(tmpfile,sizeof(tmpfile),"temp-%d.rdb", (int) childpid);
     unlink(tmpfile);
 }
 
 /* Load a Redis object of the specified type from the specified file.
  * On success a newly allocated object is returned, otherwise NULL. */
 robj *rdbLoadObject(int rdbtype, rio *rdb) {
-    robj *o, *ele, *dec;
+    robj *o = NULL, *ele, *dec;
     size_t len;
     unsigned int i;
 
-    if (rdbtype == REDIS_RDB_TYPE_STRING) {
+    if (rdbtype == RDB_TYPE_STRING) {
         /* Read string value */
         if ((o = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
         o = tryObjectEncoding(o);
-    } else if (rdbtype == REDIS_RDB_TYPE_LIST) {
+    } else if (rdbtype == RDB_TYPE_LIST) {
         /* Read list value */
-        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
 
-        /* Use a real list when there are too many entries */
-        if (len > server.list_max_ziplist_entries) {
-            o = createListObject();
-        } else {
-            o = createZiplistObject();
-        }
+        o = createQuicklistObject();
+        quicklistSetOptions(o->ptr, server.list_max_ziplist_size,
+                            server.list_compress_depth);
 
         /* Load every single element of the list */
         while(len--) {
             if ((ele = rdbLoadEncodedStringObject(rdb)) == NULL) return NULL;
-
-            /* If we are using a ziplist and the value is too big, convert
-             * the object to a real list. */
-            if (o->encoding == REDIS_ENCODING_ZIPLIST &&
-                sdsEncodedObject(ele) &&
-                sdslen(ele->ptr) > server.list_max_ziplist_value)
-                    listTypeConvert(o,REDIS_ENCODING_LINKEDLIST);
-
-            if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-                dec = getDecodedObject(ele);
-                o->ptr = ziplistPush(o->ptr,dec->ptr,sdslen(dec->ptr),REDIS_TAIL);
-                decrRefCount(dec);
-                decrRefCount(ele);
-            } else {
-                ele = tryObjectEncoding(ele);
-                listAddNodeTail(o->ptr,ele);
-            }
+            dec = getDecodedObject(ele);
+            size_t len = sdslen(dec->ptr);
+            quicklistPushTail(o->ptr, dec->ptr, len);
+            decrRefCount(dec);
+            decrRefCount(ele);
         }
-    } else if (rdbtype == REDIS_RDB_TYPE_SET) {
+    } else if (rdbtype == RDB_TYPE_SET) {
         /* Read list/set value */
-        if ((len = rdbLoadLen(rdb,NULL)) == REDIS_RDB_LENERR) return NULL;
+        if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
 
         /* Use a regular set when there are too many entries. */
         if (len > server.set_max_intset_entries) {
             o = createSetObject();
             /* It's faster to expand the dict to the right size asap in order
              * to avoid rehashing */
