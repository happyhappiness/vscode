@@ -1836,10 +1836,31 @@ static robj *tryObjectSharing(robj *o) {
     }
 }
 
+/* Check if the nul-terminated string 's' can be represented by a long
+ * (that is, is a number that fits into long without any other space or
+ * character before or after the digits).
+ *
+ * If so, the function returns REDIS_OK and *longval is set to the value
+ * of the number. Otherwise REDIS_ERR is returned */
+static int isStringRepresentableAsLong(char *s, long *longval) {
+    char buf[32], *endptr;
+    long value;
+    int slen;
+    
+    value = strtol(s, &endptr, 10);
+    if (endptr[0] != '\0') return REDIS_ERR;
+    slen = snprintf(buf,32,"%ld",value);
+
+    /* If the number converted back into a string is not identical
+     * then it's not possible to encode the string as integer */
+    if (strlen(buf) != (unsigned)slen || memcmp(buf,s,slen)) return REDIS_ERR;
+    if (longval) *longval = value;
+    return REDIS_OK;
+}
+
 /* Try to encode a string object in order to save space */
 static int tryObjectEncoding(robj *o) {
     long value;
-    char *endptr, buf[32];
     sds s = o->ptr;
 
     if (o->encoding != REDIS_ENCODING_RAW)
@@ -1853,15 +1874,8 @@ static int tryObjectEncoding(robj *o) {
     /* Currently we try to encode only strings */
     assert(o->type == REDIS_STRING);
 
-    /* Check if it's possible to encode this value as a long. We are assuming
-     * that sizeof(long) = sizeof(void) in all the supported archs. */
-    value = strtol(s, &endptr, 10);
-    if (endptr[0] != '\0') return REDIS_ERR;
-    snprintf(buf,32,"%ld",value);
-
-    /* If the number converted back into a string is not identical
-     * then it's not possible to encode the string as integer */
-    if (strlen(buf) != sdslen(s) || memcmp(buf,s,sdslen(s))) return REDIS_ERR;
+    /* Check if we can represent this string as a long integer */
+    if (isStringRepresentableAsLong(s,&value) == REDIS_ERR) return REDIS_ERR;
 
     /* Ok, this object can be encoded */
     o->encoding = REDIS_ENCODING_INT;
@@ -1886,6 +1900,25 @@ static robj *getDecodedObject(const robj *o) {
     }
 }
 
+static int compareStringObjects(robj *a, robj *b) {
+    assert(a->type == REDIS_STRING && b->type == REDIS_STRING);
+
+    if (a->encoding == REDIS_ENCODING_INT && b->encoding == REDIS_ENCODING_INT){
+        return (long)a->ptr - (long)b->ptr;
+    } else {
+        int retval;
+
+        incrRefCount(a);
+        incrRefCount(b);
+        if (a->encoding != REDIS_ENCODING_RAW) a = getDecodedObject(a);
+        if (b->encoding != REDIS_ENCODING_RAW) b = getDecodedObject(a);
+        retval = sdscmp(a->ptr,b->ptr);
+        decrRefCount(a);
+        decrRefCount(b);
+        return retval;
+    }
+}
+
 /*============================ DB saving/loading ============================ */
 
 static int rdbSaveType(FILE *fp, unsigned char type) {
@@ -3090,7 +3123,7 @@ static void lremCommand(redisClient *c) {
                 robj *ele = listNodeValue(ln);
 
                 next = fromtail ? ln->prev : ln->next;
-                if (sdscmp(ele->ptr,c->argv[3]->ptr) == 0) {
+                if (compareStringObjects(ele,c->argv[3]) == 0) {
                     listDelNode(list,ln);
                     server.dirty++;
                     removed++;
@@ -4375,6 +4408,8 @@ static void debugCommand(redisClient *c) {
 
 #ifdef HAVE_BACKTRACE
 static struct redisFunctionSym symsTable[] = {
+{"compareStringObjects", (unsigned long)compareStringObjects},
+{"isStringRepresentableAsLong", (unsigned long)isStringRepresentableAsLong},
 {"dictEncObjKeyCompare", (unsigned long)dictEncObjKeyCompare},
 {"dictEncObjHash", (unsigned long)dictEncObjHash},
 {"incrDecrCommand", (unsigned long)incrDecrCommand},