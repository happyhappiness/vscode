@@ -161,7 +161,7 @@ double extractDistanceOrReply(client *c, robj **argv,
         addReplyError(c,"radius cannot be negative");
         return -1;
     }
-    
+
     double to_meters = extractUnitOrReply(c,argv[1]);
     if (to_meters < 0) {
         return -1;
@@ -738,16 +738,15 @@ void geoposCommand(client *c) {
     int j;
 
     /* Look up the requested zset */
-    robj *zobj = NULL;
-    if ((zobj = lookupKeyReadOrReply(c, c->argv[1], shared.emptymultibulk))
-        == NULL || checkType(c, zobj, OBJ_ZSET)) return;
+    robj *zobj = lookupKeyRead(c->db, c->argv[1]);
+    if (zobj && checkType(c, zobj, OBJ_ZSET)) return;
 
     /* Report elements one after the other, using a null bulk reply for
      * missing elements. */
     addReplyMultiBulkLen(c,c->argc-2);
     for (j = 2; j < c->argc; j++) {
         double score;
-        if (zsetScore(zobj, c->argv[j]->ptr, &score) == C_ERR) {
+        if (!zobj || zsetScore(zobj, c->argv[j]->ptr, &score) == C_ERR) {
             addReply(c,shared.nullmultibulk);
         } else {
             /* Decode... */
@@ -782,7 +781,7 @@ void geodistCommand(client *c) {
 
     /* Look up the requested zset */
     robj *zobj = NULL;
-    if ((zobj = lookupKeyReadOrReply(c, c->argv[1], shared.emptybulk))
+    if ((zobj = lookupKeyReadOrReply(c, c->argv[1], shared.nullbulk))
         == NULL || checkType(c, zobj, OBJ_ZSET)) return;
 
     /* Get the scores. We need both otherwise NULL is returned. */