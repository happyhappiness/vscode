@@ -7551,7 +7551,7 @@ int loadAppendOnlyFile(char *filename) {
 }
 
 /* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
-static int fwriteBulk(FILE *fp, robj *obj) {
+static int fwriteBulkObject(FILE *fp, robj *obj) {
     char buf[128];
     int decrrc = 0;
 
@@ -7576,6 +7576,18 @@ static int fwriteBulk(FILE *fp, robj *obj) {
     return 0;
 }
 
+/* Write binary-safe string into a file in the bulkformat
+ * $<count>\r\n<payload>\r\n */
+static int fwriteBulkString(FILE *fp, char *s, unsigned long len) {
+    char buf[128];
+
+    snprintf(buf,sizeof(buf),"$%ld\r\n",(unsigned long)len);
+    if (fwrite(buf,strlen(buf),1,fp) == 0) return 0;
+    if (len && fwrite(s,len,1,fp) == 0) return 0;
+    if (fwrite("\r\n",2,1,fp) == 0) return 0;
+    return 1;
+}
+
 /* Write a double value in bulk format $<count>\r\n<payload>\r\n */
 static int fwriteBulkDouble(FILE *fp, double d) {
     char buf[128], dbuf[128];
@@ -7658,8 +7670,8 @@ static int rewriteAppendOnlyFile(char *filename) {
                 char cmd[]="*3\r\n$3\r\nSET\r\n";
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
                 /* Key and value */
-                if (fwriteBulk(fp,key) == 0) goto werr;
-                if (fwriteBulk(fp,o) == 0) goto werr;
+                if (fwriteBulkObject(fp,key) == 0) goto werr;
+                if (fwriteBulkObject(fp,o) == 0) goto werr;
             } else if (o->type == REDIS_LIST) {
                 /* Emit the RPUSHes needed to rebuild the list */
                 list *list = o->ptr;
@@ -7672,8 +7684,8 @@ static int rewriteAppendOnlyFile(char *filename) {
                     robj *eleobj = listNodeValue(ln);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulk(fp,key) == 0) goto werr;
-                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
+                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
             } else if (o->type == REDIS_SET) {
                 /* Emit the SADDs needed to rebuild the set */
@@ -7686,8 +7698,8 @@ static int rewriteAppendOnlyFile(char *filename) {
                     robj *eleobj = dictGetEntryKey(de);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulk(fp,key) == 0) goto werr;
-                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
+                    if (fwriteBulkObject(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
                 dictReleaseIterator(di);
             } else if (o->type == REDIS_ZSET) {
@@ -7702,11 +7714,43 @@ static int rewriteAppendOnlyFile(char *filename) {
                     double *score = dictGetEntryVal(de);
 
                     if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                    if (fwriteBulk(fp,key) == 0) goto werr;
+                    if (fwriteBulkObject(fp,key) == 0) goto werr;
                     if (fwriteBulkDouble(fp,*score) == 0) goto werr;
-                    if (fwriteBulk(fp,eleobj) == 0) goto werr;
+                    if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
                 }
                 dictReleaseIterator(di);
+            } else if (o->type == REDIS_HASH) {
+                char cmd[]="*4\r\n$4\r\nHSET\r\n";
+
+                /* Emit the HSETs needed to rebuild the hash */
+                if (o->encoding == REDIS_ENCODING_ZIPMAP) {
+                    unsigned char *p = zipmapRewind(o->ptr);
+                    unsigned char *field, *val;
+                    unsigned int flen, vlen;
+
+                    while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
+                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                        if (fwriteBulkObject(fp,key) == 0) goto werr;
+                        if (fwriteBulkString(fp,(char*)field,flen) == -1)
+                            return -1;
+                        if (fwriteBulkString(fp,(char*)val,vlen) == -1)
+                            return -1;
+                    }
+                } else {
+                    dictIterator *di = dictGetIterator(o->ptr);
+                    dictEntry *de;
+
+                    while((de = dictNext(di)) != NULL) {
+                        robj *field = dictGetEntryKey(de);
+                        robj *val = dictGetEntryVal(de);
+
+                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                        if (fwriteBulkObject(fp,key) == 0) goto werr;
+                        if (fwriteBulkObject(fp,field) == -1) return -1;
+                        if (fwriteBulkObject(fp,val) == -1) return -1;
+                    }
+                    dictReleaseIterator(di);
+                }
             } else {
                 redisAssert(0 != 0);
             }
@@ -7716,7 +7760,7 @@ static int rewriteAppendOnlyFile(char *filename) {
                 /* If this key is already expired skip it */
                 if (expiretime < now) continue;
                 if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                if (fwriteBulk(fp,key) == 0) goto werr;
+                if (fwriteBulkObject(fp,key) == 0) goto werr;
                 if (fwriteBulkLong(fp,expiretime) == 0) goto werr;
             }
             if (swapped) decrRefCount(o);