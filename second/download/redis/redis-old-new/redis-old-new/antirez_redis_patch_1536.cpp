@@ -1,5 +1,6 @@
 #include "redis.h"
 #include "bio.h"
+#include "rio.h"
 
 #include <signal.h>
 #include <fcntl.h>
@@ -386,11 +387,26 @@ int loadAppendOnlyFile(char *filename) {
     exit(1);
 }
 
+/* Delegate writing an object to writing a bulk string or bulk long long.
+ * This is not placed in rio.c since that adds the redis.h dependency. */
+int rioWriteBulkObject(rio *r, robj *obj) {
+    /* Avoid using getDecodedObject to help copy-on-write (we are often
+     * in a child process when this function is called). */
+    if (obj->encoding == REDIS_ENCODING_INT) {
+        return rioWriteBulkLongLong(r,(long)obj->ptr);
+    } else if (obj->encoding == REDIS_ENCODING_RAW) {
+        return rioWriteBulkString(r,obj->ptr,sdslen(obj->ptr));
+    } else {
+        redisPanic("Unknown string encoding");
+    }
+}
+
 /* Write a sequence of commands able to fully rebuild the dataset into
  * "filename". Used both by REWRITEAOF and BGREWRITEAOF. */
 int rewriteAppendOnlyFile(char *filename) {
     dictIterator *di = NULL;
     dictEntry *de;
+    rio aof;
     FILE *fp;
     char tmpfile[256];
     int j;
@@ -404,6 +420,8 @@ int rewriteAppendOnlyFile(char *filename) {
         redisLog(REDIS_WARNING, "Failed rewriting the append only file: %s", strerror(errno));
         return REDIS_ERR;
     }
+
+    aof = rioInitWithFile(fp);
     for (j = 0; j < server.dbnum; j++) {
         char selectcmd[] = "*2\r\n$6\r\nSELECT\r\n";
         redisDb *db = server.db+j;
@@ -416,8 +434,8 @@ int rewriteAppendOnlyFile(char *filename) {
         }
 
         /* SELECT the new DB */
-        if (fwrite(selectcmd,sizeof(selectcmd)-1,1,fp) == 0) goto werr;
-        if (fwriteBulkLongLong(fp,j) == 0) goto werr;
+        if (rioWrite(&aof,selectcmd,sizeof(selectcmd)-1) == 0) goto werr;
+        if (rioWriteBulkLongLong(&aof,j) == 0) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -435,10 +453,10 @@ int rewriteAppendOnlyFile(char *filename) {
             if (o->type == REDIS_STRING) {
                 /* Emit a SET command */
                 char cmd[]="*3\r\n$3\r\nSET\r\n";
-                if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
+                if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
                 /* Key and value */
-                if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                if (fwriteBulkObject(fp,o) == 0) goto werr;
+                if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                if (rioWriteBulkObject(&aof,o) == 0) goto werr;
             } else if (o->type == REDIS_LIST) {
                 /* Emit the RPUSHes needed to rebuild the list */
                 char cmd[]="*3\r\n$5\r\nRPUSH\r\n";
@@ -450,13 +468,13 @@ int rewriteAppendOnlyFile(char *filename) {
                     long long vlong;
 
                     while(ziplistGet(p,&vstr,&vlen,&vlong)) {
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
                         if (vstr) {
-                            if (fwriteBulkString(fp,(char*)vstr,vlen) == 0)
+                            if (rioWriteBulkString(&aof,(char*)vstr,vlen) == 0)
                                 goto werr;
                         } else {
-                            if (fwriteBulkLongLong(fp,vlong) == 0)
+                            if (rioWriteBulkLongLong(&aof,vlong) == 0)
                                 goto werr;
                         }
                         p = ziplistNext(zl,p);
@@ -470,9 +488,9 @@ int rewriteAppendOnlyFile(char *filename) {
                     while((ln = listNext(&li))) {
                         robj *eleobj = listNodeValue(ln);
 
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,eleobj) == 0) goto werr;
                     }
                 } else {
                     redisPanic("Unknown list encoding");
@@ -485,18 +503,18 @@ int rewriteAppendOnlyFile(char *filename) {
                     int ii = 0;
                     int64_t llval;
                     while(intsetGet(o->ptr,ii++,&llval)) {
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkLongLong(fp,llval) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkLongLong(&aof,llval) == 0) goto werr;
                     }
                 } else if (o->encoding == REDIS_ENCODING_HT) {
                     dictIterator *di = dictGetIterator(o->ptr);
                     dictEntry *de;
                     while((de = dictNext(di)) != NULL) {
                         robj *eleobj = dictGetEntryKey(de);
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,eleobj) == 0) goto werr;
                     }
                     dictReleaseIterator(di);
                 } else {
@@ -523,14 +541,14 @@ int rewriteAppendOnlyFile(char *filename) {
                         redisAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
                         score = zzlGetScore(sptr);
 
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkDouble(fp,score) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkDouble(&aof,score) == 0) goto werr;
                         if (vstr != NULL) {
-                            if (fwriteBulkString(fp,(char*)vstr,vlen) == 0)
+                            if (rioWriteBulkString(&aof,(char*)vstr,vlen) == 0)
                                 goto werr;
                         } else {
-                            if (fwriteBulkLongLong(fp,vll) == 0)
+                            if (rioWriteBulkLongLong(&aof,vll) == 0)
                                 goto werr;
                         }
                         zzlNext(zl,&eptr,&sptr);
@@ -544,10 +562,10 @@ int rewriteAppendOnlyFile(char *filename) {
                         robj *eleobj = dictGetEntryKey(de);
                         double *score = dictGetEntryVal(de);
 
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkDouble(fp,*score) == 0) goto werr;
-                        if (fwriteBulkObject(fp,eleobj) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkDouble(&aof,*score) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,eleobj) == 0) goto werr;
                     }
                     dictReleaseIterator(di);
                 } else {
@@ -563,11 +581,11 @@ int rewriteAppendOnlyFile(char *filename) {
                     unsigned int flen, vlen;
 
                     while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkString(fp,(char*)field,flen) == 0)
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkString(&aof,(char*)field,flen) == 0)
                             goto werr;
-                        if (fwriteBulkString(fp,(char*)val,vlen) == 0)
+                        if (rioWriteBulkString(&aof,(char*)val,vlen) == 0)
                             goto werr;
                     }
                 } else {
@@ -578,10 +596,10 @@ int rewriteAppendOnlyFile(char *filename) {
                         robj *field = dictGetEntryKey(de);
                         robj *val = dictGetEntryVal(de);
 
-                        if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                        if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                        if (fwriteBulkObject(fp,field) == 0) goto werr;
-                        if (fwriteBulkObject(fp,val) == 0) goto werr;
+                        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,field) == 0) goto werr;
+                        if (rioWriteBulkObject(&aof,val) == 0) goto werr;
                     }
                     dictReleaseIterator(di);
                 }
@@ -593,9 +611,9 @@ int rewriteAppendOnlyFile(char *filename) {
                 char cmd[]="*3\r\n$8\r\nEXPIREAT\r\n";
                 /* If this key is already expired skip it */
                 if (expiretime < now) continue;
-                if (fwrite(cmd,sizeof(cmd)-1,1,fp) == 0) goto werr;
-                if (fwriteBulkObject(fp,&key) == 0) goto werr;
-                if (fwriteBulkLongLong(fp,expiretime) == 0) goto werr;
+                if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
+                if (rioWriteBulkLongLong(&aof,expiretime) == 0) goto werr;
             }
         }
         dictReleaseIterator(di);