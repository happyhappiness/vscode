@@ -2,7 +2,7 @@
  * line editing lib needs to be 20,000 lines of C code.
  *
  * You can find the latest source code at:
- * 
+ *
  *   http://github.com/antirez/linenoise
  *
  * Does a number of crazy assumptions that happen to be true in 99.9999% of
@@ -14,18 +14,18 @@
  * Copyright (c) 2010-2013, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
- * 
+ *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are
  * met:
- * 
+ *
  *  *  Redistributions of source code must retain the above copyright
  *     notice, this list of conditions and the following disclaimer.
  *
  *  *  Redistributions in binary form must reproduce the above copyright
  *     notice, this list of conditions and the following disclaimer in the
  *     documentation and/or other materials provided with the distribution.
- * 
+ *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
@@ -37,7 +37,7 @@
  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
- * 
+ *
  * ------------------------------------------------------------------------
  *
  * References:
@@ -56,10 +56,6 @@
  * flickering effect with some slow terminal, but the lesser sequences
  * the more compatible.
  *
- * CHA (Cursor Horizontal Absolute)
- *    Sequence: ESC [ n G
- *    Effect: moves cursor to column n
- *
  * EL (Erase Line)
  *    Sequence: ESC [ n K
  *    Effect: if n is 0 or missing, clear from cursor to end of line
@@ -68,7 +64,19 @@
  *
  * CUF (CUrsor Forward)
  *    Sequence: ESC [ n C
- *    Effect: moves cursor forward of n chars
+ *    Effect: moves cursor forward n chars
+ *
+ * CUB (CUrsor Backward)
+ *    Sequence: ESC [ n D
+ *    Effect: moves cursor backward n chars
+ *
+ * The following is used to get the terminal width if getting
+ * the width with the TIOCGWINSZ ioctl fails
+ *
+ * DSR (Device Status Report)
+ *    Sequence: ESC [ 6 n
+ *    Effect: reports the current cusor position as ESC [ n ; m R
+ *            where n is the row and m is the column
  *
  * When multi line mode is enabled, we also use an additional escape
  * sequence. However multi line editing is disabled by default.
@@ -81,17 +89,18 @@
  *    Sequence: ESC [ n B
  *    Effect: moves cursor down of n chars.
  *
- * The following are used to clear the screen: ESC [ H ESC [ 2 J
- * This is actually composed of two sequences:
+ * When linenoiseClearScreen() is called, two additional escape sequences
+ * are used in order to clear the screen and position the cursor at home
+ * position.
  *
- * cursorhome
+ * CUP (Cursor position)
  *    Sequence: ESC [ H
  *    Effect: moves the cursor to upper left corner
  *
- * ED2 (Clear entire screen)
+ * ED (Erase display)
  *    Sequence: ESC [ 2 J
  *    Effect: clear the whole screen
- * 
+ *
  */
 
 #include <termios.h>
@@ -332,7 +341,7 @@ static void freeCompletions(linenoiseCompletions *lc) {
 /* This is an helper function for linenoiseEdit() and is called when the
  * user types the <tab> key in order to complete the string currently in the
  * input.
- * 
+ *
  * The state of the editing is encapsulated into the pointed linenoiseState
  * structure as described in the structure definition. */
 static int completeLine(struct linenoiseState *ls) {
@@ -459,7 +468,7 @@ static void refreshSingleLine(struct linenoiseState *l) {
     size_t len = l->len;
     size_t pos = l->pos;
     struct abuf ab;
-    
+
     while((plen+pos) >= l->cols) {
         buf++;
         len--;
@@ -471,7 +480,7 @@ static void refreshSingleLine(struct linenoiseState *l) {
 
     abInit(&ab);
     /* Cursor to left edge */
-    snprintf(seq,64,"\x1b[0G");
+    snprintf(seq,64,"\r");
     abAppend(&ab,seq,strlen(seq));
     /* Write the prompt and the current buffer content */
     abAppend(&ab,l->prompt,strlen(l->prompt));
@@ -480,7 +489,7 @@ static void refreshSingleLine(struct linenoiseState *l) {
     snprintf(seq,64,"\x1b[0K");
     abAppend(&ab,seq,strlen(seq));
     /* Move cursor to original position. */
-    snprintf(seq,64,"\x1b[0G\x1b[%dC", (int)(pos+plen));
+    snprintf(seq,64,"\r\x1b[%dC", (int)(pos+plen));
     abAppend(&ab,seq,strlen(seq));
     if (write(fd,ab.b,ab.len) == -1) {} /* Can't recover from write error. */
     abFree(&ab);
@@ -496,6 +505,7 @@ static void refreshMultiLine(struct linenoiseState *l) {
     int rows = (plen+l->len+l->cols-1)/l->cols; /* rows used by current buf. */
     int rpos = (plen+l->oldpos+l->cols)/l->cols; /* cursor relative row. */
     int rpos2; /* rpos after refresh. */
+    int col; /* colum position, zero-based. */
     int old_rows = l->maxrows;
     int fd = l->ofd, j;
     struct abuf ab;
@@ -515,15 +525,15 @@ static void refreshMultiLine(struct linenoiseState *l) {
     /* Now for every row clear it, go up. */
     for (j = 0; j < old_rows-1; j++) {
         lndebug("clear+up");
-        snprintf(seq,64,"\x1b[0G\x1b[0K\x1b[1A");
+        snprintf(seq,64,"\r\x1b[0K\x1b[1A");
         abAppend(&ab,seq,strlen(seq));
     }
 
     /* Clean the top line. */
     lndebug("clear");
-    snprintf(seq,64,"\x1b[0G\x1b[0K");
+    snprintf(seq,64,"\r\x1b[0K");
     abAppend(&ab,seq,strlen(seq));
-    
+
     /* Write the prompt and the current buffer content */
     abAppend(&ab,l->prompt,strlen(l->prompt));
     abAppend(&ab,l->buf,l->len);
@@ -536,7 +546,7 @@ static void refreshMultiLine(struct linenoiseState *l) {
     {
         lndebug("<newline>");
         abAppend(&ab,"\n",1);
-        snprintf(seq,64,"\x1b[0G");
+        snprintf(seq,64,"\r");
         abAppend(&ab,seq,strlen(seq));
         rows++;
         if (rows > (int)l->maxrows) l->maxrows = rows;
@@ -554,8 +564,12 @@ static void refreshMultiLine(struct linenoiseState *l) {
     }
 
     /* Set column. */
-    lndebug("set col %d", 1+((plen+(int)l->pos) % (int)l->cols));
-    snprintf(seq,64,"\x1b[%dG", 1+((plen+(int)l->pos) % (int)l->cols));
+    col = (plen+(int)l->pos) % (int)l->cols;
+    lndebug("set col %d", 1+col);
+    if (col)
+        snprintf(seq,64,"\r\x1b[%dC", col);
+    else
+        snprintf(seq,64,"\r");
     abAppend(&ab,seq,strlen(seq));
 
     lndebug("\n");
@@ -732,7 +746,7 @@ static int linenoiseEdit(int stdin_fd, int stdout_fd, char *buf, size_t buflen,
     /* The latest history entry is always our current buffer, that
      * initially is just an empty string. */
     linenoiseHistoryAdd("");
-    
+
     if (write(l.ofd,prompt,l.plen) == -1) return -1;
     while(1) {
         char c;
@@ -757,6 +771,7 @@ static int linenoiseEdit(int stdin_fd, int stdout_fd, char *buf, size_t buflen,
         case ENTER:    /* enter */
             history_len--;
             free(history[history_len]);
+            if (mlmode) linenoiseEditMoveEnd(&l);
             return (int)l.len;
         case CTRL_C:     /* ctrl-c */
             errno = EAGAIN;
@@ -765,8 +780,8 @@ static int linenoiseEdit(int stdin_fd, int stdout_fd, char *buf, size_t buflen,
         case 8:     /* ctrl-h */
             linenoiseEditBackspace(&l);
             break;
-        case CTRL_D:     /* ctrl-d, remove char at right of cursor, or of the
-                       line is empty, act as end-of-file. */
+        case CTRL_D:     /* ctrl-d, remove char at right of cursor, or if the
+                            line is empty, act as end-of-file. */
             if (l.len > 0) {
                 linenoiseEditDelete(&l);
             } else {
@@ -904,7 +919,7 @@ void linenoisePrintKeyCodes(void) {
 
         printf("'%c' %02x (%d) (type quit to exit)\n",
             isprint(c) ? c : '?', (int)c, (int)c);
-        printf("\x1b[0G"); /* Go left edge manually, we are in raw mode. */
+        printf("\r"); /* Go left edge manually, we are in raw mode. */
         fflush(stdout);
     }
     disableRawMode(STDIN_FILENO);
@@ -1058,7 +1073,7 @@ int linenoiseHistorySetMaxLen(int len) {
 int linenoiseHistorySave(const char *filename) {
     FILE *fp = fopen(filename,"w");
     int j;
-    
+
     if (fp == NULL) return -1;
     for (j = 0; j < history_len; j++)
         fprintf(fp,"%s\n",history[j]);
@@ -1074,12 +1089,12 @@ int linenoiseHistorySave(const char *filename) {
 int linenoiseHistoryLoad(const char *filename) {
     FILE *fp = fopen(filename,"r");
     char buf[LINENOISE_MAX_LINE];
-    
+
     if (fp == NULL) return -1;
 
     while (fgets(buf,LINENOISE_MAX_LINE,fp) != NULL) {
         char *p;
-        
+
         p = strchr(buf,'\r');
         if (!p) p = strchr(buf,'\n');
         if (p) *p = '\0';