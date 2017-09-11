@@ -351,9 +351,9 @@ int isObjectRepresentableAsLongLong(robj *o, long long *llval) {
     serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
     if (o->encoding == OBJ_ENCODING_INT) {
         if (llval) *llval = (long) o->ptr;
-        return REDIS_OK;
+        return C_OK;
     } else {
-        return string2ll(o->ptr,sdslen(o->ptr),llval) ? REDIS_OK : REDIS_ERR;
+        return string2ll(o->ptr,sdslen(o->ptr),llval) ? C_OK : C_ERR;
     }
 }
 
@@ -551,29 +551,29 @@ int getDoubleFromObject(robj *o, double *target) {
                     (value == HUGE_VAL || value == -HUGE_VAL || value == 0)) ||
                 errno == EINVAL ||
                 isnan(value))
-                return REDIS_ERR;
+                return C_ERR;
         } else if (o->encoding == OBJ_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
             redisPanic("Unknown string encoding");
         }
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg) {
     double value;
-    if (getDoubleFromObject(o, &value) != REDIS_OK) {
+    if (getDoubleFromObject(o, &value) != C_OK) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is not a valid float");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongDoubleFromObject(robj *o, long double *target) {
@@ -589,29 +589,29 @@ int getLongDoubleFromObject(robj *o, long double *target) {
             value = strtold(o->ptr, &eptr);
             if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' ||
                 errno == ERANGE || isnan(value))
-                return REDIS_ERR;
+                return C_ERR;
         } else if (o->encoding == OBJ_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
             redisPanic("Unknown string encoding");
         }
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongDoubleFromObjectOrReply(client *c, robj *o, long double *target, const char *msg) {
     long double value;
-    if (getLongDoubleFromObject(o, &value) != REDIS_OK) {
+    if (getLongDoubleFromObject(o, &value) != C_OK) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is not a valid float");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongLongFromObject(robj *o, long long *target) {
@@ -627,45 +627,45 @@ int getLongLongFromObject(robj *o, long long *target) {
             value = strtoll(o->ptr, &eptr, 10);
             if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' ||
                 errno == ERANGE)
-                return REDIS_ERR;
+                return C_ERR;
         } else if (o->encoding == OBJ_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
             redisPanic("Unknown string encoding");
         }
     }
     if (target) *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg) {
     long long value;
-    if (getLongLongFromObject(o, &value) != REDIS_OK) {
+    if (getLongLongFromObject(o, &value) != C_OK) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is not an integer or out of range");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg) {
     long long value;
 
-    if (getLongLongFromObjectOrReply(c, o, &value, msg) != REDIS_OK) return REDIS_ERR;
+    if (getLongLongFromObjectOrReply(c, o, &value, msg) != C_OK) return C_ERR;
     if (value < LONG_MIN || value > LONG_MAX) {
         if (msg != NULL) {
             addReplyError(c,(char*)msg);
         } else {
             addReplyError(c,"value is out of range");
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
     *target = value;
-    return REDIS_OK;
+    return C_OK;
 }
 
 char *strEncoding(int encoding) {