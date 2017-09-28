     config.interactive = 1;
     linenoiseSetMultiLine(1);
     linenoiseSetCompletionCallback(completionCallback);
 
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
 
     cliRefreshPrompt();
     while((line = linenoise(context ? config.prompt : "not connected> ")) != NULL) {
