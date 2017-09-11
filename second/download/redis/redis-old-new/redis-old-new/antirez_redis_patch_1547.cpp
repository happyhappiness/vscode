@@ -110,17 +110,29 @@ void flushAppendOnlyFile(void) {
     }
 }
 
-sds catAppendOnlyGenericCommand(sds buf, int argc, robj **argv) {
-    int j;
-    buf = sdscatprintf(buf,"*%d\r\n",argc);
+sds catAppendOnlyGenericCommand(sds dst, int argc, robj **argv) {
+    char buf[32];
+    int len, j;
+    robj *o;
+
+    buf[0] = '*';
+    len = 1+ll2string(buf+1,sizeof(buf)-1,argc);
+    buf[len++] = '\r';
+    buf[len++] = '\n';
+    dst = sdscatlen(dst,buf,len);
+
     for (j = 0; j < argc; j++) {
-        robj *o = getDecodedObject(argv[j]);
-        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
-        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
-        buf = sdscatlen(buf,"\r\n",2);
+        o = getDecodedObject(argv[j]);
+        buf[0] = '$';
+        len = 1+ll2string(buf+1,sizeof(buf)-1,sdslen(o->ptr));
+        buf[len++] = '\r';
+        buf[len++] = '\n';
+        dst = sdscatlen(dst,buf,len);
+        dst = sdscatlen(dst,o->ptr,sdslen(o->ptr));
+        dst = sdscatlen(dst,"\r\n",2);
         decrRefCount(o);
     }
-    return buf;
+    return dst;
 }
 
 sds catAppendOnlyExpireAtCommand(sds buf, robj *key, robj *seconds) {