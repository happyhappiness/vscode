@@ -5,6 +5,14 @@
  * String Commands
  *----------------------------------------------------------------------------*/
 
+static int checkStringLength(redisClient *c, long long size) {
+    if (size > 512*1024*1024) {
+        addReplyError(c,"string exceeds maximum allowed size (512MB)");
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire) {
     int retval;
     long seconds = 0; /* initialized to avoid an harmness warning */
@@ -172,6 +180,83 @@ void getbitCommand(redisClient *c) {
     addReply(c, on ? shared.cone : shared.czero);
 }
 
+void setrangeCommand(redisClient *c) {
+    robj *o;
+    long offset;
+    sds value = c->argv[3]->ptr;
+
+    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
+        return;
+
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
+        /* Negative offset is always 0 for non-existing keys */
+        if (offset < 0) offset = 0;
+
+        /* Return 0 when setting nothing on a non-existing string */
+        if (sdslen(value) == 0) {
+            addReply(c,shared.czero);
+            return;
+        }
+
+        /* Return when the resulting string exceeds allowed size */
+        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
+            return;
+
+        o = createObject(REDIS_STRING,sdsempty());
+        dbAdd(c->db,c->argv[1],o);
+    } else {
+        int olen;
+
+        /* Key exists, check type */
+        if (checkType(c,o,REDIS_STRING))
+            return;
+
+        /* Find out existing value length */
+        if (o->encoding == REDIS_ENCODING_INT) {
+            char llbuf[32];
+            olen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
+        } else {
+            olen = sdslen(o->ptr);
+        }
+
+        /* Return existing string length when setting nothing */
+        if (sdslen(value) == 0) {
+            addReplyLongLong(c,olen);
+            return;
+        }
+
+        /* Convert negative indexes. Note that for SETRANGE, the meaning of a
+         * negative index is a little different than for other commands.
+         * Here, an offset of -1 points to the trailing NULL byte of the
+         * string instead of the last character. */
+        if (offset < 0) {
+            offset = olen+1+offset;
+            if (offset < 0) offset = 0;
+        }
+
+        /* Return when the resulting string exceeds allowed size */
+        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
+            return;
+
+        /* Create a copy when the object is shared or encoded. */
+        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
+            robj *decoded = getDecodedObject(o);
+            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
+            decrRefCount(decoded);
+            dbReplace(c->db,c->argv[1],o);
+        }
+    }
+
+    if (sdslen(value) > 0) {
+        o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
+        memcpy((char*)o->ptr+offset,value,sdslen(value));
+        touchWatchedKey(c->db,c->argv[1]);
+        server.dirty++;
+    }
+    addReplyLongLong(c,sdslen(o->ptr));
+}
+
 void mgetCommand(redisClient *c) {
     int j;
 