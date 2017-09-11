@@ -60,6 +60,8 @@
 #define OUTPUT_CSV 2
 #define REDIS_CLI_KEEPALIVE_INTERVAL 15 /* seconds */
 #define REDIS_CLI_DEFAULT_PIPE_TIMEOUT 30 /* seconds */
+#define REDIS_CLI_HISTFILE_ENV "REDISCLI_HISTFILE"
+#define REDIS_CLI_HISTFILE_DEFAULT ".rediscli_history"
 
 static redisContext *context;
 static struct config {
@@ -138,6 +140,30 @@ static void cliRefreshPrompt(void) {
     snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
 }
 
+static sds getHistoryPath() {
+    char *path = NULL;
+    sds historyPath = NULL;
+
+    /* check the env for a histfile override */
+    path = getenv(REDIS_CLI_HISTFILE_ENV);
+    if (path != NULL && *path != '\0') {
+        if (!strcmp("/dev/null", path)) {
+            return NULL;
+        }
+
+        /* if the env is set, return it */
+        historyPath = sdscatprintf(sdsempty(), "%s", path);
+    } else {
+        char *home = getenv("HOME");
+        if (home != NULL && *home != '\0') {
+            /* otherwise, return the default */
+            historyPath = sdscatprintf(sdsempty(), "%s/%s", home, REDIS_CLI_HISTFILE_DEFAULT);
+        }
+    }
+
+    return historyPath;
+}
+
 /*------------------------------------------------------------------------------
  * Help functions
  *--------------------------------------------------------------------------- */
@@ -891,10 +917,9 @@ static void repl(void) {
 
     /* Only use history when stdin is a tty. */
     if (isatty(fileno(stdin))) {
-        history = 1;
-
-        if (getenv("HOME") != NULL) {
-            historyfile = sdscatprintf(sdsempty(),"%s/.rediscli_history",getenv("HOME"));
+        historyfile = getHistoryPath();
+        if (historyfile != NULL) {
+            history = 1;
             linenoiseHistoryLoad(historyfile);
         }
     }