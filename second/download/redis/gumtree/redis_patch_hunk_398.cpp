             if (len && fread(argsds,len,1,fp) == 0) {
                 sdsfree(argsds);
                 fakeClient->argc = j; /* Free up to j-1. */
                 freeFakeClientArgv(fakeClient);
                 goto readerr;
             }
-            argv[j] = createObject(REDIS_STRING,argsds);
+            argv[j] = createObject(OBJ_STRING,argsds);
             if (fread(buf,2,1,fp) == 0) {
                 fakeClient->argc = j+1; /* Free up to j. */
                 freeFakeClientArgv(fakeClient);
                 goto readerr; /* discard CRLF */
             }
         }
 
         /* Command lookup */
         cmd = lookupCommand(argv[0]->ptr);
         if (!cmd) {
-            redisLog(REDIS_WARNING,"Unknown command '%s' reading the append only file", (char*)argv[0]->ptr);
+            serverLog(LL_WARNING,"Unknown command '%s' reading the append only file", (char*)argv[0]->ptr);
             exit(1);
         }
 
         /* Run the command in the context of a fake client */
         cmd->proc(fakeClient);
 
         /* The fake client should not have a reply */
-        redisAssert(fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0);
+        serverAssert(fakeClient->bufpos == 0 && listLength(fakeClient->reply) == 0);
         /* The fake client should never get blocked */
-        redisAssert((fakeClient->flags & REDIS_BLOCKED) == 0);
+        serverAssert((fakeClient->flags & CLIENT_BLOCKED) == 0);
 
         /* Clean up. Command code may have changed argv/argc so we use the
          * argv/argc of the client instead of the local variables. */
         freeFakeClientArgv(fakeClient);
         if (server.aof_load_truncated) valid_up_to = ftello(fp);
     }
 
     /* This point can only be reached when EOF is reached without errors.
      * If the client is in the middle of a MULTI/EXEC, log error and quit. */
-    if (fakeClient->flags & REDIS_MULTI) goto uxeof;
+    if (fakeClient->flags & CLIENT_MULTI) goto uxeof;
 
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
-        redisLog(REDIS_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
+        if (fakeClient) freeFakeClient(fakeClient); /* avoid valgrind warning */
+        serverLog(LL_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
         exit(1);
     }
 
 uxeof: /* Unexpected AOF end of file. */
     if (server.aof_load_truncated) {
-        redisLog(REDIS_WARNING,"!!! Warning: short read while loading the AOF file !!!");
-        redisLog(REDIS_WARNING,"!!! Truncating the AOF at offset %llu !!!",
+        serverLog(LL_WARNING,"!!! Warning: short read while loading the AOF file !!!");
+        serverLog(LL_WARNING,"!!! Truncating the AOF at offset %llu !!!",
             (unsigned long long) valid_up_to);
         if (valid_up_to == -1 || truncate(filename,valid_up_to) == -1) {
             if (valid_up_to == -1) {
-                redisLog(REDIS_WARNING,"Last valid command offset is invalid");
+                serverLog(LL_WARNING,"Last valid command offset is invalid");
             } else {
-                redisLog(REDIS_WARNING,"Error truncating the AOF file: %s",
+                serverLog(LL_WARNING,"Error truncating the AOF file: %s",
                     strerror(errno));
             }
         } else {
             /* Make sure the AOF file descriptor points to the end of the
              * file after the truncate call. */
             if (server.aof_fd != -1 && lseek(server.aof_fd,0,SEEK_END) == -1) {
-                redisLog(REDIS_WARNING,"Can't seek the end of the AOF file: %s",
+                serverLog(LL_WARNING,"Can't seek the end of the AOF file: %s",
                     strerror(errno));
             } else {
-                redisLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "AOF loaded anyway because aof-load-truncated is enabled");
                 goto loaded_ok;
             }
         }
     }
-    redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
+    if (fakeClient) freeFakeClient(fakeClient); /* avoid valgrind warning */
+    serverLog(LL_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
     exit(1);
 
 fmterr: /* Format error. */
-    redisLog(REDIS_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
+    if (fakeClient) freeFakeClient(fakeClient); /* avoid valgrind warning */
+    serverLog(LL_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
     exit(1);
 }
 
 /* ----------------------------------------------------------------------------
  * AOF rewrite
  * ------------------------------------------------------------------------- */
 
 /* Delegate writing an object to writing a bulk string or bulk long long.
- * This is not placed in rio.c since that adds the redis.h dependency. */
+ * This is not placed in rio.c since that adds the server.h dependency. */
 int rioWriteBulkObject(rio *r, robj *obj) {
     /* Avoid using getDecodedObject to help copy-on-write (we are often
      * in a child process when this function is called). */
-    if (obj->encoding == REDIS_ENCODING_INT) {
+    if (obj->encoding == OBJ_ENCODING_INT) {
         return rioWriteBulkLongLong(r,(long)obj->ptr);
     } else if (sdsEncodedObject(obj)) {
         return rioWriteBulkString(r,obj->ptr,sdslen(obj->ptr));
     } else {
-        redisPanic("Unknown string encoding");
+        serverPanic("Unknown string encoding");
     }
 }
 
 /* Emit the commands needed to rebuild a list object.
  * The function returns 0 on error, 1 on success. */
 int rewriteListObject(rio *r, robj *key, robj *o) {
     long long count = 0, items = listTypeLength(o);
 
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-        unsigned char *zl = o->ptr;
-        unsigned char *p = ziplistIndex(zl,0);
-        unsigned char *vstr;
-        unsigned int vlen;
-        long long vlong;
+    if (o->encoding == OBJ_ENCODING_QUICKLIST) {
+        quicklist *list = o->ptr;
+        quicklistIter *li = quicklistGetIterator(list, AL_START_HEAD);
+        quicklistEntry entry;
 
-        while(ziplistGet(p,&vstr,&vlen,&vlong)) {
+        while (quicklistNext(li,&entry)) {
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
-
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
                 if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
                 if (rioWriteBulkString(r,"RPUSH",5) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
-            if (vstr) {
-                if (rioWriteBulkString(r,(char*)vstr,vlen) == 0) return 0;
-            } else {
-                if (rioWriteBulkLongLong(r,vlong) == 0) return 0;
-            }
-            p = ziplistNext(zl,p);
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
-            items--;
-        }
-    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
-        list *list = o->ptr;
-        listNode *ln;
-        listIter li;
-
-        listRewind(list,&li);
-        while((ln = listNext(&li))) {
-            robj *eleobj = listNodeValue(ln);
-
-            if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
 
-                if (rioWriteBulkCount(r,'*',2+cmd_items) == 0) return 0;
-                if (rioWriteBulkString(r,"RPUSH",5) == 0) return 0;
-                if (rioWriteBulkObject(r,key) == 0) return 0;
+            if (entry.value) {
+                if (rioWriteBulkString(r,(char*)entry.value,entry.sz) == 0) return 0;
+            } else {
+                if (rioWriteBulkLongLong(r,entry.longval) == 0) return 0;
             }
-            if (rioWriteBulkObject(r,eleobj) == 0) return 0;
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
+        quicklistReleaseIterator(li);
     } else {
-        redisPanic("Unknown list encoding");
+        serverPanic("Unknown list encoding");
     }
     return 1;
 }
 
 /* Emit the commands needed to rebuild a set object.
  * The function returns 0 on error, 1 on success. */
 int rewriteSetObject(rio *r, robj *key, robj *o) {
     long long count = 0, items = setTypeSize(o);
 
-    if (o->encoding == REDIS_ENCODING_INTSET) {
+    if (o->encoding == OBJ_ENCODING_INTSET) {
         int ii = 0;
         int64_t llval;
 
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
-    } else if (o->encoding == REDIS_ENCODING_HT) {
+    } else if (o->encoding == OBJ_ENCODING_HT) {
         dictIterator *di = dictGetIterator(o->ptr);
         dictEntry *de;
 
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
 
 /* Emit the commands needed to rebuild a sorted set object.
  * The function returns 0 on error, 1 on success. */
 int rewriteSortedSetObject(rio *r, robj *key, robj *o) {
     long long count = 0, items = zsetLength(o);
 
-    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (o->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *zl = o->ptr;
         unsigned char *eptr, *sptr;
         unsigned char *vstr;
         unsigned int vlen;
         long long vll;
         double score;
 
         eptr = ziplistIndex(zl,0);
-        redisAssert(eptr != NULL);
+        serverAssert(eptr != NULL);
         sptr = ziplistNext(zl,eptr);
-        redisAssert(sptr != NULL);
+        serverAssert(sptr != NULL);
 
         while (eptr != NULL) {
-            redisAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
+            serverAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
             score = zzlGetScore(sptr);
 
             if (count == 0) {
-                int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                    REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+                int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                    AOF_REWRITE_ITEMS_PER_CMD : items;
 
                 if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
                 if (rioWriteBulkString(r,"ZADD",4) == 0) return 0;
                 if (rioWriteBulkObject(r,key) == 0) return 0;
             }
             if (rioWriteBulkDouble(r,score) == 0) return 0;
             if (vstr != NULL) {
                 if (rioWriteBulkString(r,(char*)vstr,vlen) == 0) return 0;
             } else {
                 if (rioWriteBulkLongLong(r,vll) == 0) return 0;
             }
             zzlNext(zl,&eptr,&sptr);
-            if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+            if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
             items--;
         }
-    } else if (o->encoding == REDIS_ENCODING_SKIPLIST) {
+    } else if (o->encoding == OBJ_ENCODING_SKIPLIST) {
         zset *zs = o->ptr;
         dictIterator *di = dictGetIterator(zs->dict);
         dictEntry *de;
 
         while((de = dictNext(di)) != NULL) {
             robj *eleobj = dictGetKey(de);
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
 
 /* Write either the key or the value of the currently selected item of a hash.
  * The 'hi' argument passes a valid Redis hash iterator.
  * The 'what' filed specifies if to write a key or a value and can be
- * either REDIS_HASH_KEY or REDIS_HASH_VALUE.
+ * either OBJ_HASH_KEY or OBJ_HASH_VALUE.
  *
  * The function returns 0 on error, non-zero on success. */
 static int rioWriteHashIteratorCursor(rio *r, hashTypeIterator *hi, int what) {
-    if (hi->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (hi->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *vstr = NULL;
         unsigned int vlen = UINT_MAX;
         long long vll = LLONG_MAX;
 
         hashTypeCurrentFromZiplist(hi, what, &vstr, &vlen, &vll);
         if (vstr) {
             return rioWriteBulkString(r, (char*)vstr, vlen);
         } else {
             return rioWriteBulkLongLong(r, vll);
         }
 
-    } else if (hi->encoding == REDIS_ENCODING_HT) {
+    } else if (hi->encoding == OBJ_ENCODING_HT) {
         robj *value;
 
         hashTypeCurrentFromHashTable(hi, what, &value);
         return rioWriteBulkObject(r, value);
     }
 
-    redisPanic("Unknown hash encoding");
+    serverPanic("Unknown hash encoding");
     return 0;
 }
 
 /* Emit the commands needed to rebuild a hash object.
  * The function returns 0 on error, 1 on success. */
 int rewriteHashObject(rio *r, robj *key, robj *o) {
     hashTypeIterator *hi;
     long long count = 0, items = hashTypeLength(o);
 
     hi = hashTypeInitIterator(o);
-    while (hashTypeNext(hi) != REDIS_ERR) {
+    while (hashTypeNext(hi) != C_ERR) {
         if (count == 0) {
-            int cmd_items = (items > REDIS_AOF_REWRITE_ITEMS_PER_CMD) ?
-                REDIS_AOF_REWRITE_ITEMS_PER_CMD : items;
+            int cmd_items = (items > AOF_REWRITE_ITEMS_PER_CMD) ?
+                AOF_REWRITE_ITEMS_PER_CMD : items;
 
             if (rioWriteBulkCount(r,'*',2+cmd_items*2) == 0) return 0;
             if (rioWriteBulkString(r,"HMSET",5) == 0) return 0;
             if (rioWriteBulkObject(r,key) == 0) return 0;
         }
 
-        if (rioWriteHashIteratorCursor(r, hi, REDIS_HASH_KEY) == 0) return 0;
-        if (rioWriteHashIteratorCursor(r, hi, REDIS_HASH_VALUE) == 0) return 0;
-        if (++count == REDIS_AOF_REWRITE_ITEMS_PER_CMD) count = 0;
+        if (rioWriteHashIteratorCursor(r, hi, OBJ_HASH_KEY) == 0) return 0;
+        if (rioWriteHashIteratorCursor(r, hi, OBJ_HASH_VALUE) == 0) return 0;
+        if (++count == AOF_REWRITE_ITEMS_PER_CMD) count = 0;
         items--;
     }
 
     hashTypeReleaseIterator(hi);
 
     return 1;
