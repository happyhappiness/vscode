@@ -630,7 +630,10 @@ void pfmergeCommand(redisClient *c) {
     addReply(c,shared.ok);
 }
 
-/* This command performs a self-test of the HLL registers implementation.
+/* ========================== Testing / Debugging  ========================== */
+
+/* PFSELFTEST
+ * This command performs a self-test of the HLL registers implementation.
  * Something that is not easy to test from within the outside. */
 #define REDIS_HLL_TEST_CYCLES 1000
 void pfselftestCommand(redisClient *c) {
@@ -701,3 +704,38 @@ void pfselftestCommand(redisClient *c) {
 cleanup:
     sdsfree(bitcounters);
 }
+
+/* PFGETREG
+ * Return the registers values of the specified HLL. */
+void pfgetregCommand(redisClient *c) {
+    robj *o = lookupKeyRead(c->db,c->argv[1]);
+    uint8_t *registers;
+    int j;
+
+    if (o == NULL) {
+        addReplyError(c,"The specified key does not exist");
+        return;
+    } else {
+        /* Key exists, check type */
+        if (checkType(c,o,REDIS_STRING))
+            return;
+
+        /* If this is a string representing an HLL, the size should match
+         * exactly. */
+        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
+            addReplyErrorFormat(c,
+                "PFCOUNT target key must contain a %d bytes string.",
+                REDIS_HLL_SIZE);
+            return;
+        }
+
+        registers = o->ptr;
+        addReplyMultiBulkLen(c,REDIS_HLL_REGISTERS);
+        for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
+            uint8_t val;
+
+            HLL_GET_REGISTER(val,registers,j);
+            addReplyLongLong(c,val);
+        }
+    }
+}