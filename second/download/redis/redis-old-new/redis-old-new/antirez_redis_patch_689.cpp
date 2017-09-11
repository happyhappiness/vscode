@@ -1233,7 +1233,7 @@ void pfcountCommand(redisClient *c) {
      *
      * The user specified a single key. Either return the cached value
      * or compute one and update the cache. */
-    o = lookupKeyRead(c->db,c->argv[1]);
+    o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
         /* No key? Cardinality is zero since no element was added, otherwise
          * we would have a key as HLLADD creates it as a side effect. */
@@ -1458,7 +1458,7 @@ void pfdebugCommand(redisClient *c) {
     robj *o;
     int j;
 
-    o = lookupKeyRead(c->db,c->argv[2]);
+    o = lookupKeyWrite(c->db,c->argv[2]);
     if (o == NULL) {
         addReplyError(c,"The specified key does not exist");
         return;