@@ -51,14 +51,35 @@
  *
  * [2] P. Flajolet, Éric Fusy, O. Gandouet, and F. Meunier. Hyperloglog: The
  *     analysis of a near-optimal cardinality estimation algorithm.
- */
+ *
+ * The representation used by Redis is the following:
+ *
+ * +--------+--------+--------+------//      //--+---------------------+
+ * |11000000|22221111|33333322|55444444 ....     | 64 bit cardinality  |
+ * +--------+--------+--------+------//      //--+---------------------+
+ *
+ * The 6 bits counters are encoded one after the other starting from the
+ * LSB to the MSB, and using the next bytes as needed.
+ *
+ * At the end of the 16k counters, there is an additional 64 bit integer
+ * stored in little endian format with the latest cardinality computed that
+ * can be reused if the data structure was not modified since the last
+ * computation (this is useful because there are high probabilities that
+ * HLLADD operations don't modify the actual data structure and hence the
+ * approximated cardinality).
+ *
+ * When the most significant bit in the most significant byte of the cached
+ * cardinality is set, it means that the data structure was modified and
+ * we can't reuse the cached value that must be recomputed. */
 
 #define REDIS_HLL_P 14 /* The greater is P, the smaller the error. */
 #define REDIS_HLL_REGISTERS (1<<REDIS_HLL_P) /* With P=14, 16384 registers. */
 #define REDIS_HLL_P_MASK (REDIS_HLL_REGISTERS-1) /* Mask to index register. */
 #define REDIS_HLL_BITS 6 /* Enough to count up to 63 leading zeroes. */
 #define REDIS_HLL_REGISTER_MAX ((1<<REDIS_HLL_BITS)-1)
-#define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)
+/* Note: REDIS_HLL_SIZE define has a final "+8" since we store a 64 bit
+ * integer at the end of the HyperLogLog structure to cache the cardinality. */
+#define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)+8
 
 /* =========================== Low level bit macros ========================= */
 
@@ -439,6 +460,8 @@ void hllAddCommand(redisClient *c) {
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
         server.dirty++;
+        /* Invalidate the cached cardinality. */
+        registers[REDIS_HLL_SIZE-1] |= (1<<7);
     }
     addReply(c, updated ? shared.cone : shared.czero);
 }
@@ -447,6 +470,7 @@ void hllAddCommand(redisClient *c) {
 void hllCountCommand(redisClient *c) {
     robj *o = lookupKeyRead(c->db,c->argv[1]);
     uint8_t *registers;
+    uint64_t card;
 
     if (o == NULL) {
         /* No key? Cardinality is zero since no element was added, otherwise
@@ -465,8 +489,32 @@ void hllCountCommand(redisClient *c) {
                 REDIS_HLL_SIZE);
             return;
         }
+
+        /* Check if the cached cardinality is valid. */
         registers = o->ptr;
-        addReplyLongLong(c,hllCount(registers));
+        if ((registers[REDIS_HLL_SIZE-1] & (1<<7)) == 0) {
+            /* Just return the cached value. */
+            card = (uint64_t)registers[REDIS_HLL_SIZE-8];
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-7] << 8;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-6] << 16;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-5] << 24;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-4] << 32;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-3] << 40;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-2] << 48;
+            card |= (uint64_t)registers[REDIS_HLL_SIZE-1] << 56;
+        } else {
+            /* Recompute it and update the cached value. */
+            card = hllCount(registers);
+            registers[REDIS_HLL_SIZE-8] = card & 0xff;
+            registers[REDIS_HLL_SIZE-7] = (card >> 8) & 0xff;
+            registers[REDIS_HLL_SIZE-6] = (card >> 16) & 0xff;
+            registers[REDIS_HLL_SIZE-5] = (card >> 24) & 0xff;
+            registers[REDIS_HLL_SIZE-4] = (card >> 32) & 0xff;
+            registers[REDIS_HLL_SIZE-3] = (card >> 40) & 0xff;
+            registers[REDIS_HLL_SIZE-2] = (card >> 48) & 0xff;
+            registers[REDIS_HLL_SIZE-1] = (card >> 56) & 0xff;
+        }
+        addReplyLongLong(c,card);
     }
 }
 