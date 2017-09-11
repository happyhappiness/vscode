@@ -63,6 +63,8 @@
 #define REDIS_CLI_DEFAULT_PIPE_TIMEOUT 30 /* seconds */
 #define REDIS_CLI_HISTFILE_ENV "REDISCLI_HISTFILE"
 #define REDIS_CLI_HISTFILE_DEFAULT ".rediscli_history"
+#define REDIS_CLI_RCFILE_ENV "REDISCLI_RCFILE"
+#define REDIS_CLI_RCFILE_DEFAULT ".redisclirc"
 
 /* --latency-dist palettes. */
 int spectrum_palette_color_size = 19;
@@ -118,6 +120,11 @@ static struct config {
     int last_cmd_type;
 } config;
 
+/* User preferences. */
+static struct pref {
+    int hints;
+} pref;
+
 static volatile sig_atomic_t force_cancel_loop = 0;
 static void usage(void);
 static void slaveMode(void);
@@ -159,28 +166,35 @@ static void cliRefreshPrompt(void) {
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
@@ -259,11 +273,17 @@ static void cliOutputCommandHelp(struct commandHelp *help, int group) {
 static void cliOutputGenericHelp(void) {
     sds version = cliVersion();
     printf(
-        "redis-cli %s\r\n"
-        "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
-        "      \"help <command>\" for help on <command>\r\n"
-        "      \"help <tab>\" to get a list of possible help topics\r\n"
-        "      \"quit\" to exit\r\n",
+        "redis-cli %s\n"
+        "To get help about Redis commands type:\n"
+        "      \"help @<group>\" to get a list of commands in <group>\n"
+        "      \"help <command>\" for help on <command>\n"
+        "      \"help <tab>\" to get a list of possible help topics\n"
+        "      \"quit\" to exit\n"
+        "\n"
+        "To set redis-cli perferences:\n"
+        "      \":set hints\" enable online hints\n"
+        "      \":set nohints\" disable online hints\n"
+        "Set your preferences in ~/.redisclirc\n",
         version
     );
     sdsfree(version);
@@ -345,6 +365,8 @@ static void completionCallback(const char *buf, linenoiseCompletions *lc) {
 
 /* Linenoise hints callback. */
 static char *hintsCallback(const char *buf, int *color, int *bold) {
+    if (!pref.hints) return NULL;
+
     int i, argc, buflen = strlen(buf);
     sds *argv = sdssplitargs(buf,&argc);
     int endspace = buflen && isspace(buf[buflen-1]);
@@ -1141,6 +1163,45 @@ static sds *cliSplitArgs(char *line, int *argc) {
     }
 }
 
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
@@ -1154,13 +1215,15 @@ static void repl(void) {
     linenoiseSetHintsCallback(hintsCallback);
     linenoiseSetFreeHintsCallback(freeHintsCallback);
 
-    /* Only use history when stdin is a tty. */
+    /* Only use history and load the rc file when stdin is a tty. */
     if (isatty(fileno(stdin))) {
-        historyfile = getHistoryPath();
+        historyfile = getDotfilePath(REDIS_CLI_HISTFILE_ENV,REDIS_CLI_HISTFILE_DEFAULT);
         if (historyfile != NULL) {
             history = 1;
             linenoiseHistoryLoad(historyfile);
+            sdsfree(historyfile);
         }
+        cliLoadPreferences();
     }
 
     cliRefreshPrompt();
@@ -1179,6 +1242,9 @@ static void repl(void) {
                     strcasecmp(argv[0],"exit") == 0)
                 {
                     exit(0);
+                } else if (argv[0][0] == ':') {
+                    cliSetPreferences(argv,argc,1);
+                    continue;
                 } else if (strcasecmp(argv[0],"restart") == 0) {
                     if (config.eval) {
                         config.eval_ldb = 1;
@@ -2459,6 +2525,8 @@ int main(int argc, char **argv) {
     config.enable_ldb_on_eval = 0;
     config.last_cmd_type = -1;
 
+    pref.hints = 1;
+
     spectrum_palette = spectrum_palette_color;
     spectrum_palette_size = spectrum_palette_color_size;
 