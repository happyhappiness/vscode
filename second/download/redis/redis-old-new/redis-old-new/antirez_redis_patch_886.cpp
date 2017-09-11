@@ -991,6 +991,55 @@ int hllAdd(robj *o, unsigned char *ele, size_t elesize) {
     }
 }
 
+/* Merge by computing MAX(registers[i],hll[i]) the HyperLogLog 'hll'
+ * with an array of uint8_t HLL_REGISTERS registers pointed by 'max'.
+ *
+ * The hll object must be already validated via isHLLObjectOrReply()
+ * or in some other way.
+ *
+ * If the HyperLogLog is sparse and is found to be invalid, REDIS_ERR
+ * is returned, otherwise the function always succeeds. */
+int hllMerge(uint8_t *max, robj *hll) {
+    struct hllhdr *hdr = hll->ptr;
+    int i;
+
+    if (hdr->encoding == HLL_DENSE) {
+        uint8_t val;
+
+        for (i = 0; i < HLL_REGISTERS; i++) {
+            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
+            if (val > max[i]) max[i] = val;
+        }
+    } else {
+        uint8_t *p = hll->ptr, *end = p + sdslen(hll->ptr);
+        long runlen, regval;
+
+        p += HLL_HDR_SIZE;
+        i = 0;
+        while(p < end) {
+            if (HLL_SPARSE_IS_ZERO(p)) {
+                runlen = HLL_SPARSE_ZERO_LEN(p);
+                i += runlen;
+                p++;
+            } else if (HLL_SPARSE_IS_XZERO(p)) {
+                runlen = HLL_SPARSE_XZERO_LEN(p);
+                i += runlen;
+                p += 2;
+            } else {
+                runlen = HLL_SPARSE_VAL_LEN(p);
+                regval = HLL_SPARSE_VAL_VALUE(p);
+                while(runlen--) {
+                    if (regval > max[i]) max[i] = regval;
+                    i++;
+                }
+                p++;
+            }
+        }
+        if (i != HLL_REGISTERS) return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* ========================== HyperLogLog commands ========================== */
 
 /* Create an HLL object. We always create the HLL using sparse encoding.
@@ -1157,7 +1206,7 @@ void pfcountCommand(redisClient *c) {
 void pfmergeCommand(redisClient *c) {
     uint8_t max[HLL_REGISTERS];
     struct hllhdr *hdr;
-    int j, i;
+    int j;
 
     /* Compute an HLL with M[i] = MAX(M[i]_j).
      * We we the maximum into the max array of registers. We'll write
@@ -1171,43 +1220,9 @@ void pfmergeCommand(redisClient *c) {
 
         /* Merge with this HLL with our 'max' HHL by setting max[i]
          * to MAX(max[i],hll[i]). */
-        hdr = o->ptr;
-        if (hdr->encoding == HLL_DENSE) {
-            uint8_t val;
-
-            for (i = 0; i < HLL_REGISTERS; i++) {
-                HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
-                if (val > max[i]) max[i] = val;
-            }
-        } else {
-            uint8_t *p = o->ptr, *end = p + sdslen(o->ptr);
-            long runlen, regval;
-
-            p += HLL_HDR_SIZE;
-            i = 0;
-            while(p < end) {
-                if (HLL_SPARSE_IS_ZERO(p)) {
-                    runlen = HLL_SPARSE_ZERO_LEN(p);
-                    i += runlen;
-                    p++;
-                } else if (HLL_SPARSE_IS_XZERO(p)) {
-                    runlen = HLL_SPARSE_XZERO_LEN(p);
-                    i += runlen;
-                    p += 2;
-                } else {
-                    runlen = HLL_SPARSE_VAL_LEN(p);
-                    regval = HLL_SPARSE_VAL_VALUE(p);
-                    while(runlen--) {
-                        if (regval > max[i]) max[i] = regval;
-                        i++;
-                    }
-                    p++;
-                }
-            }
-            if (i != HLL_REGISTERS) {
-                addReplySds(c,sdsnew(invalid_hll_err));
-                return;
-            }
+        if (hllMerge(max,o) == REDIS_ERR) {
+            addReplySds(c,sdsnew(invalid_hll_err));
+            return;
         }
     }
 
@@ -1241,7 +1256,7 @@ void pfmergeCommand(redisClient *c) {
     HLL_INVALIDATE_CACHE(hdr);
 
     signalModifiedKey(c->db,c->argv[1]);
-    /* We generate an HLLADD event for HLLMERGE for semantical simplicity
+    /* We generate an PFADD event for PFMERGE for semantical simplicity
      * since in theory this is a mass-add of elements. */
     notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
     server.dirty++;