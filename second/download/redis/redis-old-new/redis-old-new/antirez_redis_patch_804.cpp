@@ -1386,7 +1386,7 @@ void pfselftestCommand(redisClient *c) {
      * The test adds unique elements and check that the estimated value
      * is always reasonable bounds.
      *
-     * We check that the error is smaller than 4 times than the expected
+     * We check that the error is smaller than a few times than the expected
      * standard error, to make it very unlikely for the test to fail because
      * of a "bad" run.
      *
@@ -1422,8 +1422,16 @@ void pfselftestCommand(redisClient *c) {
         /* Check error. */
         if (j == checkpoint) {
             int64_t abserr = checkpoint - (int64_t)hllCount(hdr,NULL);
+            uint64_t maxerr = ceil(relerr*6*checkpoint);
+
+            /* Adjust the max error we expect for cardinality 10
+             * since from time to time it is statistically likely to get
+             * much higher error due to collision, resulting into a false
+             * positive. */
+            if (j == 10) maxerr = 1;
+
             if (abserr < 0) abserr = -abserr;
-            if (abserr > (uint64_t)(relerr*4*checkpoint)) {
+            if (abserr > maxerr) {
                 addReplyErrorFormat(c,
                     "TESTFAILED Too big error. card:%llu abserr:%llu",
                     (unsigned long long) checkpoint,