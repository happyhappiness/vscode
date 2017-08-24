@@ -9,7 +9,7 @@
 #define FLEX_SCANNER
 #define YY_FLEX_MAJOR_VERSION 2
 #define YY_FLEX_MINOR_VERSION 5
-#define YY_FLEX_SUBMINOR_VERSION 31
+#define YY_FLEX_SUBMINOR_VERSION 35
 #if YY_FLEX_SUBMINOR_VERSION > 0
 #define FLEX_BETA
 #endif
@@ -31,7 +31,15 @@
 
 /* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */
 
-#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
+#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
+
+/* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
+ * if you want the limit (max/min) macros for int types.
+ */
+#ifndef __STDC_LIMIT_MACROS
+#define __STDC_LIMIT_MACROS 1
+#endif
+
 #include <inttypes.h>
 typedef int8_t flex_int8_t;
 typedef uint8_t flex_uint8_t;
@@ -46,7 +54,6 @@ typedef int flex_int32_t;
 typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
-#endif /* ! C99 */
 
 /* Limits of integral types. */
 #ifndef INT8_MIN
@@ -77,6 +84,8 @@ typedef unsigned int flex_uint32_t;
 #define UINT32_MAX             (4294967295U)
 #endif
 
+#endif /* ! C99 */
+
 #endif /* ! FLEXINT_H */
 
 #ifdef __cplusplus
@@ -86,11 +95,12 @@ typedef unsigned int flex_uint32_t;
 
 #else   /* ! __cplusplus */
 
-#if __STDC__
+/* C99 requires __STDC__ to be defined as 1. */
+#if defined (__STDC__)
 
 #define YY_USE_CONST
 
-#endif  /* __STDC__ */
+#endif  /* defined (__STDC__) */
 #endif  /* ! __cplusplus */
 
 #ifdef YY_USE_CONST
@@ -126,8 +136,6 @@ typedef void* yyscan_t;
 #define yycolumn (YY_CURRENT_BUFFER_LVALUE->yy_bs_column)
 #define yy_flex_debug yyg->yy_flex_debug_r
 
-int cmListFileLexer_yylex_init (yyscan_t* scanner);
-
 /* Enter a start condition.  This macro really ought to take a parameter,
  * but we do it the disgusting crufty way forced on us by the ()-less
  * definition of BEGIN.
@@ -151,9 +159,21 @@ int cmListFileLexer_yylex_init (yyscan_t* scanner);
 
 /* Size of default input buffer. */
 #ifndef YY_BUF_SIZE
+#ifdef __ia64__
+/* On IA-64, the buffer size is 16k, not 8k.
+ * Moreover, YY_BUF_SIZE is 2*YY_READ_BUF_SIZE in the general case.
+ * Ditto for the __ia64__ case accordingly.
+ */
+#define YY_BUF_SIZE 32768
+#else
 #define YY_BUF_SIZE 16384
+#endif /* __ia64__ */
 #endif
 
+/* The state buf must be large enough to hold one state per character in the main buffer.
+ */
+#define YY_STATE_BUF_SIZE   ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))
+
 #ifndef YY_TYPEDEF_YY_BUFFER_STATE
 #define YY_TYPEDEF_YY_BUFFER_STATE
 typedef struct yy_buffer_state *YY_BUFFER_STATE;
@@ -192,14 +212,9 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
                 } \
         while ( 0 )
 
-/* The following is because we cannot portably get our hands on size_t
- * (without autoconf's help, which isn't available because we want
- * flex-generated scanners to compile on their own).
- */
-
 #ifndef YY_TYPEDEF_YY_SIZE_T
 #define YY_TYPEDEF_YY_SIZE_T
-typedef unsigned int yy_size_t;
+typedef size_t yy_size_t;
 #endif
 
 #ifndef YY_STRUCT_YY_BUFFER_STATE
@@ -354,21 +369,21 @@ static void yy_fatal_error (yyconst char msg[] ,yyscan_t yyscanner );
         *yy_cp = '\0'; \
         yyg->yy_c_buf_p = yy_cp;
 
-#define YY_NUM_RULES 14
-#define YY_END_OF_BUFFER 15
+#define YY_NUM_RULES 15
+#define YY_END_OF_BUFFER 16
 /* This struct is not used in this scanner,
    but its presence is necessary. */
 struct yy_trans_info
         {
         flex_int32_t yy_verify;
         flex_int32_t yy_nxt;
         };
-static yyconst flex_int16_t yy_accept[39] =
+static yyconst flex_int16_t yy_accept[40] =
     {   0,
-        0,    0,    0,    0,   15,    6,   12,    1,    7,    2,
-        6,    3,    4,    6,   13,    8,    9,   10,   11,    6,
-        0,    6,    0,    2,    0,    5,    6,    8,    0,    0,
-        0,    0,    0,    0,    0,    0,    0,    0
+        0,    0,    0,    0,   16,    6,   13,    1,    7,    2,
+        6,    3,    4,    6,   14,    8,   10,   11,   12,    6,
+        0,    6,    0,    2,    0,    5,    6,    8,    0,    9,
+        0,    0,    0,    0,    0,    0,    0,    0,    0
     } ;
 
 static yyconst flex_int32_t yy_ec[256] =
@@ -409,60 +424,58 @@ static yyconst flex_int32_t yy_meta[13] =
         4,    1
     } ;
 
-static yyconst flex_int16_t yy_base[48] =
+static yyconst flex_int16_t yy_base[49] =
     {   0,
-        0,    0,   10,   20,   34,   32,   89,   89,   89,    0,
-       23,   89,   89,   35,    0,   18,   89,   89,   44,    0,
-       49,   21,    0,    0,   19,    0,    0,   15,   59,    0,
-       18,    0,   15,   12,   11,   10,    9,   89,   64,   68,
-       72,   76,   80,   13,   84,   12,   10
+        0,    0,   10,   20,   35,   32,   86,   86,   86,    0,
+       26,   86,   86,   35,    0,   19,   86,   86,   44,    0,
+       49,   22,    0,    0,   20,    0,    0,   16,   22,   86,
+        0,   18,    0,   15,   12,   11,   10,    9,   86,   61,
+       65,   69,   73,   77,   13,   81,   12,   10
     } ;
 
-static yyconst flex_int16_t yy_def[48] =
+static yyconst flex_int16_t yy_def[49] =
     {   0,
-       38,    1,   39,   39,   38,   38,   38,   38,   38,   40,
-        6,   38,   38,    6,   41,   42,   38,   38,   42,    6,
-       38,    6,   43,   40,   44,   14,    6,   42,   42,   21,
-       21,   45,   46,   44,   47,   46,   47,    0,   38,   38,
-       38,   38,   38,   38,   38,   38,   38
+       39,    1,   40,   40,   39,   39,   39,   39,   39,   41,
+        6,   39,   39,    6,   42,   43,   39,   39,   43,    6,
+       39,    6,   44,   41,   45,   14,    6,   43,   43,   39,
+       21,   21,   46,   47,   45,   48,   47,   48,    0,   39,
+       39,   39,   39,   39,   39,   39,   39,   39
     } ;
 
-static yyconst flex_int16_t yy_nxt[102] =
+static yyconst flex_int16_t yy_nxt[99] =
     {   0,
         6,    7,    8,    7,    9,   10,   11,   12,   13,    6,
-       14,   15,   17,   37,   18,   36,   34,   30,   20,   30,
-       27,   19,   17,   20,   18,   35,   29,   27,   33,   29,
-       25,   19,   20,   38,   38,   38,   21,   38,   22,   38,
-       38,   20,   20,   23,   26,   26,   28,   38,   28,   30,
-       30,   38,   38,   20,   38,   31,   38,   38,   30,   30,
-       32,   28,   38,   28,   16,   16,   16,   16,   24,   38,
-       24,   24,   27,   38,   27,   27,   28,   38,   38,   28,
-       20,   38,   20,   20,   30,   38,   30,   30,    5,   38,
-       38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
-
-       38
+       14,   15,   17,   38,   18,   37,   35,   31,   20,   31,
+       27,   19,   17,   20,   18,   36,   28,   29,   27,   34,
+       29,   19,   20,   25,   39,   39,   21,   39,   22,   39,
+       39,   20,   20,   23,   26,   26,   30,   39,   28,   31,
+       31,   39,   39,   20,   39,   32,   39,   39,   31,   31,
+       33,   16,   16,   16,   16,   24,   39,   24,   24,   27,
+       39,   27,   27,   28,   39,   39,   28,   20,   39,   20,
+       20,   31,   39,   31,   31,    5,   39,   39,   39,   39,
+       39,   39,   39,   39,   39,   39,   39,   39
+
     } ;
 
-static yyconst flex_int16_t yy_chk[102] =
+static yyconst flex_int16_t yy_chk[99] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
-        1,    1,    3,   47,    3,   46,   44,   37,   36,   35,
-       34,    3,    4,   33,    4,   31,   28,   25,   22,   16,
-       11,    4,    6,    5,    0,    0,    6,    0,    6,    0,
+        1,    1,    3,   48,    3,   47,   45,   38,   37,   36,
+       35,    3,    4,   34,    4,   32,   29,   28,   25,   22,
+       16,    4,    6,   11,    5,    0,    6,    0,    6,    0,
         0,    6,    6,    6,   14,   14,   19,    0,   19,   21,
        21,    0,    0,   21,    0,   21,    0,    0,   21,   21,
-       21,   29,    0,   29,   39,   39,   39,   39,   40,    0,
-       40,   40,   41,    0,   41,   41,   42,    0,    0,   42,
-       43,    0,   43,   43,   45,    0,   45,   45,   38,   38,
-       38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
+       21,   40,   40,   40,   40,   41,    0,   41,   41,   42,
+        0,   42,   42,   43,    0,    0,   43,   44,    0,   44,
+       44,   46,    0,   46,   46,   39,   39,   39,   39,   39,
+       39,   39,   39,   39,   39,   39,   39,   39
 
-       38
     } ;
 
 /* Table of booleans, true if rule could match eol. */
-static yyconst flex_int32_t yy_rule_can_match_eol[15] =
+static yyconst flex_int32_t yy_rule_can_match_eol[16] =
     {   0,
-1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,     };
+1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,     };
 
 /* The intent behind this definition is that it'll catch
  * any uses of REJECT which flex missed.
@@ -494,6 +507,7 @@ Run flex like this:
 
 Modify cmListFileLexer.c:
   - remove TABs
+  - remove use of the 'register' storage class specifier
   - remove the yyunput function
   - add a statement "(void)yyscanner;" to the top of these methods:
       yy_fatal_error, cmListFileLexer_yyalloc, cmListFileLexer_yyrealloc, cmListFileLexer_yyfree
@@ -540,7 +554,7 @@ static void cmListFileLexerDestroy(cmListFileLexer* lexer);
 
 /*--------------------------------------------------------------------------*/
 
-#line 568 "cmListFileLexer.c"
+#line 560 "cmListFileLexer.c"
 
 #define INITIAL 0
 #define STRING 1
@@ -591,6 +605,12 @@ struct yyguts_t
 
     }; /* end struct yyguts_t */
 
+static int yy_init_globals (yyscan_t yyscanner );
+
+int cmListFileLexer_yylex_init (yyscan_t* scanner);
+
+int cmListFileLexer_yylex_init_extra (YY_EXTRA_TYPE user_defined,yyscan_t* scanner);
+
 /* Accessor methods to globals.
    These are made visible to non-reentrant scanners for convenience. */
 
@@ -620,6 +640,10 @@ int cmListFileLexer_yyget_lineno (yyscan_t yyscanner );
 
 void cmListFileLexer_yyset_lineno (int line_number ,yyscan_t yyscanner );
 
+int cmListFileLexer_yyget_column  (yyscan_t yyscanner );
+
+void cmListFileLexer_yyset_column (int column_no ,yyscan_t yyscanner );
+
 /* Macros after this point can all be overridden by user definitions in
  * section 1.
  */
@@ -652,15 +676,20 @@ static int input (yyscan_t yyscanner );
 
 /* Amount of stuff to slurp up with each read. */
 #ifndef YY_READ_BUF_SIZE
+#ifdef __ia64__
+/* On IA-64, the buffer size is 16k, not 8k */
+#define YY_READ_BUF_SIZE 16384
+#else
 #define YY_READ_BUF_SIZE 8192
+#endif /* __ia64__ */
 #endif
 
 /* Copy whatever the last rule matched to the standard output. */
 #ifndef ECHO
 /* This used to be an fputs(), but since the string might contain NUL's,
  * we now use fwrite().
  */
-#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
+#define ECHO do { if (fwrite( yytext, yyleng, 1, yyout )) {} } while (0)
 #endif
 
 /* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
@@ -754,14 +783,14 @@ YY_DECL
         int yy_act;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-#line 100 "cmListFileLexer.in.l"
+#line 79 "cmListFileLexer.in.l"
 
 
-#line 787 "cmListFileLexer.c"
+#line 794 "cmListFileLexer.c"
 
-        if ( yyg->yy_init )
+        if ( !yyg->yy_init )
                 {
-                yyg->yy_init = 0;
+                yyg->yy_init = 1;
 
 #ifdef YY_USER_INIT
                 YY_USER_INIT;
@@ -810,13 +839,13 @@ YY_DECL
                         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                                 {
                                 yy_current_state = (int) yy_def[yy_current_state];
-                                if ( yy_current_state >= 39 )
+                                if ( yy_current_state >= 40 )
                                         yy_c = yy_meta[(unsigned int) yy_c];
                                 }
                         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
                         ++yy_cp;
                         }
-                while ( yy_base[yy_current_state] != 89 );
+                while ( yy_base[yy_current_state] != 86 );
 
 yy_find_action:
                 yy_act = yy_accept[yy_current_state];
@@ -855,7 +884,7 @@ YY_DECL
 case 1:
 /* rule 1 can match eol */
 YY_RULE_SETUP
-#line 102 "cmListFileLexer.in.l"
+#line 81 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_Newline;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -865,14 +894,14 @@ YY_RULE_SETUP
 }
 case 2:
 YY_RULE_SETUP
-#line 110 "cmListFileLexer.in.l"
+#line 89 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
 }
         YY_BREAK
 case 3:
 YY_RULE_SETUP
-#line 114 "cmListFileLexer.in.l"
+#line 93 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ParenLeft;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -881,7 +910,7 @@ YY_RULE_SETUP
 }
 case 4:
 YY_RULE_SETUP
-#line 121 "cmListFileLexer.in.l"
+#line 100 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ParenRight;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -890,7 +919,7 @@ YY_RULE_SETUP
 }
 case 5:
 YY_RULE_SETUP
-#line 128 "cmListFileLexer.in.l"
+#line 107 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_Identifier;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -899,7 +928,7 @@ YY_RULE_SETUP
 }
 case 6:
 YY_RULE_SETUP
-#line 135 "cmListFileLexer.in.l"
+#line 114 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -908,7 +937,7 @@ YY_RULE_SETUP
 }
 case 7:
 YY_RULE_SETUP
-#line 142 "cmListFileLexer.in.l"
+#line 121 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ArgumentQuoted;
   cmListFileLexerSetToken(lexer, "", 0);
@@ -917,9 +946,8 @@ YY_RULE_SETUP
 }
         YY_BREAK
 case 8:
-/* rule 8 can match eol */
 YY_RULE_SETUP
-#line 149 "cmListFileLexer.in.l"
+#line 128 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   lexer->column += yyleng;
@@ -928,65 +956,75 @@ YY_RULE_SETUP
 case 9:
 /* rule 9 can match eol */
 YY_RULE_SETUP
-#line 154 "cmListFileLexer.in.l"
+#line 133 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   ++lexer->line;
   lexer->column = 1;
 }
         YY_BREAK
 case 10:
+/* rule 10 can match eol */
+YY_RULE_SETUP
+#line 139 "cmListFileLexer.in.l"
+{
+  cmListFileLexerAppend(lexer, yytext, yyleng);
+  ++lexer->line;
+  lexer->column = 1;
+}
+        YY_BREAK
+case 11:
 YY_RULE_SETUP
-#line 160 "cmListFileLexer.in.l"
+#line 145 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
   BEGIN(INITIAL);
   return 1;
 }
-case 11:
+case 12:
 YY_RULE_SETUP
-#line 166 "cmListFileLexer.in.l"
+#line 151 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   lexer->column += yyleng;
 }
         YY_BREAK
 case YY_STATE_EOF(STRING):
-#line 171 "cmListFileLexer.in.l"
+#line 156 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_BadString;
   BEGIN(INITIAL);
   return 1;
 }
-case 12:
+case 13:
 YY_RULE_SETUP
-#line 177 "cmListFileLexer.in.l"
+#line 162 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
 }
         YY_BREAK
-case 13:
+case 14:
 YY_RULE_SETUP
-#line 181 "cmListFileLexer.in.l"
+#line 166 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_BadCharacter;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
   lexer->column += yyleng;
   return 1;
 }
 case YY_STATE_EOF(INITIAL):
-#line 188 "cmListFileLexer.in.l"
+#line 173 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_None;
   cmListFileLexerSetToken(lexer, 0, 0);
   return 0;
 }
-case 14:
+case 15:
 YY_RULE_SETUP
-#line 194 "cmListFileLexer.in.l"
+#line 179 "cmListFileLexer.in.l"
 ECHO;
         YY_BREAK
-#line 1025 "cmListFileLexer.c"
+#line 1041 "cmListFileLexer.c"
 
         case YY_END_OF_BUFFER:
                 {
@@ -1171,7 +1209,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
         else
                 {
-                        size_t num_to_read =
+                        int num_to_read =
                         YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
 
                 while ( num_to_read <= 0 )
@@ -1216,7 +1254,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                 /* Read in more data. */
                 YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
-                        yyg->yy_n_chars, num_to_read );
+                        yyg->yy_n_chars, (size_t) num_to_read );
 
                 YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
                 }
@@ -1240,6 +1278,14 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         else
                 ret_val = EOB_ACT_CONTINUE_SCAN;
 
+        if ((yy_size_t) (yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
+                /* Extend the array by 50%, plus the number we really need. */
+                yy_size_t new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);
+                YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmListFileLexer_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );
+                if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
+                        YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
+        }
+
         yyg->yy_n_chars += number_to_move;
         YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
         YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
@@ -1270,7 +1316,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                 while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                         {
                         yy_current_state = (int) yy_def[yy_current_state];
-                        if ( yy_current_state >= 39 )
+                        if ( yy_current_state >= 40 )
                                 yy_c = yy_meta[(unsigned int) yy_c];
                         }
                 yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
@@ -1287,7 +1333,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
     static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state , yyscan_t yyscanner)
 {
         int yy_is_jam;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner; /* This var may be unused depending upon options. */
         char *yy_cp = yyg->yy_c_buf_p;
 
         YY_CHAR yy_c = 1;
@@ -1299,11 +1345,11 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                 {
                 yy_current_state = (int) yy_def[yy_current_state];
-                if ( yy_current_state >= 39 )
+                if ( yy_current_state >= 40 )
                         yy_c = yy_meta[(unsigned int) yy_c];
                 }
         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-        yy_is_jam = (yy_current_state == 38);
+        yy_is_jam = (yy_current_state == 39);
 
         return yy_is_jam ? 0 : yy_current_state;
 }
@@ -1633,6 +1679,8 @@ static void cmListFileLexer_yyensure_buffer_stack (yyscan_t yyscanner)
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyalloc
                                                                 (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
+                if ( ! yyg->yy_buffer_stack )
+                        YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );
 
                 memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
 
@@ -1651,6 +1699,8 @@ static void cmListFileLexer_yyensure_buffer_stack (yyscan_t yyscanner)
                                                                 (yyg->yy_buffer_stack,
                                                                 num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
+                if ( ! yyg->yy_buffer_stack )
+                        YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );
 
                 /* zero only the new slots.*/
                 memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
@@ -1695,42 +1745,42 @@ YY_BUFFER_STATE cmListFileLexer_yy_scan_buffer  (char * base, yy_size_t  size ,
 
 /** Setup the input buffer state to scan a string. The next call to cmListFileLexer_yylex() will
  * scan from a @e copy of @a str.
- * @param str a NUL-terminated string to scan
+ * @param yystr a NUL-terminated string to scan
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  * @note If you want to scan bytes that may contain NUL values, then use
  *       cmListFileLexer_yy_scan_bytes() instead.
  */
-YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
+YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)
 {
 
-        return cmListFileLexer_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
+        return cmListFileLexer_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
 }
 
 /** Setup the input buffer state to scan the given bytes. The next call to cmListFileLexer_yylex() will
  * scan from a @e copy of @a bytes.
- * @param bytes the byte buffer to scan
- * @param len the number of bytes in the buffer pointed to by @a bytes.
+ * @param yybytes the byte buffer to scan
+ * @param _yybytes_len the number of bytes in the buffer pointed to by @a bytes.
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  */
-YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
+YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * yybytes, int  _yybytes_len , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
         char *buf;
         yy_size_t n;
         int i;
 
         /* Get memory for full buffer, including space for trailing EOB's. */
-        n = len + 2;
+        n = _yybytes_len + 2;
         buf = (char *) cmListFileLexer_yyalloc(n ,yyscanner );
         if ( ! buf )
                 YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_bytes()" );
 
-        for ( i = 0; i < len; ++i )
-                buf[i] = bytes[i];
+        for ( i = 0; i < _yybytes_len; ++i )
+                buf[i] = yybytes[i];
 
-        buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;
+        buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
 
         b = cmListFileLexer_yy_scan_buffer(buf,n ,yyscanner);
         if ( ! b )
@@ -1918,21 +1968,87 @@ void cmListFileLexer_yyset_debug (int  bdebug , yyscan_t yyscanner)
 
 /* Accessor methods for yylval and yylloc */
 
+/* User-visible API */
+
+/* cmListFileLexer_yylex_init is special because it creates the scanner itself, so it is
+ * the ONLY reentrant function that doesn't take the scanner as the last argument.
+ * That's why we explicitly handle the declaration, instead of using our macros.
+ */
+
+int cmListFileLexer_yylex_init(yyscan_t* ptr_yy_globals)
+
+{
+    if (ptr_yy_globals == NULL){
+        errno = EINVAL;
+        return 1;
+    }
+
+    *ptr_yy_globals = (yyscan_t) cmListFileLexer_yyalloc ( sizeof( struct yyguts_t ), NULL );
+
+    if (*ptr_yy_globals == NULL){
+        errno = ENOMEM;
+        return 1;
+    }
+
+    /* By setting to 0xAA, we expose bugs in yy_init_globals. Leave at 0x00 for releases. */
+    memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));
+
+    return yy_init_globals ( *ptr_yy_globals );
+}
+
+/* cmListFileLexer_yylex_init_extra has the same functionality as cmListFileLexer_yylex_init, but follows the
+ * convention of taking the scanner as the last argument. Note however, that
+ * this is a *pointer* to a scanner, as it will be allocated by this call (and
+ * is the reason, too, why this function also must handle its own declaration).
+ * The user defined value in the first argument will be available to cmListFileLexer_yyalloc in
+ * the yyextra field.
+ */
+
+int cmListFileLexer_yylex_init_extra(YY_EXTRA_TYPE yy_user_defined,yyscan_t* ptr_yy_globals )
+
+{
+    struct yyguts_t dummy_yyguts;
+
+    cmListFileLexer_yyset_extra (yy_user_defined, &dummy_yyguts);
+
+    if (ptr_yy_globals == NULL){
+        errno = EINVAL;
+        return 1;
+    }
+
+    *ptr_yy_globals = (yyscan_t) cmListFileLexer_yyalloc ( sizeof( struct yyguts_t ), &dummy_yyguts );
+
+    if (*ptr_yy_globals == NULL){
+        errno = ENOMEM;
+        return 1;
+    }
+
+    /* By setting to 0xAA, we expose bugs in
+    yy_init_globals. Leave at 0x00 for releases. */
+    memset(*ptr_yy_globals,0x00,sizeof(struct yyguts_t));
+
+    cmListFileLexer_yyset_extra (yy_user_defined, *ptr_yy_globals);
+
+    return yy_init_globals ( *ptr_yy_globals );
+}
+
 static int yy_init_globals (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     /* Initialization is the same as for the non-reentrant scanner.
-       This function is called once per scanner lifetime. */
+     * This function is called from cmListFileLexer_yylex_destroy(), so don't allocate here.
+     */
 
     yyg->yy_buffer_stack = 0;
     yyg->yy_buffer_stack_top = 0;
     yyg->yy_buffer_stack_max = 0;
     yyg->yy_c_buf_p = (char *) 0;
-    yyg->yy_init = 1;
+    yyg->yy_init = 0;
     yyg->yy_start = 0;
+
     yyg->yy_start_stack_ptr = 0;
     yyg->yy_start_stack_depth = 0;
-    yyg->yy_start_stack = (int *) 0;
+    yyg->yy_start_stack =  NULL;
 
 /* Defined in main.c */
 #ifdef YY_STDINIT
@@ -1949,33 +2065,6 @@ static int yy_init_globals (yyscan_t yyscanner)
     return 0;
 }
 
-/* User-visible API */
-
-/* cmListFileLexer_yylex_init is special because it creates the scanner itself, so it is
- * the ONLY reentrant function that doesn't take the scanner as the last argument.
- * That's why we explicitly handle the declaration, instead of using our macros.
- */
-
-int cmListFileLexer_yylex_init(yyscan_t* ptr_yy_globals)
-
-{
-    if (ptr_yy_globals == NULL){
-        errno = EINVAL;
-        return 1;
-    }
-
-    *ptr_yy_globals = (yyscan_t) cmListFileLexer_yyalloc ( sizeof( struct yyguts_t ), NULL );
-
-    if (*ptr_yy_globals == NULL){
-        errno = ENOMEM;
-        return 1;
-    }
-
-    memset(*ptr_yy_globals,0,sizeof(struct yyguts_t));
-
-    return yy_init_globals ( *ptr_yy_globals );
-}
-
 /* cmListFileLexer_yylex_destroy is for both reentrant and non-reentrant scanners. */
 int cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
 {
@@ -1996,8 +2085,13 @@ int cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
         cmListFileLexer_yyfree(yyg->yy_start_stack ,yyscanner );
         yyg->yy_start_stack = NULL;
 
+    /* Reset the globals. This is important in a non-reentrant scanner so the next time
+     * cmListFileLexer_yylex() is called, initialization will occur. */
+    yy_init_globals( yyscanner);
+
     /* Destroy the main struct (reentrant only). */
     cmListFileLexer_yyfree ( yyscanner , yyscanner );
+    yyscanner = NULL;
     return 0;
 }
 
@@ -2009,7 +2103,6 @@ int cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
 static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , yyscan_t yyscanner)
 {
         int i;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         for ( i = 0; i < n; ++i )
                 s1[i] = s2[i];
 }
@@ -2019,7 +2112,6 @@ static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , yyscan_t yysca
 static int yy_flex_strlen (yyconst char * s , yyscan_t yyscanner)
 {
         int n;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         for ( n = 0; s[n]; ++n )
                 ;
 
@@ -2054,19 +2146,7 @@ void cmListFileLexer_yyfree (void * ptr , yyscan_t yyscanner)
 
 #define YYTABLES_NAME "yytables"
 
-#undef YY_NEW_FILE
-#undef YY_FLUSH_BUFFER
-#undef yy_set_bol
-#undef yy_new_buffer
-#undef yy_set_interactive
-#undef yytext_ptr
-#undef YY_DO_BEFORE_ACTION
-
-#ifdef YY_DECL_IS_OURS
-#undef YY_DECL_IS_OURS
-#undef YY_DECL
-#endif
-#line 194 "cmListFileLexer.in.l"
+#line 179 "cmListFileLexer.in.l"
 
 
 
@@ -2122,7 +2202,7 @@ static void cmListFileLexerAppend(cmListFileLexer* lexer, const char* text,
     }
 
   /* We need to extend the buffer.  */
-  temp = (char*)malloc(newSize);
+  temp = malloc(newSize);
   if(lexer->token.text)
     {
     memcpy(temp, lexer->token.text, lexer->token.length);