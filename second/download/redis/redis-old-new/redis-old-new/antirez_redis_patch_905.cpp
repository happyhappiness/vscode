@@ -445,11 +445,13 @@ int hllPatLen(unsigned char *ele, size_t elesize, int *regp) {
         count++;
         bit <<= 1;
     }
-    if (regp) *regp = (int) index;
+    *regp = (int) index;
     return count;
 }
 
-/* "Add" the element in the hyperloglog data structure.
+/* ================== Dense representation implementation  ================== */
+
+/* "Add" the element in the dense hyperloglog data structure.
  * Actually nothing is added, but the max 0 pattern counter of the subset
  * the element belongs to is incremented if needed.
  *
@@ -460,7 +462,7 @@ int hllPatLen(unsigned char *ele, size_t elesize, int *regp) {
  * The function always succeed, however if as a result of the operation
  * the approximated cardinality changed, 1 is returned. Otherwise 0
  * is returned. */
-int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
+int hllDenseAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
     uint8_t oldcount, count;
     int index;
 
@@ -475,30 +477,15 @@ int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
     }
 }
 
-/* Return the approximated cardinality of the set based on the armonic
- * mean of the registers values. */
-uint64_t hllCount(uint8_t *registers) {
-    double m = HLL_REGISTERS;
-    double alpha = 0.7213/(1+1.079/m);
+/* Compute SUM(2^-reg) in the dense representation.
+ * PE is an array with a pre-computer table of values 2^-reg indexed by reg.
+ * As a side effect the integer pointed by 'ezp' is set to the number
+ * of zero registers. */
+double hllDenseSum(uint8_t *registers, double *PE, int *ezp) {
     double E = 0;
-    int ez = 0; /* Number of registers equal to 0. */
-    int j;
+    int j, ez = 0;
 
-    /* We precompute 2^(-reg[j]) in a small table in order to
-     * speedup the computation of SUM(2^-register[0..i]). */
-    static int initialized = 0;
-    static double PE[64];
-    if (!initialized) {
-        PE[0] = 1; /* 2^(-reg[j]) is 1 when m is 0. */
-        for (j = 1; j < 64; j++) {
-            /* 2^(-reg[j]) is the same as 1/2^reg[j]. */
-            PE[j] = 1.0/(1ULL << j);
-        }
-        initialized = 1;
-    }
-
-    /* Compute SUM(2^-register[0..i]).
-     * Redis default is to use 16384 registers 6 bits each. The code works
+    /* Redis default is to use 16384 registers 6 bits each. The code works
      * with other values by modifying the defines, but for our target value
      * we take a faster path with unrolled loops. */
     if (HLL_REGISTERS == 16384 && HLL_BITS == 6) {
@@ -545,6 +532,47 @@ uint64_t hllCount(uint8_t *registers) {
             }
         }
     }
+    *ezp = ez;
+    return E;
+}
+
+/* ================== Sparse representation implementation  ================= */
+
+/* ========================= HyperLogLog Count ==============================
+ * This is the core of the algorithm where the approximated count is computed.
+ * The function uses the lower level hllDenseSum() and hllSparseSum() functions
+ * as helpers to compute the SUM(2^-reg) part of the computation, which is
+ * representation-specific, while all the rest is common. */
+
+/* Return the approximated cardinality of the set based on the armonic
+ * mean of the registers values. */
+uint64_t hllCount(struct hllhdr *hdr) {
+    double m = HLL_REGISTERS;
+    double alpha = 0.7213/(1+1.079/m);
+    double E;
+    int ez; /* Number of registers equal to 0. */
+    int j;
+
+    /* We precompute 2^(-reg[j]) in a small table in order to
+     * speedup the computation of SUM(2^-register[0..i]). */
+    static int initialized = 0;
+    static double PE[64];
+    if (!initialized) {
+        PE[0] = 1; /* 2^(-reg[j]) is 1 when m is 0. */
+        for (j = 1; j < 64; j++) {
+            /* 2^(-reg[j]) is the same as 1/2^reg[j]. */
+            PE[j] = 1.0/(1ULL << j);
+        }
+        initialized = 1;
+    }
+
+    /* Compute SUM(2^-register[0..i]). */
+    if (hdr->encoding == HLL_DENSE) {
+        E = hllDenseSum(hdr->registers,PE,&ez);
+    } else {
+        E = 0; /* FIXME */
+    }
+
     /* Muliply the inverse of E for alpha_m * m^2 to have the raw estimate. */
     E = (1/E)*alpha*m*m;
 
@@ -645,8 +673,8 @@ void pfaddCommand(redisClient *c) {
     /* Perform the low level ADD operation for every element. */
     hdr = o->ptr;
     for (j = 2; j < c->argc; j++) {
-        if (hllAdd(hdr->registers, (unsigned char*)c->argv[j]->ptr,
-                sdslen(c->argv[j]->ptr)))
+        if (hllDenseAdd(hdr->registers, (unsigned char*)c->argv[j]->ptr,
+                        sdslen(c->argv[j]->ptr)))
         {
             updated++;
         }
@@ -688,7 +716,7 @@ void pfcountCommand(redisClient *c) {
             card |= (uint64_t)hdr->card[7] << 56;
         } else {
             /* Recompute it and update the cached value. */
-            card = hllCount(hdr->registers);
+            card = hllCount(hdr);
             hdr->card[0] = card & 0xff;
             hdr->card[1] = (card >> 8) & 0xff;
             hdr->card[2] = (card >> 16) & 0xff;
@@ -775,6 +803,7 @@ void pfmergeCommand(redisClient *c) {
 void pfselftestCommand(redisClient *c) {
     int j, i;
     sds bitcounters = sdsnewlen(NULL,HLL_DENSE_SIZE);
+    struct hllhdr *hdr = (struct hllhdr*) bitcounters;
     uint8_t bytecounters[HLL_REGISTERS];
 
     /* Test 1: access registers.
@@ -788,13 +817,13 @@ void pfselftestCommand(redisClient *c) {
             unsigned int r = rand() & HLL_REGISTER_MAX;
 
             bytecounters[i] = r;
-            HLL_DENSE_SET_REGISTER(bitcounters,i,r);
+            HLL_DENSE_SET_REGISTER(hdr->registers,i,r);
         }
         /* Check that we are able to retrieve the same values. */
         for (i = 0; i < HLL_REGISTERS; i++) {
             unsigned int val;
 
-            HLL_DENSE_GET_REGISTER(val,bitcounters,i);
+            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
             if (val != bytecounters[i]) {
                 addReplyErrorFormat(c,
                     "TESTFAILED Register %d should be %d but is %d",
@@ -811,17 +840,16 @@ void pfselftestCommand(redisClient *c) {
      * We check that the error is smaller than 4 times than the expected
      * standard error, to make it very unlikely for the test to fail because
      * of a "bad" run. */
-    memset(bitcounters,0,HLL_DENSE_SIZE);
+    memset(hdr->registers,0,HLL_DENSE_SIZE-HLL_HDR_SIZE);
     double relerr = 1.04/sqrt(HLL_REGISTERS);
     int64_t checkpoint = 1000;
     uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
     uint64_t ele;
     for (j = 1; j <= 10000000; j++) {
         ele = j ^ seed;
-        hllAdd((uint8_t*)bitcounters,(unsigned char*)&ele,sizeof(ele));
+        hllDenseAdd(hdr->registers,(unsigned char*)&ele,sizeof(ele));
         if (j == checkpoint) {
-            int64_t abserr = checkpoint-
-                             (int64_t)hllCount((uint8_t*)bitcounters);
+            int64_t abserr = checkpoint- (int64_t)hllCount(hdr);
             if (abserr < 0) abserr = -abserr;
             if (abserr > (uint64_t)(relerr*4*checkpoint)) {
                 addReplyErrorFormat(c,