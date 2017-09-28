     return ustime()/1000;
 }
 
 static void cliRefreshPrompt(void) {
     int len;
 
+    if (config.eval_ldb) return;
     if (config.hostsocket != NULL)
         len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                        config.hostsocket);
     else
-        len = snprintf(config.prompt,sizeof(config.prompt),
-                       strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
-                       config.hostip, config.hostport);
+        len = anetFormatAddr(config.prompt, sizeof(config.prompt),
+                           config.hostip, config.hostport);
     /* Add [dbnum] if needed */
     if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
         len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
             config.dbnum);
     snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
 }
 
-static sds getHistoryPath() {
+/* Return the name of the dotfile for the specified 'dotfilename'.
+ * Normally it just concatenates user $HOME to the file specified
+ * in 'dotfilename'. However if the environment varialbe 'envoverride'
+ * is set, its value is taken as the path.
+ *
+ * The function returns NULL (if the file is /dev/null or cannot be
+ * obtained for some error), or an SDS string that must be freed by
+ * the user. */
+static sds getDotfilePath(char *envoverride, char *dotfilename) {
     char *path = NULL;
-    sds historyPath = NULL;
+    sds dotPath = NULL;
 
-    /* check the env for a histfile override */
-    path = getenv(REDIS_CLI_HISTFILE_ENV);
+    /* Check the env for a dotfile override. */
+    path = getenv(envoverride);
     if (path != NULL && *path != '\0') {
         if (!strcmp("/dev/null", path)) {
             return NULL;
         }
 
-        /* if the env is set, return it */
-        historyPath = sdscatprintf(sdsempty(), "%s", path);
+        /* If the env is set, return it. */
+        dotPath = sdsnew(path);
     } else {
         char *home = getenv("HOME");
         if (home != NULL && *home != '\0') {
-            /* otherwise, return the default */
-            historyPath = sdscatprintf(sdsempty(), "%s/%s", home, REDIS_CLI_HISTFILE_DEFAULT);
+            /* If no override is set use $HOME/<dotfilename>. */
+            dotPath = sdscatprintf(sdsempty(), "%s/%s", home, dotfilename);
         }
     }
-
-    return historyPath;
+    return dotPath;
 }
 
 /*------------------------------------------------------------------------------
  * Help functions
  *--------------------------------------------------------------------------- */
 
