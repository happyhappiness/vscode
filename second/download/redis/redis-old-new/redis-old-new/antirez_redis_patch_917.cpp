@@ -458,7 +458,7 @@ void pfaddCommand(redisClient *c) {
          * exactly. */
         if (stringObjectLen(o) != REDIS_HLL_SIZE) {
             addReplyErrorFormat(c,
-                "HLLADD target key must contain a %d bytes string.",
+                "PFADD target key must contain a %d bytes string.",
                 REDIS_HLL_SIZE);
             return;
         }
@@ -475,7 +475,7 @@ void pfaddCommand(redisClient *c) {
     }
     if (updated) {
         signalModifiedKey(c->db,c->argv[1]);
-        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
+        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
         server.dirty++;
         /* Invalidate the cached cardinality. */
         registers[REDIS_HLL_SIZE-1] |= (1<<7);
@@ -502,7 +502,7 @@ void pfcountCommand(redisClient *c) {
          * exactly. */
         if (stringObjectLen(o) != REDIS_HLL_SIZE) {
             addReplyErrorFormat(c,
-                "HLLCOUNT target key must contain a %d bytes string.",
+                "PFCOUNT target key must contain a %d bytes string.",
                 REDIS_HLL_SIZE);
             return;
         }
@@ -562,7 +562,7 @@ void pfmergeCommand(redisClient *c) {
 
         if (stringObjectLen(o) != REDIS_HLL_SIZE) {
             addReplyErrorFormat(c,
-                "HLLADD target key must contain a %d bytes string.",
+                "PFADD target key must contain a %d bytes string.",
                 REDIS_HLL_SIZE);
             return;
         }
@@ -602,7 +602,7 @@ void pfmergeCommand(redisClient *c) {
     signalModifiedKey(c->db,c->argv[1]);
     /* We generate an HLLADD event for HLLMERGE for semantical simplicity
      * since in theory this is a mass-add of elements. */
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"hlladd",c->argv[1],c->db->id);
+    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
     server.dirty++;
     addReply(c,shared.ok);
 }