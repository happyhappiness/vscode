@@ -126,7 +126,7 @@ typedef void* yyscan_t;
 #define yycolumn (YY_CURRENT_BUFFER_LVALUE->yy_bs_column)
 #define yy_flex_debug yyg->yy_flex_debug_r
 
-int yylex_init (yyscan_t* scanner);
+int cmListFileLexer_yylex_init (yyscan_t* scanner);
 
 /* Enter a start condition.  This macro really ought to take a parameter,
  * but we do it the disgusting crufty way forced on us by the ()-less
@@ -145,7 +145,7 @@ int yylex_init (yyscan_t* scanner);
 #define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)
 
 /* Special action meaning "start processing a new file". */
-#define YY_NEW_FILE yyrestart(yyin ,yyscanner )
+#define YY_NEW_FILE cmListFileLexer_yyrestart(yyin ,yyscanner )
 
 #define YY_END_OF_BUFFER_CHAR 0
 
@@ -165,7 +165,7 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 
     /* Note: We specifically omit the test for yy_rule_can_match_eol because it requires
      *       access to the local variable yy_act. Since yyless() is a macro, it would break
-     *       existing scanners that call yyless() from OUTSIDE yylex. 
+     *       existing scanners that call yyless() from OUTSIDE cmListFileLexer_yylex. 
      *       One obvious solution it to make yy_act a global. I tried that, and saw
      *       a 5% performance hit in a non-yylineno scanner, because yy_act is
      *       normally declared as a register variable-- so it is not worth it.
@@ -192,6 +192,8 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
                 } \
         while ( 0 )
 
+#define unput(c) yyunput( c, yyg->yytext_ptr , yyscanner )
+
 /* The following is because we cannot portably get our hands on size_t
  * (without autoconf's help, which isn't available because we want
  * flex-generated scanners to compile on their own).
@@ -259,7 +261,7 @@ struct yy_buffer_state
          * possible backing-up.
          *
          * When we actually see the EOF, we change the status to "new"
-         * (via yyrestart()), so that the user can continue scanning by
+         * (via cmListFileLexer_yyrestart()), so that the user can continue scanning by
          * just pointing yyin at a new input file.
          */
 #define YY_BUFFER_EOF_PENDING 2
@@ -282,46 +284,46 @@ struct yy_buffer_state
  */
 #define YY_CURRENT_BUFFER_LVALUE yyg->yy_buffer_stack[yyg->yy_buffer_stack_top]
 
-void yyrestart (FILE *input_file ,yyscan_t yyscanner );
-void yy_switch_to_buffer (YY_BUFFER_STATE new_buffer ,yyscan_t yyscanner );
-YY_BUFFER_STATE yy_create_buffer (FILE *file,int size ,yyscan_t yyscanner );
-void yy_delete_buffer (YY_BUFFER_STATE b ,yyscan_t yyscanner );
-void yy_flush_buffer (YY_BUFFER_STATE b ,yyscan_t yyscanner );
-void yypush_buffer_state (YY_BUFFER_STATE new_buffer ,yyscan_t yyscanner );
-void yypop_buffer_state (yyscan_t yyscanner );
+void cmListFileLexer_yyrestart (FILE *input_file ,yyscan_t yyscanner );
+void cmListFileLexer_yy_switch_to_buffer (YY_BUFFER_STATE new_buffer ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmListFileLexer_yy_create_buffer (FILE *file,int size ,yyscan_t yyscanner );
+void cmListFileLexer_yy_delete_buffer (YY_BUFFER_STATE b ,yyscan_t yyscanner );
+void cmListFileLexer_yy_flush_buffer (YY_BUFFER_STATE b ,yyscan_t yyscanner );
+void cmListFileLexer_yypush_buffer_state (YY_BUFFER_STATE new_buffer ,yyscan_t yyscanner );
+void cmListFileLexer_yypop_buffer_state (yyscan_t yyscanner );
 
-static void yyensure_buffer_stack (yyscan_t yyscanner );
-static void yy_load_buffer_state (yyscan_t yyscanner );
-static void yy_init_buffer (YY_BUFFER_STATE b,FILE *file ,yyscan_t yyscanner );
+static void cmListFileLexer_yyensure_buffer_stack (yyscan_t yyscanner );
+static void cmListFileLexer_yy_load_buffer_state (yyscan_t yyscanner );
+static void cmListFileLexer_yy_init_buffer (YY_BUFFER_STATE b,FILE *file ,yyscan_t yyscanner );
 
-#define YY_FLUSH_BUFFER yy_flush_buffer(YY_CURRENT_BUFFER ,yyscanner)
+#define YY_FLUSH_BUFFER cmListFileLexer_yy_flush_buffer(YY_CURRENT_BUFFER ,yyscanner)
 
-YY_BUFFER_STATE yy_scan_buffer (char *base,yy_size_t size ,yyscan_t yyscanner );
-YY_BUFFER_STATE yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
-YY_BUFFER_STATE yy_scan_bytes (yyconst char *bytes,int len ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmListFileLexer_yy_scan_buffer (char *base,yy_size_t size ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes (yyconst char *bytes,int len ,yyscan_t yyscanner );
 
-void *yyalloc (yy_size_t ,yyscan_t yyscanner );
-void *yyrealloc (void *,yy_size_t ,yyscan_t yyscanner );
-void yyfree (void * ,yyscan_t yyscanner );
+void *cmListFileLexer_yyalloc (yy_size_t ,yyscan_t yyscanner );
+void *cmListFileLexer_yyrealloc (void *,yy_size_t ,yyscan_t yyscanner );
+void cmListFileLexer_yyfree (void * ,yyscan_t yyscanner );
 
-#define yy_new_buffer yy_create_buffer
+#define yy_new_buffer cmListFileLexer_yy_create_buffer
 
 #define yy_set_interactive(is_interactive) \
         { \
         if ( ! YY_CURRENT_BUFFER ){ \
-        yyensure_buffer_stack (yyscanner); \
+        cmListFileLexer_yyensure_buffer_stack (yyscanner); \
                 YY_CURRENT_BUFFER_LVALUE =    \
-            yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
+            cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
         } \
         YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive; \
         }
 
 #define yy_set_bol(at_bol) \
         { \
         if ( ! YY_CURRENT_BUFFER ){\
-        yyensure_buffer_stack (yyscanner); \
+        cmListFileLexer_yyensure_buffer_stack (yyscanner); \
                 YY_CURRENT_BUFFER_LVALUE =    \
-            yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
+            cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
         } \
         YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
         }
@@ -330,7 +332,7 @@ void yyfree (void * ,yyscan_t yyscanner );
 
 /* Begin user sect3 */
 
-#define yywrap(n) 1
+#define cmListFileLexer_yywrap(n) 1
 #define YY_SKIP_YYWRAP
 
 typedef unsigned char YY_CHAR;
@@ -493,13 +495,13 @@ This file must be translated to C and modified to build everywhere.
 
 Run flex like this:
 
-  flex -ocmListFileLexer.c cmListFileLexer.in.l
+  flex --prefix=cmListFileLexer_yy -ocmListFileLexer.c cmListFileLexer.in.l
 
 Modify cmListFileLexer.c:
   - remove TABs
   - remove the yyunput function
   - add a statement "(void)yyscanner;" to the top of these methods:
-      yy_fatal_error, yyalloc, yyrealloc, yyfree
+      yy_fatal_error, cmListFileLexer_yyalloc, cmListFileLexer_yyrealloc, cmListFileLexer_yyfree
   - remove all YY_BREAK lines occurring right after return statements
 
 */
@@ -510,9 +512,9 @@ Modify cmListFileLexer.c:
 #define YY_NO_UNISTD_H 1
 #define ECHO
 
-/* Setup the proper yylex declaration.  */
+/* Setup the proper cmListFileLexer_yylex declaration.  */
 #define YY_EXTRA_TYPE cmListFileLexer*
-#define YY_DECL int yylex (yyscan_t yyscanner, cmListFileLexer* lexer)
+#define YY_DECL int cmListFileLexer_yylex (yyscan_t yyscanner, cmListFileLexer* lexer)
 
 /* Disable some warnings.  */
 #if defined(_MSC_VER)
@@ -555,7 +557,7 @@ static void cmListFileLexerDestroy(cmListFileLexer* lexer);
 /* Replace the lexer input function.  */
 #undef YY_INPUT
 #define YY_INPUT(buf, result, max_size) \
-  { result = cmListFileLexerInput(yyget_extra(yyscanner), buf, max_size); }
+  { result = cmListFileLexerInput(cmListFileLexer_yyget_extra(yyscanner), buf, max_size); }
 
 /*--------------------------------------------------------------------------*/
 
@@ -613,41 +615,41 @@ struct yyguts_t
 /* Accessor methods to globals.
    These are made visible to non-reentrant scanners for convenience. */
 
-int yylex_destroy (yyscan_t yyscanner );
+int cmListFileLexer_yylex_destroy (yyscan_t yyscanner );
 
-int yyget_debug (yyscan_t yyscanner );
+int cmListFileLexer_yyget_debug (yyscan_t yyscanner );
 
-void yyset_debug (int debug_flag ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_debug (int debug_flag ,yyscan_t yyscanner );
 
-YY_EXTRA_TYPE yyget_extra (yyscan_t yyscanner );
+YY_EXTRA_TYPE cmListFileLexer_yyget_extra (yyscan_t yyscanner );
 
-void yyset_extra (YY_EXTRA_TYPE user_defined ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_extra (YY_EXTRA_TYPE user_defined ,yyscan_t yyscanner );
 
-FILE *yyget_in (yyscan_t yyscanner );
+FILE *cmListFileLexer_yyget_in (yyscan_t yyscanner );
 
-void yyset_in  (FILE * in_str ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_in  (FILE * in_str ,yyscan_t yyscanner );
 
-FILE *yyget_out (yyscan_t yyscanner );
+FILE *cmListFileLexer_yyget_out (yyscan_t yyscanner );
 
-void yyset_out  (FILE * out_str ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_out  (FILE * out_str ,yyscan_t yyscanner );
 
-int yyget_leng (yyscan_t yyscanner );
+int cmListFileLexer_yyget_leng (yyscan_t yyscanner );
 
-char *yyget_text (yyscan_t yyscanner );
+char *cmListFileLexer_yyget_text (yyscan_t yyscanner );
 
-int yyget_lineno (yyscan_t yyscanner );
+int cmListFileLexer_yyget_lineno (yyscan_t yyscanner );
 
-void yyset_lineno (int line_number ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_lineno (int line_number ,yyscan_t yyscanner );
 
 /* Macros after this point can all be overridden by user definitions in
  * section 1.
  */
 
 #ifndef YY_SKIP_YYWRAP
 #ifdef __cplusplus
-extern "C" int yywrap (yyscan_t yyscanner );
+extern "C" int cmListFileLexer_yywrap (yyscan_t yyscanner );
 #else
-extern int yywrap (yyscan_t yyscanner );
+extern int cmListFileLexer_yywrap (yyscan_t yyscanner );
 #endif
 #endif
 
@@ -744,9 +746,9 @@ static int input (yyscan_t yyscanner );
 #ifndef YY_DECL
 #define YY_DECL_IS_OURS 1
 
-extern int yylex (yyscan_t yyscanner);
+extern int cmListFileLexer_yylex (yyscan_t yyscanner);
 
-#define YY_DECL int yylex (yyscan_t yyscanner)
+#define YY_DECL int cmListFileLexer_yylex (yyscan_t yyscanner)
 #endif /* !YY_DECL */
 
 /* Code executed at the beginning of each rule, after yytext and yyleng
@@ -796,12 +798,12 @@ YY_DECL
                         yyout = stdout;
 
                 if ( ! YY_CURRENT_BUFFER ) {
-                        yyensure_buffer_stack (yyscanner);
+                        cmListFileLexer_yyensure_buffer_stack (yyscanner);
                         YY_CURRENT_BUFFER_LVALUE =
-                                yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
+                                cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
                 }
 
-                yy_load_buffer_state(yyscanner );
+                cmListFileLexer_yy_load_buffer_state(yyscanner );
                 }
 
         while ( 1 )             /* loops until end-of-file is reached */
@@ -1021,7 +1023,7 @@ ECHO;
                         /* We're scanning a new file or input source.  It's
                          * possible that this happened because the user
                          * just pointed yyin at a new source and called
-                         * yylex().  If so, then we have to assure
+                         * cmListFileLexer_yylex().  If so, then we have to assure
                          * consistency between YY_CURRENT_BUFFER and our
                          * globals.  Here is the right place to do so, because
                          * this is the first action (other than possibly a
@@ -1081,7 +1083,7 @@ ECHO;
                                 {
                                 yyg->yy_did_buffer_switch_on_eof = 0;
 
-                                if ( yywrap(yyscanner ) )
+                                if ( cmListFileLexer_yywrap(yyscanner ) )
                                         {
                                         /* Note: because we've taken care in
                                          * yy_get_next_buffer() to have set up
@@ -1134,7 +1136,7 @@ ECHO;
                         "fatal flex scanner internal error--no action found" );
         } /* end of action switch */
                 } /* end of scanning one token */
-} /* end of yylex */
+} /* end of cmListFileLexer_yylex */
 
 /* yy_get_next_buffer - try to read in a new buffer
  *
@@ -1213,7 +1215,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                                 b->yy_ch_buf = (char *)
                                         /* Include room in for 2 EOB chars. */
-                                        yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
+                                        cmListFileLexer_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
                                 }
                         else
                                 /* Can't grow it, we don't own it. */
@@ -1245,7 +1247,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                 if ( number_to_move == YY_MORE_ADJ )
                         {
                         ret_val = EOB_ACT_END_OF_FILE;
-                        yyrestart(yyin  ,yyscanner);
+                        cmListFileLexer_yyrestart(yyin  ,yyscanner);
                         }
 
                 else
@@ -1369,13 +1371,13 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                                          */
 
                                         /* Reset buffer status. */
-                                        yyrestart(yyin ,yyscanner);
+                                        cmListFileLexer_yyrestart(yyin ,yyscanner);
 
                                         /*FALLTHROUGH*/
 
                                 case EOB_ACT_END_OF_FILE:
                                         {
-                                        if ( yywrap(yyscanner ) )
+                                        if ( cmListFileLexer_yywrap(yyscanner ) )
                                                 return EOF;
 
                                         if ( ! yyg->yy_did_buffer_switch_on_eof )
@@ -1414,34 +1416,34 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
  * @param yyscanner The scanner object.
  * @note This function does not reset the start condition to @c INITIAL .
  */
-    void yyrestart  (FILE * input_file , yyscan_t yyscanner)
+    void cmListFileLexer_yyrestart  (FILE * input_file , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         if ( ! YY_CURRENT_BUFFER ){
-        yyensure_buffer_stack (yyscanner);
+        cmListFileLexer_yyensure_buffer_stack (yyscanner);
                 YY_CURRENT_BUFFER_LVALUE =
-            yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
+            cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
         }
 
-        yy_init_buffer(YY_CURRENT_BUFFER,input_file ,yyscanner);
-        yy_load_buffer_state(yyscanner );
+        cmListFileLexer_yy_init_buffer(YY_CURRENT_BUFFER,input_file ,yyscanner);
+        cmListFileLexer_yy_load_buffer_state(yyscanner );
 }
 
 /** Switch to a different input buffer.
  * @param new_buffer The new input buffer.
  * @param yyscanner The scanner object.
  */
-    void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer , yyscan_t yyscanner)
+    void cmListFileLexer_yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* TODO. We should be able to replace this entire function body
          * with
-         *              yypop_buffer_state();
-         *              yypush_buffer_state(new_buffer);
+         *              cmListFileLexer_yypop_buffer_state();
+         *              cmListFileLexer_yypush_buffer_state(new_buffer);
      */
-        yyensure_buffer_stack (yyscanner);
+        cmListFileLexer_yyensure_buffer_stack (yyscanner);
         if ( YY_CURRENT_BUFFER == new_buffer )
                 return;
 
@@ -1454,17 +1456,17 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                 }
 
         YY_CURRENT_BUFFER_LVALUE = new_buffer;
-        yy_load_buffer_state(yyscanner );
+        cmListFileLexer_yy_load_buffer_state(yyscanner );
 
         /* We don't actually know whether we did this switch during
-         * EOF (yywrap()) processing, but the only time this flag
-         * is looked at is after yywrap() is called, so it's safe
+         * EOF (cmListFileLexer_yywrap()) processing, but the only time this flag
+         * is looked at is after cmListFileLexer_yywrap() is called, so it's safe
          * to go ahead and always set it.
          */
         yyg->yy_did_buffer_switch_on_eof = 1;
 }
 
-static void yy_load_buffer_state  (yyscan_t yyscanner)
+static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
@@ -1479,35 +1481,35 @@ static void yy_load_buffer_state  (yyscan_t yyscanner)
  * @param yyscanner The scanner object.
  * @return the allocated buffer state.
  */
-    YY_BUFFER_STATE yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
+    YY_BUFFER_STATE cmListFileLexer_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
     
-        b = (YY_BUFFER_STATE) yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
+        b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
-                YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );
+                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_create_buffer()" );
 
         b->yy_buf_size = size;
 
         /* yy_ch_buf has to be 2 characters longer than the size given because
          * we need to put in 2 end-of-buffer characters.
          */
-        b->yy_ch_buf = (char *) yyalloc(b->yy_buf_size + 2 ,yyscanner );
+        b->yy_ch_buf = (char *) cmListFileLexer_yyalloc(b->yy_buf_size + 2 ,yyscanner );
         if ( ! b->yy_ch_buf )
-                YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );
+                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_create_buffer()" );
 
         b->yy_is_our_buffer = 1;
 
-        yy_init_buffer(b,file ,yyscanner);
+        cmListFileLexer_yy_init_buffer(b,file ,yyscanner);
 
         return b;
 }
 
 /** Destroy the buffer.
- * @param b a buffer created with yy_create_buffer()
+ * @param b a buffer created with cmListFileLexer_yy_create_buffer()
  * @param yyscanner The scanner object.
  */
-    void yy_delete_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
+    void cmListFileLexer_yy_delete_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
@@ -1518,9 +1520,9 @@ static void yy_load_buffer_state  (yyscan_t yyscanner)
                 YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;
 
         if ( b->yy_is_our_buffer )
-                yyfree((void *) b->yy_ch_buf ,yyscanner );
+                cmListFileLexer_yyfree((void *) b->yy_ch_buf ,yyscanner );
 
-        yyfree((void *) b ,yyscanner );
+        cmListFileLexer_yyfree((void *) b ,yyscanner );
 }
 
 #ifndef __cplusplus
@@ -1529,21 +1531,21 @@ extern int isatty (int );
     
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
- * such as during a yyrestart() or at EOF.
+ * such as during a cmListFileLexer_yyrestart() or at EOF.
  */
-    static void yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file , yyscan_t yyscanner)
+    static void cmListFileLexer_yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file , yyscan_t yyscanner)
 
 {
         int oerrno = errno;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        yy_flush_buffer(b ,yyscanner);
+        cmListFileLexer_yy_flush_buffer(b ,yyscanner);
 
         b->yy_input_file = file;
         b->yy_fill_buffer = 1;
 
-    /* If b is the current buffer, then yy_init_buffer was _probably_
-     * called from yyrestart() or through yy_get_next_buffer.
+    /* If b is the current buffer, then cmListFileLexer_yy_init_buffer was _probably_
+     * called from cmListFileLexer_yyrestart() or through yy_get_next_buffer.
      * In that case, we don't want to reset the lineno or column.
      */
     if (b != YY_CURRENT_BUFFER){
@@ -1560,7 +1562,7 @@ extern int isatty (int );
  * @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
  * @param yyscanner The scanner object.
  */
-    void yy_flush_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
+    void cmListFileLexer_yy_flush_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         if ( ! b )
@@ -1581,7 +1583,7 @@ extern int isatty (int );
         b->yy_buffer_status = YY_BUFFER_NEW;
 
         if ( b == YY_CURRENT_BUFFER )
-                yy_load_buffer_state(yyscanner );
+                cmListFileLexer_yy_load_buffer_state(yyscanner );
 }
 
 /** Pushes the new state onto the stack. The new state becomes
@@ -1590,15 +1592,15 @@ extern int isatty (int );
  *  @param new_buffer The new state.
  *  @param yyscanner The scanner object.
  */
-void yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscanner)
+void cmListFileLexer_yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         if (new_buffer == NULL)
                 return;
 
-        yyensure_buffer_stack(yyscanner);
+        cmListFileLexer_yyensure_buffer_stack(yyscanner);
 
-        /* This block is copied from yy_switch_to_buffer. */
+        /* This block is copied from cmListFileLexer_yy_switch_to_buffer. */
         if ( YY_CURRENT_BUFFER )
                 {
                 /* Flush out information for old buffer. */
@@ -1612,36 +1614,36 @@ void yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscanner)
                 yyg->yy_buffer_stack_top++;
         YY_CURRENT_BUFFER_LVALUE = new_buffer;
 
-        /* copied from yy_switch_to_buffer. */
-        yy_load_buffer_state(yyscanner );
+        /* copied from cmListFileLexer_yy_switch_to_buffer. */
+        cmListFileLexer_yy_load_buffer_state(yyscanner );
         yyg->yy_did_buffer_switch_on_eof = 1;
 }
 
 /** Removes and deletes the top of the stack, if present.
  *  The next element becomes the new top.
  *  @param yyscanner The scanner object.
  */
-void yypop_buffer_state (yyscan_t yyscanner)
+void cmListFileLexer_yypop_buffer_state (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         if (!YY_CURRENT_BUFFER)
                 return;
 
-        yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
+        cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
         YY_CURRENT_BUFFER_LVALUE = NULL;
         if (yyg->yy_buffer_stack_top > 0)
                 --yyg->yy_buffer_stack_top;
 
         if (YY_CURRENT_BUFFER) {
-                yy_load_buffer_state(yyscanner );
+                cmListFileLexer_yy_load_buffer_state(yyscanner );
                 yyg->yy_did_buffer_switch_on_eof = 1;
         }
 }
 
 /* Allocates the stack if it does not exist.
  *  Guarantees space for at least one push.
  */
-static void yyensure_buffer_stack (yyscan_t yyscanner)
+static void cmListFileLexer_yyensure_buffer_stack (yyscan_t yyscanner)
 {
         int num_to_alloc;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
@@ -1653,7 +1655,7 @@ static void yyensure_buffer_stack (yyscan_t yyscanner)
                  * immediate realloc on the next call.
          */
                 num_to_alloc = 1;
-                yyg->yy_buffer_stack = (struct yy_buffer_state**)yyalloc
+                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyalloc
                                                                 (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
                 
@@ -1670,7 +1672,7 @@ static void yyensure_buffer_stack (yyscan_t yyscanner)
                 int grow_size = 8 /* arbitrary grow size */;
 
                 num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
-                yyg->yy_buffer_stack = (struct yy_buffer_state**)yyrealloc
+                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyrealloc
                                                                 (yyg->yy_buffer_stack,
                                                                 num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
@@ -1687,7 +1689,7 @@ static void yyensure_buffer_stack (yyscan_t yyscanner)
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object. 
  */
-YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
+YY_BUFFER_STATE cmListFileLexer_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
     
@@ -1697,9 +1699,9 @@ YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscann
                 /* They forgot to leave room for the EOB's. */
                 return 0;
 
-        b = (YY_BUFFER_STATE) yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
+        b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
-                YY_FATAL_ERROR( "out of dynamic memory in yy_scan_buffer()" );
+                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_buffer()" );
 
         b->yy_buf_size = size - 2;      /* "- 2" to take care of EOB's */
         b->yy_buf_pos = b->yy_ch_buf = base;
@@ -1711,33 +1713,33 @@ YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscann
         b->yy_fill_buffer = 0;
         b->yy_buffer_status = YY_BUFFER_NEW;
 
-        yy_switch_to_buffer(b ,yyscanner );
+        cmListFileLexer_yy_switch_to_buffer(b ,yyscanner );
 
         return b;
 }
 
-/** Setup the input buffer state to scan a string. The next call to yylex() will
+/** Setup the input buffer state to scan a string. The next call to cmListFileLexer_yylex() will
  * scan from a @e copy of @a str.
  * @param str a NUL-terminated string to scan
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  * @note If you want to scan bytes that may contain NUL values, then use
- *       yy_scan_bytes() instead.
+ *       cmListFileLexer_yy_scan_bytes() instead.
  */
-YY_BUFFER_STATE yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
+YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
 {
     
-        return yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
+        return cmListFileLexer_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
 }
 
-/** Setup the input buffer state to scan the given bytes. The next call to yylex() will
+/** Setup the input buffer state to scan the given bytes. The next call to cmListFileLexer_yylex() will
  * scan from a @e copy of @a bytes.
  * @param bytes the byte buffer to scan
  * @param len the number of bytes in the buffer pointed to by @a bytes.
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  */
-YY_BUFFER_STATE yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
+YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
         char *buf;
@@ -1746,18 +1748,18 @@ YY_BUFFER_STATE yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscan
     
         /* Get memory for full buffer, including space for trailing EOB's. */
         n = len + 2;
-        buf = (char *) yyalloc(n ,yyscanner );
+        buf = (char *) cmListFileLexer_yyalloc(n ,yyscanner );
         if ( ! buf )
-                YY_FATAL_ERROR( "out of dynamic memory in yy_scan_bytes()" );
+                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_bytes()" );
 
         for ( i = 0; i < len; ++i )
                 buf[i] = bytes[i];
 
         buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;
 
-        b = yy_scan_buffer(buf,n ,yyscanner);
+        b = cmListFileLexer_yy_scan_buffer(buf,n ,yyscanner);
         if ( ! b )
-                YY_FATAL_ERROR( "bad buffer in yy_scan_bytes()" );
+                YY_FATAL_ERROR( "bad buffer in cmListFileLexer_yy_scan_bytes()" );
 
         /* It's okay to grow etc. this buffer, and we should throw it
          * away when we're done.
@@ -1800,7 +1802,7 @@ static void yy_fatal_error (yyconst char* msg , yyscan_t yyscanner)
 /** Get the user-defined data for this scanner.
  * @param yyscanner The scanner object.
  */
-YY_EXTRA_TYPE yyget_extra  (yyscan_t yyscanner)
+YY_EXTRA_TYPE cmListFileLexer_yyget_extra  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyextra;
@@ -1809,7 +1811,7 @@ YY_EXTRA_TYPE yyget_extra  (yyscan_t yyscanner)
 /** Get the current line number.
  * @param yyscanner The scanner object.
  */
-int yyget_lineno  (yyscan_t yyscanner)
+int cmListFileLexer_yyget_lineno  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     
@@ -1822,7 +1824,7 @@ int yyget_lineno  (yyscan_t yyscanner)
 /** Get the current column number.
  * @param yyscanner The scanner object.
  */
-int yyget_column  (yyscan_t yyscanner)
+int cmListFileLexer_yyget_column  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     
@@ -1835,7 +1837,7 @@ int yyget_column  (yyscan_t yyscanner)
 /** Get the input stream.
  * @param yyscanner The scanner object.
  */
-FILE *yyget_in  (yyscan_t yyscanner)
+FILE *cmListFileLexer_yyget_in  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyin;
@@ -1844,7 +1846,7 @@ FILE *yyget_in  (yyscan_t yyscanner)
 /** Get the output stream.
  * @param yyscanner The scanner object.
  */
-FILE *yyget_out  (yyscan_t yyscanner)
+FILE *cmListFileLexer_yyget_out  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyout;
@@ -1853,7 +1855,7 @@ FILE *yyget_out  (yyscan_t yyscanner)
 /** Get the length of the current token.
  * @param yyscanner The scanner object.
  */
-int yyget_leng  (yyscan_t yyscanner)
+int cmListFileLexer_yyget_leng  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyleng;
@@ -1863,7 +1865,7 @@ int yyget_leng  (yyscan_t yyscanner)
  * @param yyscanner The scanner object.
  */
 
-char *yyget_text  (yyscan_t yyscanner)
+char *cmListFileLexer_yyget_text  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yytext;
@@ -1873,7 +1875,7 @@ char *yyget_text  (yyscan_t yyscanner)
  * @param user_defined The data to be associated with this scanner.
  * @param yyscanner The scanner object.
  */
-void yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscanner)
+void cmListFileLexer_yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     yyextra = user_defined ;
@@ -1883,13 +1885,13 @@ void yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscanner)
  * @param line_number
  * @param yyscanner The scanner object.
  */
-void yyset_lineno (int  line_number , yyscan_t yyscanner)
+void cmListFileLexer_yyset_lineno (int  line_number , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "yyset_lineno called with no buffer" , yyscanner); 
+           yy_fatal_error( "cmListFileLexer_yyset_lineno called with no buffer" , yyscanner); 
     
     yylineno = line_number;
 }
@@ -1898,13 +1900,13 @@ void yyset_lineno (int  line_number , yyscan_t yyscanner)
  * @param line_number
  * @param yyscanner The scanner object.
  */
-void yyset_column (int  column_no , yyscan_t yyscanner)
+void cmListFileLexer_yyset_column (int  column_no , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "yyset_column called with no buffer" , yyscanner); 
+           yy_fatal_error( "cmListFileLexer_yyset_column called with no buffer" , yyscanner); 
     
     yycolumn = column_no;
 }
@@ -1913,27 +1915,27 @@ void yyset_column (int  column_no , yyscan_t yyscanner)
  * input buffer.
  * @param in_str A readable stream.
  * @param yyscanner The scanner object.
- * @see yy_switch_to_buffer
+ * @see cmListFileLexer_yy_switch_to_buffer
  */
-void yyset_in (FILE *  in_str , yyscan_t yyscanner)
+void cmListFileLexer_yyset_in (FILE *  in_str , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     yyin = in_str ;
 }
 
-void yyset_out (FILE *  out_str , yyscan_t yyscanner)
+void cmListFileLexer_yyset_out (FILE *  out_str , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     yyout = out_str ;
 }
 
-int yyget_debug  (yyscan_t yyscanner)
+int cmListFileLexer_yyget_debug  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yy_flex_debug;
 }
 
-void yyset_debug (int  bdebug , yyscan_t yyscanner)
+void cmListFileLexer_yyset_debug (int  bdebug , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     yy_flex_debug = bdebug ;
@@ -1967,27 +1969,27 @@ static int yy_init_globals (yyscan_t yyscanner)
 #endif
 
     /* For future reference: Set errno on error, since we are called by
-     * yylex_init()
+     * cmListFileLexer_yylex_init()
      */
     return 0;
 }
 
 /* User-visible API */
 
-/* yylex_init is special because it creates the scanner itself, so it is
+/* cmListFileLexer_yylex_init is special because it creates the scanner itself, so it is
  * the ONLY reentrant function that doesn't take the scanner as the last argument.
  * That's why we explicitly handle the declaration, instead of using our macros.
  */
 
-int yylex_init(yyscan_t* ptr_yy_globals)
+int cmListFileLexer_yylex_init(yyscan_t* ptr_yy_globals)
 
 {
     if (ptr_yy_globals == NULL){
         errno = EINVAL;
         return 1;
     }
 
-    *ptr_yy_globals = (yyscan_t) yyalloc ( sizeof( struct yyguts_t ), NULL );
+    *ptr_yy_globals = (yyscan_t) cmListFileLexer_yyalloc ( sizeof( struct yyguts_t ), NULL );
 
     if (*ptr_yy_globals == NULL){
         errno = ENOMEM;
@@ -1999,28 +2001,28 @@ int yylex_init(yyscan_t* ptr_yy_globals)
     return yy_init_globals ( *ptr_yy_globals );
 }
 
-/* yylex_destroy is for both reentrant and non-reentrant scanners. */
-int yylex_destroy  (yyscan_t yyscanner)
+/* cmListFileLexer_yylex_destroy is for both reentrant and non-reentrant scanners. */
+int cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
     /* Pop the buffer stack, destroying each element. */
         while(YY_CURRENT_BUFFER){
-                yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
+                cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
                 YY_CURRENT_BUFFER_LVALUE = NULL;
-                yypop_buffer_state(yyscanner);
+                cmListFileLexer_yypop_buffer_state(yyscanner);
         }
 
         /* Destroy the stack itself. */
-        yyfree(yyg->yy_buffer_stack ,yyscanner);
+        cmListFileLexer_yyfree(yyg->yy_buffer_stack ,yyscanner);
         yyg->yy_buffer_stack = NULL;
 
     /* Destroy the start condition stack. */
-        yyfree(yyg->yy_start_stack ,yyscanner );
+        cmListFileLexer_yyfree(yyg->yy_start_stack ,yyscanner );
         yyg->yy_start_stack = NULL;
 
     /* Destroy the main struct (reentrant only). */
-    yyfree ( yyscanner , yyscanner );
+    cmListFileLexer_yyfree ( yyscanner , yyscanner );
     return 0;
 }
 
@@ -2050,13 +2052,13 @@ static int yy_flex_strlen (yyconst char * s , yyscan_t yyscanner)
 }
 #endif
 
-void *yyalloc (yy_size_t  size , yyscan_t yyscanner)
+void *cmListFileLexer_yyalloc (yy_size_t  size , yyscan_t yyscanner)
 {
         (void)yyscanner;
         return (void *) malloc( size );
 }
 
-void *yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
+void *cmListFileLexer_yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
 {
         (void)yyscanner;
         /* The cast to (char *) in the following accommodates both
@@ -2069,10 +2071,10 @@ void *yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
         return (void *) realloc( (char *) ptr, size );
 }
 
-void yyfree (void * ptr , yyscan_t yyscanner)
+void cmListFileLexer_yyfree (void * ptr , yyscan_t yyscanner)
 {
         (void)yyscanner;
-        free( (char *) ptr );   /* see yyrealloc() for (char *) cast */
+        free( (char *) ptr );   /* see cmListFileLexer_yyrealloc() for (char *) cast */
 }
 
 #define YYTABLES_NAME "yytables"
@@ -2186,8 +2188,8 @@ static void cmListFileLexerInit(cmListFileLexer* lexer)
 {
   if(lexer->file || lexer->string_buffer)
     {
-    yylex_init(&lexer->scanner);
-    yyset_extra(lexer,lexer->scanner);
+    cmListFileLexer_yylex_init(&lexer->scanner);
+    cmListFileLexer_yyset_extra(lexer, lexer->scanner);
     }
 }
 
@@ -2196,7 +2198,7 @@ static void cmListFileLexerDestroy(cmListFileLexer* lexer)
 {
   if(lexer->file || lexer->string_buffer)
     {
-    yylex_destroy(lexer->scanner);
+    cmListFileLexer_yylex_destroy(lexer->scanner);
     if(lexer->file)
       {
       fclose(lexer->file);
@@ -2281,7 +2283,7 @@ cmListFileLexer_Token* cmListFileLexer_Scan(cmListFileLexer* lexer)
     {
     return 0;
     }
-  if(yylex(lexer->scanner,lexer))
+  if(cmListFileLexer_yylex(lexer->scanner, lexer))
     {
     return &lexer->token;
     }