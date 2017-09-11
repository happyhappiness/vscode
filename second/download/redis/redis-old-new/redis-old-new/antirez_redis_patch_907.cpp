@@ -61,33 +61,42 @@
  *    for representing HyperLogLogs with many registers set to 0 in
  *    a memory efficient way.
  *
- * Dense representation
- * ===
  *
- * The dense representation used by Redis is the following:
+ * HLL header
+ * ===
  *
- * +--------+--------+--------+------//      //--+----------+------+-----+
- * |11000000|22221111|33333322|55444444 ....     | uint64_t | HYLL | Ver |
- * +--------+--------+--------+------//      //--+----------+------+-----+
+ * Both the dense and sparse representation have a 16 byte header as follows:
  *
- * The 6 bits counters are encoded one after the other starting from the
- * LSB to the MSB, and using the next bytes as needed.
+ * +------+---+-----+----------+
+ * | HYLL | E | N/U | Cardin.  |
+ * +------+---+-----+----------+
  *
- * At the end of the 16k counters, there is an additional 64 bit integer
- * stored in little endian format with the latest cardinality computed that
- * can be reused if the data structure was not modified since the last
- * computation (this is useful because there are high probabilities that
- * HLLADD operations don't modify the actual data structure and hence the
- * approximated cardinality).
+ * The first 4 bytes are a magic string set to the bytes "HYLL".
+ * "E" is one byte encoding, currently set to HLL_DENSE or
+ * HLL_SPARSE. N/U are three not used bytes.
  *
- * After the cached cardinality there are 4 bytes of magic set to the
- * string "HYLL", and a 4 bytes version field that is reserved for
- * future uses and is currently set to 0.
+ * The "Cardin." field is a 64 bit integer stored in little endian format
+ * with the latest cardinality computed that can be reused if the data
+ * structure was not modified since the last computation (this is useful
+ * because there are high probabilities that HLLADD operations don't
+ * modify the actual data structure and hence the approximated cardinality).
  *
  * When the most significant bit in the most significant byte of the cached
  * cardinality is set, it means that the data structure was modified and
  * we can't reuse the cached value that must be recomputed.
  *
+ * Dense representation
+ * ===
+ *
+ * The dense representation used by Redis is the following:
+ *
+ * +--------+--------+--------+------//      //--+
+ * |11000000|22221111|33333322|55444444 ....     |
+ * +--------+--------+--------+------//      //--+
+ *
+ * The 6 bits counters are encoded one after the other starting from the
+ * LSB to the MSB, and using the next bytes as needed.
+ *
  * Sparse representation
  * ===
  *
@@ -167,17 +176,31 @@
  * involved in updating the sparse representation is not justified by the
  * memory savings. The exact maximum length of the sparse representation
  * when this implementation switches to the dense representation is
- * configured via the define REDIS_HLL_SPARSE_MAX.
+ * configured via the define HLL_SPARSE_MAX.
  */
 
-#define REDIS_HLL_P 14 /* The greater is P, the smaller the error. */
-#define REDIS_HLL_REGISTERS (1<<REDIS_HLL_P) /* With P=14, 16384 registers. */
-#define REDIS_HLL_P_MASK (REDIS_HLL_REGISTERS-1) /* Mask to index register. */
-#define REDIS_HLL_BITS 6 /* Enough to count up to 63 leading zeroes. */
-#define REDIS_HLL_REGISTER_MAX ((1<<REDIS_HLL_BITS)-1)
-/* Note: REDIS_HLL_SIZE define has a final "+8" since we store a 64 bit
- * integer at the end of the HyperLogLog structure to cache the cardinality. */
-#define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)+8+8
+struct hllhdr {
+    char magic[4];      /* "HYLL" */
+    uint8_t encoding;   /* HLL_DENSE or HLL_SPARSE. */
+    uint8_t notused[3]; /* Reserved for future use, must be zero. */
+    uint8_t card[8];    /* Cached cardinality, little endian. */
+    uint8_t registers[]; /* Data bytes. */
+};
+
+/* The cached cardinality MSB is used to signal validity of the cached value. */
+#define HLL_INVALIDATE_CACHE(hdr) (hdr)->card[0] |= (1<<7)
+#define HLL_VALID_CACHE(hdr) (((hdr)->card[0] & (1<<7)) == 0)
+
+#define HLL_P 14 /* The greater is P, the smaller the error. */
+#define HLL_REGISTERS (1<<HLL_P) /* With P=14, 16384 registers. */
+#define HLL_P_MASK (HLL_REGISTERS-1) /* Mask to index register. */
+#define HLL_BITS 6 /* Enough to count up to 63 leading zeroes. */
+#define HLL_REGISTER_MAX ((1<<HLL_BITS)-1)
+#define HLL_HDR_SIZE sizeof(struct hllhdr)
+#define HLL_DENSE_SIZE (HLL_HDR_SIZE+((HLL_REGISTERS*HLL_BITS+7)/8))
+#define HLL_DENSE 0 /* Dense encoding */
+#define HLL_SPARSE 1 /* Sparse encoding */
+#define HLL_MAX_ENCODING 1
 
 /* =========================== Low level bit macros ========================= */
 
@@ -310,25 +333,25 @@
  * 'p' is an array of unsigned bytes. */
 #define HLL_GET_REGISTER(target,p,regnum) do { \
     uint8_t *_p = (uint8_t*) p; \
-    unsigned long _byte = regnum*REDIS_HLL_BITS/8; \
-    unsigned long _fb = regnum*REDIS_HLL_BITS&7; \
+    unsigned long _byte = regnum*HLL_BITS/8; \
+    unsigned long _fb = regnum*HLL_BITS&7; \
     unsigned long _fb8 = 8 - _fb; \
     unsigned long b0 = _p[_byte]; \
     unsigned long b1 = _p[_byte+1]; \
-    target = ((b0 >> _fb) | (b1 << _fb8)) & REDIS_HLL_REGISTER_MAX; \
+    target = ((b0 >> _fb) | (b1 << _fb8)) & HLL_REGISTER_MAX; \
 } while(0)
 
 /* Set the value of the register at position 'regnum' to 'val'.
  * 'p' is an array of unsigned bytes. */
 #define HLL_SET_REGISTER(p,regnum,val) do { \
     uint8_t *_p = (uint8_t*) p; \
-    unsigned long _byte = regnum*REDIS_HLL_BITS/8; \
-    unsigned long _fb = regnum*REDIS_HLL_BITS&7; \
+    unsigned long _byte = regnum*HLL_BITS/8; \
+    unsigned long _fb = regnum*HLL_BITS&7; \
     unsigned long _fb8 = 8 - _fb; \
     unsigned long _v = val; \
-    _p[_byte] &= ~(REDIS_HLL_REGISTER_MAX << _fb); \
+    _p[_byte] &= ~(HLL_REGISTER_MAX << _fb); \
     _p[_byte] |= _v << _fb; \
-    _p[_byte+1] &= ~(REDIS_HLL_REGISTER_MAX >> _fb8); \
+    _p[_byte+1] &= ~(HLL_REGISTER_MAX >> _fb8); \
     _p[_byte+1] |= _v >> _fb8; \
 } while(0)
 
@@ -399,7 +422,7 @@ uint64_t MurmurHash64A (const void * key, int len, unsigned int seed) {
  * Actually nothing is added, but the max 0 pattern counter of the subset
  * the element belongs to is incremented if needed.
  *
- * 'registers' is expected to have room for REDIS_HLL_REGISTERS plus an
+ * 'registers' is expected to have room for HLL_REGISTERS plus an
  * additional byte on the right. This requirement is met by sds strings
  * automatically since they are implicitly null terminated.
  *
@@ -410,7 +433,7 @@ int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
     uint64_t hash, bit, index;
     uint8_t oldcount, count;
 
-    /* Count the number of zeroes starting from bit REDIS_HLL_REGISTERS
+    /* Count the number of zeroes starting from bit HLL_REGISTERS
      * (that is a power of two corresponding to the first bit we don't use
      * as index). The max run can be 64-P+1 bits.
      *
@@ -423,15 +446,15 @@ int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
      * there are high probabilities to find a 1 after a few iterations. */
     hash = MurmurHash64A(ele,elesize,0xadc83b19ULL);
     hash |= ((uint64_t)1<<63); /* Make sure the loop terminates. */
-    bit = REDIS_HLL_REGISTERS; /* First bit not used to address the register. */
+    bit = HLL_REGISTERS; /* First bit not used to address the register. */
     count = 1; /* Initialized to 1 since we count the "00000...1" pattern. */
     while((hash & bit) == 0) {
         count++;
         bit <<= 1;
     }
 
     /* Update the register if this element produced a longer run of zeroes. */
-    index = hash & REDIS_HLL_P_MASK; /* Index a register inside registers. */
+    index = hash & HLL_P_MASK; /* Index a register inside registers. */
     HLL_GET_REGISTER(oldcount,registers,index);
     if (count > oldcount) {
         HLL_SET_REGISTER(registers,index,count);
@@ -444,7 +467,7 @@ int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
 /* Return the approximated cardinality of the set based on the armonic
  * mean of the registers values. */
 uint64_t hllCount(uint8_t *registers) {
-    double m = REDIS_HLL_REGISTERS;
+    double m = HLL_REGISTERS;
     double alpha = 0.7213/(1+1.079/m);
     double E = 0;
     int ez = 0; /* Number of registers equal to 0. */
@@ -467,7 +490,7 @@ uint64_t hllCount(uint8_t *registers) {
      * Redis default is to use 16384 registers 6 bits each. The code works
      * with other values by modifying the defines, but for our target value
      * we take a faster path with unrolled loops. */
-    if (REDIS_HLL_REGISTERS == 16384 && REDIS_HLL_BITS == 6) {
+    if (HLL_REGISTERS == 16384 && HLL_BITS == 6) {
         uint8_t *r = registers;
         unsigned long r0, r1, r2, r3, r4, r5, r6, r7, r8, r9,
                       r10, r11, r12, r13, r14, r15;
@@ -499,7 +522,7 @@ uint64_t hllCount(uint8_t *registers) {
             r += 12;
         }
     } else {
-        for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
+        for (j = 0; j < HLL_REGISTERS; j++) {
             unsigned long reg;
 
             HLL_GET_REGISTER(reg,registers,j);
@@ -552,35 +575,49 @@ robj *createHLLObject(void) {
     /* Create a string of the right size filled with zero bytes.
      * Note that the cached cardinality is set to 0 as a side effect
      * that is exactly the cardinality of an empty HLL. */
-    o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
+    o = createObject(REDIS_STRING,sdsnewlen(NULL,HLL_DENSE_SIZE));
     p = o->ptr;
-    memcpy(p+REDIS_HLL_SIZE-8,"HYLL",4);
+    memcpy(p,"HYLL",4);
     return o;
 }
 
-/* Check if the object is a String of REDIS_HLL_SIZE bytes.
+/* Check if the object is a String with a valid HLL representation.
  * Return REDIS_OK if this is true, otherwise reply to the client
  * with an error and return REDIS_ERR. */
 int isHLLObjectOrReply(redisClient *c, robj *o) {
+    struct hllhdr *hdr;
+
     /* Key exists, check type */
     if (checkType(c,o,REDIS_STRING))
         return REDIS_ERR; /* Error already sent. */
 
-    /* If this is a string representing an HLL, the size should match
-     * exactly. */
-    if (stringObjectLen(o) != REDIS_HLL_SIZE) {
-        addReplySds(c,
-            sdsnew("-WRONGTYPE Key is not a valid "
-                   "HyperLogLog string value.\r\n"));
-        return REDIS_ERR;
-    }
+    if (stringObjectLen(o) < sizeof(*hdr)) goto invalid;
+    hdr = o->ptr;
+
+    /* Magic should be "HYLL". */
+    if (hdr->magic[0] != 'H' || hdr->magic[1] != 'Y' ||
+        hdr->magic[2] != 'L' || hdr->magic[3] != 'L') goto invalid;
+
+    if (hdr->encoding > HLL_MAX_ENCODING) goto invalid;
+
+    /* Dense representation string length should match exactly. */
+    if (hdr->encoding == HLL_DENSE &&
+        stringObjectLen(o) != HLL_DENSE_SIZE) goto invalid;
+
+    /* All tests passed. */
     return REDIS_OK;
+
+invalid:
+    addReplySds(c,
+        sdsnew("-WRONGTYPE Key is not a valid "
+               "HyperLogLog string value.\r\n"));
+    return REDIS_ERR;
 }
 
 /* PFADD var ele ele ele ... ele => :0 or :1 */
 void pfaddCommand(redisClient *c) {
     robj *o = lookupKeyWrite(c->db,c->argv[1]);
-    uint8_t *registers;
+    struct hllhdr *hdr;
     int updated = 0, j;
 
     if (o == NULL) {
@@ -595,9 +632,9 @@ void pfaddCommand(redisClient *c) {
         o = dbUnshareStringValue(c->db,c->argv[1],o);
     }
     /* Perform the low level ADD operation for every element. */
-    registers = o->ptr;
+    hdr = o->ptr;
     for (j = 2; j < c->argc; j++) {
-        if (hllAdd(registers, (unsigned char*)c->argv[j]->ptr,
+        if (hllAdd(hdr->registers, (unsigned char*)c->argv[j]->ptr,
                 sdslen(c->argv[j]->ptr)))
         {
             updated++;
@@ -607,16 +644,15 @@ void pfaddCommand(redisClient *c) {
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
         server.dirty++;
-        /* Invalidate the cached cardinality. */
-        registers[REDIS_HLL_SIZE-9] |= (1<<7);
+        HLL_INVALIDATE_CACHE(hdr);
     }
     addReply(c, updated ? shared.cone : shared.czero);
 }
 
 /* PFCOUNT var -> approximated cardinality of set. */
 void pfcountCommand(redisClient *c) {
     robj *o = lookupKeyRead(c->db,c->argv[1]);
-    uint8_t *registers;
+    struct hllhdr *hdr;
     uint64_t card;
 
     if (o == NULL) {
@@ -628,28 +664,28 @@ void pfcountCommand(redisClient *c) {
         o = dbUnshareStringValue(c->db,c->argv[1],o);
 
         /* Check if the cached cardinality is valid. */
-        registers = o->ptr;
-        if ((registers[REDIS_HLL_SIZE-9] & (1<<7)) == 0) {
+        hdr = o->ptr;
+        if (HLL_VALID_CACHE(hdr)) {
             /* Just return the cached value. */
-            card = (uint64_t)registers[REDIS_HLL_SIZE-16];
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-15] << 8;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-14] << 16;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-13] << 24;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-12] << 32;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-11] << 40;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-10] << 48;
-            card |= (uint64_t)registers[REDIS_HLL_SIZE-9] << 56;
+            card = (uint64_t)hdr->card[0];
+            card |= (uint64_t)hdr->card[1] << 8;
+            card |= (uint64_t)hdr->card[2] << 16;
+            card |= (uint64_t)hdr->card[3] << 24;
+            card |= (uint64_t)hdr->card[4] << 32;
+            card |= (uint64_t)hdr->card[5] << 40;
+            card |= (uint64_t)hdr->card[6] << 48;
+            card |= (uint64_t)hdr->card[7] << 56;
         } else {
             /* Recompute it and update the cached value. */
-            card = hllCount(registers);
-            registers[REDIS_HLL_SIZE-16] = card & 0xff;
-            registers[REDIS_HLL_SIZE-15] = (card >> 8) & 0xff;
-            registers[REDIS_HLL_SIZE-14] = (card >> 16) & 0xff;
-            registers[REDIS_HLL_SIZE-13] = (card >> 24) & 0xff;
-            registers[REDIS_HLL_SIZE-12] = (card >> 32) & 0xff;
-            registers[REDIS_HLL_SIZE-11] = (card >> 40) & 0xff;
-            registers[REDIS_HLL_SIZE-10] = (card >> 48) & 0xff;
-            registers[REDIS_HLL_SIZE-9] = (card >> 56) & 0xff;
+            card = hllCount(hdr->registers);
+            hdr->card[0] = card & 0xff;
+            hdr->card[1] = (card >> 8) & 0xff;
+            hdr->card[2] = (card >> 16) & 0xff;
+            hdr->card[3] = (card >> 24) & 0xff;
+            hdr->card[4] = (card >> 32) & 0xff;
+            hdr->card[5] = (card >> 40) & 0xff;
+            hdr->card[6] = (card >> 48) & 0xff;
+            hdr->card[7] = (card >> 56) & 0xff;
             /* This is not considered a read-only command even if the
              * data structure is not modified, since the cached value
              * may be modified and given that the HLL is a Redis string
@@ -663,8 +699,8 @@ void pfcountCommand(redisClient *c) {
 
 /* PFMERGE dest src1 src2 src3 ... srcN => OK */
 void pfmergeCommand(redisClient *c) {
-    uint8_t max[REDIS_HLL_REGISTERS];
-    uint8_t *registers;
+    uint8_t max[HLL_REGISTERS];
+    struct hllhdr *hdr;
     int j, i;
 
     /* Compute an HLL with M[i] = MAX(M[i]_j).
@@ -681,9 +717,9 @@ void pfmergeCommand(redisClient *c) {
 
         /* Merge with this HLL with our 'max' HHL by setting max[i]
          * to MAX(max[i],hll[i]). */
-        registers = o->ptr;
-        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
-            HLL_GET_REGISTER(val,registers,i);
+        hdr = o->ptr;
+        for (i = 0; i < HLL_REGISTERS; i++) {
+            HLL_GET_REGISTER(val,hdr->registers,i);
             if (val > max[i]) max[i] = val;
         }
     }
@@ -705,11 +741,11 @@ void pfmergeCommand(redisClient *c) {
 
     /* Write the resulting HLL to the destination HLL registers and
      * invalidate the cached value. */
-    registers = o->ptr;
-    for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
-        HLL_SET_REGISTER(registers,j,max[j]);
+    hdr = o->ptr;
+    for (j = 0; j < HLL_REGISTERS; j++) {
+        HLL_SET_REGISTER(hdr->registers,j,max[j]);
     }
-    registers[REDIS_HLL_SIZE-9] |= (1<<7);
+    HLL_INVALIDATE_CACHE(hdr);
 
     signalModifiedKey(c->db,c->argv[1]);
     /* We generate an HLLADD event for HLLMERGE for semantical simplicity
@@ -724,27 +760,27 @@ void pfmergeCommand(redisClient *c) {
 /* PFSELFTEST
  * This command performs a self-test of the HLL registers implementation.
  * Something that is not easy to test from within the outside. */
-#define REDIS_HLL_TEST_CYCLES 1000
+#define HLL_TEST_CYCLES 1000
 void pfselftestCommand(redisClient *c) {
     int j, i;
-    sds bitcounters = sdsnewlen(NULL,REDIS_HLL_SIZE);
-    uint8_t bytecounters[REDIS_HLL_REGISTERS];
+    sds bitcounters = sdsnewlen(NULL,HLL_DENSE_SIZE);
+    uint8_t bytecounters[HLL_REGISTERS];
 
     /* Test 1: access registers.
      * The test is conceived to test that the different counters of our data
      * structure are accessible and that setting their values both result in
      * the correct value to be retained and not affect adjacent values. */
-    for (j = 0; j < REDIS_HLL_TEST_CYCLES; j++) {
+    for (j = 0; j < HLL_TEST_CYCLES; j++) {
         /* Set the HLL counters and an array of unsigned byes of the
          * same size to the same set of random values. */
-        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
-            unsigned int r = rand() & REDIS_HLL_REGISTER_MAX;
+        for (i = 0; i < HLL_REGISTERS; i++) {
+            unsigned int r = rand() & HLL_REGISTER_MAX;
 
             bytecounters[i] = r;
             HLL_SET_REGISTER(bitcounters,i,r);
         }
         /* Check that we are able to retrieve the same values. */
-        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
+        for (i = 0; i < HLL_REGISTERS; i++) {
             unsigned int val;
 
             HLL_GET_REGISTER(val,bitcounters,i);
@@ -764,8 +800,8 @@ void pfselftestCommand(redisClient *c) {
      * We check that the error is smaller than 4 times than the expected
      * standard error, to make it very unlikely for the test to fail because
      * of a "bad" run. */
-    memset(bitcounters,0,REDIS_HLL_SIZE);
-    double relerr = 1.04/sqrt(REDIS_HLL_REGISTERS);
+    memset(bitcounters,0,HLL_DENSE_SIZE);
+    double relerr = 1.04/sqrt(HLL_REGISTERS);
     int64_t checkpoint = 1000;
     uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
     uint64_t ele;
@@ -798,7 +834,7 @@ void pfselftestCommand(redisClient *c) {
  * Return the registers values of the specified HLL. */
 void pfgetregCommand(redisClient *c) {
     robj *o = lookupKeyRead(c->db,c->argv[1]);
-    uint8_t *registers;
+    struct hllhdr *hdr;
     int j;
 
     if (o == NULL) {
@@ -807,12 +843,12 @@ void pfgetregCommand(redisClient *c) {
     } else {
         if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
 
-        registers = o->ptr;
-        addReplyMultiBulkLen(c,REDIS_HLL_REGISTERS);
-        for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
+        hdr = o->ptr;
+        addReplyMultiBulkLen(c,HLL_REGISTERS);
+        for (j = 0; j < HLL_REGISTERS; j++) {
             uint8_t val;
 
-            HLL_GET_REGISTER(val,registers,j);
+            HLL_GET_REGISTER(val,hdr->registers,j);
             addReplyLongLong(c,val);
         }
     }