@@ -1786,7 +1786,7 @@ void configCommand(redisClient *c) {
         }
     } else {
         addReplyError(c,
-            "CONFIG subcommand must be one of GET, SET, RESETSTAT");
+            "CONFIG subcommand must be one of GET, SET, RESETSTAT, REWRITE");
     }
     return;
 