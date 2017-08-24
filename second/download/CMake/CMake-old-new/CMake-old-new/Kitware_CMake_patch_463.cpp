@@ -44,7 +44,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t; 
+typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 #endif /* ! C99 */
@@ -165,7 +165,7 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
-    
+
 /* Return all but the first "n" matched characters back to the input
    stream. */
 #define yyless(n) \
@@ -231,7 +231,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-    
+
   /* Whether to try to fill the input buffer when we reach the
    * end of it.
    */
@@ -787,51 +787,51 @@ YY_DECL
 case 1:
 YY_RULE_SETUP
 #line 88 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ yylvalp->Number = atoi(yytext); return exp_NUMBER; } 
+{ yylvalp->Number = atoi(yytext); return exp_NUMBER; }
 case 2:
 YY_RULE_SETUP
 #line 90 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
 { return exp_PLUS; }
 case 3:
 YY_RULE_SETUP
 #line 91 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_MINUS; } 
+{ return exp_MINUS; }
 case 4:
 YY_RULE_SETUP
 #line 92 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_TIMES; } 
+{ return exp_TIMES; }
 case 5:
 YY_RULE_SETUP
 #line 93 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_DIVIDE; } 
+{ return exp_DIVIDE; }
 case 6:
 YY_RULE_SETUP
 #line 94 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_MOD; } 
+{ return exp_MOD; }
 case 7:
 YY_RULE_SETUP
 #line 95 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_OR; } 
+{ return exp_OR; }
 case 8:
 YY_RULE_SETUP
 #line 96 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_AND; } 
+{ return exp_AND; }
 case 9:
 YY_RULE_SETUP
 #line 97 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_XOR; } 
+{ return exp_XOR; }
 case 10:
 YY_RULE_SETUP
 #line 98 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_NOT; } 
+{ return exp_NOT; }
 case 11:
 YY_RULE_SETUP
 #line 99 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_SHIFTLEFT; } 
+{ return exp_SHIFTLEFT; }
 case 12:
 YY_RULE_SETUP
 #line 100 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
-{ return exp_SHIFTRIGHT; } 
+{ return exp_SHIFTRIGHT; }
 case 13:
 YY_RULE_SETUP
 #line 101 "/home/andy/vtk/CMake/Source/cmExprLexer.in.l"
@@ -1319,7 +1319,7 @@ static void cmExpr_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmExpr_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
   YY_BUFFER_STATE b;
-    
+
   b = (YY_BUFFER_STATE) cmExpr_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
   if ( ! b )
     YY_FATAL_ERROR( "out of dynamic memory in cmExpr_yy_create_buffer()" );
@@ -1363,7 +1363,7 @@ static void cmExpr_yy_load_buffer_state  (yyscan_t yyscanner)
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-    
+
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmExpr_yyrestart() or at EOF.
@@ -1389,7 +1389,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-    
+
   errno = oerrno;
 }
 
@@ -1493,9 +1493,9 @@ static void cmExpr_yyensure_buffer_stack (yyscan_t yyscanner)
     yyg->yy_buffer_stack = (struct yy_buffer_state**)cmExpr_yyalloc
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
@@ -1522,12 +1522,12 @@ static void cmExpr_yyensure_buffer_stack (yyscan_t yyscanner)
  * @param base the character buffer
  * @param size the size in bytes of the character buffer
  * @param yyscanner The scanner object.
- * @return the newly allocated buffer state object. 
+ * @return the newly allocated buffer state object.
  */
 YY_BUFFER_STATE cmExpr_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
   YY_BUFFER_STATE b;
-    
+
   if ( size < 2 ||
        base[size-2] != YY_END_OF_BUFFER_CHAR ||
        base[size-1] != YY_END_OF_BUFFER_CHAR )
@@ -1564,7 +1564,7 @@ YY_BUFFER_STATE cmExpr_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t
  */
 YY_BUFFER_STATE cmExpr_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
 {
-    
+
   return cmExpr_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
 }
 
@@ -1581,7 +1581,7 @@ YY_BUFFER_STATE cmExpr_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t
   char *buf;
   yy_size_t n;
   int i;
-    
+
   /* Get memory for full buffer, including space for trailing EOB's. */
   n = len + 2;
   buf = (char *) cmExpr_yyalloc(n ,yyscanner );
@@ -1649,10 +1649,10 @@ YY_EXTRA_TYPE cmExpr_yyget_extra  (yyscan_t yyscanner)
 int cmExpr_yyget_lineno  (yyscan_t yyscanner)
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
 
@@ -1662,10 +1662,10 @@ int cmExpr_yyget_lineno  (yyscan_t yyscanner)
 int cmExpr_yyget_column  (yyscan_t yyscanner)
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
 
@@ -1726,8 +1726,8 @@ void cmExpr_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmExpr_yyset_lineno called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmExpr_yyset_lineno called with no buffer" , yyscanner);
+
     yylineno = line_number;
 }
 
@@ -1741,8 +1741,8 @@ void cmExpr_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmExpr_yyset_column called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmExpr_yyset_column called with no buffer" , yyscanner);
+
     yycolumn = column_no;
 }
 