@@ -202,7 +202,7 @@ struct hllhdr {
 #define HLL_SPARSE 1 /* Sparse encoding */
 #define HLL_MAX_ENCODING 1
 
-static char *invalid_hll_err = "Corrupted HLL object detected";
+static char *invalid_hll_err = "-INVALIDOBJ Corrupted HLL object detected\r\n";
 
 /* =========================== Low level bit macros ========================= */
 
@@ -1086,7 +1086,7 @@ void pfaddCommand(redisClient *c) {
             updated++;
             break;
         case -1:
-            addReplyError(c,invalid_hll_err);
+            addReplySds(c,sdsnew(invalid_hll_err));
             return;
         }
     }
@@ -1131,7 +1131,7 @@ void pfcountCommand(redisClient *c) {
             /* Recompute it and update the cached value. */
             card = hllCount(hdr,&invalid);
             if (invalid) {
-                addReplyError(c,invalid_hll_err);
+                addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }
             hdr->card[0] = card & 0xff;
@@ -1205,7 +1205,7 @@ void pfmergeCommand(redisClient *c) {
                 }
             }
             if (i != HLL_REGISTERS) {
-                addReplyError(c,invalid_hll_err);
+                addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }
         }
@@ -1228,7 +1228,7 @@ void pfmergeCommand(redisClient *c) {
 
     /* Only support dense objects as destination. */
     if (hllSparseToDense(o) == REDIS_ERR) {
-        addReplyError(c,invalid_hll_err);
+        addReplySds(c,sdsnew(invalid_hll_err));
         return;
     }
 
@@ -1371,7 +1371,7 @@ void pfdebugCommand(redisClient *c) {
 
         if (hdr->encoding == HLL_SPARSE) {
             if (hllSparseToDense(o) == REDIS_ERR) {
-                addReplyError(c,invalid_hll_err);
+                addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }
             server.dirty++; /* Force propagation on encoding change. */
@@ -1435,7 +1435,7 @@ void pfdebugCommand(redisClient *c) {
 
         if (hdr->encoding == HLL_SPARSE) {
             if (hllSparseToDense(o) == REDIS_ERR) {
-                addReplyError(c,invalid_hll_err);
+                addReplySds(c,sdsnew(invalid_hll_err));
                 return;
             }
             conv = 1;