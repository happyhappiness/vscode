@@ -116,7 +116,8 @@ static void cliRefreshPrompt(void) {
         len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                        config.hostsocket);
     else
-        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d",
+        len = snprintf(config.prompt,sizeof(config.prompt),
+                       strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
                        config.hostip, config.hostport);
     /* Add [dbnum] if needed */
     if (config.dbnum != 0)