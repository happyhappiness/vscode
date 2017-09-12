@@ -1270,6 +1270,7 @@ void migrateCommand(redisClient *c) {
         strerror(errno));
     fclose(fp);
     close(fd);
+    return;
 
 file_rd_err:
     redisLog(REDIS_WARNING,"Can't read from tmp file for MIGRATE: %s",
@@ -1278,6 +1279,7 @@ void migrateCommand(redisClient *c) {
         strerror(errno));
     fclose(fp);
     close(fd);
+    return;
 
 socket_wr_err:
     redisLog(REDIS_NOTICE,"Can't write to target node for MIGRATE: %s",
@@ -1286,6 +1288,7 @@ void migrateCommand(redisClient *c) {
         strerror(errno));
     fclose(fp);
     close(fd);
+    return;
 
 socket_rd_err:
     redisLog(REDIS_NOTICE,"Can't read from target node for MIGRATE: %s",
@@ -1294,6 +1297,81 @@ void migrateCommand(redisClient *c) {
         strerror(errno));
     fclose(fp);
     close(fd);
+    return;
+}
+
+/* DUMP keyname
+ * DUMP is actually not used by Redis Cluster but it is the obvious
+ * complement of RESTORE and can be useful for different applications. */
+void dumpCommand(redisClient *c) {
+    char buf[64];
+    FILE *fp;
+    robj *o, *dumpobj;
+    sds dump = NULL;
+    off_t payload_len;
+    unsigned int type;
+
+    /* Check if the key is here. */
+    if ((o = lookupKeyRead(c->db,c->argv[1])) == NULL) {
+        addReply(c,shared.nullbulk);
+        return;
+    }
+    
+    /* Create temp file */
+    snprintf(buf,sizeof(buf),"redis-dump-%d.tmp",getpid());
+    fp = fopen(buf,"w+");
+    if (!fp) {
+        redisLog(REDIS_WARNING,"Can't open tmp file for MIGRATE: %s",
+            strerror(errno));
+        addReplyErrorFormat(c,"DUMP failed, tmp file creation error: %s.",
+            strerror(errno));
+        return;
+    }
+    unlink(buf);
+
+    /* Dump the serailized object and read it back in memory.
+     * We prefix it with a one byte containing the type ID.
+     * This is the serialization format understood by RESTORE. */
+    if (rdbSaveObject(fp,o) == -1) goto file_wr_err;
+    payload_len = ftello(fp);
+    if (fseeko(fp,0,SEEK_SET) == -1) goto file_rd_err;
+    dump = sdsnewlen(NULL,payload_len+1);
+    if (payload_len && fread(dump+1,payload_len,1,fp) != 1) goto file_rd_err;
+    fclose(fp);
+    type = o->type;
+    if (type == REDIS_LIST && o->encoding == REDIS_ENCODING_ZIPLIST)
+        type = REDIS_LIST_ZIPLIST;
+    else if (type == REDIS_HASH && o->encoding == REDIS_ENCODING_ZIPMAP)
+        type = REDIS_HASH_ZIPMAP;
+    else if (type == REDIS_SET && o->encoding == REDIS_ENCODING_INTSET)
+        type = REDIS_SET_INTSET;
+    else
+        type = o->type;
+    dump[0] = type;
+
+    /* Transfer to the client */
+    dumpobj = createObject(REDIS_STRING,dump);
+    addReplyBulk(c,dumpobj);
+    decrRefCount(dumpobj);
+    return;
+
+file_wr_err:
+    redisLog(REDIS_WARNING,"Can't write on tmp file for DUMP: %s",
+        strerror(errno));
+    addReplyErrorFormat(c,"DUMP failed, tmp file write error: %s.",
+        strerror(errno));
+    sdsfree(dump);
+    fclose(fp);
+    return;
+
+file_rd_err:
+    redisLog(REDIS_WARNING,"Can't read from tmp file for DUMP: %s",
+        strerror(errno));
+    addReplyErrorFormat(c,"DUMP failed, tmp file read error: %s.",
+        strerror(errno));
+    sdsfree(dump);
+    fclose(fp);
+    return;
 }
 
 /* -----------------------------------------------------------------------------