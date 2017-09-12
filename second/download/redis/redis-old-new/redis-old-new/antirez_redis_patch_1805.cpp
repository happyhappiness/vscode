@@ -111,17 +111,18 @@ void setbitCommand(redisClient *c) {
     robj *o;
     char *err = "bit is not an integer or out of range";
     size_t bitoffset;
-    long long bitvalue;
-    int byte, bit, on;
+    int byte, bit;
+    int byteval, bitval;
+    long on;
 
     if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
         return;
 
-    if (getLongLongFromObjectOrReply(c,c->argv[3],&bitvalue,err) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != REDIS_OK)
         return;
 
-    /* A bit can only be set to be on or off... */
-    if (bitvalue & ~1) {
+    /* Bits can only be set or cleared... */
+    if (on & ~1) {
         addReplyError(c,err);
         return;
     }
@@ -142,23 +143,30 @@ void setbitCommand(redisClient *c) {
         }
     }
 
+    /* Grow sds value to the right length if necessary */
     byte = bitoffset >> 3;
-    bit = 7 - (bitoffset & 0x7);
-    on = bitvalue & 0x1;
     o->ptr = sdsgrowzero(o->ptr,byte+1);
-    ((char*)o->ptr)[byte] |= on << bit;
-    ((char*)o->ptr)[byte] &= ~((!on) << bit);
 
+    /* Get current values */
+    byteval = ((char*)o->ptr)[byte];
+    bit = 7 - (bitoffset & 0x7);
+    bitval = byteval & (1 << bit);
+
+    /* Update byte with new bit value and return original value */
+    byteval &= ~(1 << bit);
+    byteval |= ((on & 0x1) << bit);
+    ((char*)o->ptr)[byte] = byteval;
     touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
-    addReply(c,shared.cone);
+    addReply(c, bitval ? shared.cone : shared.czero);
 }
 
 void getbitCommand(redisClient *c) {
     robj *o;
-    size_t bitoffset, byte, bitmask;
-    int on = 0;
     char llbuf[32];
+    size_t bitoffset;
+    size_t byte, bit;
+    size_t bitval = 0;
 
     if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
         return;
@@ -167,15 +175,16 @@ void getbitCommand(redisClient *c) {
         checkType(c,o,REDIS_STRING)) return;
 
     byte = bitoffset >> 3;
-    bitmask = 1 << (7 - (bitoffset & 0x7));
+    bit = 7 - (bitoffset & 0x7);
     if (o->encoding != REDIS_ENCODING_RAW) {
         if (byte < (size_t)ll2string(llbuf,sizeof(llbuf),(long)o->ptr))
-            on = llbuf[byte] & bitmask;
+            bitval = llbuf[byte] & (1 << bit);
     } else {
         if (byte < sdslen(o->ptr))
-            on = ((sds)o->ptr)[byte] & bitmask;
+            bitval = ((char*)o->ptr)[byte] & (1 << bit);
     }
-    addReply(c, on ? shared.cone : shared.czero);
+
+    addReply(c, bitval ? shared.cone : shared.czero);
 }
 
 void setrangeCommand(redisClient *c) {
@@ -186,11 +195,13 @@ void setrangeCommand(redisClient *c) {
     if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
         return;
 
+    if (offset < 0) {
+        addReplyError(c,"offset is out of range");
+        return;
+    }
+
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
-        /* Negative offset is always 0 for non-existing keys */
-        if (offset < 0) offset = 0;
-
         /* Return 0 when setting nothing on a non-existing string */
         if (sdslen(value) == 0) {
             addReply(c,shared.czero);
@@ -204,35 +215,19 @@ void setrangeCommand(redisClient *c) {
         o = createObject(REDIS_STRING,sdsempty());
         dbAdd(c->db,c->argv[1],o);
     } else {
-        int olen;
+        size_t olen;
 
         /* Key exists, check type */
         if (checkType(c,o,REDIS_STRING))
             return;
 
-        /* Find out existing value length */
-        if (o->encoding == REDIS_ENCODING_INT) {
-            char llbuf[32];
-            olen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
-        } else {
-            olen = sdslen(o->ptr);
-        }
-
         /* Return existing string length when setting nothing */
+        olen = stringObjectLen(o);
         if (sdslen(value) == 0) {
             addReplyLongLong(c,olen);
             return;
         }
 
-        /* Convert negative indexes. Note that for SETRANGE, the meaning of a
-         * negative index is a little different than for other commands.
-         * Here, an offset of -1 points to the trailing NULL byte of the
-         * string instead of the last character. */
-        if (offset < 0) {
-            offset = olen+1+offset;
-            if (offset < 0) offset = 0;
-        }
-
         /* Return when the resulting string exceeds allowed size */
         if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
             return;
@@ -391,31 +386,26 @@ void decrbyCommand(redisClient *c) {
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
@@ -427,7 +417,6 @@ void appendCommand(redisClient *c) {
 
         /* Append the value */
         o->ptr = sdscatlen(o->ptr,append->ptr,sdslen(append->ptr));
-        decrRefCount(append);
         totlen = sdslen(o->ptr);
     }
     touchWatchedKey(c->db,c->argv[1]);
@@ -437,18 +426,8 @@ void appendCommand(redisClient *c) {
 
 void strlenCommand(redisClient *c) {
     robj *o;
-
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_STRING)) return;
-
-    if (o->encoding == REDIS_ENCODING_RAW) {
-        addReplyLongLong(c,sdslen(o->ptr));
-    } else if (o->encoding == REDIS_ENCODING_INT) {
-        char llbuf[32];
-        int len = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
-        addReplyLongLong(c,len);
-    } else {
-        redisPanic("Unknown string encoding");
-    }
+    addReplyLongLong(c,stringObjectLen(o));
 }
 