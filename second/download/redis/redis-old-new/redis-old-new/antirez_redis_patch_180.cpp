@@ -161,7 +161,7 @@ static void cliRefreshPrompt(void) {
         len = anetFormatAddr(config.prompt, sizeof(config.prompt),
                            config.hostip, config.hostport);
     /* Add [dbnum] if needed */
-    if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
+    if (config.dbnum != 0)
         len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
             config.dbnum);
     snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");