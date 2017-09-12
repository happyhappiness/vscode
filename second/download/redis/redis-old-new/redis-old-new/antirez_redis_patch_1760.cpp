@@ -141,12 +141,13 @@ int dsClose(void) {
 }
 
 /* Convert key into full path for this object. Dirty but hopefully
- * is fast enough. */
-void dsKeyToPath(redisDb *db, char *buf, robj *key) {
+ * is fast enough. Returns the length of the returned path. */
+int dsKeyToPath(redisDb *db, char *buf, robj *key) {
     SHA1_CTX ctx;
     unsigned char hash[20];
     char hex[40], digits[] = "0123456789abcdef";
     int j, l;
+    char *origbuf = buf;
 
     SHA1Init(&ctx);
     SHA1Update(&ctx,key->ptr,sdslen(key->ptr));
@@ -179,19 +180,33 @@ void dsKeyToPath(redisDb *db, char *buf, robj *key) {
     buf[0] = '_';
     memcpy(buf+1,hex,40);
     buf[41] = '\0';
+    return (buf-origbuf)+41;
 }
 
 int dsSet(redisDb *db, robj *key, robj *val) {
-    char buf[1024];
+    char buf[1024], buf2[1024];
     FILE *fp;
-    int retval;
+    int retval, len;
 
-    dsKeyToPath(db,buf,key);
-    fp = fopen(buf,"w");
+    len = dsKeyToPath(db,buf,key);
+    memcpy(buf2,buf,len);
+    snprintf(buf2+len,sizeof(buf2)-len,"%ld.%ld",(long)time(NULL),(long)val);
+    fp = fopen(buf2,"w");
     if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
         return REDIS_ERR;
     fclose(fp);
-    if (retval == 0) unlink(buf); /* Expired key. Unlink failing not critical */
+    if (retval == 0) {
+        /* Expired key. Unlink failing not critical */
+        unlink(buf);
+        unlink(buf2);
+    } else {
+        /* Use rename for atomic updadte of value */
+        if (rename(buf2,buf) == -1) {
+            redisLog(REDIS_WARNING,"rename(2) returned an error: %s",
+                strerror(errno));
+            redisPanic("Unrecoverable diskstore error. Exiting.");
+        }
+    }
     return REDIS_OK;
 }
 