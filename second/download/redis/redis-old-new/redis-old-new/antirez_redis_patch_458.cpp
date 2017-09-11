@@ -563,8 +563,8 @@ double hllDenseSum(uint8_t *registers, double *PE, int *ezp) {
  * representation. Both representations are represented by SDS strings, and
  * the input representation is freed as a side effect.
  *
- * The function returns REDIS_OK if the sparse representation was valid,
- * otherwise REDIS_ERR is returned if the representation was corrupted. */
+ * The function returns C_OK if the sparse representation was valid,
+ * otherwise C_ERR is returned if the representation was corrupted. */
 int hllSparseToDense(robj *o) {
     sds sparse = o->ptr, dense;
     struct hllhdr *hdr, *oldhdr = (struct hllhdr*)sparse;
@@ -573,7 +573,7 @@ int hllSparseToDense(robj *o) {
 
     /* If the representation is already the right one return ASAP. */
     hdr = (struct hllhdr*) sparse;
-    if (hdr->encoding == HLL_DENSE) return REDIS_OK;
+    if (hdr->encoding == HLL_DENSE) return C_OK;
 
     /* Create a string of the right size filled with zero bytes.
      * Note that the cached cardinality is set to 0 as a side effect
@@ -610,13 +610,13 @@ int hllSparseToDense(robj *o) {
      * set to HLL_REGISTERS. */
     if (idx != HLL_REGISTERS) {
         sdsfree(dense);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Free the old representation and set the new one. */
     sdsfree(o->ptr);
     o->ptr = dense;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* "Add" the element in the sparse hyperloglog data structure.
@@ -866,7 +866,7 @@ int hllSparseAdd(robj *o, unsigned char *ele, size_t elesize) {
     return 1;
 
 promote: /* Promote to dense representation. */
-    if (hllSparseToDense(o) == REDIS_ERR) return -1; /* Corrupted HLL. */
+    if (hllSparseToDense(o) == C_ERR) return -1; /* Corrupted HLL. */
     hdr = o->ptr;
 
     /* We need to call hllDenseAdd() to perform the operation after the
@@ -1039,7 +1039,7 @@ int hllAdd(robj *o, unsigned char *ele, size_t elesize) {
  * The hll object must be already validated via isHLLObjectOrReply()
  * or in some other way.
  *
- * If the HyperLogLog is sparse and is found to be invalid, REDIS_ERR
+ * If the HyperLogLog is sparse and is found to be invalid, C_ERR
  * is returned, otherwise the function always succeeds. */
 int hllMerge(uint8_t *max, robj *hll) {
     struct hllhdr *hdr = hll->ptr;
@@ -1077,9 +1077,9 @@ int hllMerge(uint8_t *max, robj *hll) {
                 p++;
             }
         }
-        if (i != HLL_REGISTERS) return REDIS_ERR;
+        if (i != HLL_REGISTERS) return C_ERR;
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* ========================== HyperLogLog commands ========================== */
@@ -1119,14 +1119,14 @@ robj *createHLLObject(void) {
 }
 
 /* Check if the object is a String with a valid HLL representation.
- * Return REDIS_OK if this is true, otherwise reply to the client
- * with an error and return REDIS_ERR. */
+ * Return C_OK if this is true, otherwise reply to the client
+ * with an error and return C_ERR. */
 int isHLLObjectOrReply(client *c, robj *o) {
     struct hllhdr *hdr;
 
     /* Key exists, check type */
     if (checkType(c,o,OBJ_STRING))
-        return REDIS_ERR; /* Error already sent. */
+        return C_ERR; /* Error already sent. */
 
     if (stringObjectLen(o) < sizeof(*hdr)) goto invalid;
     hdr = o->ptr;
@@ -1142,13 +1142,13 @@ int isHLLObjectOrReply(client *c, robj *o) {
         stringObjectLen(o) != HLL_DENSE_SIZE) goto invalid;
 
     /* All tests passed. */
-    return REDIS_OK;
+    return C_OK;
 
 invalid:
     addReplySds(c,
         sdsnew("-WRONGTYPE Key is not a valid "
                "HyperLogLog string value.\r\n"));
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* PFADD var ele ele ele ... ele => :0 or :1 */
@@ -1165,7 +1165,7 @@ void pfaddCommand(client *c) {
         dbAdd(c->db,c->argv[1],o);
         updated++;
     } else {
-        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
+        if (isHLLObjectOrReply(c,o) != C_OK) return;
         o = dbUnshareStringValue(c->db,c->argv[1],o);
     }
     /* Perform the low level ADD operation for every element. */
@@ -1214,11 +1214,11 @@ void pfcountCommand(client *c) {
             /* Check type and size. */
             robj *o = lookupKeyRead(c->db,c->argv[j]);
             if (o == NULL) continue; /* Assume empty HLL for non existing var.*/
-            if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
+            if (isHLLObjectOrReply(c,o) != C_OK) return;
 
             /* Merge with this HLL with our 'max' HHL by setting max[i]
              * to MAX(max[i],hll[i]). */
-            if (hllMerge(registers,o) == REDIS_ERR) {
+            if (hllMerge(registers,o) == C_ERR) {
                 addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }
@@ -1239,7 +1239,7 @@ void pfcountCommand(client *c) {
          * we would have a key as HLLADD creates it as a side effect. */
         addReply(c,shared.czero);
     } else {
-        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
+        if (isHLLObjectOrReply(c,o) != C_OK) return;
         o = dbUnshareStringValue(c->db,c->argv[1],o);
 
         /* Check if the cached cardinality is valid. */
@@ -1295,11 +1295,11 @@ void pfmergeCommand(client *c) {
         /* Check type and size. */
         robj *o = lookupKeyRead(c->db,c->argv[j]);
         if (o == NULL) continue; /* Assume empty HLL for non existing var. */
-        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
+        if (isHLLObjectOrReply(c,o) != C_OK) return;
 
         /* Merge with this HLL with our 'max' HHL by setting max[i]
          * to MAX(max[i],hll[i]). */
-        if (hllMerge(max,o) == REDIS_ERR) {
+        if (hllMerge(max,o) == C_ERR) {
             addReplySds(c,sdsnew(invalid_hll_err));
             return;
         }
@@ -1321,7 +1321,7 @@ void pfmergeCommand(client *c) {
     }
 
     /* Only support dense objects as destination. */
-    if (hllSparseToDense(o) == REDIS_ERR) {
+    if (hllSparseToDense(o) == C_ERR) {
         addReplySds(c,sdsnew(invalid_hll_err));
         return;
     }
@@ -1463,7 +1463,7 @@ void pfdebugCommand(client *c) {
         addReplyError(c,"The specified key does not exist");
         return;
     }
-    if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
+    if (isHLLObjectOrReply(c,o) != C_OK) return;
     o = dbUnshareStringValue(c->db,c->argv[2],o);
     hdr = o->ptr;
 
@@ -1472,7 +1472,7 @@ void pfdebugCommand(client *c) {
         if (c->argc != 3) goto arityerr;
 
         if (hdr->encoding == HLL_SPARSE) {
-            if (hllSparseToDense(o) == REDIS_ERR) {
+            if (hllSparseToDense(o) == C_ERR) {
                 addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }
@@ -1536,7 +1536,7 @@ void pfdebugCommand(client *c) {
         if (c->argc != 3) goto arityerr;
 
         if (hdr->encoding == HLL_SPARSE) {
-            if (hllSparseToDense(o) == REDIS_ERR) {
+            if (hllSparseToDense(o) == C_ERR) {
                 addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }