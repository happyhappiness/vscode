@@ -8730,40 +8730,17 @@ int loadAppendOnlyFile(char *filename) {
     exit(1);
 }
 
-/* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
-static int fwriteBulkObject(FILE *fp, robj *obj) {
-    char buf[128];
-    int decrrc = 0;
-
-    /* Avoid the incr/decr ref count business if possible to help
-     * copy-on-write (we are often in a child process when this function
-     * is called).
-     * Also makes sure that key objects don't get incrRefCount-ed when VM
-     * is enabled */
-    if (obj->encoding != REDIS_ENCODING_RAW) {
-        obj = getDecodedObject(obj);
-        decrrc = 1;
-    }
-    snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
-    if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
-    if (sdslen(obj->ptr) && fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0)
-        goto err;
-    if (fwrite("\r\n",2,1,fp) == 0) goto err;
-    if (decrrc) decrRefCount(obj);
-    return 1;
-err:
-    if (decrrc) decrRefCount(obj);
-    return 0;
-}
-
 /* Write binary-safe string into a file in the bulkformat
  * $<count>\r\n<payload>\r\n */
 static int fwriteBulkString(FILE *fp, char *s, unsigned long len) {
-    char buf[128];
-
-    snprintf(buf,sizeof(buf),"$%ld\r\n",(unsigned long)len);
-    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
-    if (len && fwrite(s,len,1,fp) == 0) return 0;
+    char cbuf[128];
+    int clen;
+    cbuf[0] = '$';
+    clen = 1+ll2string(cbuf+1,sizeof(cbuf)-1,len);
+    cbuf[clen++] = '\r';
+    cbuf[clen++] = '\n';
+    if (fwrite(cbuf,clen,1,fp) == 0) return 0;
+    if (len > 0 && fwrite(s,len,1,fp) == 0) return 0;
     if (fwrite("\r\n",2,1,fp) == 0) return 0;
     return 1;
 }
@@ -8780,16 +8757,28 @@ static int fwriteBulkDouble(FILE *fp, double d) {
 }
 
 /* Write a long value in bulk format $<count>\r\n<payload>\r\n */
-static int fwriteBulkLong(FILE *fp, long l) {
-    char buf[128], lbuf[128];
-
-    snprintf(lbuf,sizeof(lbuf),"%ld\r\n",l);
-    snprintf(buf,sizeof(buf),"$%lu\r\n",(unsigned long)strlen(lbuf)-2);
-    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
-    if (fwrite(lbuf,strlen(lbuf),1,fp) == 0) return 0;
+static int fwriteBulkLongLong(FILE *fp, long long l) {
+    char bbuf[128], lbuf[128];
+    unsigned int blen, llen;
+    llen = ll2string(lbuf,32,l);
+    blen = snprintf(bbuf,sizeof(bbuf),"$%u\r\n%s\r\n",llen,lbuf);
+    if (fwrite(bbuf,blen,1,fp) == 0) return 0;
     return 1;
 }
 
+/* Delegate writing an object to writing a bulk string or bulk long long. */
+static int fwriteBulkObject(FILE *fp, robj *obj) {
+    /* Avoid using getDecodedObject to help copy-on-write (we are often
+     * in a child process when this function is called). */
+    if (obj->encoding == REDIS_ENCODING_INT) {
+        return fwriteBulkLongLong(fp,(long)obj->ptr);
+    } else if (obj->encoding == REDIS_ENCODING_RAW) {
+        return fwriteBulkString(fp,obj->ptr,sdslen(obj->ptr));
+    } else {
+        redisPanic("Unknown string encoding");
+    }
+}
+
 /* Write a sequence of commands able to fully rebuild the dataset into
  * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
 static int rewriteAppendOnlyFile(char *filename) {
@@ -8821,7 +8810,7 @@ static int rewriteAppendOnlyFile(char *filename) {
 
         /* SELECT the new DB */
         if (fwrite(selectcmd,sizeof(selectcmd)-1,1,fp) == 0) goto werr;
-        if (fwriteBulkLong(fp,j) == 0) goto werr;
+        if (fwriteBulkLongLong(fp,j) == 0) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -8941,7 +8930,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 if (expiretime < now) continue;
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                 if (fwriteBulkObject(fp,key) == 0) goto werr;
-                if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
+                if (fwriteBulkLongLong(fp,expiretime) == 0) goto werr;
             }
             if (swapped) decrRefCount(o);
         }