@@ -909,6 +909,16 @@ uint64_t hllCount(struct hllhdr *hdr) {
     return (uint64_t) E;
 }
 
+/* Call hllDenseAdd() or hllSparseAdd() according to the HLL encoding. */
+int hllAdd(robj *o, unsigned char *ele, size_t elesize) {
+    struct hllhdr *hdr = o->ptr;
+    switch(hdr->encoding) {
+    case HLL_DENSE: return hllDenseAdd(hdr->registers,ele,elesize);
+    case HLL_SPARSE: return hllSparseAdd(o,ele,elesize);
+    default: return -1; /* Invalid representation. */
+    }
+}
+
 /* ========================== HyperLogLog commands ========================== */
 
 /* Create an HLL object. We always create the HLL using sparse encoding.
@@ -996,14 +1006,19 @@ void pfaddCommand(redisClient *c) {
         o = dbUnshareStringValue(c->db,c->argv[1],o);
     }
     /* Perform the low level ADD operation for every element. */
-    hdr = o->ptr;
     for (j = 2; j < c->argc; j++) {
-        if (hllDenseAdd(hdr->registers, (unsigned char*)c->argv[j]->ptr,
-                        sdslen(c->argv[j]->ptr)))
-        {
+        int retval = hllAdd(o, (unsigned char*)c->argv[j]->ptr,
+                               sdslen(c->argv[j]->ptr));
+        switch(retval) {
+        case 1:
             updated++;
+            break;
+        case -1:
+            addReplyError(c,"Invalid HyperLogLog representation");
+            return;
         }
     }
+    hdr = o->ptr;
     if (updated) {
         signalModifiedKey(c->db,c->argv[1]);
         notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);