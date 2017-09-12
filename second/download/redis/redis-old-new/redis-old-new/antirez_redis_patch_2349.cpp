@@ -1657,7 +1657,7 @@ static int rdbSaveLzfStringObject(FILE *fp, robj *obj) {
     if ((out = zmalloc(outlen)) == NULL) return 0;
     comprlen = lzf_compress(obj->ptr, sdslen(obj->ptr), out, outlen);
     if (comprlen == 0) {
-        free(out);
+        zfree(out);
         return 0;
     }
     /* Data compressed! Let's save it on disk */
@@ -1666,11 +1666,11 @@ static int rdbSaveLzfStringObject(FILE *fp, robj *obj) {
     if (rdbSaveLen(fp,comprlen) == -1) goto writeerr;
     if (rdbSaveLen(fp,sdslen(obj->ptr)) == -1) goto writeerr;
     if (fwrite(out,comprlen,1,fp) == 0) goto writeerr;
-    free(out);
+    zfree(out);
     return comprlen;
 
 writeerr:
-    free(out);
+    zfree(out);
     return -1;
 }
 
@@ -1690,8 +1690,8 @@ static int rdbSaveStringObject(FILE *fp, robj *obj) {
     }
 
     /* Try LZF compression - under 20 bytes it's unable to compress even
-     * aaaaaaaaaaaaaaaaaa so to try is just useful to make the CPU hot */
-    if (0 && len > 20) {
+     * aaaaaaaaaaaaaaaaaa so skip it */
+    if (len > 20) {
         int retval;
 
         retval = rdbSaveLzfStringObject(fp,obj);
@@ -1892,6 +1892,24 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
     return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
 }
 
+static robj *rdbLoadLzfStringObject(FILE*fp, int rdbver) {
+    unsigned int len, clen;
+    unsigned char *c = NULL;
+    sds val = NULL;
+
+    if ((clen = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((len = rdbLoadLen(fp,rdbver,NULL)) == REDIS_RDB_LENERR) return NULL;
+    if ((c = zmalloc(clen)) == NULL) goto err;
+    if ((val = sdsnewlen(NULL,len)) == NULL) goto err;
+    if (fread(c,clen,1,fp) == 0) goto err;
+    if (lzf_decompress(c,clen,val,len) == 0) goto err;
+    return createObject(REDIS_STRING,val);
+err:
+    zfree(c);
+    sdsfree(val);
+    return NULL;
+}
+
 static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
     int isencoded;
     uint32_t len;
@@ -1904,6 +1922,8 @@ static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
         case REDIS_RDB_ENC_INT16:
         case REDIS_RDB_ENC_INT32:
             return tryObjectSharing(rdbLoadIntegerObject(fp,len));
+        case REDIS_RDB_ENC_LZF:
+            return tryObjectSharing(rdbLoadLzfStringObject(fp,rdbver));
         default:
             assert(0!=0);
         }