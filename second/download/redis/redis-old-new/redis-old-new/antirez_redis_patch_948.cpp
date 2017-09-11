@@ -363,6 +363,18 @@ void debugCommand(redisClient *c) {
     {
         server.active_expire_enabled = atoi(c->argv[2]->ptr);
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"cmdkeys") && c->argc >= 3) {
+        struct redisCommand *cmd = lookupCommand(c->argv[2]->ptr);
+        int *keys, numkeys, j;
+
+        if (!cmd) {
+            addReplyError(c,"Invalid command specified");
+            return;
+        }
+        keys = getKeysFromCommand(cmd,c->argv+2,c->argc-2,&numkeys);
+        addReplyMultiBulkLen(c,numkeys);
+        for (j = 0; j < numkeys; j++) addReplyBulk(c,c->argv[keys[j]+2]);
+        getKeysFreeResult(keys);
     } else {
         addReplyErrorFormat(c, "Unknown DEBUG subcommand or wrong number of arguments for '%s'",
             (char*)c->argv[1]->ptr);