@@ -165,7 +165,8 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 
     #define YY_LESS_LINENO(n)
     
-/* Return all but the first "n" matched characters back to the input stream. */
+/* Return all but the first "n" matched characters back to the input
+   stream. */
 #define yyless(n) \
   do \
     { \
@@ -245,9 +246,9 @@ struct yy_buffer_state
    * still have a bunch of tokens to match, though, because of
    * possible backing-up.
    *
-   * When we actually see the EOF, we change the status to "new"
-   * (via cmCommandArgument_yyrestart()), so that the user can continue scanning by
-   * just pointing yyin at a new input file.
+   * When we actually see the EOF, we change the status to "new" (via
+   * cmCommandArgument_yyrestart()), so that the user can continue scanning
+   * by just pointing yyin at a new input file.
    */
 #define YY_BUFFER_EOF_PENDING 2
 
@@ -264,24 +265,32 @@ struct yy_buffer_state
                           ? yyg->yy_buffer_stack[yyg->yy_buffer_stack_top] \
                           : NULL)
 
-/* Same as previous macro, but useful when we know that the buffer stack is not
- * NULL or when we need an lvalue. For internal use only.
+/* Same as previous macro, but useful when we know that the buffer stack is
+ * not NULL or when we need an lvalue. For internal use only.
  */
 #define YY_CURRENT_BUFFER_LVALUE yyg->yy_buffer_stack[yyg->yy_buffer_stack_top]
 
 void cmCommandArgument_yyrestart (FILE *input_file ,yyscan_t yyscanner );
-void cmCommandArgument_yy_switch_to_buffer (YY_BUFFER_STATE new_buffer ,yyscan_t yyscanner );
-YY_BUFFER_STATE cmCommandArgument_yy_create_buffer (FILE *file,int size ,yyscan_t yyscanner );
-void cmCommandArgument_yy_delete_buffer (YY_BUFFER_STATE b ,yyscan_t yyscanner );
-void cmCommandArgument_yy_flush_buffer (YY_BUFFER_STATE b ,yyscan_t yyscanner );
-void cmCommandArgument_yypush_buffer_state (YY_BUFFER_STATE new_buffer ,yyscan_t yyscanner );
+void cmCommandArgument_yy_switch_to_buffer (YY_BUFFER_STATE new_buffer ,
+                                            yyscan_t yyscanner );
+YY_BUFFER_STATE cmCommandArgument_yy_create_buffer (FILE *file,int size ,
+                                                    yyscan_t yyscanner );
+void cmCommandArgument_yy_delete_buffer (YY_BUFFER_STATE b ,
+                                         yyscan_t yyscanner );
+void cmCommandArgument_yy_flush_buffer (YY_BUFFER_STATE b ,
+                                        yyscan_t yyscanner );
+void cmCommandArgument_yypush_buffer_state (YY_BUFFER_STATE new_buffer ,
+                                            yyscan_t yyscanner );
 void cmCommandArgument_yypop_buffer_state (yyscan_t yyscanner );
 
 static void cmCommandArgument_yyensure_buffer_stack (yyscan_t yyscanner );
 static void cmCommandArgument_yy_load_buffer_state (yyscan_t yyscanner );
-static void cmCommandArgument_yy_init_buffer (YY_BUFFER_STATE b,FILE *file ,yyscan_t yyscanner );
+static void cmCommandArgument_yy_init_buffer (YY_BUFFER_STATE b,
+                                              FILE *file ,
+                                              yyscan_t yyscanner );
 
-#define YY_FLUSH_BUFFER cmCommandArgument_yy_flush_buffer(YY_CURRENT_BUFFER ,yyscanner)
+#define YY_FLUSH_BUFFER cmCommandArgument_yy_flush_buffer(YY_CURRENT_BUFFER ,
+                                                          yyscanner)
 
 YY_BUFFER_STATE cmCommandArgument_yy_scan_buffer (char *base,yy_size_t size ,yyscan_t yyscanner );
 YY_BUFFER_STATE cmCommandArgument_yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
@@ -630,8 +639,8 @@ static int input (yyscan_t yyscanner );
 #define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
 #endif
 
-/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
- * is returned in "result".
+/* Gets input and stuffs it into "buf".  number of characters read, or
+ * YY_NULL, is returned in "result".
  */
 #ifndef YY_INPUT
 #define YY_INPUT(buf,result,max_size) \
@@ -1171,7 +1180,8 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
   return ret_val;
 }
 
-/* yy_get_previous_state - get the state just before the EOB char was reached */
+/* yy_get_previous_state - get the state just before the EOB char was
+   reached */
 
     static yy_state_type yy_get_previous_state (yyscan_t yyscanner)
 {
@@ -1352,10 +1362,10 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
   YY_CURRENT_BUFFER_LVALUE = new_buffer;
   cmCommandArgument_yy_load_buffer_state(yyscanner );
 
-  /* We don't actually know whether we did this switch during
-   * EOF (cmCommandArgument_yywrap()) processing, but the only time this flag
-   * is looked at is after cmCommandArgument_yywrap() is called, so it's safe
-   * to go ahead and always set it.
+  /* We don't actually know whether we did this switch during EOF
+   * (cmCommandArgument_yywrap()) processing, but the only time this flag is
+   * looked at is after cmCommandArgument_yywrap() is called, so it's safe to
+   * go ahead and always set it.
    */
   yyg->yy_did_buffer_switch_on_eof = 1;
 }
@@ -1369,11 +1379,10 @@ static void cmCommandArgument_yy_load_buffer_state  (yyscan_t yyscanner)
   yyg->yy_hold_char = *yyg->yy_c_buf_p;
 }
 
-/** Allocate and initialize an input buffer state.
- * @param file A readable stream.
- * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.
- * @param yyscanner The scanner object.
- * @return the allocated buffer state.
+/** Allocate and initialize an input buffer state.  @param file A readable
+ * stream.  @param size The character buffer size in bytes. When in doubt,
+ * use @c YY_BUF_SIZE.  @param yyscanner The scanner object.  @return the
+ * allocated buffer state.
  */
     YY_BUFFER_STATE cmCommandArgument_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
@@ -1438,9 +1447,10 @@ extern int isatty (int );
   b->yy_input_file = file;
   b->yy_fill_buffer = 1;
 
-    /* If b is the current buffer, then cmCommandArgument_yy_init_buffer was _probably_
-     * called from cmCommandArgument_yyrestart() or through yy_get_next_buffer.
-     * In that case, we don't want to reset the lineno or column.
+    /* If b is the current buffer, then cmCommandArgument_yy_init_buffer was
+     * _probably_ called from cmCommandArgument_yyrestart() or through
+     * yy_get_next_buffer.  In that case, we don't want to reset the lineno
+     * or column.
      */
     if (b != YY_CURRENT_BUFFER){
         b->yy_bs_lineno = 1;
@@ -1452,9 +1462,9 @@ extern int isatty (int );
   errno = oerrno;
 }
 
-/** Discard all buffered characters. On the next scan, YY_INPUT will be called.
- * @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
- * @param yyscanner The scanner object.
+/** Discard all buffered characters. On the next scan, YY_INPUT will be
+ * called.  @param b the buffer state to be flushed, usually @c
+ * YY_CURRENT_BUFFER.  @param yyscanner The scanner object.
  */
     void cmCommandArgument_yy_flush_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
 {
@@ -1577,11 +1587,10 @@ static void cmCommandArgument_yyensure_buffer_stack (yyscan_t yyscanner)
   }
 }
 
-/** Setup the input buffer state to scan directly from a user-specified character buffer.
- * @param base the character buffer
- * @param size the size in bytes of the character buffer
- * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object. 
+/** Setup the input buffer state to scan directly from a user-specified
+ * character buffer.  @param base the character buffer @param size the size
+ * in bytes of the character buffer @param yyscanner The scanner object.
+ * @return the newly allocated buffer state object.
  */
 YY_BUFFER_STATE cmCommandArgument_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
@@ -1612,26 +1621,24 @@ YY_BUFFER_STATE cmCommandArgument_yy_scan_buffer  (char * base, yy_size_t  size
   return b;
 }
 
-/** Setup the input buffer state to scan a string. The next call to cmCommandArgument_yylex() will
- * scan from a @e copy of @a str.
- * @param str a NUL-terminated string to scan
- * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object.
- * @note If you want to scan bytes that may contain NUL values, then use
- *       cmCommandArgument_yy_scan_bytes() instead.
+/** Setup the input buffer state to scan a string. The next call to
+ * cmCommandArgument_yylex() will scan from a @e copy of @a str.  @param str
+ * a NUL-terminated string to scan @param yyscanner The scanner object.
+ * @return the newly allocated buffer state object.  @note If you want to
+ * scan bytes that may contain NUL values, then use
+ * cmCommandArgument_yy_scan_bytes() instead.
  */
 YY_BUFFER_STATE cmCommandArgument_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
 {
     
   return cmCommandArgument_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
 }
 
-/** Setup the input buffer state to scan the given bytes. The next call to cmCommandArgument_yylex() will
- * scan from a @e copy of @a bytes.
- * @param bytes the byte buffer to scan
- * @param len the number of bytes in the buffer pointed to by @a bytes.
- * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object.
+/** Setup the input buffer state to scan the given bytes. The next call to
+ * cmCommandArgument_yylex() will scan from a @e copy of @a bytes.  @param
+ * bytes the byte buffer to scan @param len the number of bytes in the buffer
+ * pointed to by @a bytes.  @param yyscanner The scanner object.  @return the
+ * newly allocated buffer state object.
  */
 YY_BUFFER_STATE cmCommandArgument_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
 {
@@ -1799,7 +1806,12 @@ void cmCommandArgument_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmCommandArgument_yyset_column called with no buffer" , yyscanner); 
+          {
+          yy_fatal_error
+            ("cmCommandArgument_yyset_column called with no buffer" , 
+             yyscanner); 
+          }
+        
     
     yycolumn = column_no;
 }
@@ -1869,9 +1881,10 @@ static int yy_init_globals (yyscan_t yyscanner)
 
 /* User-visible API */
 
-/* cmCommandArgument_yylex_init is special because it creates the scanner itself, so it is
- * the ONLY reentrant function that doesn't take the scanner as the last argument.
- * That's why we explicitly handle the declaration, instead of using our macros.
+/* cmCommandArgument_yylex_init is special because it creates the scanner
+ * itself, so it is the ONLY reentrant function that doesn't take the scanner
+ * as the last argument.  That's why we explicitly handle the declaration,
+ * instead of using our macros.
  */
 
 int cmCommandArgument_yylex_init(yyscan_t* ptr_yy_globals)
@@ -1894,7 +1907,8 @@ int cmCommandArgument_yylex_init(yyscan_t* ptr_yy_globals)
     return yy_init_globals ( *ptr_yy_globals );
 }
 
-/* cmCommandArgument_yylex_destroy is for both reentrant and non-reentrant scanners. */
+/* cmCommandArgument_yylex_destroy is for both reentrant and non-reentrant
+   scanners. */
 int cmCommandArgument_yylex_destroy  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
@@ -1924,7 +1938,8 @@ int cmCommandArgument_yylex_destroy  (yyscan_t yyscanner)
  */
 
 #ifndef yytext_ptr
-static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , yyscan_t yyscanner)
+static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , 
+                             yyscan_t yyscanner)
 {
   register int i;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
@@ -1964,7 +1979,8 @@ void *cmCommandArgument_yyrealloc  (void * ptr, yy_size_t  size , yyscan_t)
 
 void cmCommandArgument_yyfree (void * ptr , yyscan_t)
 {
-  free( (char *) ptr );  /* see cmCommandArgument_yyrealloc() for (char *) cast */
+  free( (char *) ptr );  
+  /* see cmCommandArgument_yyrealloc() for (char *) cast */
 }
 
 #define YYTABLES_NAME "yytables"