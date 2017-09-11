@@ -2521,6 +2521,15 @@ void sentinelCommand(redisClient *c) {
             sentinelFlushConfig();
             addReply(c,shared.ok);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"remove")) {
+        /* SENTINEL REMOVE <name> */
+        sentinelRedisInstance *ri;
+
+        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
+            == NULL) return;
+        dictDelete(sentinel.masters,c->argv[2]->ptr);
+        sentinelFlushConfig();
+        addReply(c,shared.ok);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);