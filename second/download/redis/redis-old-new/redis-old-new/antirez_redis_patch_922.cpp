@@ -30,6 +30,7 @@
  */
 
 #include <stdint.h>
+#include <math.h>
 #include "redis.h"
 
 /* The Redis HyperLogLog implementation is based on the following ideas:
@@ -262,6 +263,41 @@ int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
     }
 }
 
+/* Return the approximated cardinality of the set based on the armonic
+ * mean of the registers values. */
+uint64_t hllCount(uint8_t *registers) {
+    double m = REDIS_HLL_REGISTERS;
+    double alpha = 0.7213/(1+1.079/m);
+    double E = 0;
+    int ez = 0; /* Number of registers equal to 0. */
+    int j;
+
+    for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
+        uint8_t reg;
+
+        /* Compute SUM(2^-register[0..i]). */
+        HLL_GET_REGISTER(reg,registers,j);
+        if (reg == 0) {
+            ez++;
+            E += 1; /* 2^(-reg[j]) is 1 when m is 0. */
+        } else {
+            E += 1.0/(2ULL << reg); /* 2^(-reg[j]) is the same as 1/2^reg[j]. */
+        }
+    }
+    /* Muliply the inverse of E for alpha_m * m^2 to have the raw estimate. */
+    E = (1/E)*alpha*m*m;
+
+    /* Apply corrections for small cardinalities. */
+    if (E < m*2.5 && ez != 0) {
+        E = m*log(m/ez); /* LINEARCOUNTING() */
+    }
+    /* We don't apply the correction for E > 1/30 of 2^32 since we use
+     * a 64 bit function and 6 bit counters. To apply the correction for
+     * 1/30 of 2^64 is not needed since it would require a huge set
+     * to approach such a value. */
+    return (uint64_t) E;
+}
+
 /* ========================== HyperLogLog commands ========================== */
 
 /* HLLADD var ele ele ele ... ele => :0 or :1 */
@@ -299,7 +335,7 @@ void hllAddCommand(redisClient *c) {
         }
     }
     /* Perform the low level ADD operation for every element. */
-    registers = (uint8_t*) o->ptr;
+    registers = o->ptr;
     for (j = 2; j < c->argc; j++) {
         if (hllAdd(registers, (unsigned char*)c->argv[j]->ptr,
                 sdslen(c->argv[j]->ptr)))
@@ -315,6 +351,34 @@ void hllAddCommand(redisClient *c) {
     addReply(c, updated ? shared.cone : shared.czero);
 }
 
+/* HLLCOUNT var -> approximated cardinality of set. */
+void hllCountCommand(redisClient *c) {
+    robj *o = lookupKeyRead(c->db,c->argv[1]);
+    uint8_t *registers;
+
+    if (o == NULL) {
+        /* No key? Cardinality is zero since no element was added, otherwise
+         * we would have a key as HHLADD creates it as a side effect. */
+        addReply(c,shared.czero);
+    } else {
+        /* Key exists, check type */
+        if (checkType(c,o,REDIS_STRING))
+            return;
+
+        /* If this is a string representing an HLL, the size should match
+         * exactly. */
+        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
+            addReplyErrorFormat(c,
+                "HLLCOUNT target key must contain a %d bytes string.",
+                REDIS_HLL_SIZE);
+            return;
+        }
+        registers = o->ptr;
+        addReplyLongLong(c,hllCount(registers));
+    }
+}
+
+
 /* This command performs a self-test of the HLL registers implementation.
  * Something that is not easy to test from within the outside.
  *