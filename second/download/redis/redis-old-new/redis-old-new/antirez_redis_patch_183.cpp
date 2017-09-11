@@ -45,6 +45,7 @@
 
 extern int rdbCheckMode;
 void rdbCheckError(const char *fmt, ...);
+void rdbCheckSetError(const char *fmt, ...);
 
 void rdbCheckThenExit(char *reason, int where) {
      if (!rdbCheckMode) {
@@ -341,7 +342,10 @@ void *rdbLoadLzfStringObject(rio *rdb, int flags, size_t *lenptr) {
 
     /* Load the compressed representation and uncompress it to target. */
     if (rioRead(rdb,c,clen) == 0) goto err;
-    if (lzf_decompress(c,clen,val,len) == 0) goto err;
+    if (lzf_decompress(c,clen,val,len) == 0) {
+        if (rdbCheckMode) rdbCheckSetError("Invalid LZF compressed string");
+        goto err;
+    }
     zfree(c);
 
     if (plain || sds) {