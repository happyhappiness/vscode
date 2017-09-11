@@ -475,7 +475,7 @@ void pfaddCommand(redisClient *c) {
     }
     if (updated) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
         server.dirty++;
         /* Invalidate the cached cardinality. */
         registers[REDIS_HLL_SIZE-1] |= (1<<7);
@@ -602,7 +602,7 @@ void pfmergeCommand(redisClient *c) {
     signalModifiedKey(c->db,c->argv[1]);
     /* We generate an HLLADD event for HLLMERGE for semantical simplicity
      * since in theory this is a mass-add of elements. */
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.ok);
 }