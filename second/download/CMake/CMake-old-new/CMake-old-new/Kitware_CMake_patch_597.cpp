@@ -43,7 +43,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t; 
+typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 #endif /* ! C99 */
@@ -164,8 +164,9 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
-    
-/* Return all but the first "n" matched characters back to the input stream. */
+
+/* Return all but the first "n" matched characters back to the input stream.
+ */
 #define yyless(n) \
         do \
                 { \
@@ -174,7 +175,8 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
         YY_LESS_LINENO(yyless_macro_arg);\
                 *yy_cp = yyg->yy_hold_char; \
                 YY_RESTORE_YY_MORE_OFFSET \
-                yyg->yy_c_buf_p = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
+                yyg->yy_c_buf_p \
+                  = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
                 YY_DO_BEFORE_ACTION; /* set up yytext again */ \
                 } \
         while ( 0 )
@@ -231,7 +233,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-    
+
         /* Whether to try to fill the input buffer when we reach the
          * end of it.
          */
@@ -248,8 +250,8 @@ struct yy_buffer_state
          * possible backing-up.
          *
          * When we actually see the EOF, we change the status to "new"
-         * (via cmDependsFortran_yyrestart()), so that the user can continue scanning by
-         * just pointing yyin at a new input file.
+         * (via cmDependsFortran_yyrestart()), so that the user can continue
+         * scanning by just pointing yyin at a new input file.
          */
 #define YY_BUFFER_EOF_PENDING 2
 
@@ -774,7 +776,7 @@ extern int cmDependsFortran_yywrap (yyscan_t yyscanner );
 #endif
 
     static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
-    
+
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -1722,7 +1724,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmDependsFortran_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-    
+
         b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_create_buffer()" );
@@ -1766,7 +1768,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-    
+
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmDependsFortran_yyrestart() or at EOF.
@@ -1792,7 +1794,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-    
+
         errno = oerrno;
 }
 
@@ -1896,9 +1898,9 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyalloc
                                                                 (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
-                
+
                 memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
-                                
+
                 yyg->yy_buffer_stack_max = num_to_alloc;
                 yyg->yy_buffer_stack_top = 0;
                 return;
@@ -1925,12 +1927,12 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
  * @param base the character buffer
  * @param size the size in bytes of the character buffer
  * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object. 
+ * @return the newly allocated buffer state object.
  */
 YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-    
+
         if ( size < 2 ||
              base[size-2] != YY_END_OF_BUFFER_CHAR ||
              base[size-1] != YY_END_OF_BUFFER_CHAR )
@@ -1966,7 +1968,7 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer  (char * base, yy_size_t  size ,
  */
 YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
 {
-    
+
         return cmDependsFortran_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
 }
 
@@ -1983,7 +1985,7 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * bytes, int  len
         char *buf;
         yy_size_t n;
         int i;
-    
+
         /* Get memory for full buffer, including space for trailing EOB's. */
         n = len + 2;
         buf = (char *) cmDependsFortran_yyalloc(n ,yyscanner );
@@ -2051,10 +2053,10 @@ YY_EXTRA_TYPE cmDependsFortran_yyget_extra  (yyscan_t yyscanner)
 int cmDependsFortran_yyget_lineno  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    
+
         if (! YY_CURRENT_BUFFER)
             return 0;
-    
+
     return yylineno;
 }
 
@@ -2064,10 +2066,10 @@ int cmDependsFortran_yyget_lineno  (yyscan_t yyscanner)
 int cmDependsFortran_yyget_column  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    
+
         if (! YY_CURRENT_BUFFER)
             return 0;
-    
+
     return yycolumn;
 }
 
@@ -2128,8 +2130,8 @@ void cmDependsFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner);
+
     yylineno = line_number;
 }
 
@@ -2143,8 +2145,8 @@ void cmDependsFortran_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner);
+
     yycolumn = column_no;
 }
 