@@ -559,16 +559,19 @@ double hllDenseSum(uint8_t *registers, double *PE, int *ezp) {
 
 /* Convert the HLL with sparse representation given as input in its dense
  * representation. Both representations are represented by SDS strings, and
- * the input representation is freed as a side effect. */
-void hllSparseToDense(robj *o) {
+ * the input representation is freed as a side effect.
+ *
+ * The function returns REDIS_OK if the sparse representation was valid,
+ * otherwise REDIS_ERR is returned if the representation was corrupted. */
+int hllSparseToDense(robj *o) {
     sds sparse = o->ptr, dense;
     struct hllhdr *hdr, *oldhdr = (struct hllhdr*)sparse;
     int idx = 0, runlen, regval;
     uint8_t *p = (uint8_t*)sparse, *end = p+sdslen(sparse);
 
     /* If the representation is already the right one return ASAP. */
     hdr = (struct hllhdr*) sparse;
-    if (hdr->encoding == HLL_DENSE) return;
+    if (hdr->encoding == HLL_DENSE) return REDIS_OK;
 
     /* Create a string of the right size filled with zero bytes.
      * Note that the cached cardinality is set to 0 as a side effect
@@ -601,9 +604,17 @@ void hllSparseToDense(robj *o) {
         }
     }
 
+    /* If the sparse representation was valid, we expect to find idx
+     * set to HLL_REGISTERS. */
+    if (idx != HLL_REGISTERS) {
+        sdsfree(dense);
+        return REDIS_ERR;
+    }
+
     /* Free the old representation and set the new one. */
     sdsfree(o->ptr);
     o->ptr = dense;
+    return REDIS_OK;
 }
 
 /* "Add" the element in the sparse hyperloglog data structure.
@@ -809,7 +820,7 @@ int hllSparseAdd(robj *o, unsigned char *ele, size_t elesize) {
     return 1;
 
 promote: /* Promote to dense representation. */
-    hllSparseToDense(o);
+    if (hllSparseToDense(o) == REDIS_ERR) return -1; /* Corrupted HLL. */
     hdr = o->ptr;
     return hllDenseAdd(hdr->registers, ele, elesize);
 }
@@ -1236,7 +1247,11 @@ void pfdebugCommand(redisClient *c) {
         if (c->argc != 3) goto arityerr;
 
         addReplyMultiBulkLen(c,HLL_REGISTERS);
-        hllSparseToDense(o);
+        if (hllSparseToDense(o) == REDIS_ERR) {
+            addReplyError(c,"HLL sparse encoding is corrupted");
+            return;
+        }
+        hdr = o->ptr;
         for (j = 0; j < HLL_REGISTERS; j++) {
             uint8_t val;
 