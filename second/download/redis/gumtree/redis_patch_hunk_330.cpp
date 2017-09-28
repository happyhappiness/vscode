 static void disableRawMode(int fd) {
     /* Don't even check the return value as it's too late. */
     if (rawmode && tcsetattr(fd,TCSAFLUSH,&orig_termios) != -1)
         rawmode = 0;
 }
 
-/* At exit we'll try to fix the terminal to the initial conditions. */
-static void linenoiseAtExit(void) {
-    disableRawMode(STDIN_FILENO);
-    freeHistory();
+/* Use the ESC [6n escape sequence to query the horizontal cursor position
+ * and return it. On error -1 is returned, on success the position of the
+ * cursor. */
+static int getCursorPosition(int ifd, int ofd) {
+    char buf[32];
+    int cols, rows;
+    unsigned int i = 0;
+
+    /* Report cursor location */
+    if (write(ofd, "\x1b[6n", 4) != 4) return -1;
+
+    /* Read the response: ESC [ rows ; cols R */
+    while (i < sizeof(buf)-1) {
+        if (read(ifd,buf+i,1) != 1) break;
+        if (buf[i] == 'R') break;
+        i++;
+    }
+    buf[i] = '\0';
+
+    /* Parse it. */
+    if (buf[0] != ESC || buf[1] != '[') return -1;
+    if (sscanf(buf+2,"%d;%d",&rows,&cols) != 2) return -1;
+    return cols;
 }
 
-static int getColumns(void) {
+/* Try to get the number of columns in the current terminal, or assume 80
+ * if it fails. */
+static int getColumns(int ifd, int ofd) {
     struct winsize ws;
 
-    if (ioctl(1, TIOCGWINSZ, &ws) == -1) return 80;
-    return ws.ws_col;
+    if (ioctl(1, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
+        /* ioctl() failed. Try to query the terminal itself. */
+        int start, cols;
+
+        /* Get the initial position so we can restore it later. */
+        start = getCursorPosition(ifd,ofd);
+        if (start == -1) goto failed;
+
+        /* Go to right margin and get position. */
+        if (write(ofd,"\x1b[999C",6) != 6) goto failed;
+        cols = getCursorPosition(ifd,ofd);
+        if (cols == -1) goto failed;
+
+        /* Restore position. */
+        if (cols > start) {
+            char seq[32];
+            snprintf(seq,32,"\x1b[%dD",cols-start);
+            if (write(ofd,seq,strlen(seq)) == -1) {
+                /* Can't recover... */
+            }
+        }
+        return cols;
+    } else {
+        return ws.ws_col;
+    }
+
+failed:
+    return 80;
 }
 
-static void refreshLine(int fd, const char *prompt, char *buf, size_t len, size_t pos, size_t cols) {
-    char seq[64];
-    size_t plen = strlen(prompt);
-    
-    while((plen+pos) >= cols) {
-        buf++;
-        len--;
-        pos--;
-    }
-    while (plen+len > cols) {
-        len--;
+/* Clear the screen. Used to handle ctrl+l */
+void linenoiseClearScreen(void) {
+    if (write(STDOUT_FILENO,"\x1b[H\x1b[2J",7) <= 0) {
+        /* nothing to do, just to avoid warning. */
     }
-
-    /* Cursor to left edge */
-    snprintf(seq,64,"\x1b[0G");
-    if (write(fd,seq,strlen(seq)) == -1) return;
-    /* Write the prompt and the current buffer content */
-    if (write(fd,prompt,strlen(prompt)) == -1) return;
-    if (write(fd,buf,len) == -1) return;
-    /* Erase to right */
-    snprintf(seq,64,"\x1b[0K");
-    if (write(fd,seq,strlen(seq)) == -1) return;
-    /* Move cursor to original position. */
-    snprintf(seq,64,"\x1b[0G\x1b[%dC", (int)(pos+plen));
-    if (write(fd,seq,strlen(seq)) == -1) return;
 }
 
-static void beep() {
+/* Beep, used for completion when there is nothing to complete or when all
+ * the choices were already shown. */
+static void linenoiseBeep(void) {
     fprintf(stderr, "\x7");
     fflush(stderr);
 }
 
+/* ============================== Completion ================================ */
+
+/* Free a list of completion option populated by linenoiseAddCompletion(). */
 static void freeCompletions(linenoiseCompletions *lc) {
     size_t i;
     for (i = 0; i < lc->len; i++)
         free(lc->cvec[i]);
     if (lc->cvec != NULL)
         free(lc->cvec);
 }
 
-static int completeLine(int fd, const char *prompt, char *buf, size_t buflen, size_t *len, size_t *pos, size_t cols) {
+/* This is an helper function for linenoiseEdit() and is called when the
+ * user types the <tab> key in order to complete the string currently in the
+ * input.
+ * 
+ * The state of the editing is encapsulated into the pointed linenoiseState
+ * structure as described in the structure definition. */
+static int completeLine(struct linenoiseState *ls) {
     linenoiseCompletions lc = { 0, NULL };
     int nread, nwritten;
     char c = 0;
 
-    completionCallback(buf,&lc);
+    completionCallback(ls->buf,&lc);
     if (lc.len == 0) {
-        beep();
+        linenoiseBeep();
     } else {
         size_t stop = 0, i = 0;
-        size_t clen;
 
         while(!stop) {
             /* Show completion or original buffer */
             if (i < lc.len) {
-                clen = strlen(lc.cvec[i]);
-                refreshLine(fd,prompt,lc.cvec[i],clen,clen,cols);
+                struct linenoiseState saved = *ls;
+
+                ls->len = ls->pos = strlen(lc.cvec[i]);
+                ls->buf = lc.cvec[i];
+                refreshLine(ls);
+                ls->len = saved.len;
+                ls->pos = saved.pos;
+                ls->buf = saved.buf;
             } else {
-                refreshLine(fd,prompt,buf,*len,*pos,cols);
+                refreshLine(ls);
             }
 
-            nread = read(fd,&c,1);
+            nread = read(ls->ifd,&c,1);
             if (nread <= 0) {
                 freeCompletions(&lc);
                 return -1;
             }
 
             switch(c) {
                 case 9: /* tab */
                     i = (i+1) % (lc.len+1);
-                    if (i == lc.len) beep();
+                    if (i == lc.len) linenoiseBeep();
                     break;
                 case 27: /* escape */
                     /* Re-show original buffer */
-                    if (i < lc.len) {
-                        refreshLine(fd,prompt,buf,*len,*pos,cols);
-                    }
+                    if (i < lc.len) refreshLine(ls);
                     stop = 1;
                     break;
                 default:
                     /* Update buffer and return */
                     if (i < lc.len) {
-                        nwritten = snprintf(buf,buflen,"%s",lc.cvec[i]);
-                        *len = *pos = nwritten;
+                        nwritten = snprintf(ls->buf,ls->buflen,"%s",lc.cvec[i]);
+                        ls->len = ls->pos = nwritten;
                     }
                     stop = 1;
                     break;
             }
         }
     }
 
     freeCompletions(&lc);
     return c; /* Return last read character */
 }
 
-void linenoiseClearScreen(void) {
-    if (write(STDIN_FILENO,"\x1b[H\x1b[2J",7) <= 0) {
-        /* nothing to do, just to avoid warning. */
+/* Register a callback function to be called for tab-completion. */
+void linenoiseSetCompletionCallback(linenoiseCompletionCallback *fn) {
+    completionCallback = fn;
+}
+
+/* This function is used by the callback function registered by the user
+ * in order to add completion options given the input string when the
+ * user typed <tab>. See the example.c source code for a very easy to
+ * understand example. */
+void linenoiseAddCompletion(linenoiseCompletions *lc, const char *str) {
+    size_t len = strlen(str);
+    char *copy, **cvec;
+
+    copy = malloc(len+1);
+    if (copy == NULL) return;
+    memcpy(copy,str,len+1);
+    cvec = realloc(lc->cvec,sizeof(char*)*(lc->len+1));
+    if (cvec == NULL) {
+        free(copy);
+        return;
+    }
+    lc->cvec = cvec;
+    lc->cvec[lc->len++] = copy;
+}
+
+/* =========================== Line editing ================================= */
+
+/* We define a very simple "append buffer" structure, that is an heap
+ * allocated string where we can append to. This is useful in order to
+ * write all the escape sequences in a buffer and flush them to the standard
+ * output in a single call, to avoid flickering effects. */
+struct abuf {
+    char *b;
+    int len;
+};
+
+static void abInit(struct abuf *ab) {
+    ab->b = NULL;
+    ab->len = 0;
+}
+
+static void abAppend(struct abuf *ab, const char *s, int len) {
+    char *new = realloc(ab->b,ab->len+len);
+
+    if (new == NULL) return;
+    memcpy(new+ab->len,s,len);
+    ab->b = new;
+    ab->len += len;
+}
+
+static void abFree(struct abuf *ab) {
+    free(ab->b);
+}
+
+/* Single line low level line refresh.
+ *
+ * Rewrite the currently edited line accordingly to the buffer content,
+ * cursor position, and number of columns of the terminal. */
+static void refreshSingleLine(struct linenoiseState *l) {
+    char seq[64];
+    size_t plen = strlen(l->prompt);
+    int fd = l->ofd;
+    char *buf = l->buf;
+    size_t len = l->len;
+    size_t pos = l->pos;
+    struct abuf ab;
+    
+    while((plen+pos) >= l->cols) {
+        buf++;
+        len--;
+        pos--;
+    }
+    while (plen+len > l->cols) {
+        len--;
+    }
+
+    abInit(&ab);
+    /* Cursor to left edge */
+    snprintf(seq,64,"\x1b[0G");
+    abAppend(&ab,seq,strlen(seq));
+    /* Write the prompt and the current buffer content */
+    abAppend(&ab,l->prompt,strlen(l->prompt));
+    abAppend(&ab,buf,len);
+    /* Erase to right */
+    snprintf(seq,64,"\x1b[0K");
+    abAppend(&ab,seq,strlen(seq));
+    /* Move cursor to original position. */
+    snprintf(seq,64,"\x1b[0G\x1b[%dC", (int)(pos+plen));
+    abAppend(&ab,seq,strlen(seq));
+    if (write(fd,ab.b,ab.len) == -1) {} /* Can't recover from write error. */
+    abFree(&ab);
+}
+
+/* Multi line low level line refresh.
+ *
+ * Rewrite the currently edited line accordingly to the buffer content,
+ * cursor position, and number of columns of the terminal. */
+static void refreshMultiLine(struct linenoiseState *l) {
+    char seq[64];
+    int plen = strlen(l->prompt);
+    int rows = (plen+l->len+l->cols-1)/l->cols; /* rows used by current buf. */
+    int rpos = (plen+l->oldpos+l->cols)/l->cols; /* cursor relative row. */
+    int rpos2; /* rpos after refresh. */
+    int old_rows = l->maxrows;
+    int fd = l->ofd, j;
+    struct abuf ab;
+
+    /* Update maxrows if needed. */
+    if (rows > (int)l->maxrows) l->maxrows = rows;
+
+    /* First step: clear all the lines used before. To do so start by
+     * going to the last row. */
+    abInit(&ab);
+    if (old_rows-rpos > 0) {
+        lndebug("go down %d", old_rows-rpos);
+        snprintf(seq,64,"\x1b[%dB", old_rows-rpos);
+        abAppend(&ab,seq,strlen(seq));
+    }
+
+    /* Now for every row clear it, go up. */
+    for (j = 0; j < old_rows-1; j++) {
+        lndebug("clear+up");
+        snprintf(seq,64,"\x1b[0G\x1b[0K\x1b[1A");
+        abAppend(&ab,seq,strlen(seq));
+    }
+
+    /* Clean the top line. */
+    lndebug("clear");
+    snprintf(seq,64,"\x1b[0G\x1b[0K");
+    abAppend(&ab,seq,strlen(seq));
+    
+    /* Write the prompt and the current buffer content */
+    abAppend(&ab,l->prompt,strlen(l->prompt));
+    abAppend(&ab,l->buf,l->len);
+
+    /* If we are at the very end of the screen with our prompt, we need to
+     * emit a newline and move the prompt to the first column. */
+    if (l->pos &&
+        l->pos == l->len &&
+        (l->pos+plen) % l->cols == 0)
+    {
+        lndebug("<newline>");
+        abAppend(&ab,"\n",1);
+        snprintf(seq,64,"\x1b[0G");
+        abAppend(&ab,seq,strlen(seq));
+        rows++;
+        if (rows > (int)l->maxrows) l->maxrows = rows;
+    }
+
+    /* Move cursor to right position. */
+    rpos2 = (plen+l->pos+l->cols)/l->cols; /* current cursor relative row. */
+    lndebug("rpos2 %d", rpos2);
+
+    /* Go up till we reach the expected positon. */
+    if (rows-rpos2 > 0) {
+        lndebug("go-up %d", rows-rpos2);
+        snprintf(seq,64,"\x1b[%dA", rows-rpos2);
+        abAppend(&ab,seq,strlen(seq));
+    }
+
+    /* Set column. */
+    lndebug("set col %d", 1+((plen+(int)l->pos) % (int)l->cols));
+    snprintf(seq,64,"\x1b[%dG", 1+((plen+(int)l->pos) % (int)l->cols));
+    abAppend(&ab,seq,strlen(seq));
+
+    lndebug("\n");
+    l->oldpos = l->pos;
+
+    if (write(fd,ab.b,ab.len) == -1) {} /* Can't recover from write error. */
+    abFree(&ab);
+}
+
+/* Calls the two low level functions refreshSingleLine() or
+ * refreshMultiLine() according to the selected mode. */
+static void refreshLine(struct linenoiseState *l) {
+    if (mlmode)
+        refreshMultiLine(l);
+    else
+        refreshSingleLine(l);
+}
+
+/* Insert the character 'c' at cursor current position.
+ *
+ * On error writing to the terminal -1 is returned, otherwise 0. */
+int linenoiseEditInsert(struct linenoiseState *l, char c) {
+    if (l->len < l->buflen) {
+        if (l->len == l->pos) {
+            l->buf[l->pos] = c;
+            l->pos++;
+            l->len++;
+            l->buf[l->len] = '\0';
+            if ((!mlmode && l->plen+l->len < l->cols) /* || mlmode */) {
+                /* Avoid a full update of the line in the
+                 * trivial case. */
+                if (write(l->ofd,&c,1) == -1) return -1;
+            } else {
+                refreshLine(l);
+            }
+        } else {
+            memmove(l->buf+l->pos+1,l->buf+l->pos,l->len-l->pos);
+            l->buf[l->pos] = c;
+            l->len++;
+            l->pos++;
+            l->buf[l->len] = '\0';
+            refreshLine(l);
+        }
+    }
+    return 0;
+}
+
+/* Move cursor on the left. */
+void linenoiseEditMoveLeft(struct linenoiseState *l) {
+    if (l->pos > 0) {
+        l->pos--;
+        refreshLine(l);
+    }
+}
+
+/* Move cursor on the right. */
+void linenoiseEditMoveRight(struct linenoiseState *l) {
+    if (l->pos != l->len) {
+        l->pos++;
+        refreshLine(l);
+    }
+}
+
+/* Move cursor to the start of the line. */
+void linenoiseEditMoveHome(struct linenoiseState *l) {
+    if (l->pos != 0) {
+        l->pos = 0;
+        refreshLine(l);
+    }
+}
+
+/* Move cursor to the end of the line. */
+void linenoiseEditMoveEnd(struct linenoiseState *l) {
+    if (l->pos != l->len) {
+        l->pos = l->len;
+        refreshLine(l);
     }
 }
 
-static int linenoisePrompt(int fd, char *buf, size_t buflen, const char *prompt) {
-    size_t plen = strlen(prompt);
-    size_t pos = 0;
-    size_t len = 0;
-    size_t cols = getColumns();
-    int history_index = 0;
-    size_t old_pos;
+/* Substitute the currently edited line with the next or previous history
+ * entry as specified by 'dir'. */
+#define LINENOISE_HISTORY_NEXT 0
+#define LINENOISE_HISTORY_PREV 1
+void linenoiseEditHistoryNext(struct linenoiseState *l, int dir) {
+    if (history_len > 1) {
+        /* Update the current history entry before to
+         * overwrite it with the next one. */
+        free(history[history_len - 1 - l->history_index]);
+        history[history_len - 1 - l->history_index] = strdup(l->buf);
+        /* Show the new entry */
+        l->history_index += (dir == LINENOISE_HISTORY_PREV) ? 1 : -1;
+        if (l->history_index < 0) {
+            l->history_index = 0;
+            return;
+        } else if (l->history_index >= history_len) {
+            l->history_index = history_len-1;
+            return;
+        }
+        strncpy(l->buf,history[history_len - 1 - l->history_index],l->buflen);
+        l->buf[l->buflen-1] = '\0';
+        l->len = l->pos = strlen(l->buf);
+        refreshLine(l);
+    }
+}
+
+/* Delete the character at the right of the cursor without altering the cursor
+ * position. Basically this is what happens with the "Delete" keyboard key. */
+void linenoiseEditDelete(struct linenoiseState *l) {
+    if (l->len > 0 && l->pos < l->len) {
+        memmove(l->buf+l->pos,l->buf+l->pos+1,l->len-l->pos-1);
+        l->len--;
+        l->buf[l->len] = '\0';
+        refreshLine(l);
+    }
+}
+
+/* Backspace implementation. */
+void linenoiseEditBackspace(struct linenoiseState *l) {
+    if (l->pos > 0 && l->len > 0) {
+        memmove(l->buf+l->pos-1,l->buf+l->pos,l->len-l->pos);
+        l->pos--;
+        l->len--;
+        l->buf[l->len] = '\0';
+        refreshLine(l);
+    }
+}
+
+/* Delete the previosu word, maintaining the cursor at the start of the
+ * current word. */
+void linenoiseEditDeletePrevWord(struct linenoiseState *l) {
+    size_t old_pos = l->pos;
     size_t diff;
 
-    buf[0] = '\0';
-    buflen--; /* Make sure there is always space for the nulterm */
+    while (l->pos > 0 && l->buf[l->pos-1] == ' ')
+        l->pos--;
+    while (l->pos > 0 && l->buf[l->pos-1] != ' ')
+        l->pos--;
+    diff = old_pos - l->pos;
+    memmove(l->buf+l->pos,l->buf+old_pos,l->len-old_pos+1);
+    l->len -= diff;
+    refreshLine(l);
+}
+
+/* This function is the core of the line editing capability of linenoise.
+ * It expects 'fd' to be already in "raw mode" so that every key pressed
+ * will be returned ASAP to read().
+ *
+ * The resulting string is put into 'buf' when the user type enter, or
+ * when ctrl+d is typed.
+ *
+ * The function returns the length of the current buffer. */
+static int linenoiseEdit(int stdin_fd, int stdout_fd, char *buf, size_t buflen, const char *prompt)
+{
+    struct linenoiseState l;
+
+    /* Populate the linenoise state that we pass to functions implementing
+     * specific editing functionalities. */
+    l.ifd = stdin_fd;
+    l.ofd = stdout_fd;
+    l.buf = buf;
+    l.buflen = buflen;
+    l.prompt = prompt;
+    l.plen = strlen(prompt);
+    l.oldpos = l.pos = 0;
+    l.len = 0;
+    l.cols = getColumns(stdin_fd, stdout_fd);
+    l.maxrows = 0;
+    l.history_index = 0;
+
+    /* Buffer starts empty. */
+    l.buf[0] = '\0';
+    l.buflen--; /* Make sure there is always space for the nulterm */
 
     /* The latest history entry is always our current buffer, that
      * initially is just an empty string. */
     linenoiseHistoryAdd("");
     
-    if (write(fd,prompt,plen) == -1) return -1;
+    if (write(l.ofd,prompt,l.plen) == -1) return -1;
     while(1) {
         char c;
         int nread;
-        char seq[2], seq2[2];
+        char seq[3];
 
-        nread = read(fd,&c,1);
-        if (nread <= 0) return len;
+        nread = read(l.ifd,&c,1);
+        if (nread <= 0) return l.len;
 
         /* Only autocomplete when the callback is set. It returns < 0 when
          * there was an error reading from fd. Otherwise it will return the
          * character that should be handled next. */
         if (c == 9 && completionCallback != NULL) {
-            c = completeLine(fd,prompt,buf,buflen,&len,&pos,cols);
+            c = completeLine(&l);
             /* Return on errors */
-            if (c < 0) return len;
+            if (c < 0) return l.len;
             /* Read next character when 0 */
             if (c == 0) continue;
         }
 
         switch(c) {
-        case 13:    /* enter */
+        case ENTER:    /* enter */
             history_len--;
             free(history[history_len]);
-            return (int)len;
-        case 3:     /* ctrl-c */
+            return (int)l.len;
+        case CTRL_C:     /* ctrl-c */
             errno = EAGAIN;
             return -1;
-        case 127:   /* backspace */
+        case BACKSPACE:   /* backspace */
         case 8:     /* ctrl-h */
-            if (pos > 0 && len > 0) {
-                memmove(buf+pos-1,buf+pos,len-pos);
-                pos--;
-                len--;
-                buf[len] = '\0';
-                refreshLine(fd,prompt,buf,len,pos,cols);
-            }
+            linenoiseEditBackspace(&l);
             break;
-        case 4:     /* ctrl-d, remove char at right of cursor */
-            if (len > 1 && pos < (len-1)) {
-                memmove(buf+pos,buf+pos+1,len-pos);
-                len--;
-                buf[len] = '\0';
-                refreshLine(fd,prompt,buf,len,pos,cols);
-            } else if (len == 0) {
+        case CTRL_D:     /* ctrl-d, remove char at right of cursor, or of the
+                       line is empty, act as end-of-file. */
+            if (l.len > 0) {
+                linenoiseEditDelete(&l);
+            } else {
                 history_len--;
                 free(history[history_len]);
                 return -1;
             }
             break;
-        case 20:    /* ctrl-t */
-            if (pos > 0 && pos < len) {
-                int aux = buf[pos-1];
-                buf[pos-1] = buf[pos];
-                buf[pos] = aux;
-                if (pos != len-1) pos++;
-                refreshLine(fd,prompt,buf,len,pos,cols);
+        case CTRL_T:    /* ctrl-t, swaps current character with previous. */
+            if (l.pos > 0 && l.pos < l.len) {
+                int aux = buf[l.pos-1];
+                buf[l.pos-1] = buf[l.pos];
+                buf[l.pos] = aux;
+                if (l.pos != l.len-1) l.pos++;
+                refreshLine(&l);
             }
             break;
-        case 2:     /* ctrl-b */
-            goto left_arrow;
-        case 6:     /* ctrl-f */
-            goto right_arrow;
-        case 16:    /* ctrl-p */
-            seq[1] = 65;
-            goto up_down_arrow;
-        case 14:    /* ctrl-n */
-            seq[1] = 66;
-            goto up_down_arrow;
-            break;
-        case 27:    /* escape sequence */
-            if (read(fd,seq,2) == -1) break;
-            if (seq[0] == 91 && seq[1] == 68) {
-left_arrow:
-                /* left arrow */
-                if (pos > 0) {
-                    pos--;
-                    refreshLine(fd,prompt,buf,len,pos,cols);
-                }
-            } else if (seq[0] == 91 && seq[1] == 67) {
-right_arrow:
-                /* right arrow */
-                if (pos != len) {
-                    pos++;
-                    refreshLine(fd,prompt,buf,len,pos,cols);
-                }
-            } else if (seq[0] == 91 && (seq[1] == 65 || seq[1] == 66)) {
-up_down_arrow:
-                /* up and down arrow: history */
-                if (history_len > 1) {
-                    /* Update the current history entry before to
-                     * overwrite it with tne next one. */
-                    free(history[history_len-1-history_index]);
-                    history[history_len-1-history_index] = strdup(buf);
-                    /* Show the new entry */
-                    history_index += (seq[1] == 65) ? 1 : -1;
-                    if (history_index < 0) {
-                        history_index = 0;
+        case CTRL_B:     /* ctrl-b */
+            linenoiseEditMoveLeft(&l);
+            break;
+        case CTRL_F:     /* ctrl-f */
+            linenoiseEditMoveRight(&l);
+            break;
+        case CTRL_P:    /* ctrl-p */
+            linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_PREV);
+            break;
+        case CTRL_N:    /* ctrl-n */
+            linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_NEXT);
+            break;
+        case ESC:    /* escape sequence */
+            /* Read the next two bytes representing the escape sequence.
+             * Use two calls to handle slow terminals returning the two
+             * chars at different times. */
+            if (read(l.ifd,seq,1) == -1) break;
+            if (read(l.ifd,seq+1,1) == -1) break;
+
+            /* ESC [ sequences. */
+            if (seq[0] == '[') {
+                if (seq[1] >= '0' && seq[1] <= '9') {
+                    /* Extended escape, read additional byte. */
+                    if (read(l.ifd,seq+2,1) == -1) break;
+                    if (seq[2] == '~') {
+                        switch(seq[1]) {
+                        case '3': /* Delete key. */
+                            linenoiseEditDelete(&l);
+                            break;
+                        }
+                    }
+                } else {
+                    switch(seq[1]) {
+                    case 'A': /* Up */
+                        linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_PREV);
                         break;
-                    } else if (history_index >= history_len) {
-                        history_index = history_len-1;
+                    case 'B': /* Down */
+                        linenoiseEditHistoryNext(&l, LINENOISE_HISTORY_NEXT);
+                        break;
+                    case 'C': /* Right */
+                        linenoiseEditMoveRight(&l);
+                        break;
+                    case 'D': /* Left */
+                        linenoiseEditMoveLeft(&l);
+                        break;
+                    case 'H': /* Home */
+                        linenoiseEditMoveHome(&l);
+                        break;
+                    case 'F': /* End*/
+                        linenoiseEditMoveEnd(&l);
                         break;
                     }
-                    strncpy(buf,history[history_len-1-history_index],buflen);
-                    buf[buflen] = '\0';
-                    len = pos = strlen(buf);
-                    refreshLine(fd,prompt,buf,len,pos,cols);
                 }
-            } else if (seq[0] == 91 && seq[1] > 48 && seq[1] < 55) {
-                /* extended escape */
-                if (read(fd,seq2,2) == -1) break;
-                if (seq[1] == 51 && seq2[0] == 126) {
-                    /* delete */
-                    if (len > 0 && pos < len) {
-                        memmove(buf+pos,buf+pos+1,len-pos-1);
-                        len--;
-                        buf[len] = '\0';
-                        refreshLine(fd,prompt,buf,len,pos,cols);
-                    }
+            }
+
+            /* ESC O sequences. */
+            else if (seq[0] == 'O') {
+                switch(seq[1]) {
+                case 'H': /* Home */
+                    linenoiseEditMoveHome(&l);
+                    break;
+                case 'F': /* End*/
+                    linenoiseEditMoveEnd(&l);
+                    break;
                 }
             }
             break;
         default:
-            if (len < buflen) {
-                if (len == pos) {
-                    buf[pos] = c;
-                    pos++;
-                    len++;
-                    buf[len] = '\0';
-                    if (plen+len < cols) {
-                        /* Avoid a full update of the line in the
-                         * trivial case. */
-                        if (write(fd,&c,1) == -1) return -1;
-                    } else {
-                        refreshLine(fd,prompt,buf,len,pos,cols);
-                    }
-                } else {
-                    memmove(buf+pos+1,buf+pos,len-pos);
-                    buf[pos] = c;
-                    len++;
-                    pos++;
-                    buf[len] = '\0';
-                    refreshLine(fd,prompt,buf,len,pos,cols);
-                }
-            }
+            if (linenoiseEditInsert(&l,c)) return -1;
             break;
-        case 21: /* Ctrl+u, delete the whole line. */
+        case CTRL_U: /* Ctrl+u, delete the whole line. */
             buf[0] = '\0';
-            pos = len = 0;
-            refreshLine(fd,prompt,buf,len,pos,cols);
+            l.pos = l.len = 0;
+            refreshLine(&l);
             break;
-        case 11: /* Ctrl+k, delete from current to end of line. */
-            buf[pos] = '\0';
-            len = pos;
-            refreshLine(fd,prompt,buf,len,pos,cols);
-            break;
-        case 1: /* Ctrl+a, go to the start of the line */
-            pos = 0;
-            refreshLine(fd,prompt,buf,len,pos,cols);
-            break;
-        case 5: /* ctrl+e, go to the end of the line */
-            pos = len;
-            refreshLine(fd,prompt,buf,len,pos,cols);
+        case CTRL_K: /* Ctrl+k, delete from current to end of line. */
+            buf[l.pos] = '\0';
+            l.len = l.pos;
+            refreshLine(&l);
             break;
-        case 12: /* ctrl+l, clear screen */
+        case CTRL_A: /* Ctrl+a, go to the start of the line */
+            linenoiseEditMoveHome(&l);
+            break;
+        case CTRL_E: /* ctrl+e, go to the end of the line */
+            linenoiseEditMoveEnd(&l);
+            break;
+        case CTRL_L: /* ctrl+l, clear screen */
             linenoiseClearScreen();
-            refreshLine(fd,prompt,buf,len,pos,cols);
+            refreshLine(&l);
             break;
-        case 23: /* ctrl+w, delete previous word */
-            old_pos = pos;
-            while (pos > 0 && buf[pos-1] == ' ')
-                pos--;
-            while (pos > 0 && buf[pos-1] != ' ')
-                pos--;
-            diff = old_pos - pos;
-            memmove(&buf[pos], &buf[old_pos], len-old_pos+1);
-            len -= diff;
-            refreshLine(fd,prompt,buf,len,pos,cols);
+        case CTRL_W: /* ctrl+w, delete previous word */
+            linenoiseEditDeletePrevWord(&l);
             break;
         }
     }
-    return len;
+    return l.len;
+}
+
+/* This special mode is used by linenoise in order to print scan codes
+ * on screen for debugging / development purposes. It is implemented
+ * by the linenoise_example program using the --keycodes option. */
+void linenoisePrintKeyCodes(void) {
+    char quit[4];
+
+    printf("Linenoise key codes debugging mode.\n"
+            "Press keys to see scan codes. Type 'quit' at any time to exit.\n");
+    if (enableRawMode(STDIN_FILENO) == -1) return;
+    memset(quit,' ',4);
+    while(1) {
+        char c;
+        int nread;
+
+        nread = read(STDIN_FILENO,&c,1);
+        if (nread <= 0) continue;
+        memmove(quit,quit+1,sizeof(quit)-1); /* shift string to left. */
+        quit[sizeof(quit)-1] = c; /* Insert current char on the right. */
+        if (memcmp(quit,"quit",sizeof(quit)) == 0) break;
+
+        printf("'%c' %02x (%d) (type quit to exit)\n",
+            isprint(c) ? c : '?', (int)c, (int)c);
+        printf("\x1b[0G"); /* Go left edge manually, we are in raw mode. */
+        fflush(stdout);
+    }
+    disableRawMode(STDIN_FILENO);
 }
 
+/* This function calls the line editing function linenoiseEdit() using
+ * the STDIN file descriptor set in raw mode. */
 static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
-    int fd = STDIN_FILENO;
     int count;
 
     if (buflen == 0) {
         errno = EINVAL;
         return -1;
     }
     if (!isatty(STDIN_FILENO)) {
+        /* Not a tty: read from file / pipe. */
         if (fgets(buf, buflen, stdin) == NULL) return -1;
         count = strlen(buf);
         if (count && buf[count-1] == '\n') {
             count--;
             buf[count] = '\0';
         }
     } else {
-        if (enableRawMode(fd) == -1) return -1;
-        count = linenoisePrompt(fd, buf, buflen, prompt);
-        disableRawMode(fd);
+        /* Interactive editing. */
+        if (enableRawMode(STDIN_FILENO) == -1) return -1;
+        count = linenoiseEdit(STDIN_FILENO, STDOUT_FILENO, buf, buflen, prompt);
+        disableRawMode(STDIN_FILENO);
         printf("\n");
     }
     return count;
 }
 
+/* The high level function that is the main API of the linenoise library.
+ * This function checks if the terminal has basic capabilities, just checking
+ * for a blacklist of stupid terminals, and later either calls the line
+ * editing function or uses dummy fgets() so that you will be able to type
+ * something even in the most desperate of the conditions. */
 char *linenoise(const char *prompt) {
     char buf[LINENOISE_MAX_LINE];
     int count;
 
     if (isUnsupportedTerm()) {
         size_t len;
