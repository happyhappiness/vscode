@@ -331,7 +331,7 @@ struct hllhdr {
 
 /* Store the value of the register at position 'regnum' into variable 'target'.
  * 'p' is an array of unsigned bytes. */
-#define HLL_GET_REGISTER(target,p,regnum) do { \
+#define HLL_DENSE_GET_REGISTER(target,p,regnum) do { \
     uint8_t *_p = (uint8_t*) p; \
     unsigned long _byte = regnum*HLL_BITS/8; \
     unsigned long _fb = regnum*HLL_BITS&7; \
@@ -343,7 +343,7 @@ struct hllhdr {
 
 /* Set the value of the register at position 'regnum' to 'val'.
  * 'p' is an array of unsigned bytes. */
-#define HLL_SET_REGISTER(p,regnum,val) do { \
+#define HLL_DENSE_SET_REGISTER(p,regnum,val) do { \
     uint8_t *_p = (uint8_t*) p; \
     unsigned long _byte = regnum*HLL_BITS/8; \
     unsigned long _fb = regnum*HLL_BITS&7; \
@@ -418,20 +418,12 @@ uint64_t MurmurHash64A (const void * key, int len, unsigned int seed) {
     return h;
 }
 
-/* "Add" the element in the hyperloglog data structure.
- * Actually nothing is added, but the max 0 pattern counter of the subset
- * the element belongs to is incremented if needed.
- *
- * 'registers' is expected to have room for HLL_REGISTERS plus an
- * additional byte on the right. This requirement is met by sds strings
- * automatically since they are implicitly null terminated.
- *
- * The function always succeed, however if as a result of the operation
- * the approximated cardinality changed, 1 is returned. Otherwise 0
- * is returned. */
-int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
+/* Given a string element to add to the HyperLogLog, returns the length
+ * of the pattern 000..1 of the element hash. As a side effect 'regp' is
+ * set to the register index this element hashes to. */
+int hllPatLen(unsigned char *ele, size_t elesize, int *regp) {
     uint64_t hash, bit, index;
-    uint8_t oldcount, count;
+    int count;
 
     /* Count the number of zeroes starting from bit HLL_REGISTERS
      * (that is a power of two corresponding to the first bit we don't use
@@ -445,19 +437,38 @@ int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
      * This may sound like inefficient, but actually in the average case
      * there are high probabilities to find a 1 after a few iterations. */
     hash = MurmurHash64A(ele,elesize,0xadc83b19ULL);
+    index = hash & HLL_P_MASK; /* Register index. */
     hash |= ((uint64_t)1<<63); /* Make sure the loop terminates. */
     bit = HLL_REGISTERS; /* First bit not used to address the register. */
     count = 1; /* Initialized to 1 since we count the "00000...1" pattern. */
     while((hash & bit) == 0) {
         count++;
         bit <<= 1;
     }
+    if (regp) *regp = (int) index;
+    return count;
+}
+
+/* "Add" the element in the hyperloglog data structure.
+ * Actually nothing is added, but the max 0 pattern counter of the subset
+ * the element belongs to is incremented if needed.
+ *
+ * 'registers' is expected to have room for HLL_REGISTERS plus an
+ * additional byte on the right. This requirement is met by sds strings
+ * automatically since they are implicitly null terminated.
+ *
+ * The function always succeed, however if as a result of the operation
+ * the approximated cardinality changed, 1 is returned. Otherwise 0
+ * is returned. */
+int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
+    uint8_t oldcount, count;
+    int index;
 
     /* Update the register if this element produced a longer run of zeroes. */
-    index = hash & HLL_P_MASK; /* Index a register inside registers. */
-    HLL_GET_REGISTER(oldcount,registers,index);
+    count = hllPatLen(ele,elesize,&index);
+    HLL_DENSE_GET_REGISTER(oldcount,registers,index);
     if (count > oldcount) {
-        HLL_SET_REGISTER(registers,index,count);
+        HLL_DENSE_SET_REGISTER(registers,index,count);
         return 1;
     } else {
         return 0;
@@ -525,7 +536,7 @@ uint64_t hllCount(uint8_t *registers) {
         for (j = 0; j < HLL_REGISTERS; j++) {
             unsigned long reg;
 
-            HLL_GET_REGISTER(reg,registers,j);
+            HLL_DENSE_GET_REGISTER(reg,registers,j);
             if (reg == 0) {
                 ez++;
                 E += 1; /* 2^(-reg[j]) is 1 when m is 0. */
@@ -719,7 +730,7 @@ void pfmergeCommand(redisClient *c) {
          * to MAX(max[i],hll[i]). */
         hdr = o->ptr;
         for (i = 0; i < HLL_REGISTERS; i++) {
-            HLL_GET_REGISTER(val,hdr->registers,i);
+            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
             if (val > max[i]) max[i] = val;
         }
     }
@@ -743,7 +754,7 @@ void pfmergeCommand(redisClient *c) {
      * invalidate the cached value. */
     hdr = o->ptr;
     for (j = 0; j < HLL_REGISTERS; j++) {
-        HLL_SET_REGISTER(hdr->registers,j,max[j]);
+        HLL_DENSE_SET_REGISTER(hdr->registers,j,max[j]);
     }
     HLL_INVALIDATE_CACHE(hdr);
 
@@ -777,13 +788,13 @@ void pfselftestCommand(redisClient *c) {
             unsigned int r = rand() & HLL_REGISTER_MAX;
 
             bytecounters[i] = r;
-            HLL_SET_REGISTER(bitcounters,i,r);
+            HLL_DENSE_SET_REGISTER(bitcounters,i,r);
         }
         /* Check that we are able to retrieve the same values. */
         for (i = 0; i < HLL_REGISTERS; i++) {
             unsigned int val;
 
-            HLL_GET_REGISTER(val,bitcounters,i);
+            HLL_DENSE_GET_REGISTER(val,bitcounters,i);
             if (val != bytecounters[i]) {
                 addReplyErrorFormat(c,
                     "TESTFAILED Register %d should be %d but is %d",
@@ -848,7 +859,7 @@ void pfgetregCommand(redisClient *c) {
         for (j = 0; j < HLL_REGISTERS; j++) {
             uint8_t val;
 
-            HLL_GET_REGISTER(val,hdr->registers,j);
+            HLL_DENSE_GET_REGISTER(val,hdr->registers,j);
             addReplyLongLong(c,val);
         }
     }