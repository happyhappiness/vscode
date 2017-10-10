 
 /*  2 + (2 * num_attrs) + 8 + 1 + 8 + 'm' + NUL */
 /* "\033[1;2;4;5;7;38;5;2xx;48;5;2xxm\0" */
 /*
  * The maximum length of ANSI color sequence we would generate:
  * - leading ESC '['            2
- * - attr + ';'                 2 * 8 (e.g. "1;")
- * - fg color + ';'             9 (e.g. "38;5;2xx;")
- * - fg color + ';'             9 (e.g. "48;5;2xx;")
+ * - attr + ';'                 3 * 10 (e.g. "1;")
+ * - fg color + ';'             17 (e.g. "38;2;255;255;255;")
+ * - bg color + ';'             17 (e.g. "48;2;255;255;255;")
  * - terminating 'm' NUL        2
  *
  * The above overcounts attr (we only use 5 not 8) and one semicolon
  * but it is close enough.
  */
-#define COLOR_MAXLEN 40
+#define COLOR_MAXLEN 70
 
 /*
  * IMPORTANT: Due to the way these color codes are emulated on Windows,
  * write them only using printf(), fprintf(), and fputs(). In particular,
  * do not use puts() or write().
  */
