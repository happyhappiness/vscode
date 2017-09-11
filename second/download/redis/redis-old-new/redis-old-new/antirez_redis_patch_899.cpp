@@ -869,7 +869,7 @@ int hllSparseAdd(robj *o, unsigned char *ele, size_t elesize) {
  * PE is an array with a pre-computer table of values 2^-reg indexed by reg.
  * As a side effect the integer pointed by 'ezp' is set to the number
  * of zero registers. */
-double hllSparseSum(uint8_t *sparse, int sparselen, double *PE, int *ezp) {
+double hllSparseSum(uint8_t *sparse, int sparselen, double *PE, int *ezp, int *invalid) {
     double E = 0;
     int ez = 0, idx = 0, runlen, regval;
     uint8_t *end = sparse+sparselen, *p = sparse;
@@ -895,7 +895,7 @@ double hllSparseSum(uint8_t *sparse, int sparselen, double *PE, int *ezp) {
             p++;
         }
     }
-    redisAssert(idx == HLL_REGISTERS);
+    if (idx != HLL_REGISTERS && invalid) *invalid = 1;
     *ezp = ez;
     return E;
 }
@@ -908,13 +908,14 @@ double hllSparseSum(uint8_t *sparse, int sparselen, double *PE, int *ezp) {
 
 /* Return the approximated cardinality of the set based on the armonic
  * mean of the registers values. 'hdr' points to the start of the SDS
- * representing the String object holding the HLL representation. */
-uint64_t hllCount(struct hllhdr *hdr) {
+ * representing the String object holding the HLL representation.
+ *
+ * If the sparse representation of the HLL object is not valid, the integer
+ * pointed by 'invalid' is set to non-zero, otherwise it is left untouched. */
+uint64_t hllCount(struct hllhdr *hdr, int *invalid) {
     double m = HLL_REGISTERS;
-    double alpha = 0.7213/(1+1.079/m);
-    double E;
-    int ez; /* Number of registers equal to 0. */
-    int j;
+    double E, alpha = 0.7213/(1+1.079/m);
+    int j, ez; /* Number of registers equal to 0. */
 
     /* We precompute 2^(-reg[j]) in a small table in order to
      * speedup the computation of SUM(2^-register[0..i]). */
@@ -933,7 +934,8 @@ uint64_t hllCount(struct hllhdr *hdr) {
     if (hdr->encoding == HLL_DENSE) {
         E = hllDenseSum(hdr->registers,PE,&ez);
     } else {
-        E = hllSparseSum(hdr->registers,sdslen((sds)hdr)-HLL_HDR_SIZE,PE,&ez);
+        E = hllSparseSum(hdr->registers,
+                         sdslen((sds)hdr)-HLL_HDR_SIZE,PE,&ez,invalid);
     }
 
     /* Muliply the inverse of E for alpha_m * m^2 to have the raw estimate. */
@@ -1111,8 +1113,13 @@ void pfcountCommand(redisClient *c) {
             card |= (uint64_t)hdr->card[6] << 48;
             card |= (uint64_t)hdr->card[7] << 56;
         } else {
+            int invalid = 0;
             /* Recompute it and update the cached value. */
-            card = hllCount(hdr);
+            card = hllCount(hdr,&invalid);
+            if (invalid) {
+                addReplyError(c,"Invalid HLL object");
+                return;
+            }
             hdr->card[0] = card & 0xff;
             hdr->card[1] = (card >> 8) & 0xff;
             hdr->card[2] = (card >> 16) & 0xff;
@@ -1245,7 +1252,7 @@ void pfselftestCommand(redisClient *c) {
         ele = j ^ seed;
         hllDenseAdd(hdr->registers,(unsigned char*)&ele,sizeof(ele));
         if (j == checkpoint) {
-            int64_t abserr = checkpoint- (int64_t)hllCount(hdr);
+            int64_t abserr = checkpoint - (int64_t)hllCount(hdr,NULL);
             if (abserr < 0) abserr = -abserr;
             if (abserr > (uint64_t)(relerr*4*checkpoint)) {
                 addReplyErrorFormat(c,