@@ -29,8 +29,8 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
+#include <stdint.h>
 #include "redis.h"
-#include "crc64.h"
 
 /* The Redis HyperLogLog implementation is based on the following ideas:
  *
@@ -182,6 +182,42 @@
 
 /* ========================= HyperLogLog algorithm  ========================= */
 
+/* Our hahs function is MurmurHash2, 64 bit version. */
+uint64_t MurmurHash64A (const void * key, int len, unsigned int seed) {
+    const uint64_t m = 0xc6a4a7935bd1e995;
+    const int r = 47;
+    uint64_t h = seed ^ (len * m);
+    const uint64_t *data = (const uint64_t *)key;
+    const uint64_t *end = data + (len/8);
+
+    while(data != end) {
+        uint64_t k = *data++;
+        k *= m;
+        k ^= k >> r;
+        k *= m;
+        h ^= k;
+        h *= m;
+    }
+
+    const unsigned char *data2 = (const unsigned char*)data;
+
+    switch(len & 7) {
+    case 7: h ^= (uint64_t)data2[6] << 48;
+    case 6: h ^= (uint64_t)data2[5] << 40;
+    case 5: h ^= (uint64_t)data2[4] << 32;
+    case 4: h ^= (uint64_t)data2[3] << 24;
+    case 3: h ^= (uint64_t)data2[2] << 16;
+    case 2: h ^= (uint64_t)data2[1] << 8;
+    case 1: h ^= (uint64_t)data2[0];
+            h *= m;
+    };
+
+    h ^= h >> r;
+    h *= m;
+    h ^= h >> r;
+    return h;
+}
+
 /* "Add" the element in the hyperloglog data structure.
  * Actually nothing is added, but the max 0 pattern counter of the subset
  * the element belongs to is incremented if needed.
@@ -193,7 +229,7 @@
  * The function always succeed, however if as a result of the operation
  * the approximated cardinality changed, 1 is returned. Otherwise 0
  * is returned. */
-int hllAdd(uint8_t *registers, uint8_t *ele, size_t elesize) {
+int hllAdd(uint8_t *registers, unsigned char *ele, size_t elesize) {
     uint64_t hash, bit, index;
     uint8_t oldcount, count;
 
@@ -203,7 +239,7 @@ int hllAdd(uint8_t *registers, uint8_t *ele, size_t elesize) {
      *
      * This may sound like inefficient, but actually in the average case
      * there are high probabilities to find a 1 after a few iterations. */
-    hash = crc64(0,ele,elesize);
+    hash = MurmurHash64A(ele,elesize,0);
     bit = REDIS_HLL_REGISTERS;
     count = 0;
     while((hash & bit) == 0) {
@@ -215,6 +251,7 @@ int hllAdd(uint8_t *registers, uint8_t *ele, size_t elesize) {
         bit <<= 1;
     }
 
+    /* Update the register if this element produced a longer run of zeroes. */
     index = hash & REDIS_HLL_P_MASK; /* Index a register inside registers. */
     HLL_GET_REGISTER(oldcount,registers,index);
     if (count > oldcount) {
@@ -227,6 +264,57 @@ int hllAdd(uint8_t *registers, uint8_t *ele, size_t elesize) {
 
 /* ========================== HyperLogLog commands ========================== */
 
+/* HLLADD var ele ele ele ... ele => :0 or :1 */
+void hllAddCommand(redisClient *c) {
+    robj *o = lookupKeyWrite(c->db,c->argv[1]);
+    uint8_t *registers;
+    int updated = 0, j;
+
+    if (o == NULL) {
+        /* Create the key with a string value of the exact length to
+         * hold our HLL data structure. sdsnewlen() when NULL is passed
+         * is guaranteed to return bytes initialized to zero. */
+        o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
+        dbAdd(c->db,c->argv[1],o);
+    } else {
+        /* Key exists, check type */
+        if (checkType(c,o,REDIS_STRING))
+            return;
+
+        /* If this is a string representing an HLL, the size should match
+         * exactly. */
+        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
+            addReplyErrorFormat(c,
+                "HLLADD target key must contain a %d bytes string.",
+                REDIS_HLL_SIZE);
+            return;
+        }
+
+        /* If the object is shared or encoded, we have to make a copy. */
+        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
+            robj *decoded = getDecodedObject(o);
+            o = createRawStringObject(decoded->ptr, sdslen(decoded->ptr));
+            decrRefCount(decoded);
+            dbOverwrite(c->db,c->argv[1],o);
+        }
+    }
+    /* Perform the low level ADD operation for every element. */
+    registers = (uint8_t*) o->ptr;
+    for (j = 2; j < c->argc; j++) {
+        if (hllAdd(registers, (unsigned char*)c->argv[j]->ptr,
+                sdslen(c->argv[j]->ptr)))
+        {
+            updated++;
+        }
+    }
+    if (updated) {
+        signalModifiedKey(c->db,c->argv[1]);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
+        server.dirty++;
+    }
+    addReply(c, updated ? shared.cone : shared.czero);
+}
+
 /* This command performs a self-test of the HLL registers implementation.
  * Something that is not easy to test from within the outside.
  *