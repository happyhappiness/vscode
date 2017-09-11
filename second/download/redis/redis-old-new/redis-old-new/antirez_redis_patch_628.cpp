@@ -682,6 +682,34 @@ int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
     return 1;
 }
 
+/* Save an AUX field. */
+int rdbSaveAuxField(rio *rdb, void *key, size_t keylen, void *val, size_t vallen) {
+    if (rdbSaveType(rdb,REDIS_RDB_OPCODE_AUX) == -1) return -1;
+    if (rdbSaveRawString(rdb,key,keylen) == -1) return -1;
+    if (rdbSaveRawString(rdb,val,vallen) == -1) return -1;
+    return 1;
+}
+
+/* Wrapper for rdbSaveAuxField() used when key/val length can be obtained
+ * with strlen(). */
+int rdbSaveAuxFieldStrStr(rio *rdb, char *key, char *val) {
+    return rdbSaveAuxField(rdb,key,strlen(key),val,strlen(val));
+}
+
+/* Wrapper for strlen(key) + integer type (up to long long range). */
+int rdbSaveAuxFieldStrInt(rio *rdb, char *key, long long val) {
+    char buf[REDIS_LONGSTR_SIZE];
+    int vlen = ll2string(buf,sizeof(buf),val);
+    return rdbSaveAuxField(rdb,key,strlen(key),buf,vlen);
+}
+
+/* Save a few default AUX fields with information about the RDB generated. */
+int rdbSaveInfoAuxFields(rio *rdb) {
+    if (rdbSaveAuxFieldStrStr(rdb,"redis-ver",REDIS_VERSION) == -1) return -1;
+    if (rdbSaveAuxFieldStrInt(rdb,"ctime",time(NULL)) == -1) return -1;
+    return 1;
+}
+
 /* Produces a dump of the database in RDB format sending it to the specified
  * Redis I/O channel. On success REDIS_OK is returned, otherwise REDIS_ERR
  * is returned and part of the output, or all the output, can be
@@ -702,6 +730,7 @@ int rdbSaveRio(rio *rdb, int *error) {
         rdb->update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
     if (rdbWriteRaw(rdb,magic,9) == -1) goto werr;
+    if (rdbSaveInfoAuxFields(rdb) == -1) goto werr;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
@@ -1268,6 +1297,31 @@ int rdbLoad(char *filename) {
             dictExpand(db->dict,db_size);
             dictExpand(db->expires,expires_size);
             continue; /* Read type again. */
+        } else if (type == REDIS_RDB_OPCODE_AUX) {
+            /* AUX: generic string-string fields. Use to add state to RDB
+             * which is backward compatible. Implementations of RDB loading
+             * are requierd to skip AUX fields they don't understand.
+             *
+             * An AUX field is composed of two strings: key and value. */
+            robj *auxkey, *auxval;
+            if ((auxkey = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
+            if ((auxval = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
+
+            if (((char*)auxkey->ptr)[0] == '%') {
+                /* All the fields with a name staring with '%' are considered
+                 * information fields and are logged at startup with a log
+                 * level of NOTICE. */
+                redisLog(REDIS_NOTICE,"RDB '%s': %s", auxkey->ptr, auxval->ptr);
+            } else {
+                /* We ignore fields we don't understand, as by AUX field
+                 * contract. */
+                redisLog(REDIS_DEBUG,"Unrecognized RDB AUX field: '%s'",
+                    auxkey->ptr);
+            }
+
+            zfree(auxkey);
+            zfree(auxval);
+            continue; /* Read type again. */
         }
 
         /* Read key */