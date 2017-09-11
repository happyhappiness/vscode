@@ -44,6 +44,21 @@ robj *createStringObjectFromLongLong(long long value) {
     return o;
 }
 
+/* Note: this function is defined into object.c since here it is where it
+ * belongs but it is actually designed to be used just for INCRBYFLOAT */
+robj *createStringObjectFromLongDouble(long double value) {
+    char buf[256];
+    int len;
+
+    /* We use 17 digits precision since with 128 bit floats that precision
+     * after rouding is able to represent most small decimal numbers in a way
+     * that is "non surprising" for the user (that is, most small decimal
+     * numbers will be represented in a way that when converted back into
+     * a string are exactly the same as what the user typed.) */
+    len = snprintf(buf,sizeof(buf),"%.17Lg", value);
+    return createStringObject(buf,len);
+}
+
 robj *dupStringObject(robj *o) {
     redisAssertWithInfo(NULL,o,o->encoding == REDIS_ENCODING_RAW);
     return createStringObject(o->ptr,sdslen(o->ptr));
@@ -350,8 +365,10 @@ int getDoubleFromObject(robj *o, double *target) {
     } else {
         redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
         if (o->encoding == REDIS_ENCODING_RAW) {
+            errno = 0;
             value = strtod(o->ptr, &eptr);
-            if (eptr[0] != '\0' || isnan(value)) return REDIS_ERR;
+            if (eptr[0] != '\0' || errno == ERANGE || isnan(value))
+                return REDIS_ERR;
         } else if (o->encoding == REDIS_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
@@ -369,7 +386,45 @@ int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const ch
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
-            addReplyError(c,"value is not a double");
+            addReplyError(c,"value is not a valid float");
+        }
+        return REDIS_ERR;
+    }
+
+    *target = value;
+    return REDIS_OK;
+}
+
+int getLongDoubleFromObject(robj *o, long double *target) {
+    long double value;
+    char *eptr;
+
+    if (o == NULL) {
+        value = 0;
+    } else {
+        redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
+        if (o->encoding == REDIS_ENCODING_RAW) {
+            errno = 0;
+            value = strtold(o->ptr, &eptr);
+            if (eptr[0] != '\0' || errno == ERANGE || isnan(value))
+                return REDIS_ERR;
+        } else if (o->encoding == REDIS_ENCODING_INT) {
+            value = (long)o->ptr;
+        } else {
+            redisPanic("Unknown string encoding");
+        }
+    }
+    *target = value;
+    return REDIS_OK;
+}
+
+int getLongDoubleFromObjectOrReply(redisClient *c, robj *o, long double *target, const char *msg) {
+    long double value;
+    if (getLongDoubleFromObject(o, &value) != REDIS_OK) {
+        if (msg != NULL) {
+            addReplyError(c,(char*)msg);
+        } else {
+            addReplyError(c,"value is not a valid float");
         }
         return REDIS_ERR;
     }