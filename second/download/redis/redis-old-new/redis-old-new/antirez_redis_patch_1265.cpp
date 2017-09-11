@@ -1539,15 +1539,25 @@ void dumpCommand(redisClient *c) {
     return;
 }
 
-/* RESTORE key ttl serialized-value */
+/* RESTORE key ttl serialized-value [REPLACE] */
 void restoreCommand(redisClient *c) {
     long ttl;
     rio payload;
-    int type;
+    int j, type, replace = 0;
     robj *obj;
 
+    /* Parse additional options */
+    for (j = 4; j < c->argc; j++) {
+        if (!strcasecmp(c->argv[j]->ptr,"replace")) {
+            replace = 1;
+        } else {
+            addReply(c,shared.syntaxerr);
+            return;
+        }
+    }
+
     /* Make sure this key does not already exist here... */
-    if (lookupKeyWrite(c->db,c->argv[1]) != NULL) {
+    if (!replace && lookupKeyWrite(c->db,c->argv[1]) != NULL) {
         addReplyError(c,"Target key name is busy.");
         return;
     }
@@ -1574,6 +1584,9 @@ void restoreCommand(redisClient *c) {
         return;
     }
 
+    /* Remove the old key if needed. */
+    if (replace) dbDelete(c->db,c->argv[1]);
+
     /* Create the key and set the TTL if any */
     dbAdd(c->db,c->argv[1],obj);
     if (ttl) setExpire(c->db,c->argv[1],mstime()+ttl);