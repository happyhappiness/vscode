@@ -91,7 +91,7 @@ static int getBitOffsetFromArgument(redisClient *c, robj *o, size_t *offset) {
     /* Limit offset to SIZE_T_MAX or 1GB in bytes */
     if ((loffset < 0) ||
         ((unsigned long long)loffset >= (unsigned)SIZE_T_MAX) ||
-        ((unsigned long long)loffset >> 3) >= (1024*1024*1024))
+        ((unsigned long long)loffset >> 3) >= (512*1024*1024))
     {
         addReplyError(c,err);
         return REDIS_ERR;
@@ -263,7 +263,7 @@ void decrbyCommand(redisClient *c) {
 void appendCommand(redisClient *c) {
     int retval;
     size_t totlen;
-    robj *o;
+    robj *o, *append;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
     c->argv[2] = tryObjectEncoding(c->argv[2]);
@@ -277,23 +277,27 @@ void appendCommand(redisClient *c) {
             addReply(c,shared.wrongtypeerr);
             return;
         }
-        /* If the object is specially encoded or shared we have to make
-         * a copy */
+
+        append = getDecodedObject(c->argv[2]);
+        if (o->encoding == REDIS_ENCODING_RAW &&
+            (sdslen(o->ptr) + sdslen(append->ptr)) > 512*1024*1024)
+        {
+            addReplyError(c,"string exceeds maximum allowed size (512MB)");
+            decrRefCount(append);
+            return;
+        }
+
+        /* If the object is shared or encoded, we have to make a copy */
         if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
             robj *decoded = getDecodedObject(o);
-
             o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
             decrRefCount(decoded);
             dbReplace(c->db,c->argv[1],o);
         }
-        /* APPEND! */
-        if (c->argv[2]->encoding == REDIS_ENCODING_RAW) {
-            o->ptr = sdscatlen(o->ptr,
-                c->argv[2]->ptr, sdslen(c->argv[2]->ptr));
-        } else {
-            o->ptr = sdscatprintf(o->ptr, "%ld",
-                (unsigned long) c->argv[2]->ptr);
-        }
+
+        /* Append the value */
+        o->ptr = sdscatlen(o->ptr,append->ptr,sdslen(append->ptr));
+        decrRefCount(append);
         totlen = sdslen(o->ptr);
     }
     touchWatchedKey(c->db,c->argv[1]);