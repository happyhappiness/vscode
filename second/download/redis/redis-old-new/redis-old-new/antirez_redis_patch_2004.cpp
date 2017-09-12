@@ -358,6 +358,8 @@ int getLongLongFromObject(robj *o, long long *target) {
         if (o->encoding == REDIS_ENCODING_RAW) {
             value = strtoll(o->ptr, &eptr, 10);
             if (eptr[0] != '\0') return REDIS_ERR;
+            if (errno == ERANGE && (value == LLONG_MIN || value == LLONG_MAX))
+                return REDIS_ERR;
         } else if (o->encoding == REDIS_ENCODING_INT) {
             value = (long)o->ptr;
         } else {
@@ -375,7 +377,7 @@ int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, con
         if (msg != NULL) {
             addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
         } else {
-            addReplySds(c, sdsnew("-ERR value is not an integer\r\n"));
+            addReplySds(c, sdsnew("-ERR value is not an integer or out of range\r\n"));
         }
         return REDIS_ERR;
     }