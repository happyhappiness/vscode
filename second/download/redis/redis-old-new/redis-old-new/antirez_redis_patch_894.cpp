@@ -1258,7 +1258,8 @@ void pfmergeCommand(redisClient *c) {
 void pfselftestCommand(redisClient *c) {
     int j, i;
     sds bitcounters = sdsnewlen(NULL,HLL_DENSE_SIZE);
-    struct hllhdr *hdr = (struct hllhdr*) bitcounters;
+    struct hllhdr *hdr = (struct hllhdr*) bitcounters, *hdr2;
+    robj *o = NULL;
     uint8_t bytecounters[HLL_REGISTERS];
 
     /* Test 1: access registers.
@@ -1289,20 +1290,43 @@ void pfselftestCommand(redisClient *c) {
     }
 
     /* Test 2: approximation error.
-     * The test is adds unique elements and check that the estimated value
+     * The test adds unique elements and check that the estimated value
      * is always reasonable bounds.
      * 
      * We check that the error is smaller than 4 times than the expected
      * standard error, to make it very unlikely for the test to fail because
-     * of a "bad" run. */
+     * of a "bad" run.
+     *
+     * The test is performed with both dense and sparse HLLs at the same
+     * time also verifying that the computed cardinality is the same. */
     memset(hdr->registers,0,HLL_DENSE_SIZE-HLL_HDR_SIZE);
+    o = createHLLObject();
     double relerr = 1.04/sqrt(HLL_REGISTERS);
-    int64_t checkpoint = 1000;
+    int64_t checkpoint = 1;
     uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
     uint64_t ele;
     for (j = 1; j <= 10000000; j++) {
         ele = j ^ seed;
         hllDenseAdd(hdr->registers,(unsigned char*)&ele,sizeof(ele));
+        hllAdd(o,(unsigned char*)&ele,sizeof(ele));
+
+        /* Make sure that for small cardinalities we use sparse
+         * encoding. */
+        if (j == checkpoint && j < HLL_SPARSE_MAX/2) {
+            hdr2 = o->ptr;
+            if (hdr2->encoding != HLL_SPARSE) {
+                addReplyError(c, "TESTFAILED sparse encoding not used");
+                goto cleanup;
+            }
+        }
+
+        /* Check that dense and sparse representations agree. */
+        if (j == checkpoint && hllCount(hdr,NULL) != hllCount(o->ptr,NULL)) {
+                addReplyError(c, "TESTFAILED dense/sparse disagree");
+                goto cleanup;
+        }
+
+        /* Check error. */
         if (j == checkpoint) {
             int64_t abserr = checkpoint - (int64_t)hllCount(hdr,NULL);
             if (abserr < 0) abserr = -abserr;
@@ -1322,6 +1346,7 @@ void pfselftestCommand(redisClient *c) {
 
 cleanup:
     sdsfree(bitcounters);
+    if (o) decrRefCount(o);
 }
 
 /* PFDEBUG <subcommand> <key> ... args ...