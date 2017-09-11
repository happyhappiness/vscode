@@ -314,6 +314,7 @@ static void cliOutputHelp(int argc, char **argv) {
     printf("\r\n");
 }
 
+/* Linenoise completion callback. */
 static void completionCallback(const char *buf, linenoiseCompletions *lc) {
     size_t startpos = 0;
     int mask;
@@ -342,6 +343,56 @@ static void completionCallback(const char *buf, linenoiseCompletions *lc) {
     }
 }
 
+/* Linenoise hints callback. */
+static char *hintsCallback(const char *buf, int *color, int *bold) {
+    int i, argc, buflen = strlen(buf);
+    sds *argv = sdssplitargs(buf,&argc);
+    int endspace = buflen && isspace(buf[buflen-1]);
+
+    /* Check if the argument list is empty and return ASAP. */
+    if (argc == 0) {
+        sdsfreesplitres(argv,argc);
+        return NULL;
+    }
+
+    for (i = 0; i < helpEntriesLen; i++) {
+        if (!(helpEntries[i].type & CLI_HELP_COMMAND)) continue;
+
+        if (strcasecmp(argv[0],helpEntries[i].full) == 0)
+        {
+            *color = 90;
+            *bold = 0;
+            sds hint = sdsnew(helpEntries[i].org->params);
+
+            /* Remove arguments from the returned hint to show only the
+             * ones the user did not yet typed. */
+            int toremove = argc-1;
+            while(toremove > 0 && sdslen(hint)) {
+                if (hint[0] == '[') break;
+                if (hint[0] == ' ') toremove--;
+                sdsrange(hint,1,-1);
+            }
+
+            /* Add an initial space if needed. */
+            if (!endspace) {
+                sds newhint = sdsnewlen(" ",1);
+                newhint = sdscatsds(newhint,hint);
+                sdsfree(hint);
+                hint = newhint;
+            }
+
+            sdsfreesplitres(argv,argc);
+            return hint;
+        }
+    }
+    sdsfreesplitres(argv,argc);
+    return NULL;
+}
+
+static void freeHintsCallback(void *ptr) {
+    sdsfree(ptr);
+}
+
 /*------------------------------------------------------------------------------
  * Networking / parsing
  *--------------------------------------------------------------------------- */
@@ -1100,6 +1151,8 @@ static void repl(void) {
     config.interactive = 1;
     linenoiseSetMultiLine(1);
     linenoiseSetCompletionCallback(completionCallback);
+    linenoiseSetHintsCallback(hintsCallback);
+    linenoiseSetFreeHintsCallback(freeHintsCallback);
 
     /* Only use history when stdin is a tty. */
     if (isatty(fileno(stdin))) {