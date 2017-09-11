@@ -614,7 +614,8 @@ int rdbSave(char *filename) {
     }
 
     rioInitWithFile(&rdb,fp);
-    rdb.update_cksum = rioGenericUpdateChecksum;
+    if (server.rdb_checksum)
+        rdb.update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
     if (rdbWriteRaw(&rdb,magic,9) == -1) goto werr;
 
@@ -649,7 +650,8 @@ int rdbSave(char *filename) {
     /* EOF opcode */
     if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
 
-    /* CRC64 checksum */
+    /* CRC64 checksum. It will be zero if checksum computation is disabled, the
+     * loading code skips the check in this case. */
     cksum = rdb.cksum;
     memrev64ifbe(&cksum);
     rioWrite(&rdb,&cksum,8);
@@ -1026,7 +1028,8 @@ int rdbLoad(char *filename) {
         return REDIS_ERR;
     }
     rioInitWithFile(&rdb,fp);
-    rdb.update_cksum = rioGenericUpdateChecksum;
+    if (server.rdb_checksum)
+        rdb.update_cksum = rioGenericUpdateChecksum;
     if (rioRead(&rdb,buf,9) == 0) goto eoferr;
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
@@ -1108,12 +1111,14 @@ int rdbLoad(char *filename) {
         decrRefCount(key);
     }
     /* Verify the checksum if RDB version is >= 5 */
-    if (rdbver >= 5) {
+    if (rdbver >= 5 && server.rdb_checksum) {
         uint64_t cksum, expected = rdb.cksum;
 
         if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
         memrev64ifbe(&cksum);
-        if (cksum != expected) {
+        if (cksum == 0) {
+            redisLog(REDIS_WARNING,"RDB file was saved with checksum disabled: no check performed.");
+        } else if (cksum != expected) {
             redisLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
             exit(1);
         }