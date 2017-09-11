@@ -2468,6 +2468,24 @@ void commandCommand(redisClient *c) {
         }
     } else if (!strcasecmp(c->argv[1]->ptr, "count") && c->argc == 2) {
         addReplyLongLong(c, dictSize(server.commands));
+    } else if (!strcasecmp(c->argv[1]->ptr,"getkeys") && c->argc >= 3) {
+        struct redisCommand *cmd = lookupCommand(c->argv[2]->ptr);
+        int *keys, numkeys, j;
+
+        if (!cmd) {
+            addReplyErrorFormat(c,"Invalid command specified");
+            return;
+        } else if ((cmd->arity > 0 && cmd->arity != c->argc-2) ||
+                   ((c->argc-2) < -cmd->arity))
+        {
+            addReplyError(c,"Invalid number of arguments specified for command");
+            return;
+        }
+
+        keys = getKeysFromCommand(cmd,c->argv+2,c->argc-2,&numkeys);
+        addReplyMultiBulkLen(c,numkeys);
+        for (j = 0; j < numkeys; j++) addReplyBulk(c,c->argv[keys[j]+2]);
+        getKeysFreeResult(keys);
     } else {
         addReplyError(c, "Unknown subcommand or wrong number of arguments.");
         return;