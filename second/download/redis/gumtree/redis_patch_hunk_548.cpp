 }
 
 static int issueCommand(int argc, char **argv) {
     return issueCommandRepeat(argc, argv, config.repeat);
 }
 
+/* Split the user provided command into multiple SDS arguments.
+ * This function normally uses sdssplitargs() from sds.c which is able
+ * to understand "quoted strings", escapes and so forth. However when
+ * we are in Lua debugging mode and the "eval" command is used, we want
+ * the remaining Lua script (after "e " or "eval ") to be passed verbatim
+ * as a single big argument. */
+static sds *cliSplitArgs(char *line, int *argc) {
+    if (config.eval_ldb && (strstr(line,"eval ") == line ||
+                            strstr(line,"e ") == line))
+    {
+        sds *argv = sds_malloc(sizeof(sds)*2);
+        *argc = 2;
+        int len = strlen(line);
+        int elen = line[1] == ' ' ? 2 : 5; /* "e " or "eval "? */
+        argv[0] = sdsnewlen(line,elen-1);
+        argv[1] = sdsnewlen(line+elen,len-elen);
+        return argv;
+    } else {
+        return sdssplitargs(line,argc);
+    }
+}
+
+/* Set the CLI perferences. This function is invoked when an interactive
+ * ":command" is called, or when reading ~/.redisclirc file, in order to
+ * set user preferences. */
+void cliSetPreferences(char **argv, int argc, int interactive) {
+    if (!strcasecmp(argv[0],":set") && argc >= 2) {
+        if (!strcasecmp(argv[1],"hints")) pref.hints = 1;
+        else if (!strcasecmp(argv[1],"nohints")) pref.hints = 0;
+        else {
+            printf("%sunknown redis-cli preference '%s'\n",
+                interactive ? "" : ".redisclirc: ",
+                argv[1]);
+        }
+    } else {
+        printf("%sunknown redis-cli internal command '%s'\n",
+            interactive ? "" : ".redisclirc: ",
+            argv[0]);
+    }
+}
+
+/* Load the ~/.redisclirc file if any. */
+void cliLoadPreferences(void) {
+    sds rcfile = getDotfilePath(REDIS_CLI_RCFILE_ENV,REDIS_CLI_RCFILE_DEFAULT);
+    if (rcfile == NULL) return;
+    FILE *fp = fopen(rcfile,"r");
+    char buf[1024];
+
+    if (fp) {
+        while(fgets(buf,sizeof(buf),fp) != NULL) {
+            sds *argv;
+            int argc;
+
+            argv = sdssplitargs(buf,&argc);
+            if (argc > 0) cliSetPreferences(argv,argc,0);
+            sdsfreesplitres(argv,argc);
+        }
+    }
+    sdsfree(rcfile);
+}
+
 static void repl(void) {
     sds historyfile = NULL;
     int history = 0;
     char *line;
     int argc;
     sds *argv;
 
     config.interactive = 1;
     linenoiseSetMultiLine(1);
     linenoiseSetCompletionCallback(completionCallback);
+    linenoiseSetHintsCallback(hintsCallback);
+    linenoiseSetFreeHintsCallback(freeHintsCallback);
 
-    /* Only use history when stdin is a tty. */
+    /* Only use history and load the rc file when stdin is a tty. */
     if (isatty(fileno(stdin))) {
-        historyfile = getHistoryPath();
+        historyfile = getDotfilePath(REDIS_CLI_HISTFILE_ENV,REDIS_CLI_HISTFILE_DEFAULT);
         if (historyfile != NULL) {
             history = 1;
             linenoiseHistoryLoad(historyfile);
         }
+        cliLoadPreferences();
     }
 
     cliRefreshPrompt();
     while((line = linenoise(context ? config.prompt : "not connected> ")) != NULL) {
         if (line[0] != '\0') {
-            argv = sdssplitargs(line,&argc);
+            argv = cliSplitArgs(line,&argc);
             if (history) linenoiseHistoryAdd(line);
             if (historyfile) linenoiseHistorySave(historyfile);
 
             if (argv == NULL) {
                 printf("Invalid argument(s)\n");
                 free(line);
                 continue;
             } else if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||
                     strcasecmp(argv[0],"exit") == 0)
                 {
                     exit(0);
+                } else if (argv[0][0] == ':') {
+                    cliSetPreferences(argv,argc,1);
+                    continue;
+                } else if (strcasecmp(argv[0],"restart") == 0) {
+                    if (config.eval) {
+                        config.eval_ldb = 1;
+                        config.output = OUTPUT_RAW;
+                        return; /* Return to evalMode to restart the session. */
+                    } else {
+                        printf("Use 'restart' only in Lua debugging mode.");
+                    }
                 } else if (argc == 3 && !strcasecmp(argv[0],"connect")) {
                     sdsfree(config.hostip);
                     config.hostip = sdsnew(argv[1]);
                     config.hostport = atoi(argv[2]);
                     cliRefreshPrompt();
                     cliConnect(1);
