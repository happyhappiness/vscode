@@ -1023,6 +1023,30 @@ static long long memtoll(const char *p, int *err) {
     return val*mul;
 }
 
+/* Convert a long long into a string. Returns the number of
+ * characters needed to represent the number, that can be shorter if passed
+ * buffer length is not enough to store the whole number. */
+static int ll2string(char *s, size_t len, long long value) {
+    char buf[32], *p;
+    unsigned long long v;
+    size_t l;
+
+    if (len == 0) return 0;
+    v = (value < 0) ? -value : value;
+    p = buf+31; /* point to the last character */
+    do {
+        *p-- = '0'+(v%10);
+        v /= 10;
+    } while(v);
+    if (value < 0) *p-- = '-';
+    p++;
+    l = 32-(p-buf);
+    if (l+1 > len) l = len-1; /* Make sure it fits, including the nul term */
+    memcpy(s,p,l);
+    s[l] = '\0';
+    return l;
+}
+
 static void redisLog(int level, const char *fmt, ...) {
     va_list ap;
     FILE *fp;
@@ -1126,7 +1150,7 @@ static unsigned int dictEncObjHash(const void *key) {
             char buf[32];
             int len;
 
-            len = snprintf(buf,32,"%ld",(long)o->ptr);
+            len = ll2string(buf,32,(long)o->ptr);
             return dictGenHashFunction((unsigned char*)buf, len);
         } else {
             unsigned int hash;
@@ -2897,19 +2921,7 @@ static robj *createStringObjectFromLongLong(long long value) {
             o->encoding = REDIS_ENCODING_INT;
             o->ptr = (void*)((long)value);
         } else {
-            char buf[32], *p;
-            char *c = "0123456789";
-            unsigned long v;
-
-            v = (value < 0) ? -value : value;
-            p = buf+31; /* point to the last character */
-            while(v) {
-                *p-- = c[v%10];
-                v /= 10;
-            }
-            if (value < 0) *p-- = '-';
-            p++;
-            o = createObject(REDIS_STRING,sdsnewlen(p,32-(p-buf+1)));
+            o = createObject(REDIS_STRING,sdsfromlonglong(value));
         }
     }
     return o;
@@ -3124,7 +3136,7 @@ static int isStringRepresentableAsLong(sds s, long *longval) {
 
     value = strtol(s, &endptr, 10);
     if (endptr[0] != '\0') return REDIS_ERR;
-    slen = snprintf(buf,32,"%ld",value);
+    slen = ll2string(buf,32,value);
 
     /* If the number converted back into a string is not identical
      * then it's not possible to encode the string as integer */
@@ -3177,7 +3189,7 @@ static robj *getDecodedObject(robj *o) {
     if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_INT) {
         char buf[32];
 
-        snprintf(buf,32,"%ld",(long)o->ptr);
+        ll2string(buf,32,(long)o->ptr);
         dec = createStringObject(buf,strlen(buf));
         return dec;
     } else {
@@ -3187,7 +3199,7 @@ static robj *getDecodedObject(robj *o) {
 
 /* Compare two string objects via strcmp() or alike.
  * Note that the objects may be integer-encoded. In such a case we
- * use snprintf() to get a string representation of the numbers on the stack
+ * use ll2string() to get a string representation of the numbers on the stack
  * and compare the strings, it's much faster than calling getDecodedObject().
  *
  * Important note: if objects are not integer encoded, but binary-safe strings,
@@ -3200,14 +3212,14 @@ static int compareStringObjects(robj *a, robj *b) {
 
     if (a == b) return 0;
     if (a->encoding != REDIS_ENCODING_RAW) {
-        snprintf(bufa,sizeof(bufa),"%ld",(long) a->ptr);
+        ll2string(bufa,sizeof(bufa),(long) a->ptr);
         astr = bufa;
         bothsds = 0;
     } else {
         astr = a->ptr;
     }
     if (b->encoding != REDIS_ENCODING_RAW) {
-        snprintf(bufb,sizeof(bufb),"%ld",(long) b->ptr);
+        ll2string(bufb,sizeof(bufb),(long) b->ptr);
         bstr = bufb;
         bothsds = 0;
     } else {
@@ -3235,7 +3247,7 @@ static size_t stringObjectLen(robj *o) {
     } else {
         char buf[32];
 
-        return snprintf(buf,32,"%ld",(long)o->ptr);
+        return ll2string(buf,32,(long)o->ptr);
     }
 }
 
@@ -3376,7 +3388,7 @@ static int rdbTryIntegerEncoding(char *s, size_t len, unsigned char *enc) {
     /* Check if it's possible to encode this value as a number */
     value = strtoll(s, &endptr, 10);
     if (endptr[0] != '\0') return 0;
-    snprintf(buf,32,"%lld",value);
+    ll2string(buf,32,value);
 
     /* If the number converted back into a string is not identical
      * then it's not possible to encode the string as integer */