@@ -1349,7 +1349,7 @@ void pfmergeCommand(redisClient *c) {
  * Something that is not easy to test from within the outside. */
 #define HLL_TEST_CYCLES 1000
 void pfselftestCommand(redisClient *c) {
-    int j, i;
+    unsigned int j, i;
     sds bitcounters = sdsnewlen(NULL,HLL_DENSE_SIZE);
     struct hllhdr *hdr = (struct hllhdr*) bitcounters, *hdr2;
     robj *o = NULL;
@@ -1431,7 +1431,7 @@ void pfselftestCommand(redisClient *c) {
             if (j == 10) maxerr = 1;
 
             if (abserr < 0) abserr = -abserr;
-            if (abserr > maxerr) {
+            if (abserr > (int64_t)maxerr) {
                 addReplyErrorFormat(c,
                     "TESTFAILED Too big error. card:%llu abserr:%llu",
                     (unsigned long long) checkpoint,