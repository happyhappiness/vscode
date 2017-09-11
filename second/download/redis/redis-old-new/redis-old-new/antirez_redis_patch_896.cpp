@@ -204,6 +204,8 @@ struct hllhdr {
 
 #define HLL_SPARSE_MAX 12000
 
+static char *invalid_hll_err = "Corrupted HLL object detected";
+
 /* =========================== Low level bit macros ========================= */
 
 /* Macros to access the dense representation.
@@ -1085,7 +1087,7 @@ void pfaddCommand(redisClient *c) {
             updated++;
             break;
         case -1:
-            addReplyError(c,"Invalid HyperLogLog representation");
+            addReplyError(c,invalid_hll_err);
             return;
         }
     }
@@ -1130,7 +1132,7 @@ void pfcountCommand(redisClient *c) {
             /* Recompute it and update the cached value. */
             card = hllCount(hdr,&invalid);
             if (invalid) {
-                addReplyError(c,"Invalid HLL object detected");
+                addReplyError(c,invalid_hll_err);
                 return;
             }
             hdr->card[0] = card & 0xff;
@@ -1204,7 +1206,7 @@ void pfmergeCommand(redisClient *c) {
                 }
             }
             if (i != HLL_REGISTERS) {
-                addReplyError(c,"Invalid HLL object detected");
+                addReplyError(c,invalid_hll_err);
                 return;
             }
         }
@@ -1227,7 +1229,7 @@ void pfmergeCommand(redisClient *c) {
 
     /* Only support dense objects as destination. */
     if (hllSparseToDense(o) == REDIS_ERR) {
-        addReplyError(c,"Invalid HLL object detected");
+        addReplyError(c,invalid_hll_err);
         return;
     }
 
@@ -1345,7 +1347,7 @@ void pfdebugCommand(redisClient *c) {
 
         if (hdr->encoding == HLL_SPARSE) {
             if (hllSparseToDense(o) == REDIS_ERR) {
-                addReplyError(c,"Invalid HLL object detected");
+                addReplyError(c,invalid_hll_err);
                 return;
             }
             server.dirty++; /* Force propagation on encoding change. */