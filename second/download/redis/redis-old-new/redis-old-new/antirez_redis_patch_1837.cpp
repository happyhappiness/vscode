@@ -79,10 +79,12 @@
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <unistd.h>
+#include "linenoise.h"
 
 #define LINENOISE_DEFAULT_HISTORY_MAX_LEN 100
 #define LINENOISE_MAX_LINE 4096
 static char *unsupported_term[] = {"dumb","cons25",NULL};
+static linenoiseCompletionCallback *completionCallback = NULL;
 
 static struct termios orig_termios; /* in order to restore at exit */
 static int rawmode = 0; /* for atexit() function to check if restore is needed*/
@@ -195,6 +197,70 @@ static void refreshLine(int fd, const char *prompt, char *buf, size_t len, size_
     if (write(fd,seq,strlen(seq)) == -1) return;
 }
 
+static void beep() {
+    fprintf(stderr, "\x7");
+    fflush(stderr);
+}
+
+static void freeCompletions(linenoiseCompletions *lc) {
+    size_t i;
+    for (i = 0; i < lc->len; i++)
+        free(lc->cvec[i]);
+    if (lc->cvec != NULL)
+        free(lc->cvec);
+}
+
+static int completeLine(int fd, const char *prompt, char *buf, size_t buflen, size_t *len, size_t *pos, size_t cols) {
+    linenoiseCompletions lc = { 0, NULL };
+    int nread, nwritten;
+    char c = 0;
+
+    completionCallback(buf,&lc);
+    if (lc.len == 0) {
+        beep();
+    } else {
+        size_t stop = 0, i = 0;
+        size_t clen;
+
+        while(!stop) {
+            /* Show completion or original buffer */
+            if (i < lc.len) {
+                clen = strlen(lc.cvec[i]);
+                refreshLine(fd,prompt,lc.cvec[i],clen,clen,cols);
+            } else {
+                refreshLine(fd,prompt,buf,*len,*pos,cols);
+            }
+
+            nread = read(fd,&c,1);
+            if (nread <= 0) {
+                freeCompletions(&lc);
+                return -1;
+            }
+
+            switch(c) {
+                case 9: /* tab */
+                    i = (i+1) % (lc.len+1);
+                    if (i == lc.len) beep();
+                    break;
+                case 27: /* escape */
+                    stop = 1;
+                    break;
+                default:
+                    /* update buffer and return */
+                    if (i < lc.len) {
+                        nwritten = snprintf(buf,buflen,"%s",lc.cvec[i]);
+                        *len = *pos = nwritten;
+                    }
+                    stop = 1;
+                    break;
+            }
+        }
+    }
+
+    freeCompletions(&lc);
+    return c; /* Return last read character */
+}
+
 static int linenoisePrompt(int fd, char *buf, size_t buflen, const char *prompt) {
     size_t plen = strlen(prompt);
     size_t pos = 0;
@@ -217,6 +283,18 @@ static int linenoisePrompt(int fd, char *buf, size_t buflen, const char *prompt)
 
         nread = read(fd,&c,1);
         if (nread <= 0) return len;
+
+        /* Only autocomplete when the callback is set. It returns < 0 when
+         * there was an error reading from fd. Otherwise it will return the
+         * character that should be handled next. */
+        if (c == 9 && completionCallback != NULL) {
+            c = completeLine(fd,prompt,buf,buflen,&len,&pos,cols);
+            /* Return on errors */
+            if (c < 0) return len;
+            /* Read next character when 0 */
+            if (c == 0) continue;
+        }
+
         switch(c) {
         case 13:    /* enter */
         case 4:     /* ctrl-d */
@@ -402,6 +480,19 @@ char *linenoise(const char *prompt) {
     }
 }
 
+/* Register a callback function to be called for tab-completion. */
+void linenoiseSetCompletionCallback(linenoiseCompletionCallback *fn) {
+    completionCallback = fn;
+}
+
+void linenoiseAddCompletion(linenoiseCompletions *lc, char *str) {
+    size_t len = strlen(str);
+    char *copy = malloc(len+1);
+    memcpy(copy,str,len+1);
+    lc->cvec = realloc(lc->cvec,sizeof(char*)*(lc->len+1));
+    lc->cvec[lc->len++] = copy;
+}
+
 /* Using a circular buffer is smarter, but a bit more complex to handle. */
 int linenoiseHistoryAdd(const char *line) {
     char *linecopy;