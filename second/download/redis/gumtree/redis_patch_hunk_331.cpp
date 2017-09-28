         count = linenoiseRaw(buf,LINENOISE_MAX_LINE,prompt);
         if (count == -1) return NULL;
         return strdup(buf);
     }
 }
 
-/* Register a callback function to be called for tab-completion. */
-void linenoiseSetCompletionCallback(linenoiseCompletionCallback *fn) {
-    completionCallback = fn;
+/* ================================ History ================================= */
+
+/* Free the history, but does not reset it. Only used when we have to
+ * exit() to avoid memory leaks are reported by valgrind & co. */
+static void freeHistory(void) {
+    if (history) {
+        int j;
+
+        for (j = 0; j < history_len; j++)
+            free(history[j]);
+        free(history);
+    }
 }
 
-void linenoiseAddCompletion(linenoiseCompletions *lc, char *str) {
-    size_t len = strlen(str);
-    char *copy = malloc(len+1);
-    memcpy(copy,str,len+1);
-    lc->cvec = realloc(lc->cvec,sizeof(char*)*(lc->len+1));
-    lc->cvec[lc->len++] = copy;
+/* At exit we'll try to fix the terminal to the initial conditions. */
+static void linenoiseAtExit(void) {
+    disableRawMode(STDIN_FILENO);
+    freeHistory();
 }
 
-/* Using a circular buffer is smarter, but a bit more complex to handle. */
+/* This is the API call to add a new entry in the linenoise history.
+ * It uses a fixed array of char pointers that are shifted (memmoved)
+ * when the history max length is reached in order to remove the older
+ * entry and make room for the new one, so it is not exactly suitable for huge
+ * histories, but will work well for a few hundred of entries.
+ *
+ * Using a circular buffer is smarter, but a bit more complex to handle. */
 int linenoiseHistoryAdd(const char *line) {
     char *linecopy;
 
     if (history_max_len == 0) return 0;
+
+    /* Initialization on first call. */
     if (history == NULL) {
         history = malloc(sizeof(char*)*history_max_len);
         if (history == NULL) return 0;
         memset(history,0,(sizeof(char*)*history_max_len));
     }
+
+    /* Don't add duplicated lines. */
+    if (history_len && !strcmp(history[history_len-1], line)) return 0;
+
+    /* Add an heap allocated copy of the line in the history.
+     * If we reached the max length, remove the older line. */
     linecopy = strdup(line);
     if (!linecopy) return 0;
     if (history_len == history_max_len) {
         free(history[0]);
         memmove(history,history+1,sizeof(char*)*(history_max_len-1));
         history_len--;
     }
     history[history_len] = linecopy;
     history_len++;
     return 1;
 }
 
+/* Set the maximum length for the history. This function can be called even
+ * if there is already some history, the function will make sure to retain
+ * just the latest 'len' elements if the new history length value is smaller
+ * than the amount of items already inside the history. */
 int linenoiseHistorySetMaxLen(int len) {
     char **new;
 
     if (len < 1) return 0;
     if (history) {
         int tocopy = history_len;
 
         new = malloc(sizeof(char*)*len);
         if (new == NULL) return 0;
-        if (len < tocopy) tocopy = len;
-        memcpy(new,history+(history_max_len-tocopy), sizeof(char*)*tocopy);
+
+        /* If we can't copy everything, free the elements we'll not use. */
+        if (len < tocopy) {
+            int j;
+
+            for (j = 0; j < tocopy-len; j++) free(history[j]);
+            tocopy = len;
+        }
+        memset(new,0,sizeof(char*)*len);
+        memcpy(new,history+(history_len-tocopy), sizeof(char*)*tocopy);
         free(history);
         history = new;
     }
     history_max_len = len;
     if (history_len > history_max_len)
         history_len = history_max_len;
     return 1;
 }
 
 /* Save the history in the specified file. On success 0 is returned
  * otherwise -1 is returned. */
-int linenoiseHistorySave(char *filename) {
+int linenoiseHistorySave(const char *filename) {
     FILE *fp = fopen(filename,"w");
     int j;
     
     if (fp == NULL) return -1;
     for (j = 0; j < history_len; j++)
         fprintf(fp,"%s\n",history[j]);
