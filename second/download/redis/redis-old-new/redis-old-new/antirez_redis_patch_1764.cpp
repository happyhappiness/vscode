@@ -141,10 +141,10 @@ int dsClose(void) {
 
 /* Convert key into full path for this object. Dirty but hopefully
  * is fast enough. */
-void dsKeyToPath(redisDb *db, unsigned char *buf, robj *key) {
+void dsKeyToPath(redisDb *db, char *buf, robj *key) {
     SHA1_CTX ctx;
     unsigned char hash[20];
-    char *hex, digits[] = "0123456789abcdef";
+    char hex[40], digits[] = "0123456789abcdef";
     int j, l;
 
     SHA1Init(&ctx);
@@ -185,20 +185,80 @@ int dsSet(redisDb *db, robj *key, robj *val) {
     FILE *fp;
     int retval;
 
-    dsKeyToPath(buf,key);
+    dsKeyToPath(db,buf,key);
     fp = fopen(buf,"w");
     if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
         return REDIS_ERR;
     fclose(fp);
-    if (retval == 0) unlink(buf); /* Expired key */
+    if (retval == 0) unlink(buf); /* Expired key. Unlink failing not critical */
     return REDIS_OK;
 }
 
 robj *dsGet(redisDb *db, robj *key, time_t *expire) {
-    return createStringObject("foo",3);
+    char buf[1024];
+    int type;
+    time_t expiretime = -1; /* -1 means: no expire */
+    robj *dskey; /* Key as loaded from disk. */
+    robj *val;
+    FILE *fp;
+
+    dsKeyToPath(db,buf,key);
+    fp = fopen(buf,"r");
+    if (fp == NULL && errno == ENOENT) return NULL; /* No such key */
+    if (fp == NULL) {
+        redisLog(REDIS_WARNING,"Disk store failed opening %s: %s",
+            buf, strerror(errno));
+        goto readerr;
+    }
+
+    if ((type = rdbLoadType(fp)) == -1) goto readerr;
+    if (type == REDIS_EXPIRETIME) {
+        if ((expiretime = rdbLoadTime(fp)) == -1) goto readerr;
+        /* We read the time so we need to read the object type again */
+        if ((type = rdbLoadType(fp)) == -1) goto readerr;
+    }
+    /* Read key */
+    if ((dskey = rdbLoadStringObject(fp)) == NULL) goto readerr;
+    /* Read value */
+    if ((val = rdbLoadObject(type,fp)) == NULL) goto readerr;
+    fclose(fp);
+
+    /* The key we asked, and the key returned, must be the same */
+    redisAssert(equalStringObjects(key,dskey));
+
+    /* Check if the key already expired */
+    decrRefCount(dskey);
+    if (expiretime != -1 && expiretime < time(NULL)) {
+        decrRefCount(val);
+        unlink(buf); /* This failing is non critical here */
+        return NULL;
+    }
+
+    /* Everything ok... */
+    *expire = expiretime;
+    return val;
+
+readerr:
+    redisPanic("Unrecoverable error reading from disk store");
+    return NULL; /* unreached */
 }
 
 int dsDel(redisDb *db, robj *key) {
+    char buf[1024];
+
+    dsKeyToPath(db,buf,key);
+    if (unlink(buf) == -1) {
+        if (errno == ENOENT) {
+            return REDIS_ERR;
+        } else {
+            redisLog(REDIS_WARNING,"Disk store can't remove %s: %s",
+                buf, strerror(errno));
+            redisPanic("Unrecoverable Disk store errore. Existing.");
+            return REDIS_ERR; /* unreached */
+        }
+    } else {
+        return REDIS_OK;
+    }
 }
 
 int dsExists(redisDb *db, robj *key) {