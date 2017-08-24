@@ -47,7 +47,7 @@
 #if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
 
 /* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
- * if you want the limit (max/min) macros for int types. 
+ * if you want the limit (max/min) macros for int types.
  */
 #ifndef __STDC_LIMIT_MACROS
 #define __STDC_LIMIT_MACROS 1
@@ -64,7 +64,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t; 
+typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 
@@ -189,7 +189,7 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
-    
+
 /* Return all but the first "n" matched characters back to the input stream. */
 #define yyless(n) \
         do \
@@ -251,7 +251,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-    
+
         /* Whether to try to fill the input buffer when we reach the
          * end of it.
          */
@@ -832,25 +832,25 @@ YY_RULE_SETUP
 case 2:
 YY_RULE_SETUP
 #line 72 "cmCommandArgumentLexer.in.l"
-{ 
+{
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2); 
-  return cal_NCURLY; 
-} 
+  yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2);
+  return cal_NCURLY;
+}
 case 3:
 YY_RULE_SETUP
 #line 78 "cmCommandArgumentLexer.in.l"
-{ 
+{
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2); 
-  return cal_ATNAME; 
-} 
+  yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2);
+  return cal_ATNAME;
+}
 case 4:
 YY_RULE_SETUP
 #line 84 "cmCommandArgumentLexer.in.l"
 {
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
+  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->DCURLYVariable;
   return cal_DCURLY;
 }
@@ -859,7 +859,7 @@ YY_RULE_SETUP
 #line 91 "cmCommandArgumentLexer.in.l"
 {
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
+  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->RCURLYVariable;
   return cal_RCURLY;
 }
@@ -868,17 +868,17 @@ YY_RULE_SETUP
 #line 98 "cmCommandArgumentLexer.in.l"
 {
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
+  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->ATVariable;
   return cal_AT;
 }
 case 7:
 YY_RULE_SETUP
 #line 105 "cmCommandArgumentLexer.in.l"
-{ 
+{
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
-  return cal_NAME; 
+  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
+  return cal_NAME;
 }
 case 8:
 YY_RULE_SETUP
@@ -888,40 +888,40 @@ YY_RULE_SETUP
     {
     return cal_ERROR;
     }
-  return cal_SYMBOL; 
+  return cal_SYMBOL;
 }
 case 9:
 /* rule 9 can match eol */
 YY_RULE_SETUP
 #line 119 "cmCommandArgumentLexer.in.l"
-{ 
+{
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
-  return cal_SYMBOL; 
+  yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
+  return cal_SYMBOL;
 }
 case 10:
 YY_RULE_SETUP
 #line 125 "cmCommandArgumentLexer.in.l"
 {
-  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
+  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->DOLLARVariable;
-  return cal_DOLLAR; 
+  return cal_DOLLAR;
 }
 case 11:
 YY_RULE_SETUP
 #line 131 "cmCommandArgumentLexer.in.l"
 {
-  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
+  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->LCURLYVariable;
-  return cal_LCURLY; 
+  return cal_LCURLY;
 }
 case 12:
 YY_RULE_SETUP
 #line 137 "cmCommandArgumentLexer.in.l"
 {
-  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
+  //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->BSLASHVariable;
-  return cal_BSLASH; 
+  return cal_BSLASH;
 }
 case 13:
 YY_RULE_SETUP
@@ -1419,7 +1419,7 @@ static void cmCommandArgument_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmCommandArgument_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-    
+
         b = (YY_BUFFER_STATE) cmCommandArgument_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
                 YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yy_create_buffer()" );
@@ -1463,7 +1463,7 @@ static void cmCommandArgument_yy_load_buffer_state  (yyscan_t yyscanner)
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-    
+
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmCommandArgument_yyrestart() or at EOF.
@@ -1489,7 +1489,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-    
+
         errno = oerrno;
 }
 
@@ -1595,9 +1595,9 @@ static void cmCommandArgument_yyensure_buffer_stack (yyscan_t yyscanner)
                                                                 , yyscanner);
                 if ( ! yyg->yy_buffer_stack )
                         YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yyensure_buffer_stack()" );
-                                                                  
+
                 memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
-                                
+
                 yyg->yy_buffer_stack_max = num_to_alloc;
                 yyg->yy_buffer_stack_top = 0;
                 return;
@@ -1626,12 +1626,12 @@ static void cmCommandArgument_yyensure_buffer_stack (yyscan_t yyscanner)
  * @param base the character buffer
  * @param size the size in bytes of the character buffer
  * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object. 
+ * @return the newly allocated buffer state object.
  */
 YY_BUFFER_STATE cmCommandArgument_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-    
+
         if ( size < 2 ||
              base[size-2] != YY_END_OF_BUFFER_CHAR ||
              base[size-1] != YY_END_OF_BUFFER_CHAR )
@@ -1667,7 +1667,7 @@ YY_BUFFER_STATE cmCommandArgument_yy_scan_buffer  (char * base, yy_size_t  size
  */
 YY_BUFFER_STATE cmCommandArgument_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)
 {
-    
+
         return cmCommandArgument_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
 }
 
@@ -1684,7 +1684,7 @@ YY_BUFFER_STATE cmCommandArgument_yy_scan_bytes  (yyconst char * yybytes, int  _
         char *buf;
         yy_size_t n;
         int i;
-    
+
         /* Get memory for full buffer, including space for trailing EOB's. */
         n = _yybytes_len + 2;
         buf = (char *) cmCommandArgument_yyalloc(n ,yyscanner );
@@ -1752,10 +1752,10 @@ YY_EXTRA_TYPE cmCommandArgument_yyget_extra  (yyscan_t yyscanner)
 int cmCommandArgument_yyget_lineno  (yyscan_t yyscanner)
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
 
@@ -1765,10 +1765,10 @@ int cmCommandArgument_yyget_lineno  (yyscan_t yyscanner)
 int cmCommandArgument_yyget_column  (yyscan_t yyscanner)
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
 
@@ -1829,8 +1829,8 @@ void cmCommandArgument_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmCommandArgument_yyset_lineno called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmCommandArgument_yyset_lineno called with no buffer" , yyscanner);
+
     yylineno = line_number;
 }
 
@@ -1844,8 +1844,8 @@ void cmCommandArgument_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmCommandArgument_yyset_column called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmCommandArgument_yyset_column called with no buffer" , yyscanner);
+
     yycolumn = column_no;
 }
 
@@ -1928,20 +1928,20 @@ int cmCommandArgument_yylex_init_extra(YY_EXTRA_TYPE yy_user_defined,yyscan_t* p
         errno = EINVAL;
         return 1;
     }
-        
+
     *ptr_yy_globals = (yyscan_t) cmCommandArgument_yyalloc ( sizeof( struct yyguts_t ), &dummy_yyguts );
-        
+
     if (*ptr_yy_globals == NULL){
         errno = ENOMEM;
         return 1;
     }
-    
+
     /* By setting to 0xAA, we expose bugs in
     yy_init_globals. Leave at 0x00 for releases. */
     memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));
-    
+
     cmCommandArgument_yyset_extra (yy_user_defined, *ptr_yy_globals);
-    
+
     return yy_init_globals ( *ptr_yy_globals );
 }
 