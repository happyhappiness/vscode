@@ -1923,6 +1923,12 @@ int rewriteConfig(char *path) {
  *----------------------------------------------------------------------------*/
 
 void configCommand(client *c) {
+    /* Only allow CONFIG GET while loading. */
+    if (server.loading && strcasecmp(c->argv[1]->ptr,"get")) {
+        addReplyError(c,"Only CONFIG GET is allowed during loading");
+        return;
+    }
+
     if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc != 4) goto badarity;
         configSetCommand(c);