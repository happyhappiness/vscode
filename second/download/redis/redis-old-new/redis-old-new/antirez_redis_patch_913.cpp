@@ -456,6 +456,23 @@ robj *createHLLObject(void) {
     return o;
 }
 
+/* Check if the object is a String of REDIS_HLL_SIZE bytes.
+ * Return REDIS_OK if this is true, otherwise reply to the client
+ * with an error and return REDIS_ERR. */
+int isHLLObjectOrReply(redisClient *c, robj *o) {
+    /* Key exists, check type */
+    if (checkType(c,o,REDIS_STRING))
+        return REDIS_ERR; /* Error already sent. */
+
+    /* If this is a string representing an HLL, the size should match
+     * exactly. */
+    if (stringObjectLen(o) != REDIS_HLL_SIZE) {
+        addReplyErrorFormat(c, "Key is not a valid HyperLogLog string value.");
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* PFADD var ele ele ele ... ele => :0 or :1 */
 void pfaddCommand(redisClient *c) {
     robj *o = lookupKeyWrite(c->db,c->argv[1]);
@@ -470,18 +487,7 @@ void pfaddCommand(redisClient *c) {
         dbAdd(c->db,c->argv[1],o);
         updated++;
     } else {
-        /* Key exists, check type */
-        if (checkType(c,o,REDIS_STRING))
-            return;
-
-        /* If this is a string representing an HLL, the size should match
-         * exactly. */
-        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
-            addReplyErrorFormat(c,
-                "PFADD target key must contain a %d bytes string.",
-                REDIS_HLL_SIZE);
-            return;
-        }
+        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
         o = dbUnshareStringValue(c->db,c->argv[1],o);
     }
     /* Perform the low level ADD operation for every element. */
@@ -514,18 +520,7 @@ void pfcountCommand(redisClient *c) {
          * we would have a key as HLLADD creates it as a side effect. */
         addReply(c,shared.czero);
     } else {
-        /* Key exists, check type */
-        if (checkType(c,o,REDIS_STRING))
-            return;
-
-        /* If this is a string representing an HLL, the size should match
-         * exactly. */
-        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
-            addReplyErrorFormat(c,
-                "PFCOUNT target key must contain a %d bytes string.",
-                REDIS_HLL_SIZE);
-            return;
-        }
+        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
 
         /* Check if the cached cardinality is valid. */
         registers = o->ptr;
@@ -580,15 +575,7 @@ void pfmergeCommand(redisClient *c) {
         /* Check type and size. */
         robj *o = lookupKeyRead(c->db,c->argv[j]);
         if (o == NULL) continue; /* Assume empty HLL for non existing var. */
-        if (checkType(c,o,REDIS_STRING))
-            return;
-
-        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
-            addReplyErrorFormat(c,
-                "PFADD target key must contain a %d bytes string.",
-                REDIS_HLL_SIZE);
-            return;
-        }
+        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
 
         /* Merge with this HLL with our 'max' HHL by setting max[i]
          * to MAX(max[i],hll[i]). */
@@ -716,18 +703,7 @@ void pfgetregCommand(redisClient *c) {
         addReplyError(c,"The specified key does not exist");
         return;
     } else {
-        /* Key exists, check type */
-        if (checkType(c,o,REDIS_STRING))
-            return;
-
-        /* If this is a string representing an HLL, the size should match
-         * exactly. */
-        if (stringObjectLen(o) != REDIS_HLL_SIZE) {
-            addReplyErrorFormat(c,
-                "PFCOUNT target key must contain a %d bytes string.",
-                REDIS_HLL_SIZE);
-            return;
-        }
+        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
 
         registers = o->ptr;
         addReplyMultiBulkLen(c,REDIS_HLL_REGISTERS);