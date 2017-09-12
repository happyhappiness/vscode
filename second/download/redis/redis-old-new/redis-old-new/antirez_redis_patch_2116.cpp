@@ -69,7 +69,6 @@
  * 
  */
 
-#include "fmacros.h"
 #include <termios.h>
 #include <unistd.h>
 #include <stdlib.h>
@@ -82,6 +81,7 @@
 #include <unistd.h>
 
 #define LINENOISE_MAX_LINE 4096
+static char *unsupported_term[] = {"dumb","cons25",NULL};
 
 static struct termios orig_termios; /* in order to restore at exit */
 static int rawmode = 0; /* for atexit() function to check if restore is needed*/
@@ -91,7 +91,17 @@ static int history_len = 0;
 char **history = NULL;
 
 static void linenoiseAtExit(void);
-int linenoiseHistoryAdd(char *line);
+int linenoiseHistoryAdd(const char *line);
+
+static int isUnsupportedTerm(void) {
+    char *term = getenv("TERM");
+    int j;
+
+    if (term == NULL) return 0;
+    for (j = 0; unsupported_term[j]; j++)
+        if (!strcasecmp(term,unsupported_term[j])) return 1;
+    return 0;
+}
 
 static void freeHistory(void) {
     if (history) {
@@ -341,37 +351,62 @@ static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
         errno = EINVAL;
         return -1;
     }
-    if (enableRawMode(fd) == -1) return -1;
-    count = linenoisePrompt(fd, buf, buflen, prompt);
-    disableRawMode(fd);
-    printf("\n");
+    if (!isatty(STDIN_FILENO)) {
+        if (fgets(buf, buflen, stdin) == NULL) return -1;
+        count = strlen(buf);
+        if (count && buf[count-1] == '\n') {
+            count--;
+            buf[count] = '\0';
+        }
+    } else {
+        if (enableRawMode(fd) == -1) return -1;
+        count = linenoisePrompt(fd, buf, buflen, prompt);
+        disableRawMode(fd);
+        printf("\n");
+    }
     return count;
 }
 
 char *linenoise(const char *prompt) {
     char buf[LINENOISE_MAX_LINE];
     int count;
 
-    count = linenoiseRaw(buf,LINENOISE_MAX_LINE,prompt);
-    if (count == -1) return NULL;
-    return strdup(buf);
+    if (isUnsupportedTerm()) {
+        size_t len;
+
+        printf("%s",prompt);
+        fflush(stdout);
+        if (fgets(buf,LINENOISE_MAX_LINE,stdin) == NULL) return NULL;
+        len = strlen(buf);
+        while(len && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
+            len--;
+            buf[len] = '\0';
+        }
+        return strdup(buf);
+    } else {
+        count = linenoiseRaw(buf,LINENOISE_MAX_LINE,prompt);
+        if (count == -1) return NULL;
+        return strdup(buf);
+    }
 }
 
 /* Using a circular buffer is smarter, but a bit more complex to handle. */
-int linenoiseHistoryAdd(char *line) {
+int linenoiseHistoryAdd(const char *line) {
+    char *linecopy;
+
     if (history_max_len == 0) return 0;
     if (history == 0) {
         history = malloc(sizeof(char*)*history_max_len);
         if (history == NULL) return 0;
         memset(history,0,(sizeof(char*)*history_max_len));
     }
-    line = strdup(line);
-    if (!line) return 0;
+    linecopy = strdup(line);
+    if (!linecopy) return 0;
     if (history_len == history_max_len) {
         memmove(history,history+1,sizeof(char*)*(history_max_len-1));
         history_len--;
     }
-    history[history_len] = line;
+    history[history_len] = linecopy;
     history_len++;
     return 1;
 }