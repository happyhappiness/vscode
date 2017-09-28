     redisDb *db = server.db+0;
     char buf[1024];
     long long expiretime, now = mstime();
     FILE *fp;
     rio rdb;
 
-    if ((fp = fopen(filename,"r")) == NULL) return REDIS_ERR;
+    if ((fp = fopen(filename,"r")) == NULL) return C_ERR;
 
     rioInitWithFile(&rdb,fp);
     rdb.update_cksum = rdbLoadProgressCallback;
     rdb.max_processing_chunk = server.loading_process_events_interval_bytes;
     if (rioRead(&rdb,buf,9) == 0) goto eoferr;
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
         fclose(fp);
-        redisLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
+        serverLog(LL_WARNING,"Wrong signature trying to load DB from file");
         errno = EINVAL;
-        return REDIS_ERR;
+        return C_ERR;
     }
     rdbver = atoi(buf+5);
-    if (rdbver < 1 || rdbver > REDIS_RDB_VERSION) {
+    if (rdbver < 1 || rdbver > RDB_VERSION) {
         fclose(fp);
-        redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
+        serverLog(LL_WARNING,"Can't handle RDB format version %d",rdbver);
         errno = EINVAL;
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     startLoading(fp);
     while(1) {
         robj *key, *val;
         expiretime = -1;
 
         /* Read type. */
         if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
-        if (type == REDIS_RDB_OPCODE_EXPIRETIME) {
+
+        /* Handle special types. */
+        if (type == RDB_OPCODE_EXPIRETIME) {
+            /* EXPIRETIME: load an expire associated with the next key
+             * to load. Note that after loading an expire we need to
+             * load the actual type, and continue. */
             if ((expiretime = rdbLoadTime(&rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
             if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
             /* the EXPIRETIME opcode specifies time in seconds, so convert
              * into milliseconds. */
             expiretime *= 1000;
-        } else if (type == REDIS_RDB_OPCODE_EXPIRETIME_MS) {
-            /* Milliseconds precision expire times introduced with RDB
-             * version 3. */
+        } else if (type == RDB_OPCODE_EXPIRETIME_MS) {
+            /* EXPIRETIME_MS: milliseconds precision expire times introduced
+             * with RDB v3. Like EXPIRETIME but no with more precision. */
             if ((expiretime = rdbLoadMillisecondTime(&rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
             if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
-        }
-
-        if (type == REDIS_RDB_OPCODE_EOF)
+        } else if (type == RDB_OPCODE_EOF) {
+            /* EOF: End of file, exit the main loop. */
             break;
-
-        /* Handle SELECT DB opcode as a special case */
-        if (type == REDIS_RDB_OPCODE_SELECTDB) {
-            if ((dbid = rdbLoadLen(&rdb,NULL)) == REDIS_RDB_LENERR)
+        } else if (type == RDB_OPCODE_SELECTDB) {
+            /* SELECTDB: Select the specified database. */
+            if ((dbid = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
-                redisLog(REDIS_WARNING,"FATAL: Data file was created with a Redis server configured to handle more than %d databases. Exiting\n", server.dbnum);
+                serverLog(LL_WARNING,
+                    "FATAL: Data file was created with a Redis "
+                    "server configured to handle more than %d "
+                    "databases. Exiting\n", server.dbnum);
                 exit(1);
             }
             db = server.db+dbid;
-            continue;
+            continue; /* Read type again. */
+        } else if (type == RDB_OPCODE_RESIZEDB) {
+            /* RESIZEDB: Hint about the size of the keys in the currently
+             * selected data base, in order to avoid useless rehashing. */
+            uint32_t db_size, expires_size;
+            if ((db_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
+                goto eoferr;
+            if ((expires_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
+                goto eoferr;
+            dictExpand(db->dict,db_size);
+            dictExpand(db->expires,expires_size);
+            continue; /* Read type again. */
+        } else if (type == RDB_OPCODE_AUX) {
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
+                serverLog(LL_NOTICE,"RDB '%s': %s",
+                    (char*)auxkey->ptr,
+                    (char*)auxval->ptr);
+            } else {
+                /* We ignore fields we don't understand, as by AUX field
+                 * contract. */
+                serverLog(LL_DEBUG,"Unrecognized RDB AUX field: '%s'",
+                    (char*)auxkey->ptr);
+            }
+
+            decrRefCount(auxkey);
+            decrRefCount(auxval);
+            continue; /* Read type again. */
         }
+
         /* Read key */
         if ((key = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
         /* Read value */
         if ((val = rdbLoadObject(type,&rdb)) == NULL) goto eoferr;
         /* Check if the key already expired. This function is used when loading
          * an RDB file from disk, either at startup, or when an RDB was
