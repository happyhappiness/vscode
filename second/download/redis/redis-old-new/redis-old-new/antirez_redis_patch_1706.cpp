@@ -62,7 +62,6 @@ static struct config {
     int pubsub_mode;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
-    char *historyfile;
     int raw_output; /* output mode per command */
     sds mb_delim;
 } config;
@@ -609,18 +608,31 @@ static char **convertToSds(int count, char** args) {
 
 #define LINE_BUFLEN 4096
 static void repl() {
-    int argc, j;
+    sds historyfile = NULL;
+    int history = 0;
     char *line;
+    int argc;
     sds *argv;
 
     config.interactive = 1;
     linenoiseSetCompletionCallback(completionCallback);
 
+    /* Only use history when stdin is a tty. */
+    if (isatty(fileno(stdin))) {
+        history = 1;
+
+        if (getenv("HOME") != NULL) {
+            historyfile = sdscatprintf(sdsempty(),"%s/.rediscli_history",getenv("HOME"));
+            linenoiseHistoryLoad(historyfile);
+        }
+    }
+
     while((line = linenoise(context ? "redis> " : "not connected> ")) != NULL) {
         if (line[0] != '\0') {
             argv = sdssplitargs(line,&argc);
-            linenoiseHistoryAdd(line);
-            if (config.historyfile) linenoiseHistorySave(config.historyfile);
+            if (history) linenoiseHistoryAdd(line);
+            if (historyfile) linenoiseHistorySave(historyfile);
+
             if (argv == NULL) {
                 printf("Invalid argument(s)\n");
                 continue;
@@ -654,8 +666,7 @@ static void repl() {
                 }
             }
             /* Free the argument vector */
-            for (j = 0; j < argc; j++)
-                sdsfree(argv[j]);
+            while(argc--) sdsfree(argv[argc]);
             zfree(argv);
         }
         /* linenoise() returns malloc-ed lines like readline() */
@@ -691,17 +702,10 @@ int main(int argc, char **argv) {
     config.pubsub_mode = 0;
     config.stdinarg = 0;
     config.auth = NULL;
-    config.historyfile = NULL;
     config.raw_output = !isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL);
     config.mb_delim = sdsnew("\n");
     cliInitHelp();
 
-    if (getenv("HOME") != NULL) {
-        config.historyfile = malloc(256);
-        snprintf(config.historyfile,256,"%s/.rediscli_history",getenv("HOME"));
-        linenoiseHistoryLoad(config.historyfile);
-    }
-
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;
     argv += firstarg;