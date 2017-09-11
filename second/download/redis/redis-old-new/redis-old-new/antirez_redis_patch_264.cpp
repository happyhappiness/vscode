@@ -721,6 +721,7 @@ int loadAppendOnlyFile(char *filename) {
 
 readerr: /* Read error. If feof(fp) is true, fall through to unexpected EOF. */
     if (!feof(fp)) {
+        if (fakeClient) freeFakeClient(fakeClient); /* avoid valgrind warning */
         serverLog(LL_WARNING,"Unrecoverable error reading the append only file: %s", strerror(errno));
         exit(1);
     }
@@ -750,10 +751,12 @@ int loadAppendOnlyFile(char *filename) {
             }
         }
     }
+    if (fakeClient) freeFakeClient(fakeClient); /* avoid valgrind warning */
     serverLog(LL_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
     exit(1);
 
 fmterr: /* Format error. */
+    if (fakeClient) freeFakeClient(fakeClient); /* avoid valgrind warning */
     serverLog(LL_WARNING,"Bad file format reading the append only file: make a backup of your AOF file, then use ./redis-check-aof --fix <filename>");
     exit(1);
 }
@@ -763,7 +766,7 @@ int loadAppendOnlyFile(char *filename) {
  * ------------------------------------------------------------------------- */
 
 /* Delegate writing an object to writing a bulk string or bulk long long.
- * This is not placed in rio.c since that adds the redis.h dependency. */
+ * This is not placed in rio.c since that adds the server.h dependency. */
 int rioWriteBulkObject(rio *r, robj *obj) {
     /* Avoid using getDecodedObject to help copy-on-write (we are often
      * in a child process when this function is called). */