@@ -348,3 +348,50 @@ void dsFlushDb(int dbid) {
         }
     }
 }
+
+int dsRdbSave(char *filename) {
+    char tmpfile[256];
+    int j, i;
+    time_t now = time(NULL);
+
+    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
+    fp = fopen(tmpfile,"w");
+    if (!fp) {
+        redisLog(REDIS_WARNING, "Failed saving the DB: %s", strerror(errno));
+        return REDIS_ERR;
+    }
+    if (fwrite("REDIS0001",9,1,fp) == 0) goto werr;
+
+    /* Scan all diskstore dirs looking for keys */
+    for (j = 0; j < 256; j++) {
+        for (i = 0; i < 256; i++) {
+            snprintf(buf,1024,"%s/%02x/%02x",server.ds_path,j,i);
+
+            /* Write the SELECT DB opcode */
+            if (rdbSaveType(fp,REDIS_SELECTDB) == -1) goto werr;
+            if (rdbSaveLen(fp,j) == -1) goto werr;
+        }
+    }
+
+    /* Make sure data will not remain on the OS's output buffers */
+    fflush(fp);
+    fsync(fileno(fp));
+    fclose(fp);
+
+    /* Use RENAME to make sure the DB file is changed atomically only
+     * if the generate DB file is ok. */
+    if (rename(tmpfile,filename) == -1) {
+        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
+        unlink(tmpfile);
+        return REDIS_ERR;
+    }
+    redisLog(REDIS_NOTICE,"DB saved on disk");
+    server.dirty = 0;
+    server.lastsave = time(NULL);
+    return REDIS_OK;
+
+werr:
+    fclose(fp);
+    unlink(tmpfile);
+    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
+}