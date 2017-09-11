@@ -533,6 +533,70 @@ void hllCountCommand(redisClient *c) {
     }
 }
 
+/* HLLMERGE dest src1 src2 src3 ... srcN => OK */
+void hllMergeCommand(redisClient *c) {
+    uint8_t max[REDIS_HLL_REGISTERS];
+    uint8_t *registers;
+    int j;
+
+    /* Compute an HLL with M[i] = MAX(M[i]_j).
+     * We we the maximum into the max array of registers. We'll write
+     * it to the target variable later. */
+    memset(max,0,sizeof(max));
+    for (j = 1; j < c->argc; j++) {
+        uint8_t val;
+
+        /* Check type and size. */
+        robj *o = lookupKeyRead(c->db,c->argv[j]);
+        if (o == NULL) continue; /* Assume empty HLL for non existing var. */
+        if (checkType(c,o,REDIS_STRING))
+            return;
+
+        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
+            addReplyErrorFormat(c,
+                "HLLADD target key must contain a %d bytes string.",
+                REDIS_HLL_SIZE);
+            return;
+        }
+
+        /* Get the register and set it at max[j] if it's the greatest
+         * value so far. */
+        registers = o->ptr;
+        HLL_GET_REGISTER(val,registers,j);
+        if (val > max[j]) max[j] = val;
+    }
+
+    /* Create / unshare the destination key's value if needed. */
+    robj *o = lookupKeyRead(c->db,c->argv[1]);
+    if (o == NULL) {
+        /* Create the key with a string value of the exact length to
+         * hold our HLL data structure. sdsnewlen() when NULL is passed
+         * is guaranteed to return bytes initialized to zero. */
+        o = createObject(REDIS_STRING,sdsnewlen(NULL,REDIS_HLL_SIZE));
+        dbAdd(c->db,c->argv[1],o);
+    } else {
+        /* If key exists we are sure it's of the right type/size
+         * since we checked when merging the different HLLs, so we
+         * don't check again. */
+        o = dbUnshareStringValue(c->db,c->argv[1],o);
+    }
+
+    /* Write the resulting HLL to the destination HLL registers and
+     * invalidate the cached value. */
+    registers = o->ptr;
+    for (j = 0; j < REDIS_HLL_REGISTERS; j++) {
+        HLL_SET_REGISTER(registers,j,max[j]);
+    }
+    registers[REDIS_HLL_SIZE-1] |= (1<<7);
+
+    signalModifiedKey(c->db,c->argv[1]);
+    /* We generate an HLLADD event for HLLMERGE for semantical simplicity
+     * since in theory this is a mass-add of elements. */
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
+    server.dirty++;
+    addReply(c,shared.ok);
+}
+
 /* This command performs a self-test of the HLL registers implementation.
  * Something that is not easy to test from within the outside.
  *