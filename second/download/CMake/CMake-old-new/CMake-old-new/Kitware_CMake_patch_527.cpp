@@ -9,7 +9,7 @@
 #define FLEX_SCANNER
 #define YY_FLEX_MAJOR_VERSION 2
 #define YY_FLEX_MINOR_VERSION 5
-#define YY_FLEX_SUBMINOR_VERSION 31
+#define YY_FLEX_SUBMINOR_VERSION 33
 #if YY_FLEX_SUBMINOR_VERSION > 0
 #define FLEX_BETA
 #endif
@@ -31,7 +31,15 @@
 
 /* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */
 
-#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
+#if __STDC_VERSION__ >= 199901L
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
@@ -43,7 +51,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t;
+typedef unsigned char flex_uint8_t; 
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 #endif /* ! C99 */
@@ -154,6 +162,10 @@ int cmDependsFortran_yylex_init (yyscan_t* scanner);
 #define YY_BUF_SIZE 16384
 #endif
 
+/* The state buf must be large enough to hold one state per character in the main buffer.
+ */
+#define YY_STATE_BUF_SIZE   ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))
+
 #ifndef YY_TYPEDEF_YY_BUFFER_STATE
 #define YY_TYPEDEF_YY_BUFFER_STATE
 typedef struct yy_buffer_state *YY_BUFFER_STATE;
@@ -164,9 +176,8 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
-
-/* Return all but the first "n" matched characters back to the input stream.
- */
+    
+/* Return all but the first "n" matched characters back to the input stream. */
 #define yyless(n) \
         do \
                 { \
@@ -175,8 +186,7 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
         YY_LESS_LINENO(yyless_macro_arg);\
                 *yy_cp = yyg->yy_hold_char; \
                 YY_RESTORE_YY_MORE_OFFSET \
-                yyg->yy_c_buf_p \
-                  = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
+                yyg->yy_c_buf_p = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
                 YY_DO_BEFORE_ACTION; /* set up yytext again */ \
                 } \
         while ( 0 )
@@ -233,7 +243,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-
+    
         /* Whether to try to fill the input buffer when we reach the
          * end of it.
          */
@@ -250,8 +260,8 @@ struct yy_buffer_state
          * possible backing-up.
          *
          * When we actually see the EOF, we change the status to "new"
-         * (via cmDependsFortran_yyrestart()), so that the user can continue
-         * scanning by just pointing yyin at a new input file.
+         * (via cmDependsFortran_yyrestart()), so that the user can continue scanning by
+         * just pointing yyin at a new input file.
          */
 #define YY_BUFFER_EOF_PENDING 2
 
@@ -345,46 +355,34 @@ static void yy_fatal_error (yyconst char msg[] ,yyscan_t yyscanner );
         *yy_cp = '\0'; \
         yyg->yy_c_buf_p = yy_cp;
 
-#define YY_NUM_RULES 43
-#define YY_END_OF_BUFFER 44
+#define YY_NUM_RULES 41
+#define YY_END_OF_BUFFER 42
 /* This struct is not used in this scanner,
    but its presence is necessary. */
 struct yy_trans_info
         {
         flex_int32_t yy_verify;
         flex_int32_t yy_nxt;
         };
-static yyconst flex_int16_t yy_accept[270] =
+static yyconst flex_int16_t yy_accept[155] =
     {   0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-       44,   39,   41,   40,   42,    1,   39,   39,   39,    2,
-       40,   39,   39,   39,   39,   39,   40,   39,    9,    8,
-        9,    4,    3,   39,    0,   10,    0,   39,   39,   39,
-       39,    0,   39,   39,   39,   39,    0,   37,   39,   39,
-       39,   39,   39,    0,   39,    0,   11,    0,    5,    0,
-        0,    0,    0,   39,   39,   39,   27,   39,   39,    0,
-        0,    0,    0,   39,   39,   39,   33,   39,   39,    0,
-       38,    0,   39,   39,   39,   39,   39,   16,    0,    0,
-        6,    0,    0,    0,   27,    0,    0,   39,   39,   39,
-
-       39,   39,   39,   39,   39,    0,    0,    0,   33,    0,
-        0,   39,   39,   39,   39,   39,   39,   39,   39,    0,
-       39,    0,   39,   39,   39,   39,   39,    0,    0,    0,
-        0,    0,    0,    0,    0,    0,   39,   28,   29,   39,
-       39,   39,   39,   39,    0,    0,    0,    0,    0,    0,
-        0,    0,   39,   34,   35,   39,   39,   39,   39,   39,
-        0,   39,    0,    0,   39,   39,   39,   39,   39,    0,
-        0,   28,   29,    0,    0,    0,    0,    0,   39,   30,
-       25,   39,   39,   23,    0,   34,   35,    0,    0,    0,
-        0,    0,   39,   36,   31,   39,   39,   24,    0,   39,
-
-        0,    0,   39,   39,   39,   39,   20,    0,    0,   30,
-       25,    0,    0,   23,   21,   26,   39,    0,   36,   31,
-        0,    0,   24,   22,   32,   39,    0,   39,    0,    0,
-       39,   39,   15,   39,    7,   21,   26,    0,   12,   22,
-       32,    0,   13,    0,   39,    0,    0,   39,   39,   39,
-       12,   13,    0,   14,    0,    0,   39,   19,   18,   14,
-        0,   19,   39,    0,   39,    0,   17,   17,    0
+       42,   36,   38,   37,   40,    1,   36,   36,   31,    2,
+       37,   34,   36,   35,   36,   35,   37,   36,   35,    9,
+        8,    9,    4,    3,   36,    0,   10,    0,    0,    0,
+        0,    0,    0,    0,    0,    0,    0,   31,   31,   32,
+       34,   36,   35,    0,   39,   35,    0,   36,    0,   11,
+       35,    0,    0,    5,    0,    0,    0,   21,    0,    0,
+        0,    0,    0,    0,   27,    0,   31,   31,   31,   31,
+        0,    0,    0,    0,    0,    6,    0,    0,    0,    0,
+        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
+
+        0,    0,    0,    0,    0,    0,   22,   23,    0,    0,
+        0,    0,    0,    0,    0,   28,   29,    0,    0,    0,
+        0,    0,    0,    0,    0,   24,   19,    0,    0,   17,
+        0,   18,   30,   25,    0,    0,    0,    0,    0,   15,
+       20,    0,   16,   26,    0,    0,    7,   33,    7,   12,
+       13,    0,   14,    0
     } ;
 
 static yyconst flex_int32_t yy_ec[256] =
@@ -393,16 +391,16 @@ static yyconst flex_int32_t yy_ec[256] =
         1,    1,    4,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    5,    6,    7,    8,    9,    1,   10,   11,    1,
-        1,   12,    1,    4,    1,    1,    1,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,    1,    1,   13,    1,
-        1,    1,   14,    1,   15,    1,   16,   17,   18,   19,
-        1,    1,   20,    1,    1,   21,   22,   23,   24,    1,
-        1,   25,   26,   27,   28,    1,    1,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,   15,    1,   16,   17,
-
-       18,   19,    1,    1,   20,    1,    1,   21,   22,   23,
-       24,    1,    1,   25,   26,   27,   28,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
+        1,   12,    1,    4,    1,    1,    1,   13,   13,   13,
+       13,   13,   13,   13,   13,   13,   13,    1,   14,    1,
+       15,   16,   17,    1,   18,   18,   19,   20,   21,   22,
+       18,   18,   23,   18,   18,   18,   18,   24,   18,   18,
+       18,   18,   18,   18,   25,   18,   18,   18,   18,   18,
+        1,   26,    1,    1,   27,    1,   18,   18,   28,   29,
+
+       30,   31,   18,   18,   32,   18,   18,   33,   18,   34,
+       18,   18,   18,   18,   35,   18,   36,   18,   18,   18,
+       18,   18,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
@@ -419,167 +417,152 @@ static yyconst flex_int32_t yy_ec[256] =
         1,    1,    1,    1,    1
     } ;
 
-static yyconst flex_int32_t yy_meta[29] =
+static yyconst flex_int32_t yy_meta[37] =
     {   0,
-        1,    2,    2,    3,    2,    3,    3,    1,    1,    1,
-        3,    1,    3,    1,    1,    1,    1,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,    1,    1
+        1,    2,    2,    3,    4,    3,    3,    1,    1,    3,
+        3,    1,    5,    3,    3,    1,    1,    6,    6,    6,
+        6,    6,    6,    6,    6,    1,    5,    6,    6,    6,
+        6,    6,    6,    6,    6,    6
     } ;
 
-static yyconst flex_int16_t yy_base[276] =
+static yyconst flex_int16_t yy_base[163] =
     {   0,
-        0,    0,    0,    0,  332,   26,   29,   34,   43,   44,
-      334,    0,  336,  336,  330,  336,   53,   80,   28,  336,
-      336,  318,  308,  307,  305,  302,  322,  107,  336,  321,
-       54,  336,  336,    0,  322,  336,  119,  306,   13,   29,
-      300,  146,  304,   39,   42,  298,   61,   67,   73,  303,
-       52,  302,  300,  312,  173,  313,  336,   81,   85,  297,
-       53,   69,  291,  294,   15,  295,   79,  295,  293,  291,
-       68,   80,  285,  288,   81,  289,   99,  289,  287,  121,
-      336,  123,  280,  110,  281,  283,  272,    0,  294,  136,
-      336,  279,  107,  280,  112,  280,  278,  274,  274,  274,
-
-      271,  272,  272,  267,  269,  267,  114,  268,  127,  268,
-      266,  262,  262,  262,  259,  260,  260,  255,  257,  251,
-      257,  137,  249,  247,  242,  244,  247,  262,  246,  246,
-      246,  243,  244,  244,  239,  241,  235,    0,    0,  238,
-      237,  237,  226,  234,  232,  232,  232,  229,  230,  230,
-      225,  227,  221,    0,    0,  224,  223,  223,  212,  220,
-      222,  216,  213,  211,  207,  216,  215,  212,  212,  224,
-      205,  336,  336,  208,  207,  207,  196,  204,  204,    0,
-        0,  202,  203,    0,  196,  336,  336,  199,  198,  198,
-      187,  195,  195,    0,    0,  193,  194,    0,  189,  181,
-
-      181,  190,  188,  177,  186,  188,    0,    0,  184,  336,
-      336,  181,  168,  336,    0,    0,  165,  164,  336,  336,
-      162,  156,  336,    0,    0,  154,  143,  153,  151,  140,
-      142,  144,    0,  146,  336,  336,  336,  143,    0,  336,
-      336,  142,    0,  141,  138,  130,  133,  134,  134,  131,
-      336,  336,  127,    0,  100,   99,   91,    0,    0,  336,
-       90,  336,   88,   78,   62,   49,    0,  336,  336,  186,
-       48,  189,  192,  195,  198
+        0,    0,    0,    0,  276,   34,   37,   39,   48,   49,
+      277,    0,  356,  356,  273,  356,   62,   97,   63,  356,
+      356,  259,  257,    0,   36,  129,  267,  156,  183,  356,
+      266,   69,  356,  356,    0,  267,  356,  218,  239,   10,
+       26,  234,  253,  246,  242,   42,   46,   76,   98,  356,
+      356,   82,    0,  104,  356,    0,  260,  285,  261,  356,
+        0,  258,  108,   83,  231,   80,  232,   61,  232,  230,
+      235,  236,   84,  224,   89,  224,  129,  148,  219,  225,
+      131,  217,  244,  241,  138,  356,  213,  213,  213,  210,
+      211,  211,  206,  208,  214,  215,  203,  203,  200,  196,
+
+      152,  147,  151,  173,  172,  142,  356,  356,  144,  143,
+      141,  134,  136,  142,  140,  356,  356,  130,  129,  122,
+      113,  114,  139,  123,   96,  356,  356,   94,   95,  356,
+      100,  356,  356,  356,   89,   76,   53,   94,    0,  356,
+      356,   53,  356,  356,   40,   32,  356,  356,  356,  356,
+      356,   15,  356,  356,  312,  318,  323,  325,  331,  337,
+      343,  349
     } ;
 
-static yyconst flex_int16_t yy_def[276] =
+static yyconst flex_int16_t yy_def[163] =
     {   0,
-      269,    1,    1,    1,    1,    1,  270,  270,  270,  270,
-      269,  271,  269,  269,  272,  269,  271,  271,  271,  269,
-      269,  271,  271,  271,  271,  271,  269,  273,  269,  269,
-      269,  269,  269,  271,  272,  269,  269,  271,  271,  271,
-      271,  269,  271,  271,  271,  271,  269,  269,  271,  271,
-      271,  271,  271,  269,  273,  274,  269,  269,  269,  269,
-      269,  269,  269,  271,  271,  271,  271,  271,  271,  269,
-      269,  269,  269,  271,  271,  271,  271,  271,  271,  269,
-      269,  269,  271,  271,  271,  271,  271,  271,  269,  269,
-      269,  269,  269,  269,  269,  269,  269,  271,  271,  271,
-
-      271,  271,  271,  271,  271,  269,  269,  269,  269,  269,
-      269,  271,  271,  271,  271,  271,  271,  271,  271,  269,
-      271,  269,  271,  271,  271,  271,  271,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  271,  271,  271,  271,
-      271,  271,  271,  271,  269,  269,  269,  269,  269,  269,
-      269,  269,  271,  271,  271,  271,  271,  271,  271,  271,
-      269,  271,  269,  269,  271,  271,  271,  271,  271,  269,
-      269,  269,  269,  269,  269,  269,  269,  269,  271,  271,
-      271,  271,  271,  271,  269,  269,  269,  269,  269,  269,
-      269,  269,  271,  271,  271,  271,  271,  271,  269,  271,
-
-      269,  269,  271,  271,  271,  271,  271,  275,  269,  269,
-      269,  269,  269,  269,  271,  271,  271,  269,  269,  269,
-      269,  269,  269,  271,  271,  271,  269,  271,  269,  269,
-      271,  271,  271,  271,  269,  269,  269,  269,  271,  269,
-      269,  269,  271,  269,  271,  269,  269,  271,  271,  271,
-      269,  269,  269,  271,  269,  269,  271,  271,  271,  269,
-      269,  269,  271,  269,  271,  269,  271,  269,    0,  269,
-      269,  269,  269,  269,  269
+      154,    1,    1,    1,    1,    1,  155,  155,  155,  155,
+      154,  156,  154,  154,  157,  154,  156,  156,  154,  154,
+      154,  154,  156,  158,  156,  158,  154,  159,  154,  154,
+      154,  154,  154,  154,  156,  157,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  160,  154,
+      154,  156,  158,  154,  154,   26,  154,  159,  159,  154,
+       29,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  160,  160,  160,  160,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  161,  162,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,    0,  154,  154,  154,  154,  154,  154,
+      154,  154
     } ;
 
-static yyconst flex_int16_t yy_nxt[365] =
+static yyconst flex_int16_t yy_nxt[393] =
     {   0,
        12,   13,   14,   13,   13,   15,   16,   17,   18,   19,
-       20,   12,   21,   22,   12,   12,   12,   23,   12,   24,
-       12,   25,   12,   12,   12,   12,   12,   26,   27,   47,
-       48,   30,   47,   65,   99,   66,   30,   28,   31,   32,
-      100,   28,   28,   31,   32,   30,   30,   67,   34,   33,
-       33,   68,   31,   31,   37,   58,   59,   37,   58,   75,
-       77,   76,   47,   48,   78,   47,  268,   85,   80,   38,
-       39,   80,   40,   93,   82,   94,   81,   82,   86,  267,
-       41,   42,   58,   59,   42,   58,   90,   95,  107,   90,
-      108,   96,   83,  266,   91,  102,   43,   44,  109,   45,
-
-      113,  103,  110,  265,  264,  263,  114,   46,   56,   57,
-       56,   56,   56,   56,  122,  116,  262,   56,  261,   56,
-       37,  117,   80,   37,   82,   80,  130,   82,  133,  123,
-       81,  124,  131,  146,  134,   60,   61,   90,   62,  147,
-       90,  122,  120,  149,  260,   91,   63,   42,  259,  150,
-       42,  258,  257,  256,  255,  254,  163,  253,  164,  252,
-      251,  250,   70,   71,  249,   72,  248,  247,  246,  245,
-      244,  243,  242,   73,   56,   57,   56,   56,   56,   56,
-      241,  240,  239,   56,  238,   56,   29,   29,   29,   35,
-       35,   35,   55,   55,   55,   56,   56,   56,  235,  237,
-
-      235,  236,  234,  233,  232,  231,  230,  229,  228,  227,
-      226,  225,  224,  223,  222,  221,  220,  219,  218,  217,
-      216,  215,  214,  213,  212,  211,  210,  209,  208,  207,
-      206,  205,  204,  203,  202,  201,  200,  199,  198,  197,
-      196,  195,  194,  193,  192,  191,  190,  189,  188,  187,
-      186,  185,  184,  183,  182,  181,  180,  179,  178,  177,
-      176,  175,  174,  173,  172,  171,  170,  169,  168,  167,
-      166,  165,  162,  161,  160,  159,  158,  157,  156,  155,
-      154,  153,  152,  151,  148,  145,  144,  143,  142,  141,
-      140,  139,  138,  137,  136,  135,  132,  129,  128,  127,
-
-      126,  125,  121,  119,  118,  115,  112,  111,  106,  105,
-      104,  101,   98,   97,   92,   57,   89,   88,   87,   84,
-       79,   74,   69,   64,   36,   54,   54,   53,   52,   51,
-       50,   49,   36,  269,   27,   11,  269,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
-      269,  269,  269,  269
+       20,   12,   12,   21,   22,   12,   23,   24,   24,   24,
+       24,   24,   24,   24,   24,   25,   26,   24,   24,   24,
+       24,   24,   24,   24,   24,   24,   27,   54,   55,   31,
+       54,   31,   66,   67,  153,   28,   32,   33,   32,   33,
+       31,   31,   29,   29,   34,   34,   68,   32,   32,   69,
+      152,   29,   29,   38,   48,   48,   38,   48,   49,  151,
+       63,   64,   50,   63,   73,   74,   75,   48,   48,   76,
+       48,   49,  150,   81,   85,   50,   81,   85,  146,   91,
+       39,   40,   86,   41,   92,  148,  148,   42,   43,   78,
+
+       48,   43,   78,   79,  145,   54,   55,   80,   54,   63,
+       64,   88,   63,   82,   89,   97,   44,  100,   98,  144,
+      143,   45,  101,  142,  141,  140,   46,  139,   47,   35,
+       78,   48,   81,   78,   79,   81,   35,   35,   80,   85,
+       35,   56,   85,  138,   35,   35,  137,   86,  136,   78,
+       48,  135,   78,   79,   35,   56,   58,   80,   60,  134,
+      133,  132,   82,   58,   58,  131,  130,   58,   58,  129,
+      128,   58,   58,  127,  126,  125,  124,  123,  122,  121,
+      120,   58,   58,   59,   59,   60,   59,   59,   59,   59,
+       59,   59,   59,   59,   59,   61,   59,   59,   59,   59,
+
+       61,   61,   61,   61,   61,   61,   61,   61,   59,   61,
+       61,   61,   61,   61,   61,   61,   61,   61,   61,   38,
+       78,   48,   38,   78,   79,  119,   78,   48,   80,   78,
+       79,  118,  117,  116,   80,  115,  114,  113,  112,  111,
+      110,  109,  108,  107,  106,  105,   39,   40,  104,   41,
+      103,  102,   99,   42,   43,   96,   95,   43,   94,   93,
+       90,   87,   84,   60,   83,   72,   71,   70,   65,   37,
+       62,   57,   44,   52,   51,   37,  154,   45,   27,  154,
+      154,  154,   46,  154,   47,   58,  154,   60,  154,  154,
+      154,  154,   58,   58,  154,  154,   58,   58,  154,  154,
+
+       58,   58,  154,  154,  154,  154,  154,  154,  154,  154,
+       58,   58,   30,   30,   30,   30,   30,   30,   35,  154,
+      154,  154,   35,   36,   36,   36,   36,   36,   36,   53,
+       53,   59,   59,   59,   59,   59,   59,   77,   77,   77,
+       77,   77,   77,  147,  147,  147,  154,  147,  147,  149,
+      154,  149,  154,  149,  149,   11,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154
+
     } ;
 
-static yyconst flex_int16_t yy_chk[365] =
+static yyconst flex_int16_t yy_chk[393] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,    1,    1,    6,   19,
-       19,    7,   19,   39,   65,   39,    8,    6,    7,    7,
-       65,    6,    6,    8,    8,    9,   10,   40,  271,    9,
-       10,   40,    9,   10,   17,   31,   31,   17,   31,   44,
-       45,   44,   47,   47,   45,   47,  266,   51,   48,   17,
-       17,   48,   17,   61,   49,   61,   48,   49,   51,  265,
-       17,   18,   58,   58,   18,   58,   59,   62,   71,   59,
-       71,   62,   49,  264,   59,   67,   18,   18,   72,   18,
-
-       75,   67,   72,  263,  261,  257,   75,   18,   28,   28,
-       28,   28,   28,   28,   84,   77,  256,   28,  255,   28,
-       37,   77,   80,   37,   82,   80,   93,   82,   95,   84,
-       80,   84,   93,  107,   95,   37,   37,   90,   37,  107,
-       90,  122,   82,  109,  253,   90,   37,   42,  250,  109,
-       42,  249,  248,  247,  246,  245,  122,  244,  122,  242,
-      238,  234,   42,   42,  232,   42,  231,  230,  229,  228,
-      227,  226,  222,   42,   55,   55,   55,   55,   55,   55,
-      221,  218,  217,   55,  213,   55,  270,  270,  270,  272,
-      272,  272,  273,  273,  273,  274,  274,  274,  275,  212,
-
-      275,  209,  206,  205,  204,  203,  202,  201,  200,  199,
-      197,  196,  193,  192,  191,  190,  189,  188,  185,  183,
-      182,  179,  178,  177,  176,  175,  174,  171,  170,  169,
-      168,  167,  166,  165,  164,  163,  162,  161,  160,  159,
-      158,  157,  156,  153,  152,  151,  150,  149,  148,  147,
-      146,  145,  144,  143,  142,  141,  140,  137,  136,  135,
-      134,  133,  132,  131,  130,  129,  128,  127,  126,  125,
-      124,  123,  121,  120,  119,  118,  117,  116,  115,  114,
-      113,  112,  111,  110,  108,  106,  105,  104,  103,  102,
-      101,  100,   99,   98,   97,   96,   94,   92,   89,   87,
-
-       86,   85,   83,   79,   78,   76,   74,   73,   70,   69,
-       68,   66,   64,   63,   60,   56,   54,   53,   52,   50,
-       46,   43,   41,   38,   35,   30,   27,   26,   25,   24,
-       23,   22,   15,   11,    5,  269,  269,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
-      269,  269,  269,  269
+        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
+        1,    1,    1,    1,    1,    1,    6,   25,   25,    7,
+       25,    8,   40,   40,  152,    6,    7,    7,    8,    8,
+        9,   10,    6,    6,    9,   10,   41,    9,   10,   41,
+      146,    6,    6,   17,   19,   19,   17,   19,   19,  145,
+       32,   32,   19,   32,   46,   46,   47,   48,   48,   47,
+       48,   48,  142,   52,   64,   48,   52,   64,  137,   68,
+       17,   17,   64,   17,   68,  138,  138,   17,   18,   49,
+
+       49,   18,   49,   49,  136,   54,   54,   49,   54,   63,
+       63,   66,   63,   52,   66,   73,   18,   75,   73,  135,
+      131,   18,   75,  129,  128,  125,   18,  124,   18,   26,
+       77,   77,   81,   77,   77,   81,   26,   26,   77,   85,
+       26,   26,   85,  123,   26,   26,  122,   85,  121,   78,
+       78,  120,   78,   78,   26,   26,   28,   78,   28,  119,
+      118,  115,   81,   28,   28,  114,  113,   28,   28,  112,
+      111,   28,   28,  110,  109,  106,  105,  104,  103,  102,
+      101,   28,   28,   29,   29,   29,   29,   29,   29,   29,
+       29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
+
+       29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
+       29,   29,   29,   29,   29,   29,   29,   29,   29,   38,
+       79,   79,   38,   79,   79,  100,   80,   80,   79,   80,
+       80,   99,   98,   97,   80,   96,   95,   94,   93,   92,
+       91,   90,   89,   88,   87,   84,   38,   38,   83,   38,
+       82,   76,   74,   38,   43,   72,   71,   43,   70,   69,
+       67,   65,   62,   59,   57,   45,   44,   42,   39,   36,
+       31,   27,   43,   23,   22,   15,   11,   43,    5,    0,
+        0,    0,   43,    0,   43,   58,    0,   58,    0,    0,
+        0,    0,   58,   58,    0,    0,   58,   58,    0,    0,
+
+       58,   58,    0,    0,    0,    0,    0,    0,    0,    0,
+       58,   58,  155,  155,  155,  155,  155,  155,  156,    0,
+        0,    0,  156,  157,  157,  157,  157,  157,  157,  158,
+      158,  159,  159,  159,  159,  159,  159,  160,  160,  160,
+      160,  160,  160,  161,  161,  161,    0,  161,  161,  162,
+        0,  162,    0,  162,  162,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
+      154,  154
+
     } ;
 
 /* The intent behind this definition is that it'll catch
@@ -608,7 +591,7 @@ static yyconst flex_int16_t yy_chk[365] =
 
 =========================================================================*/
 /*-------------------------------------------------------------------------
-  Portions of this source have been derived from makefdep90 version 2.6.2,
+  Portions of this source have been derived from makefdep90 version 2.8.8,
 
    Copyright (C) 2000,2001 Erik Edelmann <eedelman@beam.helsinki.fi>.
 
@@ -656,7 +639,7 @@ Modify cmDependsFortranLexer.h:
 /*--------------------------------------------------------------------------*/
 
 
-#line 682 "cmDependsFortranLexer.cxx"
+#line 643 "cmDependsFortranLexer.cxx"
 
 #define INITIAL 0
 #define free_fmt 1
@@ -710,6 +693,8 @@ struct yyguts_t
 
     }; /* end struct yyguts_t */
 
+static int yy_init_globals (yyscan_t yyscanner );
+
 /* Accessor methods to globals.
    These are made visible to non-reentrant scanners for convenience. */
 
@@ -752,7 +737,7 @@ extern int cmDependsFortran_yywrap (yyscan_t yyscanner );
 #endif
 
     static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
-
+    
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -878,14 +863,14 @@ YY_DECL
         register int yy_act;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-#line 98 "cmDependsFortranLexer.in.l"
+#line 75 "cmDependsFortranLexer.in.l"
 
 
-#line 907 "cmDependsFortranLexer.cxx"
+#line 870 "cmDependsFortranLexer.cxx"
 
-        if ( yyg->yy_init )
+        if ( !yyg->yy_init )
                 {
-                yyg->yy_init = 0;
+                yyg->yy_init = 1;
 
 #ifdef YY_USER_INIT
                 YY_USER_INIT;
@@ -935,13 +920,13 @@ YY_DECL
                         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                                 {
                                 yy_current_state = (int) yy_def[yy_current_state];
-                                if ( yy_current_state >= 270 )
+                                if ( yy_current_state >= 155 )
                                         yy_c = yy_meta[(unsigned int) yy_c];
                                 }
                         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
                         ++yy_cp;
                         }
-                while ( yy_base[yy_current_state] != 336 );
+                while ( yy_base[yy_current_state] != 356 );
 
 yy_find_action:
                 yy_act = yy_accept[yy_current_state];
@@ -967,229 +952,228 @@ YY_DECL
 
 case 1:
 YY_RULE_SETUP
-#line 100 "cmDependsFortranLexer.in.l"
+#line 77 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_StringStart(yyextra);
+  cmDependsFortranParser_SetOldStartcond(yyextra, YY_START);
   BEGIN(str_dq);
 }
         YY_BREAK
 case 2:
 YY_RULE_SETUP
-#line 105 "cmDependsFortranLexer.in.l"
+#line 83 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_StringStart(yyextra);
+  cmDependsFortranParser_SetOldStartcond(yyextra, YY_START);
   BEGIN(str_sq);
 }
         YY_BREAK
 case 3:
-#line 111 "cmDependsFortranLexer.in.l"
+#line 90 "cmDependsFortranLexer.in.l"
 case 4:
 YY_RULE_SETUP
-#line 111 "cmDependsFortranLexer.in.l"
+#line 90 "cmDependsFortranLexer.in.l"
 {
+  BEGIN(cmDependsFortranParser_GetOldStartcond(yyextra) );
   yylvalp->string = strdup(cmDependsFortranParser_StringEnd(yyextra));
   return STRING;
 }
 case 5:
 /* rule 5 can match eol */
-#line 117 "cmDependsFortranLexer.in.l"
+#line 97 "cmDependsFortranLexer.in.l"
 case 6:
 /* rule 6 can match eol */
 YY_RULE_SETUP
-#line 117 "cmDependsFortranLexer.in.l"
+#line 97 "cmDependsFortranLexer.in.l"
 /* Ignore (continued strings, free fmt) */
         YY_BREAK
 case 7:
 /* rule 7 can match eol */
 YY_RULE_SETUP
-#line 119 "cmDependsFortranLexer.in.l"
-/*Ignore (cont. strings, fixed fmt) */
+#line 99 "cmDependsFortranLexer.in.l"
+{
+  if (cmDependsFortranParser_GetOldStartcond(yyextra) == fixed_fmt)
+    ; /* Ignore (cont. strings, fixed fmt) */
+  else
+    {
+    unput(yytext[strlen(yytext)-1]);
+    }
+}
         YY_BREAK
 case 8:
 /* rule 8 can match eol */
 YY_RULE_SETUP
-#line 121 "cmDependsFortranLexer.in.l"
+#line 109 "cmDependsFortranLexer.in.l"
 {
   unput ('\n');
   BEGIN(INITIAL);
   return UNTERMINATED_STRING;
 }
 case 9:
 YY_RULE_SETUP
-#line 127 "cmDependsFortranLexer.in.l"
+#line 115 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_StringAppend(yyextra, yytext[0]);
 }
         YY_BREAK
 case 10:
 /* rule 10 can match eol */
 YY_RULE_SETUP
-#line 131 "cmDependsFortranLexer.in.l"
+#line 119 "cmDependsFortranLexer.in.l"
 { return EOSTMT; } /* Treat comments like */
 case 11:
 /* rule 11 can match eol */
 YY_RULE_SETUP
-#line 132 "cmDependsFortranLexer.in.l"
+#line 120 "cmDependsFortranLexer.in.l"
 { return EOSTMT; } /* empty lines */
 case 12:
 YY_RULE_SETUP
-#line 134 "cmDependsFortranLexer.in.l"
+#line 122 "cmDependsFortranLexer.in.l"
 { return CPP_INCLUDE; }
 case 13:
 YY_RULE_SETUP
-#line 135 "cmDependsFortranLexer.in.l"
+#line 123 "cmDependsFortranLexer.in.l"
 { return F90PPR_INCLUDE; }
 case 14:
 YY_RULE_SETUP
-#line 136 "cmDependsFortranLexer.in.l"
+#line 124 "cmDependsFortranLexer.in.l"
 { return COCO_INCLUDE; }
 case 15:
 YY_RULE_SETUP
-#line 137 "cmDependsFortranLexer.in.l"
-{ return F_INCLUDE; }
+#line 126 "cmDependsFortranLexer.in.l"
+{ return CPP_DEFINE; }
 case 16:
 YY_RULE_SETUP
-#line 138 "cmDependsFortranLexer.in.l"
-{ return USE; }
+#line 127 "cmDependsFortranLexer.in.l"
+{ return F90PPR_DEFINE; }
 case 17:
 YY_RULE_SETUP
-#line 140 "cmDependsFortranLexer.in.l"
-{
-  cmDependsFortranParser_SetInInterface(yyextra, 0);
-}
-        YY_BREAK
+#line 129 "cmDependsFortranLexer.in.l"
+{ return CPP_UNDEF; }
 case 18:
 YY_RULE_SETUP
-#line 143 "cmDependsFortranLexer.in.l"
-{
-  cmDependsFortranParser_SetInInterface(yyextra, 1);
-}
-        YY_BREAK
+#line 130 "cmDependsFortranLexer.in.l"
+{ return F90PPR_UNDEF; }
 case 19:
 YY_RULE_SETUP
-#line 147 "cmDependsFortranLexer.in.l"
-/* Ignore */
-        YY_BREAK
+#line 132 "cmDependsFortranLexer.in.l"
+{ return CPP_IFDEF; }
 case 20:
 YY_RULE_SETUP
-#line 148 "cmDependsFortranLexer.in.l"
-{
- if(!cmDependsFortranParser_GetInInterface(yyextra))
-   {
-   return MODULE;
-   }
-}
-        YY_BREAK
+#line 133 "cmDependsFortranLexer.in.l"
+{ return CPP_IFNDEF; }
 case 21:
 YY_RULE_SETUP
-#line 155 "cmDependsFortranLexer.in.l"
-{ return CPP_DEFINE; }
+#line 134 "cmDependsFortranLexer.in.l"
+{ return CPP_IF; }
 case 22:
 YY_RULE_SETUP
-#line 156 "cmDependsFortranLexer.in.l"
-{ return F90PPR_DEFINE; }
+#line 135 "cmDependsFortranLexer.in.l"
+{ return CPP_ELIF; }
 case 23:
 YY_RULE_SETUP
-#line 158 "cmDependsFortranLexer.in.l"
-{ return CPP_UNDEF; }
+#line 136 "cmDependsFortranLexer.in.l"
+{ return CPP_ELSE; }
 case 24:
 YY_RULE_SETUP
-#line 159 "cmDependsFortranLexer.in.l"
-{ return F90PPR_UNDEF; }
+#line 137 "cmDependsFortranLexer.in.l"
+{ return CPP_ENDIF; }
 case 25:
 YY_RULE_SETUP
-#line 161 "cmDependsFortranLexer.in.l"
-{ return CPP_IFDEF; }
+#line 139 "cmDependsFortranLexer.in.l"
+{ return F90PPR_IFDEF; }
 case 26:
 YY_RULE_SETUP
-#line 162 "cmDependsFortranLexer.in.l"
-{ return CPP_IFNDEF; }
+#line 140 "cmDependsFortranLexer.in.l"
+{ return F90PPR_IFNDEF; }
 case 27:
 YY_RULE_SETUP
-#line 163 "cmDependsFortranLexer.in.l"
-{ return CPP_IF; }
+#line 141 "cmDependsFortranLexer.in.l"
+{ return F90PPR_IF; }
 case 28:
 YY_RULE_SETUP
-#line 164 "cmDependsFortranLexer.in.l"
-{ return CPP_ELIF; }
+#line 142 "cmDependsFortranLexer.in.l"
+{ return F90PPR_ELIF; }
 case 29:
 YY_RULE_SETUP
-#line 165 "cmDependsFortranLexer.in.l"
-{ return CPP_ELSE; }
+#line 143 "cmDependsFortranLexer.in.l"
+{ return F90PPR_ELSE; }
 case 30:
 YY_RULE_SETUP
-#line 166 "cmDependsFortranLexer.in.l"
-{ return CPP_ENDIF; }
+#line 144 "cmDependsFortranLexer.in.l"
+{ return F90PPR_ENDIF; }
+/* Line continuations, possible involving comments.  */
 case 31:
+/* rule 31 can match eol */
 YY_RULE_SETUP
-#line 168 "cmDependsFortranLexer.in.l"
-{ return F90PPR_IFDEF; }
+#line 147 "cmDependsFortranLexer.in.l"
+
+        YY_BREAK
 case 32:
+/* rule 32 can match eol */
 YY_RULE_SETUP
-#line 169 "cmDependsFortranLexer.in.l"
-{ return F90PPR_IFNDEF; }
+#line 148 "cmDependsFortranLexer.in.l"
+
+        YY_BREAK
 case 33:
+/* rule 33 can match eol */
 YY_RULE_SETUP
-#line 170 "cmDependsFortranLexer.in.l"
-{ return F90PPR_IF; }
+#line 150 "cmDependsFortranLexer.in.l"
+{ return GARBAGE; }
 case 34:
 YY_RULE_SETUP
-#line 171 "cmDependsFortranLexer.in.l"
-{ return F90PPR_ELIF; }
+#line 152 "cmDependsFortranLexer.in.l"
+{ return ASSIGNMENT_OP; }
 case 35:
 YY_RULE_SETUP
-#line 172 "cmDependsFortranLexer.in.l"
-{ return F90PPR_ELSE; }
+#line 154 "cmDependsFortranLexer.in.l"
+{
+  yylvalp->string = strdup(yytext);
+  return WORD;
+}
 case 36:
 YY_RULE_SETUP
-#line 173 "cmDependsFortranLexer.in.l"
-{ return F90PPR_ENDIF; }
+#line 159 "cmDependsFortranLexer.in.l"
+{ return GARBAGE; }
 case 37:
 /* rule 37 can match eol */
-#line 176 "cmDependsFortranLexer.in.l"
+YY_RULE_SETUP
+#line 161 "cmDependsFortranLexer.in.l"
+{ return EOSTMT; }
 case 38:
-/* rule 38 can match eol */
 YY_RULE_SETUP
-#line 176 "cmDependsFortranLexer.in.l"
+#line 164 "cmDependsFortranLexer.in.l"
 /* Ignore */
         YY_BREAK
 case 39:
+/* rule 39 can match eol */
 YY_RULE_SETUP
-#line 179 "cmDependsFortranLexer.in.l"
-{ yylvalp->string = strdup(yytext); return WORD; }
-case 40:
-/* rule 40 can match eol */
-YY_RULE_SETUP
-#line 181 "cmDependsFortranLexer.in.l"
-{ return EOSTMT; }
-case 41:
-YY_RULE_SETUP
-#line 183 "cmDependsFortranLexer.in.l"
-/* Ignore */
+#line 165 "cmDependsFortranLexer.in.l"
+/* Ignore line-endings preceeded by \ */
         YY_BREAK
-case 42:
+case 40:
 YY_RULE_SETUP
-#line 185 "cmDependsFortranLexer.in.l"
+#line 167 "cmDependsFortranLexer.in.l"
 { return *yytext; }
 case YY_STATE_EOF(INITIAL):
 case YY_STATE_EOF(free_fmt):
 case YY_STATE_EOF(fixed_fmt):
 case YY_STATE_EOF(str_sq):
 case YY_STATE_EOF(str_dq):
-#line 187 "cmDependsFortranLexer.in.l"
+#line 169 "cmDependsFortranLexer.in.l"
 {
- if(!cmDependsFortranParser_FilePop(yyextra))
-   {
-   return YY_NULL;
-   }
+  if(!cmDependsFortranParser_FilePop(yyextra) )
+    {
+    return YY_NULL;
+    }
 }
         YY_BREAK
-case 43:
+case 41:
 YY_RULE_SETUP
-#line 194 "cmDependsFortranLexer.in.l"
+#line 176 "cmDependsFortranLexer.in.l"
 ECHO;
         YY_BREAK
-#line 1243 "cmDependsFortranLexer.cxx"
+#line 1206 "cmDependsFortranLexer.cxx"
 
         case YY_END_OF_BUFFER:
                 {
@@ -1374,10 +1358,10 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
         else
                 {
-                        size_t nuto_read =
+                        int num_to_read =
                         YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
 
-                while ( nuto_read <= 0 )
+                while ( num_to_read <= 0 )
                         { /* Not enough room in the buffer - grow it. */
 
                         /* just a shorter name for the current buffer */
@@ -1409,17 +1393,17 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                         yyg->yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];
 
-                        nuto_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
+                        num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
                                                 number_to_move - 1;
 
                         }
 
-                if ( nuto_read > YY_READ_BUF_SIZE )
-                        nuto_read = YY_READ_BUF_SIZE;
+                if ( num_to_read > YY_READ_BUF_SIZE )
+                        num_to_read = YY_READ_BUF_SIZE;
 
                 /* Read in more data. */
                 YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
-                        yyg->yy_n_chars, nuto_read );
+                        yyg->yy_n_chars, (size_t) num_to_read );
 
                 YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
                 }
@@ -1474,7 +1458,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                 while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                         {
                         yy_current_state = (int) yy_def[yy_current_state];
-                        if ( yy_current_state >= 270 )
+                        if ( yy_current_state >= 155 )
                                 yy_c = yy_meta[(unsigned int) yy_c];
                         }
                 yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
@@ -1491,7 +1475,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
     static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state , yyscan_t yyscanner)
 {
         register int yy_is_jam;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner; /* This var may be unused depending upon options. */
         register char *yy_cp = yyg->yy_c_buf_p;
 
         register YY_CHAR yy_c = 1;
@@ -1503,11 +1487,11 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                 {
                 yy_current_state = (int) yy_def[yy_current_state];
-                if ( yy_current_state >= 270 )
+                if ( yy_current_state >= 155 )
                         yy_c = yy_meta[(unsigned int) yy_c];
                 }
         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-        yy_is_jam = (yy_current_state == 269);
+        yy_is_jam = (yy_current_state == 154);
 
         return yy_is_jam ? 0 : yy_current_state;
 }
@@ -1700,7 +1684,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmDependsFortran_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-
+    
         b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_create_buffer()" );
@@ -1744,7 +1728,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-
+    
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmDependsFortran_yyrestart() or at EOF.
@@ -1770,7 +1754,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-
+    
         errno = oerrno;
 }
 
@@ -1861,7 +1845,7 @@ void cmDependsFortran_yypop_buffer_state (yyscan_t yyscanner)
  */
 static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
 {
-        int nuto_alloc;
+        int num_to_alloc;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         if (!yyg->yy_buffer_stack) {
@@ -1870,15 +1854,14 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                  * scanner will even need a stack. We use 2 instead of 1 to avoid an
                  * immediate realloc on the next call.
          */
-                nuto_alloc = 1;
+                num_to_alloc = 1;
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyalloc
-                                                                (nuto_alloc * sizeof(struct yy_buffer_state*)
+                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
                 
-                memset(yyg->yy_buffer_stack, 0, 
-                       nuto_alloc * sizeof(struct yy_buffer_state*));
+                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
                                 
-                yyg->yy_buffer_stack_max = nuto_alloc;
+                yyg->yy_buffer_stack_max = num_to_alloc;
                 yyg->yy_buffer_stack_top = 0;
                 return;
         }
@@ -1888,28 +1871,28 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                 /* Increase the buffer to prepare for a possible push. */
                 int grow_size = 8 /* arbitrary grow size */;
 
-                nuto_alloc = yyg->yy_buffer_stack_max + grow_size;
+                num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyrealloc
                                                                 (yyg->yy_buffer_stack,
-                                                                nuto_alloc * sizeof(struct yy_buffer_state*)
+                                                                num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
 
                 /* zero only the new slots.*/
                 memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
-                yyg->yy_buffer_stack_max = nuto_alloc;
+                yyg->yy_buffer_stack_max = num_to_alloc;
         }
 }
 
 /** Setup the input buffer state to scan directly from a user-specified character buffer.
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
@@ -1937,16 +1920,16 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer  (char * base, yy_size_t  size ,
 
 /** Setup the input buffer state to scan a string. The next call to cmDependsFortran_yylex() will
  * scan from a @e copy of @a str.
- * @param str a NUL-terminated string to scan
+ * @param yystr a NUL-terminated string to scan
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  * @note If you want to scan bytes that may contain NUL values, then use
  *       cmDependsFortran_yy_scan_bytes() instead.
  */
-YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
+YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)
 {
-
-        return cmDependsFortran_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
+    
+        return cmDependsFortran_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
 }
 
 /** Setup the input buffer state to scan the given bytes. The next call to cmDependsFortran_yylex() will
@@ -1956,23 +1939,23 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char * yy_str , yyscan_
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  */
-YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
+YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * yybytes, int  _yybytes_len , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
         char *buf;
         yy_size_t n;
         int i;
-
+    
         /* Get memory for full buffer, including space for trailing EOB's. */
-        n = len + 2;
+        n = _yybytes_len + 2;
         buf = (char *) cmDependsFortran_yyalloc(n ,yyscanner );
         if ( ! buf )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_scan_bytes()" );
 
-        for ( i = 0; i < len; ++i )
-                buf[i] = bytes[i];
+        for ( i = 0; i < _yybytes_len; ++i )
+                buf[i] = yybytes[i];
 
-        buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;
+        buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
 
         b = cmDependsFortran_yy_scan_buffer(buf,n ,yyscanner);
         if ( ! b )
@@ -2030,10 +2013,10 @@ YY_EXTRA_TYPE cmDependsFortran_yyget_extra  (yyscan_t yyscanner)
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
 
@@ -2043,10 +2026,10 @@ int cmDependsFortran_yyget_lineno  (yyscan_t yyscanner)
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
 
@@ -2107,8 +2090,8 @@ void cmDependsFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner);
-
+           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner); 
+    
     yylineno = line_number;
 }
 
@@ -2122,8 +2105,8 @@ void cmDependsFortran_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner);
-
+           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner); 
+    
     yycolumn = column_no;
 }
 
@@ -2159,21 +2142,51 @@ void cmDependsFortran_yyset_debug (int  bdebug , yyscan_t yyscanner)
 
 /* Accessor methods for yylval and yylloc */
 
+/* User-visible API */
+
+/* cmDependsFortran_yylex_init is special because it creates the scanner itself, so it is
+ * the ONLY reentrant function that doesn't take the scanner as the last argument.
+ * That's why we explicitly handle the declaration, instead of using our macros.
+ */
+
+int cmDependsFortran_yylex_init(yyscan_t* ptr_yy_globals)
+
+{
+    if (ptr_yy_globals == NULL){
+        errno = EINVAL;
+        return 1;
+    }
+
+    *ptr_yy_globals = (yyscan_t) cmDependsFortran_yyalloc ( sizeof( struct yyguts_t ), NULL );
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
 static int yy_init_globals (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     /* Initialization is the same as for the non-reentrant scanner.
-       This function is called once per scanner lifetime. */
+     * This function is called from cmDependsFortran_yylex_destroy(), so don't allocate here.
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
@@ -2190,33 +2203,6 @@ static int yy_init_globals (yyscan_t yyscanner)
     return 0;
 }
 
-/* User-visible API */
-
-/* cmDependsFortran_yylex_init is special because it creates the scanner itself, so it is
- * the ONLY reentrant function that doesn't take the scanner as the last argument.
- * That's why we explicitly handle the declaration, instead of using our macros.
- */
-
-int cmDependsFortran_yylex_init(yyscan_t* ptr_yy_globals)
-
-{
-    if (ptr_yy_globals == NULL){
-        errno = EINVAL;
-        return 1;
-    }
-
-    *ptr_yy_globals = (yyscan_t) cmDependsFortran_yyalloc ( sizeof( struct yyguts_t ), NULL );
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
 /* cmDependsFortran_yylex_destroy is for both reentrant and non-reentrant scanners. */
 int cmDependsFortran_yylex_destroy  (yyscan_t yyscanner)
 {
@@ -2237,8 +2223,13 @@ int cmDependsFortran_yylex_destroy  (yyscan_t yyscanner)
         cmDependsFortran_yyfree(yyg->yy_start_stack ,yyscanner );
         yyg->yy_start_stack = NULL;
 
+    /* Reset the globals. This is important in a non-reentrant scanner so the next time
+     * cmDependsFortran_yylex() is called, initialization will occur. */
+    yy_init_globals( yyscanner);
+
     /* Destroy the main struct (reentrant only). */
     cmDependsFortran_yyfree ( yyscanner , yyscanner );
+    yyscanner = NULL;
     return 0;
 }
 
@@ -2250,7 +2241,6 @@ int cmDependsFortran_yylex_destroy  (yyscan_t yyscanner)
 static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , yyscan_t yyscanner)
 {
         register int i;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         for ( i = 0; i < n; ++i )
                 s1[i] = s2[i];
 }
@@ -2260,7 +2250,6 @@ static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , yyscan_t yysca
 static int yy_flex_strlen (yyconst char * s , yyscan_t yyscanner)
 {
         register int n;
-    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
         for ( n = 0; s[n]; ++n )
                 ;
 
@@ -2292,19 +2281,7 @@ void cmDependsFortran_yyfree (void * ptr , yyscan_t)
 
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
-#line 194 "cmDependsFortranLexer.in.l"
+#line 176 "cmDependsFortranLexer.in.l"
 
 
 
@@ -2315,3 +2292,4 @@ YY_BUFFER_STATE cmDependsFortranLexer_GetCurrentBuffer(yyscan_t yyscanner)
   struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
   return YY_CURRENT_BUFFER;
 }
+