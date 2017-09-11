@@ -176,7 +176,7 @@
  * involved in updating the sparse representation is not justified by the
  * memory savings. The exact maximum length of the sparse representation
  * when this implementation switches to the dense representation is
- * configured via the define HLL_SPARSE_MAX.
+ * configured via the define server.hll_sparse_max_bytes.
  */
 
 struct hllhdr {
@@ -202,8 +202,6 @@ struct hllhdr {
 #define HLL_SPARSE 1 /* Sparse encoding */
 #define HLL_MAX_ENCODING 1
 
-#define HLL_SPARSE_MAX 3000
-
 static char *invalid_hll_err = "Corrupted HLL object detected";
 
 /* =========================== Low level bit macros ========================= */
@@ -634,7 +632,7 @@ int hllSparseToDense(robj *o) {
  * As a side effect the function may promote the HLL representation from
  * sparse to dense: this happens when a register requires to be set to a value
  * not representable with the sparse representation, or when the resulting
- * size would be greater than HLL_SPARSE_MAX. */
+ * size would be greater than server.hll_sparse_max_bytes. */
 int hllSparseAdd(robj *o, unsigned char *ele, size_t elesize) {
     struct hllhdr *hdr;
     uint8_t oldcount, count, *sparse, *end, *p, *prev, *next;
@@ -815,7 +813,8 @@ int hllSparseAdd(robj *o, unsigned char *ele, size_t elesize) {
      int oldlen = is_xzero ? 2 : 1;
      int deltalen = seqlen-oldlen;
 
-     if (deltalen > 0 && sdslen(o->ptr)+deltalen > HLL_SPARSE_MAX) goto promote;
+     if (deltalen > 0 &&
+         sdslen(o->ptr)+deltalen > server.hll_sparse_max_bytes) goto promote;
      if (deltalen && next) memmove(next+deltalen,next,end-next);
      sdsIncrLen(o->ptr,deltalen);
      memcpy(p,seq,seqlen);
@@ -1312,7 +1311,7 @@ void pfselftestCommand(redisClient *c) {
 
         /* Make sure that for small cardinalities we use sparse
          * encoding. */
-        if (j == checkpoint && j < HLL_SPARSE_MAX/2) {
+        if (j == checkpoint && j < server.hll_sparse_max_bytes/2) {
             hdr2 = o->ptr;
             if (hdr2->encoding != HLL_SPARSE) {
                 addReplyError(c, "TESTFAILED sparse encoding not used");