     return nwritten;
 }
 
 /* Load an LZF compressed string in RDB format. The returned value
  * changes according to 'flags'. For more info check the
  * rdbGenericLoadStringObject() function. */
-void *rdbLoadLzfStringObject(rio *rdb, int flags) {
+void *rdbLoadLzfStringObject(rio *rdb, int flags, size_t *lenptr) {
     int plain = flags & RDB_LOAD_PLAIN;
-    unsigned int len, clen;
+    int sds = flags & RDB_LOAD_SDS;
+    uint64_t len, clen;
     unsigned char *c = NULL;
-    sds val = NULL;
+    char *val = NULL;
 
     if ((clen = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
     if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
     if ((c = zmalloc(clen)) == NULL) goto err;
 
     /* Allocate our target according to the uncompressed size. */
     if (plain) {
         val = zmalloc(len);
+        if (lenptr) *lenptr = len;
     } else {
-        if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
+        val = sdsnewlen(NULL,len);
     }
 
     /* Load the compressed representation and uncompress it to target. */
     if (rioRead(rdb,c,clen) == 0) goto err;
     if (lzf_decompress(c,clen,val,len) == 0) {
         if (rdbCheckMode) rdbCheckSetError("Invalid LZF compressed string");
         goto err;
     }
     zfree(c);
 
-    if (plain)
+    if (plain || sds) {
         return val;
-    else
+    } else {
         return createObject(OBJ_STRING,val);
+    }
 err:
     zfree(c);
     if (plain)
         zfree(val);
     else
         sdsfree(val);
