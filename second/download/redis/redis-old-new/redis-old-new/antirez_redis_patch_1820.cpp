@@ -103,22 +103,26 @@ static int getBitOffsetFromArgument(redisClient *c, robj *o, size_t *offset) {
 
 void setbitCommand(redisClient *c) {
     robj *o;
+    char *err = "bit is not an integer or out of range";
     size_t bitoffset;
-    int on;
+    long long bitvalue;
+    int byte, bit, on;
 
     if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
         return;
 
-    on = ((sds)c->argv[3]->ptr)[0] - '0';
-    if (sdslen(c->argv[3]->ptr) != 1 || (on & ~1)) {
-        addReplyError(c,"bit should be 0 or 1");
+    if (getLongLongFromObjectOrReply(c,c->argv[3],&bitvalue,err) != REDIS_OK)
+        return;
+
+    /* A bit can only be set to be on or off... */
+    if (bitvalue & ~1) {
+        addReplyError(c,err);
         return;
     }
 
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
-        sds value = sdssetbit(sdsempty(),bitoffset,on);
-        o = createObject(REDIS_STRING,value);
+        o = createObject(REDIS_STRING,sdsempty());
         dbAdd(c->db,c->argv[1],o);
     } else {
         if (checkType(c,o,REDIS_STRING)) return;
@@ -130,9 +134,15 @@ void setbitCommand(redisClient *c) {
             decrRefCount(decoded);
             dbReplace(c->db,c->argv[1],o);
         }
-
-        o->ptr = sdssetbit(o->ptr,bitoffset,on);
     }
+
+    byte = bitoffset >> 3;
+    bit = 7 - (bitoffset & 0x7);
+    on = bitvalue & 0x1;
+    o->ptr = sdsgrowsafe(o->ptr,byte+1);
+    ((char*)o->ptr)[byte] |= on << bit;
+    ((char*)o->ptr)[byte] &= ~((!on) << bit);
+
     touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.cone);