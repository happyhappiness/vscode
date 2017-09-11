@@ -628,18 +628,17 @@ void pfmergeCommand(redisClient *c) {
 }
 
 /* This command performs a self-test of the HLL registers implementation.
- * Something that is not easy to test from within the outside.
- *
- * The test is conceived to test that the different counters of our data
- * structure are accessible and that setting their values both result in
- * the correct value to be retained and not affect adjacent values. */
-
+ * Something that is not easy to test from within the outside. */
 #define REDIS_HLL_TEST_CYCLES 1000
 void pfselftestCommand(redisClient *c) {
     int j, i;
     sds bitcounters = sdsnewlen(NULL,REDIS_HLL_SIZE);
     uint8_t bytecounters[REDIS_HLL_REGISTERS];
 
+    /* Test 1: access registers.
+     * The test is conceived to test that the different counters of our data
+     * structure are accessible and that setting their values both result in
+     * the correct value to be retained and not affect adjacent values. */
     for (j = 0; j < REDIS_HLL_TEST_CYCLES; j++) {
         /* Set the HLL counters and an array of unsigned byes of the
          * same size to the same set of random values. */
@@ -663,6 +662,36 @@ void pfselftestCommand(redisClient *c) {
         }
     }
 
+    /* Test 2: approximation error.
+     * The test is adds unique elements and check that the estimated value
+     * is always reasonable bounds.
+     * 
+     * We check that the error is smaller than 4 times than the expected
+     * standard error, to make it very unlikely for the test to fail because
+     * of a "bad" run. */
+    memset(bitcounters,0,REDIS_HLL_SIZE);
+    double relerr = 1.04/sqrt(REDIS_HLL_REGISTERS);
+    int64_t checkpoint = 1000;
+    uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
+    uint64_t ele;
+    for (j = 1; j <= 10000000; j++) {
+        ele = j ^ seed;
+        hllAdd((uint8_t*)bitcounters,(unsigned char*)&ele,sizeof(ele));
+        if (j == checkpoint) {
+            int64_t abserr = checkpoint-
+                             (int64_t)hllCount((uint8_t*)bitcounters);
+            if (abserr < 0) abserr = -abserr;
+            if (abserr > (uint64_t)(relerr*4*checkpoint)) {
+                addReplyErrorFormat(c,
+                    "TESTFAILED Too big error. card:%llu abserr:%llu",
+                    (unsigned long long) checkpoint,
+                    (unsigned long long) abserr);
+                goto cleanup;
+            }
+            checkpoint *= 10;
+        }
+    }
+
     /* Success! */
     addReply(c,shared.ok);
 