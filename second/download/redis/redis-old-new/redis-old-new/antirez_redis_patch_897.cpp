@@ -1130,7 +1130,7 @@ void pfcountCommand(redisClient *c) {
             /* Recompute it and update the cached value. */
             card = hllCount(hdr,&invalid);
             if (invalid) {
-                addReplyError(c,"Invalid HLL object");
+                addReplyError(c,"Invalid HLL object detected");
                 return;
             }
             hdr->card[0] = card & 0xff;
@@ -1163,8 +1163,6 @@ void pfmergeCommand(redisClient *c) {
      * it to the target variable later. */
     memset(max,0,sizeof(max));
     for (j = 1; j < c->argc; j++) {
-        uint8_t val;
-
         /* Check type and size. */
         robj *o = lookupKeyRead(c->db,c->argv[j]);
         if (o == NULL) continue; /* Assume empty HLL for non existing var. */
@@ -1173,14 +1171,47 @@ void pfmergeCommand(redisClient *c) {
         /* Merge with this HLL with our 'max' HHL by setting max[i]
          * to MAX(max[i],hll[i]). */
         hdr = o->ptr;
-        for (i = 0; i < HLL_REGISTERS; i++) {
-            HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
-            if (val > max[i]) max[i] = val;
+        if (hdr->encoding == HLL_DENSE) {
+            uint8_t val;
+
+            for (i = 0; i < HLL_REGISTERS; i++) {
+                HLL_DENSE_GET_REGISTER(val,hdr->registers,i);
+                if (val > max[i]) max[i] = val;
+            }
+        } else {
+            uint8_t *p = o->ptr, *end = p + sdslen(o->ptr);
+            long runlen, regval;
+
+            p += HLL_HDR_SIZE;
+            i = 0;
+            while(p < end) {
+                if (HLL_SPARSE_IS_ZERO(p)) {
+                    runlen = HLL_SPARSE_ZERO_LEN(p);
+                    i += runlen;
+                    p++;
+                } else if (HLL_SPARSE_IS_XZERO(p)) {
+                    runlen = HLL_SPARSE_XZERO_LEN(p);
+                    i += runlen;
+                    p += 2;
+                } else {
+                    runlen = HLL_SPARSE_VAL_LEN(p);
+                    regval = HLL_SPARSE_VAL_VALUE(p);
+                    while(runlen--) {
+                        if (regval > max[i]) max[i] = regval;
+                        i++;
+                    }
+                    p++;
+                }
+            }
+            if (i != HLL_REGISTERS) {
+                addReplyError(c,"Invalid HLL object detected");
+                return;
+            }
         }
     }
 
     /* Create / unshare the destination key's value if needed. */
-    robj *o = lookupKeyRead(c->db,c->argv[1]);
+    robj *o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
         /* Create the key with a string value of the exact length to
          * hold our HLL data structure. sdsnewlen() when NULL is passed
@@ -1194,6 +1225,12 @@ void pfmergeCommand(redisClient *c) {
         o = dbUnshareStringValue(c->db,c->argv[1],o);
     }
 
+    /* Only support dense objects as destination. */
+    if (hllSparseToDense(o) == REDIS_ERR) {
+        addReplyError(c,"Invalid HLL object detected");
+        return;
+    }
+
     /* Write the resulting HLL to the destination HLL registers and
      * invalidate the cached value. */
     hdr = o->ptr;
@@ -1308,7 +1345,7 @@ void pfdebugCommand(redisClient *c) {
 
         if (hdr->encoding == HLL_SPARSE) {
             if (hllSparseToDense(o) == REDIS_ERR) {
-                addReplyError(c,"HLL sparse encoding is corrupted");
+                addReplyError(c,"Invalid HLL object detected");
                 return;
             }
             server.dirty++; /* Force propagation on encoding change. */