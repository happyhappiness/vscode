@@ -10,7 +10,7 @@
  *
  * ------------------------------------------------------------------------
  *
- * Copyright (c) 2010-2013, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2016, Salvatore Sanfilippo <antirez at gmail dot com>
  * Copyright (c) 2010-2013, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
@@ -120,6 +120,8 @@
 #define LINENOISE_MAX_LINE 4096
 static char *unsupported_term[] = {"dumb","cons25","emacs",NULL};
 static linenoiseCompletionCallback *completionCallback = NULL;
+static linenoiseHintsCallback *hintsCallback = NULL;
+static linenoiseFreeHintsCallback *freeHintsCallback = NULL;
 
 static struct termios orig_termios; /* In order to restore at exit.*/
 static int rawmode = 0; /* For atexit() function to check if restore is needed*/
@@ -407,6 +409,18 @@ void linenoiseSetCompletionCallback(linenoiseCompletionCallback *fn) {
     completionCallback = fn;
 }
 
+/* Register a hits function to be called to show hits to the user at the
+ * right of the prompt. */
+void linenoiseSetHintsCallback(linenoiseHintsCallback *fn) {
+    hintsCallback = fn;
+}
+
+/* Register a function to free the hints returned by the hints callback
+ * registered with linenoiseSetHintsCallback(). */
+void linenoiseSetFreeHintsCallback(linenoiseFreeHintsCallback *fn) {
+    freeHintsCallback = fn;
+}
+
 /* This function is used by the callback function registered by the user
  * in order to add completion options given the input string when the
  * user typed <tab>. See the example.c source code for a very easy to
@@ -456,6 +470,30 @@ static void abFree(struct abuf *ab) {
     free(ab->b);
 }
 
+/* Helper of refreshSingleLine() and refreshMultiLine() to show hints
+ * to the right of the prompt. */
+void refreshShowHints(struct abuf *ab, struct linenoiseState *l, int plen) {
+    char seq[64];
+    if (hintsCallback && plen+l->len < l->cols) {
+        int color = -1, bold = 0;
+        char *hint = hintsCallback(l->buf,&color,&bold);
+        if (hint) {
+            int hintlen = strlen(hint);
+            int hintmaxlen = l->cols-(plen+l->len);
+            if (hintlen > hintmaxlen) hintlen = hintmaxlen;
+            if (bold == 1 && color == -1) color = 37;
+            if (color != -1 || bold != 0)
+                snprintf(seq,64,"\033[%d;%d;49m",bold,color);
+            abAppend(ab,seq,strlen(seq));
+            abAppend(ab,hint,hintlen);
+            if (color != -1 || bold != 0)
+                abAppend(ab,"\033[0m",4);
+            /* Call the function to free the hint returned. */
+            if (freeHintsCallback) freeHintsCallback(hint);
+        }
+    }
+}
+
 /* Single line low level line refresh.
  *
  * Rewrite the currently edited line accordingly to the buffer content,
@@ -485,6 +523,8 @@ static void refreshSingleLine(struct linenoiseState *l) {
     /* Write the prompt and the current buffer content */
     abAppend(&ab,l->prompt,strlen(l->prompt));
     abAppend(&ab,buf,len);
+    /* Show hits if any. */
+    refreshShowHints(&ab,l,plen);
     /* Erase to right */
     snprintf(seq,64,"\x1b[0K");
     abAppend(&ab,seq,strlen(seq));
@@ -538,6 +578,9 @@ static void refreshMultiLine(struct linenoiseState *l) {
     abAppend(&ab,l->prompt,strlen(l->prompt));
     abAppend(&ab,l->buf,l->len);
 
+    /* Show hits if any. */
+    refreshShowHints(&ab,l,plen);
+
     /* If we are at the very end of the screen with our prompt, we need to
      * emit a newline and move the prompt to the first column. */
     if (l->pos &&
@@ -598,7 +641,7 @@ int linenoiseEditInsert(struct linenoiseState *l, char c) {
             l->pos++;
             l->len++;
             l->buf[l->len] = '\0';
-            if ((!mlmode && l->plen+l->len < l->cols) /* || mlmode */) {
+            if ((!mlmode && l->plen+l->len < l->cols && !hintsCallback)) {
                 /* Avoid a full update of the line in the
                  * trivial case. */
                 if (write(l->ofd,&c,1) == -1) return -1;
@@ -1010,6 +1053,14 @@ char *linenoise(const char *prompt) {
     }
 }
 
+/* This is just a wrapper the user may want to call in order to make sure
+ * the linenoise returned buffer is freed with the same allocator it was
+ * created with. Useful when the main program is using an alternative
+ * allocator. */
+void linenoiseFree(void *ptr) {
+    free(ptr);
+}
+
 /* ================================ History ================================= */
 
 /* Free the history, but does not reset it. Only used when we have to