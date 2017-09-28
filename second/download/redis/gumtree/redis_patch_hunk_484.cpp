 }
 
 /*-----------------------------------------------------------------------------
  * CONFIG command entry point
  *----------------------------------------------------------------------------*/
 
-void configCommand(redisClient *c) {
+void configCommand(client *c) {
+    /* Only allow CONFIG GET while loading. */
+    if (server.loading && strcasecmp(c->argv[1]->ptr,"get")) {
+        addReplyError(c,"Only CONFIG GET is allowed during loading");
+        return;
+    }
+
     if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc != 4) goto badarity;
         configSetCommand(c);
     } else if (!strcasecmp(c->argv[1]->ptr,"get")) {
         if (c->argc != 3) goto badarity;
         configGetCommand(c);
