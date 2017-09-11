@@ -991,7 +991,7 @@ uint64_t hllCount(struct hllhdr *hdr, int *invalid) {
     } else if (hdr->encoding == HLL_RAW) {
         E = hllRawSum(hdr->registers,PE,&ez);
     } else {
-        redisPanic("Unknown HyperLogLog encoding in hllCount()");
+        serverPanic("Unknown HyperLogLog encoding in hllCount()");
     }
 
     /* Muliply the inverse of E for alpha_m * m^2 to have the raw estimate. */
@@ -1184,7 +1184,7 @@ void pfaddCommand(client *c) {
     hdr = o->ptr;
     if (updated) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
         server.dirty++;
         HLL_INVALIDATE_CACHE(hdr);
     }
@@ -1337,7 +1337,7 @@ void pfmergeCommand(client *c) {
     signalModifiedKey(c->db,c->argv[1]);
     /* We generate an PFADD event for PFMERGE for semantical simplicity
      * since in theory this is a mass-add of elements. */
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.ok);
 }