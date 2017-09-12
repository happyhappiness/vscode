@@ -354,9 +354,9 @@ int getDoubleFromObjectOrReply(redisClient *c, robj *o, double *target, const ch
     double value;
     if (getDoubleFromObject(o, &value) != REDIS_OK) {
         if (msg != NULL) {
-            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+            addReplyError(c,(char*)msg);
         } else {
-            addReplySds(c, sdsnew("-ERR value is not a double\r\n"));
+            addReplyError(c,"value is not a double");
         }
         return REDIS_ERR;
     }
@@ -393,9 +393,9 @@ int getLongLongFromObjectOrReply(redisClient *c, robj *o, long long *target, con
     long long value;
     if (getLongLongFromObject(o, &value) != REDIS_OK) {
         if (msg != NULL) {
-            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+            addReplyError(c,(char*)msg);
         } else {
-            addReplySds(c, sdsnew("-ERR value is not an integer or out of range\r\n"));
+            addReplyError(c,"value is not an integer or out of range");
         }
         return REDIS_ERR;
     }
@@ -410,9 +410,9 @@ int getLongFromObjectOrReply(redisClient *c, robj *o, long *target, const char *
     if (getLongLongFromObjectOrReply(c, o, &value, msg) != REDIS_OK) return REDIS_ERR;
     if (value < LONG_MIN || value > LONG_MAX) {
         if (msg != NULL) {
-            addReplySds(c, sdscatprintf(sdsempty(), "-ERR %s\r\n", msg));
+            addReplyError(c,(char*)msg);
         } else {
-            addReplySds(c, sdsnew("-ERR value is out of range\r\n"));
+            addReplyError(c,"value is out of range");
         }
         return REDIS_ERR;
     }