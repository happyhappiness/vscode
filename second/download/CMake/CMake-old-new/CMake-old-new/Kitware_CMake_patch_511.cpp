@@ -605,8 +605,6 @@ extern int cmCommandArgument_yywrap (yyscan_t yyscanner );
 #endif
 #endif
 
-    static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
-    
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -729,10 +727,10 @@ YY_DECL
         register int yy_act;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-#line 63 "cmCommandArgumentLexer.in.l"
+#line 64 "cmCommandArgumentLexer.in.l"
 
 
-#line 734 "cmCommandArgumentLexer.cxx"
+#line 732 "cmCommandArgumentLexer.cxx"
 
         if ( !yyg->yy_init )
                 {
@@ -817,31 +815,31 @@ YY_DECL
 
 case 1:
 YY_RULE_SETUP
-#line 65 "cmCommandArgumentLexer.in.l"
-{ 
+#line 66 "cmCommandArgumentLexer.in.l"
+{
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
-  yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2); 
-  return cal_ENVCURLY; 
-} 
+  yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2);
+  return cal_ENVCURLY;
+}
 case 2:
 YY_RULE_SETUP
-#line 71 "cmCommandArgumentLexer.in.l"
+#line 72 "cmCommandArgumentLexer.in.l"
 { 
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2); 
   return cal_NCURLY; 
 } 
 case 3:
 YY_RULE_SETUP
-#line 77 "cmCommandArgumentLexer.in.l"
+#line 78 "cmCommandArgumentLexer.in.l"
 { 
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   yyextra->AllocateParserType(yylvalp, yytext+1, strlen(yytext)-2); 
   return cal_ATNAME; 
 } 
 case 4:
 YY_RULE_SETUP
-#line 83 "cmCommandArgumentLexer.in.l"
+#line 84 "cmCommandArgumentLexer.in.l"
 {
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
@@ -850,7 +848,7 @@ YY_RULE_SETUP
 }
 case 5:
 YY_RULE_SETUP
-#line 90 "cmCommandArgumentLexer.in.l"
+#line 91 "cmCommandArgumentLexer.in.l"
 {
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
@@ -859,7 +857,7 @@ YY_RULE_SETUP
 }
 case 6:
 YY_RULE_SETUP
-#line 97 "cmCommandArgumentLexer.in.l"
+#line 98 "cmCommandArgumentLexer.in.l"
 {
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
@@ -868,15 +866,15 @@ YY_RULE_SETUP
 }
 case 7:
 YY_RULE_SETUP
-#line 104 "cmCommandArgumentLexer.in.l"
+#line 105 "cmCommandArgumentLexer.in.l"
 { 
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
   return cal_NAME; 
 }
 case 8:
 YY_RULE_SETUP
-#line 110 "cmCommandArgumentLexer.in.l"
+#line 111 "cmCommandArgumentLexer.in.l"
 {
   if ( !yyextra->HandleEscapeSymbol(yylvalp, *(yytext+1)) )
     {
@@ -887,50 +885,50 @@ YY_RULE_SETUP
 case 9:
 /* rule 9 can match eol */
 YY_RULE_SETUP
-#line 118 "cmCommandArgumentLexer.in.l"
+#line 119 "cmCommandArgumentLexer.in.l"
 { 
   //std::cerr << __LINE__ << " here: [" << yytext << "]" << std::endl;
   yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
   return cal_SYMBOL; 
 }
 case 10:
 YY_RULE_SETUP
-#line 124 "cmCommandArgumentLexer.in.l"
+#line 125 "cmCommandArgumentLexer.in.l"
 {
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
   yylvalp->str = yyextra->DOLLARVariable;
   return cal_DOLLAR; 
 }
 case 11:
 YY_RULE_SETUP
-#line 130 "cmCommandArgumentLexer.in.l"
+#line 131 "cmCommandArgumentLexer.in.l"
 {
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
   yylvalp->str = yyextra->LCURLYVariable;
   return cal_LCURLY; 
 }
 case 12:
 YY_RULE_SETUP
-#line 136 "cmCommandArgumentLexer.in.l"
+#line 137 "cmCommandArgumentLexer.in.l"
 {
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext)); 
   yylvalp->str = yyextra->BSLASHVariable;
   return cal_BSLASH; 
 }
 case 13:
 YY_RULE_SETUP
-#line 142 "cmCommandArgumentLexer.in.l"
+#line 143 "cmCommandArgumentLexer.in.l"
 {
   //yyextra->AllocateParserType(yylvalp, yytext, strlen(yytext));
   yylvalp->str = yyextra->BSLASHVariable;
   return cal_SYMBOL;
 }
 case 14:
 YY_RULE_SETUP
-#line 148 "cmCommandArgumentLexer.in.l"
+#line 149 "cmCommandArgumentLexer.in.l"
 ECHO;
         YY_BREAK
-#line 945 "cmCommandArgumentLexer.cxx"
+#line 943 "cmCommandArgumentLexer.cxx"
 case YY_STATE_EOF(INITIAL):
 case YY_STATE_EOF(ESCAPES):
 case YY_STATE_EOF(NOESCAPES):
@@ -1264,44 +1262,6 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         return yy_is_jam ? 0 : yy_current_state;
 }
 
-    static void yyunput (int c, register char * yy_bp , yyscan_t yyscanner)
-{
-        register char *yy_cp;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-
-    yy_cp = yyg->yy_c_buf_p;
-
-        /* undo effects of setting up yytext */
-        *yy_cp = yyg->yy_hold_char;
-
-        if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
-                { /* need to shift things up to make room */
-                /* +2 for EOB chars. */
-                register int number_to_move = yyg->yy_n_chars + 2;
-                register char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
-                                        YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
-                register char *source =
-                                &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];
-
-                while ( source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
-                        *--dest = *--source;
-
-                yy_cp += (int) (dest - source);
-                yy_bp += (int) (dest - source);
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars =
-                        yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_buf_size;
-
-                if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
-                        YY_FATAL_ERROR( "flex scanner push-back overflow" );
-                }
-
-        *--yy_cp = (char) c;
-
-        yyg->yytext_ptr = yy_bp;
-        yyg->yy_hold_char = *yy_cp;
-        yyg->yy_c_buf_p = yy_cp;
-}
-
 #ifndef YY_NO_INPUT
 #ifdef __cplusplus
     static int yyinput (yyscan_t yyscanner)
@@ -2087,7 +2047,7 @@ void cmCommandArgument_yyfree (void * ptr , yyscan_t)
 
 #define YYTABLES_NAME "yytables"
 
-#line 148 "cmCommandArgumentLexer.in.l"
+#line 149 "cmCommandArgumentLexer.in.l"
 
 
 