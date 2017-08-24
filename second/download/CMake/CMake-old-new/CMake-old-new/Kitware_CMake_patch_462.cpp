@@ -48,7 +48,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t; 
+typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 #endif /* ! C99 */
@@ -169,7 +169,7 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
-    
+
 /* Return all but the first "n" matched characters back to the input stream. */
 #define yyless(n) \
   do \
@@ -234,7 +234,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-    
+
   /* Whether to try to fill the input buffer when we reach the
    * end of it.
    */
@@ -1428,9 +1428,9 @@ YY_RULE_SETUP
 case 107:
 YY_RULE_SETUP
 #line 200 "cmDependsJavaLexer.in.l"
-{ 
-  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
-  return jp_NAME; 
+{
+  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
+  return jp_NAME;
 }
 case 108:
 /* rule 108 can match eol */
@@ -1447,11 +1447,11 @@ YY_RULE_SETUP
 case 110:
 YY_RULE_SETUP
 #line 207 "cmDependsJavaLexer.in.l"
-{ 
-  std::cerr << "Unknown character: " << yytext[0] 
-    << " (" << (int)yytext[0] << ")" << std::endl; 
-  yyextra->Error("Unknown character"); 
-  return jp_ERROR; 
+{
+  std::cerr << "Unknown character: " << yytext[0]
+    << " (" << (int)yytext[0] << ")" << std::endl;
+  yyextra->Error("Unknown character");
+  return jp_ERROR;
 }
 case 111:
 YY_RULE_SETUP
@@ -1933,7 +1933,7 @@ static void cmDependsJava_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmDependsJava_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
   YY_BUFFER_STATE b;
-    
+
   b = (YY_BUFFER_STATE) cmDependsJava_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
   if ( ! b )
     YY_FATAL_ERROR( "out of dynamic memory in cmDependsJava_yy_create_buffer()" );
@@ -1977,7 +1977,7 @@ static void cmDependsJava_yy_load_buffer_state  (yyscan_t yyscanner)
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-    
+
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmDependsJava_yyrestart() or at EOF.
@@ -2003,7 +2003,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-    
+
   errno = oerrno;
 }
 
@@ -2107,9 +2107,9 @@ static void cmDependsJava_yyensure_buffer_stack (yyscan_t yyscanner)
     yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsJava_yyalloc
                 (nuto_alloc * sizeof(struct yy_buffer_state*)
                 , yyscanner);
-    
+
     memset(yyg->yy_buffer_stack, 0, nuto_alloc * sizeof(struct yy_buffer_state*));
-        
+
     yyg->yy_buffer_stack_max = nuto_alloc;
     yyg->yy_buffer_stack_top = 0;
     return;
@@ -2136,12 +2136,12 @@ static void cmDependsJava_yyensure_buffer_stack (yyscan_t yyscanner)
  * @param base the character buffer
  * @param size the size in bytes of the character buffer
  * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object. 
+ * @return the newly allocated buffer state object.
  */
 YY_BUFFER_STATE cmDependsJava_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
   YY_BUFFER_STATE b;
-    
+
   if ( size < 2 ||
        base[size-2] != YY_END_OF_BUFFER_CHAR ||
        base[size-1] != YY_END_OF_BUFFER_CHAR )
@@ -2177,7 +2177,7 @@ YY_BUFFER_STATE cmDependsJava_yy_scan_buffer  (char * base, yy_size_t  size , yy
  */
 YY_BUFFER_STATE cmDependsJava_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
 {
-    
+
   return cmDependsJava_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
 }
 
@@ -2194,7 +2194,7 @@ YY_BUFFER_STATE cmDependsJava_yy_scan_bytes  (yyconst char * bytes, int  len , y
   char *buf;
   yy_size_t n;
   int i;
-    
+
   /* Get memory for full buffer, including space for trailing EOB's. */
   n = len + 2;
   buf = (char *) cmDependsJava_yyalloc(n ,yyscanner );
@@ -2262,10 +2262,10 @@ YY_EXTRA_TYPE cmDependsJava_yyget_extra  (yyscan_t yyscanner)
 int cmDependsJava_yyget_lineno  (yyscan_t yyscanner)
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
 
@@ -2275,10 +2275,10 @@ int cmDependsJava_yyget_lineno  (yyscan_t yyscanner)
 int cmDependsJava_yyget_column  (yyscan_t yyscanner)
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
 
@@ -2339,8 +2339,8 @@ void cmDependsJava_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsJava_yyset_lineno called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmDependsJava_yyset_lineno called with no buffer" , yyscanner);
+
     yylineno = line_number;
 }
 
@@ -2354,8 +2354,8 @@ void cmDependsJava_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsJava_yyset_column called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmDependsJava_yyset_column called with no buffer" , yyscanner);
+
     yycolumn = column_no;
 }
 