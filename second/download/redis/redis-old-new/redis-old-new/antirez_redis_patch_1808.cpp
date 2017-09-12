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