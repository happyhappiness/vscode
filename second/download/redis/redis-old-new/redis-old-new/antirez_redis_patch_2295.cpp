@@ -2074,24 +2074,31 @@ static robj *getDecodedObject(const robj *o) {
     }
 }
 
+/* Compare two string objects via strcmp() or alike.
+ * Note that the objects may be integer-encoded. In such a case we
+ * use snprintf() to get a string representation of the numbers on the stack
+ * and compare the strings, it's much faster than calling getDecodedObject(). */
 static int compareStringObjects(robj *a, robj *b) {
     assert(a->type == REDIS_STRING && b->type == REDIS_STRING);
+    char bufa[128], bufb[128], *astr, *bstr;
+    int bothsds = 1;
 
     if (a == b) return 0;
-    if (a->encoding == REDIS_ENCODING_INT && b->encoding == REDIS_ENCODING_INT){
-        return (long)a->ptr - (long)b->ptr;
+    if (a->encoding != REDIS_ENCODING_RAW) {
+        snprintf(bufa,sizeof(bufa),"%ld",(long) a->ptr);
+        astr = bufa;
+        bothsds = 0;
     } else {
-        int retval;
-
-        incrRefCount(a);
-        incrRefCount(b);
-        if (a->encoding != REDIS_ENCODING_RAW) a = getDecodedObject(a);
-        if (b->encoding != REDIS_ENCODING_RAW) b = getDecodedObject(a);
-        retval = sdscmp(a->ptr,b->ptr);
-        decrRefCount(a);
-        decrRefCount(b);
-        return retval;
+        astr = a->ptr;
+    }
+    if (b->encoding != REDIS_ENCODING_RAW) {
+        snprintf(bufb,sizeof(bufb),"%ld",(long) b->ptr);
+        bstr = bufb;
+        bothsds = 0;
+    } else {
+        bstr = b->ptr;
     }
+    return bothsds ? sdscmp(astr,bstr) : strcmp(astr,bstr);
 }
 
 static size_t stringObjectLen(robj *o) {