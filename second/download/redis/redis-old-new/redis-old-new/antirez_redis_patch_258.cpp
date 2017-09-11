@@ -1222,7 +1222,6 @@ static void repl(void) {
         if (historyfile != NULL) {
             history = 1;
             linenoiseHistoryLoad(historyfile);
-            sdsfree(historyfile);
         }
         cliLoadPreferences();
     }
@@ -1232,6 +1231,7 @@ static void repl(void) {
         if (line[0] != '\0') {
             argv = cliSplitArgs(line,&argc);
             if (history) linenoiseHistoryAdd(line);
+            printf("HISTORY: %s\n", historyfile);
             if (historyfile) linenoiseHistorySave(historyfile);
 
             if (argv == NULL) {