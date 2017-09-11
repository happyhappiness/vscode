@@ -2644,6 +2644,7 @@ void sentinelSetCommand(redisClient *c) {
             if (strlen(value) && access(value,X_OK) == -1) {
                 addReplyError(c,
                     "Notification script seems non existing or non executable");
+                if (changes) sentinelFlushConfig();
                 return;
             }
             sdsfree(ri->notification_script);
@@ -2655,6 +2656,7 @@ void sentinelSetCommand(redisClient *c) {
                 addReplyError(c,
                     "Client reconfiguration script seems non existing or "
                     "non executable");
+                if (changes) sentinelFlushConfig();
                 return;
             }
             sdsfree(ri->client_reconfig_script);
@@ -2665,6 +2667,11 @@ void sentinelSetCommand(redisClient *c) {
             sdsfree(ri->auth_pass);
             ri->auth_pass = strlen(value) ? sdsnew(value) : NULL;
             changes++;
+        } else {
+            addReplyErrorFormat(c,"Unknown option '%s' for SENTINEL SET",
+                option);
+            if (changes) sentinelFlushConfig();
+            return;
         }
     }
 