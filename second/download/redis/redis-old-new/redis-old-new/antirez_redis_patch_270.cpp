@@ -934,22 +934,48 @@ static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
         errno = EINVAL;
         return -1;
     }
-    if (!isatty(STDIN_FILENO)) {
-        /* Not a tty: read from file / pipe. */
-        if (fgets(buf, buflen, stdin) == NULL) return -1;
-        count = strlen(buf);
-        if (count && buf[count-1] == '\n') {
-            count--;
-            buf[count] = '\0';
+
+    if (enableRawMode(STDIN_FILENO) == -1) return -1;
+    count = linenoiseEdit(STDIN_FILENO, STDOUT_FILENO, buf, buflen, prompt);
+    disableRawMode(STDIN_FILENO);
+    printf("\n");
+    return count;
+}
+
+/* This function is called when linenoise() is called with the standard
+ * input file descriptor not attached to a TTY. So for example when the
+ * program using linenoise is called in pipe or with a file redirected
+ * to its standard input. In this case, we want to be able to return the
+ * line regardless of its length (by default we are limited to 4k). */
+static char *linenoiseNoTTY(void) {
+    char *line = NULL;
+    size_t len = 0, maxlen = 0;
+
+    while(1) {
+        if (len == maxlen) {
+            if (maxlen == 0) maxlen = 16;
+            maxlen *= 2;
+            char *oldval = line;
+            line = realloc(line,maxlen);
+            if (line == NULL) {
+                if (oldval) free(oldval);
+                return NULL;
+            }
+        }
+        int c = fgetc(stdin);
+        if (c == EOF || c == '\n') {
+            if (c == EOF && len == 0) {
+                free(line);
+                return NULL;
+            } else {
+                line[len] = '\0';
+                return line;
+            }
+        } else {
+            line[len] = c;
+            len++;
         }
-    } else {
-        /* Interactive editing. */
-        if (enableRawMode(STDIN_FILENO) == -1) return -1;
-        count = linenoiseEdit(STDIN_FILENO, STDOUT_FILENO, buf, buflen, prompt);
-        disableRawMode(STDIN_FILENO);
-        printf("\n");
     }
-    return count;
 }
 
 /* The high level function that is the main API of the linenoise library.
@@ -961,7 +987,11 @@ char *linenoise(const char *prompt) {
     char buf[LINENOISE_MAX_LINE];
     int count;
 
-    if (isUnsupportedTerm()) {
+    if (!isatty(STDIN_FILENO)) {
+        /* Not a tty: read from file / pipe. In this mode we don't want any
+         * limit to the line size, so we call a function to handle that. */
+        return linenoiseNoTTY();
+    } else if (isUnsupportedTerm()) {
         size_t len;
 
         printf("%s",prompt);