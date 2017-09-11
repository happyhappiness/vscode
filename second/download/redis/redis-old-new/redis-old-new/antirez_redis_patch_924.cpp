@@ -53,6 +53,7 @@
 
 #define REDIS_HLL_REGISTERS 16384
 #define REDIS_HLL_BITS 6
+#define REDIS_HLL_REGISTER_MAX ((1<<REDIS_HLL_BITS)-1)
 #define REDIS_HLL_SIZE ((REDIS_HLL_REGISTERS*REDIS_HLL_BITS+7)/8)
 
 /* =========================== Low level bit macros ========================= */
@@ -158,18 +159,60 @@
 
 /* Set the value of the register at position 'regnum' to 'val'.
  * 'p' is an array of unsigned bytes. */
-#define HLL_SET_REGISTER(val,p,regnum) do { \
+#define HLL_SET_REGISTER(p,regnum,val) do { \
     int _byte = regnum*REDIS_HLL_BITS/8; \
     int _leftshift = regnum*REDIS_HLL_BITS&7; \
     int _rightshift = 8 - _leftshift; \
-    unsigned int m1 = 255, m2 = (1<<REDIS_HLL_BITS)-1; \
-    p[byte] &= m1 << _rightshift; \
-    p[byte] |= val >> _leftshift; \
-    p[byte+1] &= ~(m2 << _rightshift); \
-    p[byte+1] |= val << _rightshift; \
+    unsigned int m1 = 255, m2 = REDIS_HLL_REGISTER_MAX; \
+    p[_byte] &= m1 << _rightshift; \
+    p[_byte] |= val >> _leftshift; \
+    p[_byte+1] &= ~(m2 << _rightshift); \
+    p[_byte+1] |= val << _rightshift; \
 } while(0)
 
 /* ========================= HyperLogLog algorithm  ========================= */
 
 /* ========================== HyperLogLog commands ========================== */
 
+/* This command performs a self-test of the HLL registers implementation.
+ * Something that is not easy to test from within the outside.
+ *
+ * The test is conceived to test that the different counters of our data
+ * structure are accessible and that setting their values both result in
+ * the correct value to be retained and not affect adjacent values. */
+
+#define REDIS_HLL_TEST_CYCLES 1000
+void hllSelftestCommand(redisClient *c) {
+    int j, i;
+    sds bitcounters = sdsnewlen(NULL,REDIS_HLL_SIZE);
+    uint8_t bytecounters[REDIS_HLL_REGISTERS];
+
+    for (j = 0; j < REDIS_HLL_TEST_CYCLES; j++) {
+        /* Set the HLL counters and an array of unsigned byes of the
+         * same size to the same set of random values. */
+        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
+            unsigned int r = rand() & REDIS_HLL_REGISTER_MAX;
+
+            bytecounters[i] = r;
+            HLL_SET_REGISTER(bitcounters,i,r);
+        }
+        /* Check that we are able to retrieve the same values. */
+        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
+            unsigned int val;
+
+            HLL_GET_REGISTER(val,bitcounters,i);
+            if (val != bytecounters[i]) {
+                addReplyErrorFormat(c,
+                    "TESTFAILED Register %d should be %d but is %d",
+                    i, (int) bytecounters[i], (int) val);
+                goto cleanup;
+            }
+        }
+    }
+
+    /* Success! */
+    addReply(c,shared.ok);
+
+cleanup:
+    sdsfree(bitcounters);
+}