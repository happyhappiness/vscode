@@ -1249,7 +1249,9 @@ int prepareForShutdown() {
 /*================================== Commands =============================== */
 
 void authCommand(redisClient *c) {
-    if (!server.requirepass || !strcmp(c->argv[1]->ptr, server.requirepass)) {
+    if (!server.requirepass) {
+        addReplyError(c,"Client sent AUTH, but no password is set");
+    } else if (!strcmp(c->argv[1]->ptr, server.requirepass)) {
       c->authenticated = 1;
       addReply(c,shared.ok);
     } else {