@@ -393,31 +393,26 @@ void decrbyCommand(redisClient *c) {
 }
 
 void appendCommand(redisClient *c) {
-    int retval;
     size_t totlen;
     robj *o, *append;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
-    c->argv[2] = tryObjectEncoding(c->argv[2]);
     if (o == NULL) {
         /* Create the key */
-        retval = dbAdd(c->db,c->argv[1],c->argv[2]);
+        c->argv[2] = tryObjectEncoding(c->argv[2]);
+        dbAdd(c->db,c->argv[1],c->argv[2]);
         incrRefCount(c->argv[2]);
         totlen = stringObjectLen(c->argv[2]);
     } else {
-        if (o->type != REDIS_STRING) {
-            addReply(c,shared.wrongtypeerr);
+        /* Key exists, check type */
+        if (checkType(c,o,REDIS_STRING))
             return;
-        }
 
-        append = getDecodedObject(c->argv[2]);
-        if (o->encoding == REDIS_ENCODING_RAW &&
-            (sdslen(o->ptr) + sdslen(append->ptr)) > 512*1024*1024)
-        {
-            addReplyError(c,"string exceeds maximum allowed size (512MB)");
-            decrRefCount(append);
+        /* "append" is an argument, so always an sds */
+        append = c->argv[2];
+        totlen = stringObjectLen(o)+sdslen(append->ptr);
+        if (checkStringLength(c,totlen) != REDIS_OK)
             return;
-        }
 
         /* If the object is shared or encoded, we have to make a copy */
         if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
@@ -429,7 +424,6 @@ void appendCommand(redisClient *c) {
 
         /* Append the value */
         o->ptr = sdscatlen(o->ptr,append->ptr,sdslen(append->ptr));
-        decrRefCount(append);
         totlen = sdslen(o->ptr);
     }
     touchWatchedKey(c->db,c->argv[1]);