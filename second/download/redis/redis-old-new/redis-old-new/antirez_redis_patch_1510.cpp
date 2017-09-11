@@ -737,8 +737,8 @@ void scriptCommand(redisClient *c) {
                 return;
             }
         }
+        addReplyBulkCBuffer(c,funcname+2,40);
         sdsfree(sha);
-        addReply(c,shared.ok);
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }