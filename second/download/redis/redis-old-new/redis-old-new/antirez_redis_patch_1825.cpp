@@ -1,3 +1,4 @@
+#include <limits.h>
 #include "redis.h"
 
 /*-----------------------------------------------------------------------------
@@ -80,6 +81,87 @@ void getsetCommand(redisClient *c) {
     removeExpire(c->db,c->argv[1]);
 }
 
+static int getBitOffsetFromArgument(redisClient *c, robj *o, size_t *offset) {
+    long long loffset;
+    char *err = "bit offset is not an integer or out of range";
+
+    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != REDIS_OK)
+        return REDIS_ERR;
+
+    /* Limit offset to SIZE_T_MAX or 1GB in bytes */
+    if ((loffset < 0) ||
+        ((unsigned long long)loffset >= (unsigned)SIZE_T_MAX) ||
+        ((unsigned long long)loffset >> 3) >= (1024*1024*1024))
+    {
+        addReplyError(c,err);
+        return REDIS_ERR;
+    }
+
+    *offset = (size_t)loffset;
+    return REDIS_OK;
+}
+
+void setbitCommand(redisClient *c) {
+    robj *o;
+    size_t bitoffset;
+    int on;
+
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
+        return;
+
+    on = ((sds)c->argv[3]->ptr)[0] - '0';
+    if (sdslen(c->argv[3]->ptr) != 1 || (on & ~1)) {
+        addReplyError(c,"bit should be 0 or 1");
+        return;
+    }
+
+    o = lookupKeyWrite(c->db,c->argv[1]);
+    if (o == NULL) {
+        sds value = sdssetbit(sdsempty(),bitoffset,on);
+        o = createObject(REDIS_STRING,value);
+        dbAdd(c->db,c->argv[1],o);
+    } else {
+        if (checkType(c,o,REDIS_STRING)) return;
+
+        /* Create a copy when the object is shared or encoded. */
+        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
+            robj *decoded = getDecodedObject(o);
+            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
+            decrRefCount(decoded);
+            dbReplace(c->db,c->argv[1],o);
+        }
+
+        o->ptr = sdssetbit(o->ptr,bitoffset,on);
+    }
+    touchWatchedKey(c->db,c->argv[1]);
+    server.dirty++;
+    addReply(c,shared.cone);
+}
+
+void getbitCommand(redisClient *c) {
+    robj *o;
+    size_t bitoffset, byte, bitmask;
+    int on = 0;
+    char llbuf[32];
+
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
+        return;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_STRING)) return;
+
+    byte = bitoffset >> 3;
+    bitmask = 1 << (7 - (bitoffset & 0x7));
+    if (o->encoding != REDIS_ENCODING_RAW) {
+        if (byte < (size_t)ll2string(llbuf,sizeof(llbuf),(long)o->ptr))
+            on = llbuf[byte] & bitmask;
+    } else {
+        if (byte < sdslen(o->ptr))
+            on = ((sds)o->ptr)[byte] & bitmask;
+    }
+    addReply(c, on ? shared.cone : shared.czero);
+}
+
 void mgetCommand(redisClient *c) {
     int j;
 