@@ -1474,7 +1474,7 @@ void scriptCommand(client *c) {
             addReply(c,shared.ok);
             c->flags |= CLIENT_LUA_DEBUG_SYNC;
         } else {
-            addReplyError(c,"Use SCRIPT DEBUG yes/async/no");
+            addReplyError(c,"Use SCRIPT DEBUG yes/sync/no");
         }
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");