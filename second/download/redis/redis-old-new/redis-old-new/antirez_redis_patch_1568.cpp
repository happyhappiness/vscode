@@ -1390,7 +1390,7 @@ void restoreCommand(redisClient *c) {
     long ttl;
 
     /* Make sure this key does not already exist here... */
-    if (dbExists(c->db,c->argv[1])) {
+    if (lookupKeyWrite(c->db,c->argv[1]) != NULL) {
         addReplyError(c,"Target key name is busy.");
         return;
     }