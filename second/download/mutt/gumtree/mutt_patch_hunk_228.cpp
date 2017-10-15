 			 long size);
 /* If percent is positive, it is displayed as percentage, otherwise
  * percentage is calculated from progress->size and pos if progress
  * was initialized with positive size, otherwise no percentage is shown */
 void mutt_progress_update (progress_t* progress, long pos, int percent);
 
-static inline int mutt_term_width(short wrap)
+/* Windows for different parts of the screen */
+typedef struct
+{
+  int rows;
+  int cols;
+  int row_offset;
+  int col_offset;
+} mutt_window_t;
+
+extern mutt_window_t *MuttHelpWindow;
+extern mutt_window_t *MuttIndexWindow;
+extern mutt_window_t *MuttStatusWindow;
+extern mutt_window_t *MuttMessageWindow;
+#ifdef USE_SIDEBAR
+extern mutt_window_t *MuttSidebarWindow;
+#endif
+
+void mutt_init_windows (void);
+void mutt_free_windows (void);
+void mutt_reflow_windows (void);
+int mutt_window_move (mutt_window_t *, int row, int col);
+int mutt_window_mvaddch (mutt_window_t *, int row, int col, const chtype ch);
+int mutt_window_mvaddstr (mutt_window_t *, int row, int col, const char *str);
+int mutt_window_mvprintw (mutt_window_t *, int row, int col, const char *fmt, ...);
+void mutt_window_clrtoeol (mutt_window_t *);
+void mutt_window_clearline (mutt_window_t *, int row);
+void mutt_window_getyx (mutt_window_t *, int *y, int *x);
+
+
+static inline int mutt_window_wrap_cols(mutt_window_t *win, short wrap)
 {
   if (wrap < 0)
-    return COLS > -wrap ? COLS + wrap : COLS;
+    return win->cols > -wrap ? win->cols + wrap : win->cols;
   else if (wrap)
-    return wrap < COLS ? wrap : COLS;
+    return wrap < win->cols ? wrap : win->cols;
   else
-    return COLS;
+    return win->cols;
 }
 
 extern int *ColorQuote;
 extern int ColorQuoteUsed;
 extern int ColorDefs[];
 extern COLOR_LINE *ColorHdrList;
