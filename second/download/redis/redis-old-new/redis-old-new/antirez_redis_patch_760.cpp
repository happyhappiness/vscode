@@ -645,7 +645,7 @@ int loadAppendOnlyFile(char *filename) {
             argsds = sdsnewlen(NULL,len);
             if (len && fread(argsds,len,1,fp) == 0) goto fmterr;
             argv[j] = createObject(REDIS_STRING,argsds);
-            if (fread(buf,2,1,fp) == 0) goto fmterr; /* discard CRLF */
+            if (fread(buf,2,1,fp) == 0) goto readerr; /* discard CRLF */
         }
 
         /* Command lookup */
@@ -673,7 +673,7 @@ int loadAppendOnlyFile(char *filename) {
 
     /* This point can only be reached when EOF is reached without errors.
      * If the client is in the middle of a MULTI/EXEC, log error and quit. */
-    if (fakeClient->flags & REDIS_MULTI) goto readerr;
+    if (fakeClient->flags & REDIS_MULTI) goto uxeof;
 
     fclose(fp);
     freeFakeClient(fakeClient);
@@ -683,14 +683,17 @@ int loadAppendOnlyFile(char *filename) {
     server.aof_rewrite_base_size = server.aof_current_size;
     return REDIS_OK;
 
-readerr:
-    if (feof(fp)) {
-        redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file");
-    } else {
+readerr: /* Read error. If feof(fp) is true, fall through to unexpected EOF. */
+    if (!feof(fp)) {
         redisLog(REDIS_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
+        exit(1);
     }
+
+uxeof: /* Unexpected AOF end of file. */
+    redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file");
     exit(1);
-fmterr:
+
+fmterr: /* Format error. */
     redisLog(REDIS_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
     exit(1);
 }