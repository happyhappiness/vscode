@@ -1383,11 +1383,10 @@ void clusterCommand(redisClient *c) {
 
 /* RESTORE key ttl serialized-value */
 void restoreCommand(redisClient *c) {
-    FILE *fp;
-    char buf[64];
-    robj *o;
-    unsigned char *data;
     long ttl;
+    rio payload;
+    int type;
+    robj *obj;
 
     /* Make sure this key does not already exist here... */
     if (lookupKeyWrite(c->db,c->argv[1]) != NULL) {
@@ -1403,44 +1402,16 @@ void restoreCommand(redisClient *c) {
         return;
     }
 
-    /* rdbLoadObject() only works against file descriptors so we need to
-     * dump the serialized object into a file and reload. */
-    snprintf(buf,sizeof(buf),"redis-restore-%d.tmp",getpid());
-    fp = fopen(buf,"w+");
-    if (!fp) {
-        redisLog(REDIS_WARNING,"Can't open tmp file for RESTORE: %s",
-            strerror(errno));
-        addReplyErrorFormat(c,"RESTORE failed, tmp file creation error: %s",
-            strerror(errno));
-        return;
-    }
-    unlink(buf);
-
-    /* Write the actual data and rewind the file */
-    data = (unsigned char*) c->argv[3]->ptr;
-    if (fwrite(data+1,sdslen((sds)data)-1,1,fp) != 1) {
-        redisLog(REDIS_WARNING,"Can't write against tmp file for RESTORE: %s",
-            strerror(errno));
-        addReplyError(c,"RESTORE failed, tmp file I/O error.");
-        fclose(fp);
-        return;
-    }
-    rewind(fp);
-
-    /* Finally create the object from the serialized dump and
-     * store it at the specified key. */
-    if ((data[0] > 4 && data[0] < 9) ||
-         data[0] > 11 ||
-        (o = rdbLoadObject(data[0],fp)) == NULL)
+    payload = rioInitWithBuffer(c->argv[3]->ptr);
+    if (((type = rdbLoadObjectType(&payload)) == -1) ||
+        ((obj = rdbLoadObject(type,&payload)) == NULL))
     {
-        addReplyError(c,"Bad data format.");
-        fclose(fp);
+        addReplyError(c,"Bad data format");
         return;
     }
-    fclose(fp);
 
     /* Create the key and set the TTL if any */
-    dbAdd(c->db,c->argv[1],o);
+    dbAdd(c->db,c->argv[1],obj);
     if (ttl) setExpire(c->db,c->argv[1],time(NULL)+ttl);
     addReply(c,shared.ok);
 }
@@ -1450,12 +1421,9 @@ void migrateCommand(redisClient *c) {
     int fd;
     long timeout;
     long dbid;
-    char buf[64];
-    FILE *fp;
     time_t ttl;
     robj *o;
-    unsigned char type;
-    off_t payload_len;
+    rio cmd, payload;
 
     /* Sanity check */
     if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != REDIS_OK)
@@ -1485,54 +1453,41 @@ void migrateCommand(redisClient *c) {
         return;
     }
 
-    /* Create temp file */
-    snprintf(buf,sizeof(buf),"redis-migrate-%d.tmp",getpid());
-    fp = fopen(buf,"w+");
-    if (!fp) {
-        redisLog(REDIS_WARNING,"Can't open tmp file for MIGRATE: %s",
-            strerror(errno));
-        addReplyErrorFormat(c,"MIGRATE failed, tmp file creation error: %s.",
-            strerror(errno));
-        return;
-    }
-    unlink(buf);
-
-    /* Build the SELECT + RESTORE query writing it in our temp file. */
-    if (fwriteBulkCount(fp,'*',2) == 0) goto file_wr_err;
-    if (fwriteBulkString(fp,"SELECT",6) == 0) goto file_wr_err;
-    if (fwriteBulkLongLong(fp,dbid) == 0) goto file_wr_err;
+    cmd = rioInitWithBuffer(sdsempty());
+    redisAssert(rioWriteBulkCount(&cmd,'*',2));
+    redisAssert(rioWriteBulkString(&cmd,"SELECT",6));
+    redisAssert(rioWriteBulkLongLong(&cmd,dbid));
 
     ttl = getExpire(c->db,c->argv[3]);
-    type = o->type;
-    if (fwriteBulkCount(fp,'*',4) == 0) goto file_wr_err;
-    if (fwriteBulkString(fp,"RESTORE",7) == 0) goto file_wr_err;
-    if (fwriteBulkObject(fp,c->argv[3]) == 0) goto file_wr_err;
-    if (fwriteBulkLongLong(fp, (ttl == -1) ? 0 : ttl) == 0) goto file_wr_err;
+    redisAssert(rioWriteBulkCount(&cmd,'*',4));
+    redisAssert(rioWriteBulkString(&cmd,"RESTORE",7));
+    redisAssert(c->argv[3]->encoding == REDIS_ENCODING_RAW);
+    redisAssert(rioWriteBulkString(&cmd,c->argv[3]->ptr,sdslen(c->argv[3]->ptr)));
+    redisAssert(rioWriteBulkLongLong(&cmd,(ttl == -1) ? 0 : ttl));
 
     /* Finally the last argument that is the serailized object payload
-     * in the form: <type><rdb-serailized-object>. */
-    payload_len = rdbSavedObjectLen(o);
-    if (fwriteBulkCount(fp,'$',payload_len+1) == 0) goto file_wr_err;
-    if (fwrite(&type,1,1,fp) == 0) goto file_wr_err;
-    if (rdbSaveObject(fp,o) == -1) goto file_wr_err;
-    if (fwrite("\r\n",2,1,fp) == 0) goto file_wr_err;
-
-    /* Tranfer the query to the other node */
-    rewind(fp);
+     * in the form: <type><rdb-serialized-object>. */
+    payload = rioInitWithBuffer(sdsempty());
+    redisAssert(rdbSaveObjectType(&payload,o));
+    redisAssert(rdbSaveObject(&payload,o) != -1);
+    redisAssert(rioWriteBulkString(&cmd,payload.io.buffer.ptr,sdslen(payload.io.buffer.ptr)));
+    sdsfree(payload.io.buffer.ptr);
+
+    /* Tranfer the query to the other node in 64K chunks. */
     {
-        char buf[4096];
-        size_t nread;
-
-        while ((nread = fread(buf,1,sizeof(buf),fp)) != 0) {
-            int nwritten;
-
-            nwritten = syncWrite(fd,buf,nread,timeout);
-            if (nwritten != (signed)nread) goto socket_wr_err;
+        sds buf = cmd.io.buffer.ptr;
+        size_t pos = 0, towrite;
+        int nwritten = 0;
+
+        while ((towrite = sdslen(buf)-pos) > 0) {
+            towrite = (towrite > (64*1024) ? (64*1024) : towrite);
+            nwritten = syncWrite(fd,buf+nwritten,towrite,timeout);
+            if (nwritten != (signed)towrite) goto socket_wr_err;
+            pos += nwritten;
         }
-        if (ferror(fp)) goto file_rd_err;
     }
 
-    /* Read back the reply */
+    /* Read back the reply. */
     {
         char buf1[1024];
         char buf2[1024];
@@ -1541,7 +1496,7 @@ void migrateCommand(redisClient *c) {
         if (syncReadLine(fd, buf1, sizeof(buf1), timeout) <= 0)
             goto socket_rd_err;
         if (syncReadLine(fd, buf2, sizeof(buf2), timeout) <= 0)
-                goto socket_rd_err;
+            goto socket_rd_err;
         if (buf1[0] == '-' || buf2[0] == '-') {
             addReplyErrorFormat(c,"Target instance replied with error: %s",
                 (buf1[0] == '-') ? buf1+1 : buf2+1);
@@ -1550,25 +1505,8 @@ void migrateCommand(redisClient *c) {
             addReply(c,shared.ok);
         }
     }
-    fclose(fp);
-    close(fd);
-    return;
 
-file_wr_err:
-    redisLog(REDIS_WARNING,"Can't write on tmp file for MIGRATE: %s",
-        strerror(errno));
-    addReplyErrorFormat(c,"MIGRATE failed, tmp file write error: %s.",
-        strerror(errno));
-    fclose(fp);
-    close(fd);
-    return;
-
-file_rd_err:
-    redisLog(REDIS_WARNING,"Can't read from tmp file for MIGRATE: %s",
-        strerror(errno));
-    addReplyErrorFormat(c,"MIGRATE failed, tmp file read error: %s.",
-        strerror(errno));
-    fclose(fp);
+    sdsfree(cmd.io.buffer.ptr);
     close(fd);
     return;
 
@@ -1577,7 +1515,7 @@ void migrateCommand(redisClient *c) {
         strerror(errno));
     addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
         strerror(errno));
-    fclose(fp);
+    sdsfree(cmd.io.buffer.ptr);
     close(fd);
     return;
 
@@ -1586,7 +1524,7 @@ void migrateCommand(redisClient *c) {
         strerror(errno));
     addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
         strerror(errno));
-    fclose(fp);
+    sdsfree(cmd.io.buffer.ptr);
     close(fd);
     return;
 }
@@ -1595,74 +1533,26 @@ void migrateCommand(redisClient *c) {
  * DUMP is actually not used by Redis Cluster but it is the obvious
  * complement of RESTORE and can be useful for different applications. */
 void dumpCommand(redisClient *c) {
-    char buf[64];
-    FILE *fp;
     robj *o, *dumpobj;
-    sds dump = NULL;
-    off_t payload_len;
-    unsigned int type;
+    rio payload;
 
     /* Check if the key is here. */
     if ((o = lookupKeyRead(c->db,c->argv[1])) == NULL) {
         addReply(c,shared.nullbulk);
         return;
     }
-    
-    /* Create temp file */
-    snprintf(buf,sizeof(buf),"redis-dump-%d.tmp",getpid());
-    fp = fopen(buf,"w+");
-    if (!fp) {
-        redisLog(REDIS_WARNING,"Can't open tmp file for MIGRATE: %s",
-            strerror(errno));
-        addReplyErrorFormat(c,"DUMP failed, tmp file creation error: %s.",
-            strerror(errno));
-        return;
-    }
-    unlink(buf);
-
-    /* Dump the serailized object and read it back in memory.
-     * We prefix it with a one byte containing the type ID.
-     * This is the serialization format understood by RESTORE. */
-    if (rdbSaveObject(fp,o) == -1) goto file_wr_err;
-    payload_len = ftello(fp);
-    if (fseeko(fp,0,SEEK_SET) == -1) goto file_rd_err;
-    dump = sdsnewlen(NULL,payload_len+1);
-    if (payload_len && fread(dump+1,payload_len,1,fp) != 1) goto file_rd_err;
-    fclose(fp);
-    type = o->type;
-    if (type == REDIS_LIST && o->encoding == REDIS_ENCODING_ZIPLIST)
-        type = REDIS_LIST_ZIPLIST;
-    else if (type == REDIS_HASH && o->encoding == REDIS_ENCODING_ZIPMAP)
-        type = REDIS_HASH_ZIPMAP;
-    else if (type == REDIS_SET && o->encoding == REDIS_ENCODING_INTSET)
-        type = REDIS_SET_INTSET;
-    else
-        type = o->type;
-    dump[0] = type;
+
+    /* Serialize the object in a RDB-like format. It consist of an object type
+     * byte followed by the serialized object. This is understood by RESTORE. */
+    payload = rioInitWithBuffer(sdsempty());
+    redisAssert(rdbSaveObjectType(&payload,o));
+    redisAssert(rdbSaveObject(&payload,o));
 
     /* Transfer to the client */
-    dumpobj = createObject(REDIS_STRING,dump);
+    dumpobj = createObject(REDIS_STRING,payload.io.buffer.ptr);
     addReplyBulk(c,dumpobj);
     decrRefCount(dumpobj);
     return;
-
-file_wr_err:
-    redisLog(REDIS_WARNING,"Can't write on tmp file for DUMP: %s",
-        strerror(errno));
-    addReplyErrorFormat(c,"DUMP failed, tmp file write error: %s.",
-        strerror(errno));
-    sdsfree(dump);
-    fclose(fp);
-    return;
-
-file_rd_err:
-    redisLog(REDIS_WARNING,"Can't read from tmp file for DUMP: %s",
-        strerror(errno));
-    addReplyErrorFormat(c,"DUMP failed, tmp file read error: %s.",
-        strerror(errno));
-    sdsfree(dump);
-    fclose(fp);
-    return;
 }
 
 /* -----------------------------------------------------------------------------