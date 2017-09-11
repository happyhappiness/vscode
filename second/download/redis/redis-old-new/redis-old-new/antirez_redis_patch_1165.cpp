@@ -332,9 +332,14 @@ void debugCommand(redisClient *c) {
 
         usleep(utime);
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"set-active-expire") &&
+               c->argc == 3)
+    {
+        server.active_expire_enabled = atoi(c->argv[2]->ptr);
+        addReply(c,shared.ok);
     } else {
-        addReplyError(c,
-            "Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]");
+        addReplyErrorFormat(c, "Unknown DEBUG subcommand '%s'",
+            (char*)c->argv[1]->ptr);
     }
 }
 