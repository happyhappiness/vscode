@@ -64,6 +64,7 @@ static struct config {
     char *auth;
     int raw_output; /* output mode per command */
     sds mb_delim;
+    char prompt[32];
 } config;
 
 static void usage();
@@ -84,6 +85,13 @@ static long long mstime(void) {
     return mst;
 }
 
+static void cliRefreshPrompt(void) {
+    if (config.dbnum == 0)
+        snprintf(config.prompt,sizeof(config.prompt),"redis> ");
+    else
+        snprintf(config.prompt,sizeof(config.prompt),"redis:%d> ",config.dbnum);
+}
+
 /*------------------------------------------------------------------------------
  * Help functions
  *--------------------------------------------------------------------------- */
@@ -491,8 +499,10 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             return REDIS_ERR;
         } else {
             /* Store database number when SELECT was successfully executed. */
-            if (!strcasecmp(command,"select") && argc == 2)
+            if (!strcasecmp(command,"select") && argc == 2) {
                 config.dbnum = atoi(argv[1]);
+                cliRefreshPrompt();
+            }
         }
     }
 
@@ -633,7 +643,8 @@ static void repl() {
         }
     }
 
-    while((line = linenoise(context ? "redis> " : "not connected> ")) != NULL) {
+    cliRefreshPrompt();
+    while((line = linenoise(context ? config.prompt : "not connected> ")) != NULL) {
         if (line[0] != '\0') {
             argv = sdssplitargs(line,&argc);
             if (history) linenoiseHistoryAdd(line);