@@ -68,7 +68,7 @@ static struct config {
     char *auth;
     int raw_output; /* output mode per command */
     sds mb_delim;
-    char prompt[32];
+    char prompt[128];
     char *eval;
 } config;
 
@@ -91,12 +91,19 @@ static long long mstime(void) {
 }
 
 static void cliRefreshPrompt(void) {
-    if (config.dbnum == 0)
-        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d> ",
-            config.hostip, config.hostport);
+    int len;
+
+    if (config.hostsocket != NULL)
+        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
+                       config.hostsocket);
     else
-        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d[%d]> ",
-            config.hostip, config.hostport, config.dbnum);
+        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d",
+                       config.hostip, config.hostport);
+    /* Add [dbnum] if needed */
+    if (config.dbnum != 0)
+        len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
+            config.dbnum);
+    snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
 }
 
 /*------------------------------------------------------------------------------