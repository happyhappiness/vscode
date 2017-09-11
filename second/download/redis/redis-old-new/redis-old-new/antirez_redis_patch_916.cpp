@@ -55,9 +55,9 @@
  *
  * The representation used by Redis is the following:
  *
- * +--------+--------+--------+------//      //--+---------------------+
- * |11000000|22221111|33333322|55444444 ....     | 64 bit cardinality  |
- * +--------+--------+--------+------//      //--+---------------------+
+ * +--------+--------+--------+------//      //--+----------+------+-----+
+ * |11000000|22221111|33333322|55444444 ....     | uint64_t | HYLL | Ver |
+ * +--------+--------+--------+------//      //--+----------+------+-----+
  *
  * The 6 bits counters are encoded one after the other starting from the
  * LSB to the MSB, and using the next bytes as needed.
@@ -69,6 +69,10 @@
  * HLLADD operations don't modify the actual data structure and hence the
  * approximated cardinality).
  *
+ * After the cached cardinality there are 4 bytes of magic set to the
+ * string "HYLL", and a 4 bytes version field that is reserved for
+ * future uses and is currently set to 0.
+ *
  * When the most significant bit in the most significant byte of the cached
  * cardinality is set, it means that the data structure was modified and
  * we can't reuse the cached value that must be recomputed. */
@@ -80,7 +84,7 @@
 #define REDIS_HLL_REGISTER_MAX ((1<<REDIS_HLL_BITS)-1)
 /* Note: REDIS_HLL_SIZE define has a final "+8" since we store a 64 bit
  * integer at the end of the HyperLogLog structure to cache the cardinality. */
-#define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)+8
+#define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)+8+8
 
 /* =========================== Low level bit macros ========================= */
 
@@ -436,6 +440,22 @@ uint64_t hllCount(uint8_t *registers) {
 
 /* ========================== HyperLogLog commands ========================== */
 
+/* An HyperLogLog object is a string with space for 16k 6-bit integers,
+ * a cached 64 bit cardinality value, and a 4 byte "magic" and additional
+ * 4 bytes for version reserved for future use. */
+robj *createHLLObject(void) {
+    robj *o;
+    char *p;
+
+    /* Create a string of the right size filled with zero bytes.
+     * Note that the cached cardinality is set to 0 as a side effect
+     * that is exactly the cardinality of an empty HLL. */
+    o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
+    p = o->ptr;
+    memcpy(p+REDIS_HLL_SIZE-8,"HYLL",4);
+    return o;
+}
+
 /* PFADD var ele ele ele ... ele => :0 or :1 */
 void pfaddCommand(redisClient *c) {
     robj *o = lookupKeyWrite(c->db,c->argv[1]);
@@ -446,7 +466,7 @@ void pfaddCommand(redisClient *c) {
         /* Create the key with a string value of the exact length to
          * hold our HLL data structure. sdsnewlen() when NULL is passed
          * is guaranteed to return bytes initialized to zero. */
-        o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
+        o = createHLLObject();
         dbAdd(c->db,c->argv[1],o);
         updated++;
     } else {
@@ -478,7 +498,7 @@ void pfaddCommand(redisClient *c) {
         notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
         server.dirty++;
         /* Invalidate the cached cardinality. */
-        registers[REDIS_HLL_SIZE-1] |= (1<<7);
+        registers[REDIS_HLL_SIZE-9] |= (1<<7);
     }
     addReply(c, updated ? shared.cone : shared.czero);
 }
@@ -509,27 +529,27 @@ void pfcountCommand(redisClient *c) {
 
         /* Check if the cached cardinality is valid. */
         registers = o->ptr;
-        if ((registers[REDIS_HLL_SIZE-1] & (1<<7)) == 0) {
+        if ((registers[REDIS_HLL_SIZE-9] & (1<<7)) == 0) {
             /* Just return the cached value. */
-            card = (uint64_t)registers[REDIS_HLL_SIZE-8];
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-7] << 8;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-6] << 16;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-5] << 24;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-4] << 32;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-3] << 40;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-2] << 48;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-1] << 56;
+            card = (uint64_t)registers[REDIS_HLL_SIZE-16];
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-15] << 8;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-14] << 16;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-13] << 24;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-12] << 32;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-11] << 40;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-10] << 48;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-9] << 56;
         } else {
             /* Recompute it and update the cached value. */
             card = hllCount(registers);
-            registers[REDIS_HLL_SIZE-8] = card & 0xff;
-            registers[REDIS_HLL_SIZE-7] = (card >> 8) & 0xff;
-            registers[REDIS_HLL_SIZE-6] = (card >> 16) & 0xff;
-            registers[REDIS_HLL_SIZE-5] = (card >> 24) & 0xff;
-            registers[REDIS_HLL_SIZE-4] = (card >> 32) & 0xff;
-            registers[REDIS_HLL_SIZE-3] = (card >> 40) & 0xff;
-            registers[REDIS_HLL_SIZE-2] = (card >> 48) & 0xff;
-            registers[REDIS_HLL_SIZE-1] = (card >> 56) & 0xff;
+            registers[REDIS_HLL_SIZE-16] = card & 0xff;
+            registers[REDIS_HLL_SIZE-15] = (card >> 8) & 0xff;
+            registers[REDIS_HLL_SIZE-14] = (card >> 16) & 0xff;
+            registers[REDIS_HLL_SIZE-13] = (card >> 24) & 0xff;
+            registers[REDIS_HLL_SIZE-12] = (card >> 32) & 0xff;
+            registers[REDIS_HLL_SIZE-11] = (card >> 40) & 0xff;
+            registers[REDIS_HLL_SIZE-10] = (card >> 48) & 0xff;
+            registers[REDIS_HLL_SIZE-9] = (card >> 56) & 0xff;
             /* This is not considered a read-only command even if the
              * data structure is not modified, since the cached value
              * may be modified and given that the HLL is a Redis string
@@ -582,7 +602,7 @@ void pfmergeCommand(redisClient *c) {
         /* Create the key with a string value of the exact length to
          * hold our HLL data structure. sdsnewlen() when NULL is passed
          * is guaranteed to return bytes initialized to zero. */
-        o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
+        o = createHLLObject();
         dbAdd(c->db,c->argv[1],o);
     } else {
         /* If key exists we are sure it's of the right type/size
@@ -597,7 +617,7 @@ void pfmergeCommand(redisClient *c) {
     for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
         HLL_SET_REGISTER(registers,j,max[j]);
     }
-    registers[REDIS_HLL_SIZE-1] |= (1<<7);
+    registers[REDIS_HLL_SIZE-9] |= (1<<7);
 
     signalModifiedKey(c->db,c->argv[1]);
     /* We generate an HLLADD event for HLLMERGE for semantical simplicity