@@ -69,7 +69,6 @@
  * 
  */
 
-#include "fmacros.h"
 #include <termios.h>
 #include <unistd.h>
 #include <stdlib.h>
@@ -81,13 +80,14 @@
 #include <sys/ioctl.h>
 #include <unistd.h>
 
+#define LINENOISE_DEFAULT_HISTORY_MAX_LEN 100
 #define LINENOISE_MAX_LINE 4096
 static char *unsupported_term[] = {"dumb","cons25",NULL};
 
 static struct termios orig_termios; /* in order to restore at exit */
 static int rawmode = 0; /* for atexit() function to check if restore is needed*/
 static int atexit_registered = 0; /* register atexit just 1 time */
-static int history_max_len = 100;
+static int history_max_len = LINENOISE_DEFAULT_HISTORY_MAX_LEN;
 static int history_len = 0;
 char **history = NULL;
 
@@ -219,11 +219,10 @@ static int linenoisePrompt(int fd, char *buf, size_t buflen, const char *prompt)
         if (nread <= 0) return len;
         switch(c) {
         case 13:    /* enter */
-            history_len--;
-            return len;
         case 4:     /* ctrl-d */
             history_len--;
-            return (len == 0) ? -1 : (int)len;
+            free(history[history_len]);
+            return (len == 0 && c == 4) ? -1 : (int)len;
         case 3:     /* ctrl-c */
             errno = EAGAIN;
             return -1;
@@ -396,14 +395,15 @@ int linenoiseHistoryAdd(const char *line) {
     char *linecopy;
 
     if (history_max_len == 0) return 0;
-    if (history == 0) {
+    if (history == NULL) {
         history = malloc(sizeof(char*)*history_max_len);
         if (history == NULL) return 0;
         memset(history,0,(sizeof(char*)*history_max_len));
     }
     linecopy = strdup(line);
     if (!linecopy) return 0;
     if (history_len == history_max_len) {
+        free(history[0]);
         memmove(history,history+1,sizeof(char*)*(history_max_len-1));
         history_len--;
     }
@@ -431,3 +431,39 @@ int linenoiseHistorySetMaxLen(int len) {
         history_len = history_max_len;
     return 1;
 }
+
+/* Save the history in the specified file. On success 0 is returned
+ * otherwise -1 is returned. */
+int linenoiseHistorySave(char *filename) {
+    FILE *fp = fopen(filename,"w");
+    int j;
+    
+    if (fp == NULL) return -1;
+    for (j = 0; j < history_len; j++)
+        fprintf(fp,"%s\n",history[j]);
+    fclose(fp);
+    return 0;
+}
+
+/* Load the history from the specified file. If the file does not exist
+ * zero is returned and no operation is performed.
+ *
+ * If the file exists and the operation succeeded 0 is returned, otherwise
+ * on error -1 is returned. */
+int linenoiseHistoryLoad(char *filename) {
+    FILE *fp = fopen(filename,"r");
+    char buf[LINENOISE_MAX_LINE];
+    
+    if (fp == NULL) return -1;
+
+    while (fgets(buf,LINENOISE_MAX_LINE,fp) != NULL) {
+        char *p;
+        
+        p = strchr(buf,'\r');
+        if (!p) p = strchr(buf,'\n');
+        if (p) *p = '\0';
+        linenoiseHistoryAdd(buf);
+    }
+    fclose(fp);
+    return 0;
+}