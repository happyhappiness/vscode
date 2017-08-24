@@ -1,3 +1,6 @@
+#line 2 "cmDependsFortranLexer.cxx"
+
+#line 4 "cmDependsFortranLexer.cxx"
 
 #define  YY_INT_ALIGNED short int
 
@@ -40,7 +43,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t; 
+typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 #endif /* ! C99 */
@@ -161,8 +164,9 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
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
@@ -171,7 +175,8 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
         YY_LESS_LINENO(yyless_macro_arg);\
                 *yy_cp = yyg->yy_hold_char; \
                 YY_RESTORE_YY_MORE_OFFSET \
-                yyg->yy_c_buf_p = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
+                yyg->yy_c_buf_p \
+                  = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
                 YY_DO_BEFORE_ACTION; /* set up yytext again */ \
                 } \
         while ( 0 )
@@ -228,7 +233,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-    
+
         /* Whether to try to fill the input buffer when we reach the
          * end of it.
          */
@@ -245,8 +250,8 @@ struct yy_buffer_state
          * possible backing-up.
          *
          * When we actually see the EOF, we change the status to "new"
-         * (via cmDependsFortran_yyrestart()), so that the user can continue scanning by
-         * just pointing yyin at a new input file.
+         * (via cmDependsFortran_yyrestart()), so that the user can continue
+         * scanning by just pointing yyin at a new input file.
          */
 #define YY_BUFFER_EOF_PENDING 2
 
@@ -286,9 +291,9 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer (char *base,yy_size_t size ,yysc
 YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
 YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes (yyconst char *bytes,int len ,yyscan_t yyscanner );
 
-void *cmDependsFortran_yyalloc (yy_size_t );
-void *cmDependsFortran_yyrealloc (void *, yy_size_t  );
-void cmDependsFortran_yyfree (void * );
+void *cmDependsFortran_yyalloc (yy_size_t ,yyscan_t yyscanner );
+void *cmDependsFortran_yyrealloc (void *,yy_size_t ,yyscan_t yyscanner );
+void cmDependsFortran_yyfree (void * ,yyscan_t yyscanner );
 
 #define yy_new_buffer cmDependsFortran_yy_create_buffer
 
@@ -328,7 +333,7 @@ typedef int yy_state_type;
 static yy_state_type yy_get_previous_state (yyscan_t yyscanner );
 static yy_state_type yy_try_NUL_trans (yy_state_type current_state  ,yyscan_t yyscanner);
 static int yy_get_next_buffer (yyscan_t yyscanner );
-static void yy_fatal_error (yyconst char msg[]  );
+static void yy_fatal_error (yyconst char msg[] ,yyscan_t yyscanner );
 
 /* Done after the current pattern has been matched and before the
  * corresponding action - sets up yytext.
@@ -353,10 +358,10 @@ static yyconst flex_int16_t yy_accept[270] =
     {   0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        44,   39,   41,   40,   42,    1,   39,   39,   39,    2,
-       40,   39,   39,   39,   39,   39,   39,   40,    9,    8,
+       40,   39,   39,   39,   39,   39,   40,   39,    9,    8,
         9,    4,    3,   39,    0,   10,    0,   39,   39,   39,
        39,    0,   39,   39,   39,   39,    0,   37,   39,   39,
-       39,   39,   39,   39,    0,   11,    0,    0,    5,    0,
+       39,   39,   39,    0,   39,    0,   11,    0,    5,    0,
         0,    0,    0,   39,   39,   39,   27,   39,   39,    0,
         0,    0,    0,   39,   39,   39,   33,   39,   39,    0,
        38,    0,   39,   39,   39,   39,   39,   16,    0,    0,
@@ -423,46 +428,46 @@ static yyconst flex_int32_t yy_meta[29] =
 
 static yyconst flex_int16_t yy_base[276] =
     {   0,
-        0,   17,    0,   18,  335,   28,   32,   35,   29,   44,
-      337,    0,  339,  339,  333,  339,   53,   80,   47,  339,
-      339,  321,  311,  310,  308,  305,  107,  325,  339,  324,
-       54,  339,  339,    0,  325,  339,  119,  309,   39,   18,
-      303,  146,  307,   40,   45,  301,   64,   70,   72,  306,
-       49,  305,  303,  173,  317,  339,  314,   81,   85,  300,
-       68,   80,  294,  297,   68,  298,   79,  298,  296,  294,
-       83,   82,  288,  291,   96,  292,  100,  292,  290,  123,
-      339,  124,  283,  110,  284,  286,  275,    0,  297,  133,
-      339,  282,  114,  283,  129,  283,  281,  277,  277,  277,
-
-      274,  275,  275,  270,  272,  270,  129,  271,  133,  271,
-      269,  265,  265,  265,  262,  263,  263,  258,  260,  254,
-      260,  137,  252,  250,  245,  247,  250,  265,  249,  249,
-      249,  246,  247,  247,  242,  244,  238,    0,    0,  241,
-      240,  240,  229,  237,  235,  235,  235,  232,  233,  233,
-      228,  230,  224,    0,    0,  227,  226,  226,  215,  223,
-      225,  219,  216,  214,  210,  219,  218,  215,  215,  227,
-      208,  339,  339,  211,  210,  210,  199,  207,  207,    0,
-        0,  205,  206,    0,  199,  339,  339,  202,  201,  201,
-      190,  198,  198,    0,    0,  196,  197,    0,  192,  184,
-
-      184,  193,  191,  180,  189,  191,    0,    0,  187,  339,
-      339,  185,  186,  339,    0,    0,  184,  182,  339,  339,
-      166,  166,  339,    0,    0,  164,  153,  156,  154,  143,
-      145,  148,    0,  152,  339,  339,  339,  149,    0,  339,
-      339,  147,    0,  145,  143,  135,  137,  135,  135,  127,
-      339,  339,  123,    0,  112,  109,  104,    0,    0,  339,
-       92,  339,   77,   63,   60,   35,    0,  339,  339,  186,
-       47,  189,  192,  195,  198
+        0,    0,    0,    0,  332,   26,   29,   34,   43,   44,
+      334,    0,  336,  336,  330,  336,   53,   80,   28,  336,
+      336,  318,  308,  307,  305,  302,  322,  107,  336,  321,
+       54,  336,  336,    0,  322,  336,  119,  306,   13,   29,
+      300,  146,  304,   39,   42,  298,   61,   67,   73,  303,
+       52,  302,  300,  312,  173,  313,  336,   81,   85,  297,
+       53,   69,  291,  294,   15,  295,   79,  295,  293,  291,
+       68,   80,  285,  288,   81,  289,   99,  289,  287,  121,
+      336,  123,  280,  110,  281,  283,  272,    0,  294,  136,
+      336,  279,  107,  280,  112,  280,  278,  274,  274,  274,
+
+      271,  272,  272,  267,  269,  267,  114,  268,  127,  268,
+      266,  262,  262,  262,  259,  260,  260,  255,  257,  251,
+      257,  137,  249,  247,  242,  244,  247,  262,  246,  246,
+      246,  243,  244,  244,  239,  241,  235,    0,    0,  238,
+      237,  237,  226,  234,  232,  232,  232,  229,  230,  230,
+      225,  227,  221,    0,    0,  224,  223,  223,  212,  220,
+      222,  216,  213,  211,  207,  216,  215,  212,  212,  224,
+      205,  336,  336,  208,  207,  207,  196,  204,  204,    0,
+        0,  202,  203,    0,  196,  336,  336,  199,  198,  198,
+      187,  195,  195,    0,    0,  193,  194,    0,  189,  181,
+
+      181,  190,  188,  177,  186,  188,    0,    0,  184,  336,
+      336,  181,  168,  336,    0,    0,  165,  164,  336,  336,
+      162,  156,  336,    0,    0,  154,  143,  153,  151,  140,
+      142,  144,    0,  146,  336,  336,  336,  143,    0,  336,
+      336,  142,    0,  141,  138,  130,  133,  134,  134,  131,
+      336,  336,  127,    0,  100,   99,   91,    0,    0,  336,
+       90,  336,   88,   78,   62,   49,    0,  336,  336,  186,
+       48,  189,  192,  195,  198
     } ;
 
 static yyconst flex_int16_t yy_def[276] =
     {   0,
       269,    1,    1,    1,    1,    1,  270,  270,  270,  270,
       269,  271,  269,  269,  272,  269,  271,  271,  271,  269,
-      269,  271,  271,  271,  271,  271,  273,  269,  269,  269,
+      269,  271,  271,  271,  271,  271,  269,  273,  269,  269,
       269,  269,  269,  271,  272,  269,  269,  271,  271,  271,
       271,  269,  271,  271,  271,  271,  269,  269,  271,  271,
-      271,  271,  271,  273,  274,  269,  269,  269,  269,  269,
+      271,  271,  271,  269,  273,  274,  269,  269,  269,  269,
       269,  269,  269,  271,  271,  271,  271,  271,  271,  269,
       269,  269,  269,  271,  271,  271,  271,  271,  271,  269,
       269,  269,  271,  271,  271,  271,  271,  271,  269,  269,
@@ -489,92 +494,92 @@ static yyconst flex_int16_t yy_def[276] =
       269,  269,  269,  269,  269
     } ;
 
-static yyconst flex_int16_t yy_nxt[368] =
+static yyconst flex_int16_t yy_nxt[365] =
     {   0,
        12,   13,   14,   13,   13,   15,   16,   17,   18,   19,
        20,   12,   21,   22,   12,   12,   12,   23,   12,   24,
-       12,   25,   12,   12,   12,   12,   12,   26,   27,   27,
-       28,   30,   27,   27,   30,   33,   67,   30,   31,   27,
-       68,   31,   32,   27,   31,   32,   30,   34,   47,   48,
-       33,   47,  268,   31,   37,   58,   59,   37,   58,   65,
-       75,   66,   76,   77,   85,   47,   48,   78,   47,   38,
-       39,   80,   40,   82,   80,   86,   82,  267,  266,   81,
-       41,   42,   58,   59,   42,   58,   90,   99,   93,   90,
-       94,   83,  265,  100,   91,  102,   43,   44,   95,   45,
-
-      109,  103,   96,  107,  110,  108,  264,   46,   55,   56,
-       55,   55,   55,   55,  122,  113,  116,   55,  263,   55,
-       37,  114,  117,   37,   80,   82,  262,   80,   82,  123,
-      261,  124,   81,  130,   90,   60,   61,   90,   62,  131,
-      260,  122,   91,  120,  259,  133,   63,   42,  146,  149,
-       42,  134,  258,  257,  147,  150,  163,  256,  164,  255,
-      254,  253,   70,   71,  252,   72,  251,  250,  249,  248,
-      247,  246,  245,   73,   55,   56,   55,   55,   55,   55,
-      244,  243,  242,   55,  241,   55,   29,   29,   29,   35,
-       35,   35,   54,   54,   54,   55,   55,   55,  235,  240,
-
-      235,  239,  238,  237,  236,  234,  233,  232,  231,  230,
-      229,  228,  227,  226,  225,  224,  223,  222,  221,  220,
-      219,  218,  217,  216,  215,  214,  213,  212,  211,  210,
-      209,  208,  207,  206,  205,  204,  203,  202,  201,  200,
-      199,  198,  197,  196,  195,  194,  193,  192,  191,  190,
-      189,  188,  187,  186,  185,  184,  183,  182,  181,  180,
-      179,  178,  177,  176,  175,  174,  173,  172,  171,  170,
-      169,  168,  167,  166,  165,  162,  161,  160,  159,  158,
-      157,  156,  155,  154,  153,  152,  151,  148,  145,  144,
-      143,  142,  141,  140,  139,  138,  137,  136,  135,  132,
-
-      129,  128,  127,  126,  125,  121,  119,  118,  115,  112,
-      111,  106,  105,  104,  101,   98,   97,   92,   89,   56,
-       88,   87,   84,   79,   74,   69,   64,   36,   57,   57,
-       53,   52,   51,   50,   49,   36,  269,   28,   11,  269,
+       12,   25,   12,   12,   12,   12,   12,   26,   27,   47,
+       48,   30,   47,   65,   99,   66,   30,   28,   31,   32,
+      100,   28,   28,   31,   32,   30,   30,   67,   34,   33,
+       33,   68,   31,   31,   37,   58,   59,   37,   58,   75,
+       77,   76,   47,   48,   78,   47,  268,   85,   80,   38,
+       39,   80,   40,   93,   82,   94,   81,   82,   86,  267,
+       41,   42,   58,   59,   42,   58,   90,   95,  107,   90,
+      108,   96,   83,  266,   91,  102,   43,   44,  109,   45,
+
+      113,  103,  110,  265,  264,  263,  114,   46,   56,   57,
+       56,   56,   56,   56,  122,  116,  262,   56,  261,   56,
+       37,  117,   80,   37,   82,   80,  130,   82,  133,  123,
+       81,  124,  131,  146,  134,   60,   61,   90,   62,  147,
+       90,  122,  120,  149,  260,   91,   63,   42,  259,  150,
+       42,  258,  257,  256,  255,  254,  163,  253,  164,  252,
+      251,  250,   70,   71,  249,   72,  248,  247,  246,  245,
+      244,  243,  242,   73,   56,   57,   56,   56,   56,   56,
+      241,  240,  239,   56,  238,   56,   29,   29,   29,   35,
+       35,   35,   55,   55,   55,   56,   56,   56,  235,  237,
+
+      235,  236,  234,  233,  232,  231,  230,  229,  228,  227,
+      226,  225,  224,  223,  222,  221,  220,  219,  218,  217,
+      216,  215,  214,  213,  212,  211,  210,  209,  208,  207,
+      206,  205,  204,  203,  202,  201,  200,  199,  198,  197,
+      196,  195,  194,  193,  192,  191,  190,  189,  188,  187,
+      186,  185,  184,  183,  182,  181,  180,  179,  178,  177,
+      176,  175,  174,  173,  172,  171,  170,  169,  168,  167,
+      166,  165,  162,  161,  160,  159,  158,  157,  156,  155,
+      154,  153,  152,  151,  148,  145,  144,  143,  142,  141,
+      140,  139,  138,  137,  136,  135,  132,  129,  128,  127,
+
+      126,  125,  121,  119,  118,  115,  112,  111,  106,  105,
+      104,  101,   98,   97,   92,   57,   89,   88,   87,   84,
+       79,   74,   69,   64,   36,   54,   54,   53,   52,   51,
+       50,   49,   36,  269,   27,   11,  269,  269,  269,  269,
       269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
       269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  269
+      269,  269,  269,  269
     } ;
 
-static yyconst flex_int16_t yy_chk[368] =
+static yyconst flex_int16_t yy_chk[365] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,    1,    1,    2,    4,
-        6,    9,    2,    4,    7,    9,   40,    8,    9,    6,
-       40,    7,    7,    6,    8,    8,   10,  271,   19,   19,
-       10,   19,  266,   10,   17,   31,   31,   17,   31,   39,
-       44,   39,   44,   45,   51,   47,   47,   45,   47,   17,
-       17,   48,   17,   49,   48,   51,   49,  265,  264,   48,
-       17,   18,   58,   58,   18,   58,   59,   65,   61,   59,
-       61,   49,  263,   65,   59,   67,   18,   18,   62,   18,
-
-       72,   67,   62,   71,   72,   71,  261,   18,   27,   27,
-       27,   27,   27,   27,   84,   75,   77,   27,  257,   27,
-       37,   75,   77,   37,   80,   82,  256,   80,   82,   84,
-      255,   84,   80,   93,   90,   37,   37,   90,   37,   93,
-      253,  122,   90,   82,  250,   95,   37,   42,  107,  109,
-       42,   95,  249,  248,  107,  109,  122,  247,  122,  246,
-      245,  244,   42,   42,  242,   42,  238,  234,  232,  231,
-      230,  229,  228,   42,   54,   54,   54,   54,   54,   54,
-      227,  226,  222,   54,  221,   54,  270,  270,  270,  272,
-      272,  272,  273,  273,  273,  274,  274,  274,  275,  218,
-
-      275,  217,  213,  212,  209,  206,  205,  204,  203,  202,
-      201,  200,  199,  197,  196,  193,  192,  191,  190,  189,
-      188,  185,  183,  182,  179,  178,  177,  176,  175,  174,
-      171,  170,  169,  168,  167,  166,  165,  164,  163,  162,
-      161,  160,  159,  158,  157,  156,  153,  152,  151,  150,
-      149,  148,  147,  146,  145,  144,  143,  142,  141,  140,
-      137,  136,  135,  134,  133,  132,  131,  130,  129,  128,
-      127,  126,  125,  124,  123,  121,  120,  119,  118,  117,
-      116,  115,  114,  113,  112,  111,  110,  108,  106,  105,
-      104,  103,  102,  101,  100,   99,   98,   97,   96,   94,
-
-       92,   89,   87,   86,   85,   83,   79,   78,   76,   74,
-       73,   70,   69,   68,   66,   64,   63,   60,   57,   55,
-       53,   52,   50,   46,   43,   41,   38,   35,   30,   28,
-       26,   25,   24,   23,   22,   15,   11,    5,  269,  269,
+        1,    1,    1,    1,    1,    1,    1,    1,    6,   19,
+       19,    7,   19,   39,   65,   39,    8,    6,    7,    7,
+       65,    6,    6,    8,    8,    9,   10,   40,  271,    9,
+       10,   40,    9,   10,   17,   31,   31,   17,   31,   44,
+       45,   44,   47,   47,   45,   47,  266,   51,   48,   17,
+       17,   48,   17,   61,   49,   61,   48,   49,   51,  265,
+       17,   18,   58,   58,   18,   58,   59,   62,   71,   59,
+       71,   62,   49,  264,   59,   67,   18,   18,   72,   18,
+
+       75,   67,   72,  263,  261,  257,   75,   18,   28,   28,
+       28,   28,   28,   28,   84,   77,  256,   28,  255,   28,
+       37,   77,   80,   37,   82,   80,   93,   82,   95,   84,
+       80,   84,   93,  107,   95,   37,   37,   90,   37,  107,
+       90,  122,   82,  109,  253,   90,   37,   42,  250,  109,
+       42,  249,  248,  247,  246,  245,  122,  244,  122,  242,
+      238,  234,   42,   42,  232,   42,  231,  230,  229,  228,
+      227,  226,  222,   42,   55,   55,   55,   55,   55,   55,
+      221,  218,  217,   55,  213,   55,  270,  270,  270,  272,
+      272,  272,  273,  273,  273,  274,  274,  274,  275,  212,
+
+      275,  209,  206,  205,  204,  203,  202,  201,  200,  199,
+      197,  196,  193,  192,  191,  190,  189,  188,  185,  183,
+      182,  179,  178,  177,  176,  175,  174,  171,  170,  169,
+      168,  167,  166,  165,  164,  163,  162,  161,  160,  159,
+      158,  157,  156,  153,  152,  151,  150,  149,  148,  147,
+      146,  145,  144,  143,  142,  141,  140,  137,  136,  135,
+      134,  133,  132,  131,  130,  129,  128,  127,  126,  125,
+      124,  123,  121,  120,  119,  118,  117,  116,  115,  114,
+      113,  112,  111,  110,  108,  106,  105,  104,  103,  102,
+      101,  100,   99,   98,   97,   96,   94,   92,   89,   87,
+
+       86,   85,   83,   79,   78,   76,   74,   73,   70,   69,
+       68,   66,   64,   63,   60,   56,   54,   53,   52,   50,
+       46,   43,   41,   38,   35,   30,   27,   26,   25,   24,
+       23,   22,   15,   11,    5,  269,  269,  269,  269,  269,
       269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
       269,  269,  269,  269,  269,  269,  269,  269,  269,  269,
-      269,  269,  269,  269,  269,  269,  269
+      269,  269,  269,  269
     } ;
 
 /* The intent behind this definition is that it'll catch
@@ -584,6 +589,8 @@ static yyconst flex_int16_t yy_chk[368] =
 #define yymore() yymore_used_but_not_detected
 #define YY_MORE_ADJ 0
 #define YY_RESTORE_YY_MORE_OFFSET
+#line 1 "cmDependsFortranLexer.in.l"
+#line 2 "cmDependsFortranLexer.in.l"
 /*=========================================================================
 
   Program:   CMake - Cross-Platform Makefile Generator
@@ -649,6 +656,7 @@ Modify cmDependsFortranLexer.h:
 /*--------------------------------------------------------------------------*/
 
 
+#line 682 "cmDependsFortranLexer.cxx"
 
 #define INITIAL 0
 #define free_fmt 1
@@ -744,7 +752,7 @@ extern int cmDependsFortran_yywrap (yyscan_t yyscanner );
 #endif
 
     static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
-    
+
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -827,7 +835,7 @@ static int input (yyscan_t yyscanner );
 
 /* Report a fatal error. */
 #ifndef YY_FATAL_ERROR
-#define YY_FATAL_ERROR(msg) yy_fatal_error( msg )
+#define YY_FATAL_ERROR(msg) yy_fatal_error( msg , yyscanner)
 #endif
 
 /* end tables serialization structures and prototypes */
@@ -870,6 +878,10 @@ YY_DECL
         register int yy_act;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
+#line 98 "cmDependsFortranLexer.in.l"
+
+
+#line 907 "cmDependsFortranLexer.cxx"
 
         if ( yyg->yy_init )
                 {
@@ -897,7 +909,7 @@ YY_DECL
                 cmDependsFortran_yy_load_buffer_state(yyscanner );
                 }
 
-        for ( ;; )             /* loops until end-of-file is reached */
+        for(;;)             /* loops until end-of-file is reached */
                 {
                 yy_cp = yyg->yy_c_buf_p;
 
@@ -929,7 +941,7 @@ YY_DECL
                         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
                         ++yy_cp;
                         }
-                while ( yy_base[yy_current_state] != 339 );
+                while ( yy_base[yy_current_state] != 336 );
 
 yy_find_action:
                 yy_act = yy_accept[yy_current_state];
@@ -955,92 +967,112 @@ YY_DECL
 
 case 1:
 YY_RULE_SETUP
+#line 100 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_StringStart(yyextra);
   BEGIN(str_dq);
 }
         YY_BREAK
 case 2:
 YY_RULE_SETUP
+#line 105 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_StringStart(yyextra);
   BEGIN(str_sq);
 }
         YY_BREAK
 case 3:
+#line 111 "cmDependsFortranLexer.in.l"
 case 4:
 YY_RULE_SETUP
+#line 111 "cmDependsFortranLexer.in.l"
 {
   yylvalp->string = strdup(cmDependsFortranParser_StringEnd(yyextra));
   return STRING;
 }
 case 5:
 /* rule 5 can match eol */
+#line 117 "cmDependsFortranLexer.in.l"
 case 6:
 /* rule 6 can match eol */
 YY_RULE_SETUP
+#line 117 "cmDependsFortranLexer.in.l"
 /* Ignore (continued strings, free fmt) */
         YY_BREAK
 case 7:
 /* rule 7 can match eol */
 YY_RULE_SETUP
+#line 119 "cmDependsFortranLexer.in.l"
 /*Ignore (cont. strings, fixed fmt) */
         YY_BREAK
 case 8:
 /* rule 8 can match eol */
 YY_RULE_SETUP
+#line 121 "cmDependsFortranLexer.in.l"
 {
   unput ('\n');
   BEGIN(INITIAL);
   return UNTERMINATED_STRING;
 }
 case 9:
 YY_RULE_SETUP
+#line 127 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_StringAppend(yyextra, yytext[0]);
 }
         YY_BREAK
 case 10:
 /* rule 10 can match eol */
 YY_RULE_SETUP
+#line 131 "cmDependsFortranLexer.in.l"
 { return EOSTMT; } /* Treat comments like */
 case 11:
 /* rule 11 can match eol */
 YY_RULE_SETUP
+#line 132 "cmDependsFortranLexer.in.l"
 { return EOSTMT; } /* empty lines */
 case 12:
 YY_RULE_SETUP
+#line 134 "cmDependsFortranLexer.in.l"
 { return CPP_INCLUDE; }
 case 13:
 YY_RULE_SETUP
+#line 135 "cmDependsFortranLexer.in.l"
 { return F90PPR_INCLUDE; }
 case 14:
 YY_RULE_SETUP
+#line 136 "cmDependsFortranLexer.in.l"
 { return COCO_INCLUDE; }
 case 15:
 YY_RULE_SETUP
+#line 137 "cmDependsFortranLexer.in.l"
 { return F_INCLUDE; }
 case 16:
 YY_RULE_SETUP
+#line 138 "cmDependsFortranLexer.in.l"
 { return USE; }
 case 17:
 YY_RULE_SETUP
+#line 140 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_SetInInterface(yyextra, 0);
 }
         YY_BREAK
 case 18:
 YY_RULE_SETUP
+#line 143 "cmDependsFortranLexer.in.l"
 {
   cmDependsFortranParser_SetInInterface(yyextra, 1);
 }
         YY_BREAK
 case 19:
 YY_RULE_SETUP
+#line 147 "cmDependsFortranLexer.in.l"
 /* Ignore */
         YY_BREAK
 case 20:
 YY_RULE_SETUP
+#line 148 "cmDependsFortranLexer.in.l"
 {
  if(!cmDependsFortranParser_GetInInterface(yyextra))
    {
@@ -1050,77 +1082,101 @@ YY_RULE_SETUP
         YY_BREAK
 case 21:
 YY_RULE_SETUP
+#line 155 "cmDependsFortranLexer.in.l"
 { return CPP_DEFINE; }
 case 22:
 YY_RULE_SETUP
+#line 156 "cmDependsFortranLexer.in.l"
 { return F90PPR_DEFINE; }
 case 23:
 YY_RULE_SETUP
+#line 158 "cmDependsFortranLexer.in.l"
 { return CPP_UNDEF; }
 case 24:
 YY_RULE_SETUP
+#line 159 "cmDependsFortranLexer.in.l"
 { return F90PPR_UNDEF; }
 case 25:
 YY_RULE_SETUP
+#line 161 "cmDependsFortranLexer.in.l"
 { return CPP_IFDEF; }
 case 26:
 YY_RULE_SETUP
+#line 162 "cmDependsFortranLexer.in.l"
 { return CPP_IFNDEF; }
 case 27:
 YY_RULE_SETUP
+#line 163 "cmDependsFortranLexer.in.l"
 { return CPP_IF; }
 case 28:
 YY_RULE_SETUP
+#line 164 "cmDependsFortranLexer.in.l"
 { return CPP_ELIF; }
 case 29:
 YY_RULE_SETUP
+#line 165 "cmDependsFortranLexer.in.l"
 { return CPP_ELSE; }
 case 30:
 YY_RULE_SETUP
+#line 166 "cmDependsFortranLexer.in.l"
 { return CPP_ENDIF; }
 case 31:
 YY_RULE_SETUP
+#line 168 "cmDependsFortranLexer.in.l"
 { return F90PPR_IFDEF; }
 case 32:
 YY_RULE_SETUP
+#line 169 "cmDependsFortranLexer.in.l"
 { return F90PPR_IFNDEF; }
 case 33:
 YY_RULE_SETUP
+#line 170 "cmDependsFortranLexer.in.l"
 { return F90PPR_IF; }
 case 34:
 YY_RULE_SETUP
+#line 171 "cmDependsFortranLexer.in.l"
 { return F90PPR_ELIF; }
 case 35:
 YY_RULE_SETUP
+#line 172 "cmDependsFortranLexer.in.l"
 { return F90PPR_ELSE; }
 case 36:
 YY_RULE_SETUP
+#line 173 "cmDependsFortranLexer.in.l"
 { return F90PPR_ENDIF; }
 case 37:
 /* rule 37 can match eol */
+#line 176 "cmDependsFortranLexer.in.l"
 case 38:
 /* rule 38 can match eol */
 YY_RULE_SETUP
+#line 176 "cmDependsFortranLexer.in.l"
 /* Ignore */
         YY_BREAK
 case 39:
 YY_RULE_SETUP
+#line 179 "cmDependsFortranLexer.in.l"
 { yylvalp->string = strdup(yytext); return WORD; }
 case 40:
 /* rule 40 can match eol */
 YY_RULE_SETUP
+#line 181 "cmDependsFortranLexer.in.l"
 { return EOSTMT; }
 case 41:
 YY_RULE_SETUP
+#line 183 "cmDependsFortranLexer.in.l"
 /* Ignore */
+        YY_BREAK
 case 42:
 YY_RULE_SETUP
+#line 185 "cmDependsFortranLexer.in.l"
 { return *yytext; }
 case YY_STATE_EOF(INITIAL):
 case YY_STATE_EOF(free_fmt):
 case YY_STATE_EOF(fixed_fmt):
 case YY_STATE_EOF(str_sq):
 case YY_STATE_EOF(str_dq):
+#line 187 "cmDependsFortranLexer.in.l"
 {
  if(!cmDependsFortranParser_FilePop(yyextra))
    {
@@ -1130,8 +1186,10 @@ case YY_STATE_EOF(str_dq):
         YY_BREAK
 case 43:
 YY_RULE_SETUP
+#line 194 "cmDependsFortranLexer.in.l"
 ECHO;
         YY_BREAK
+#line 1243 "cmDependsFortranLexer.cxx"
 
         case YY_END_OF_BUFFER:
                 {
@@ -1316,10 +1374,10 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
         else
                 {
-                        size_t num_to_read =
+                        size_t nuto_read =
                         YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
 
-                while ( num_to_read <= 0 )
+                while ( nuto_read <= 0 )
                         { /* Not enough room in the buffer - grow it. */
 
                         /* just a shorter name for the current buffer */
@@ -1339,7 +1397,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                                 b->yy_ch_buf = (char *)
                                         /* Include room in for 2 EOB chars. */
-                                        cmDependsFortran_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2  );
+                                        cmDependsFortran_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
                                 }
                         else
                                 /* Can't grow it, we don't own it. */
@@ -1351,17 +1409,17 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                         yyg->yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];
 
-                        num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
+                        nuto_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
                                                 number_to_move - 1;
 
                         }
 
-                if ( num_to_read > YY_READ_BUF_SIZE )
-                        num_to_read = YY_READ_BUF_SIZE;
+                if ( nuto_read > YY_READ_BUF_SIZE )
+                        nuto_read = YY_READ_BUF_SIZE;
 
                 /* Read in more data. */
                 YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
-                        yyg->yy_n_chars, num_to_read );
+                        yyg->yy_n_chars, nuto_read );
 
                 YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
                 }
@@ -1642,8 +1700,8 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmDependsFortran_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-    
-        b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) );
+
+        b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_create_buffer()" );
 
@@ -1652,7 +1710,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
         /* yy_ch_buf has to be 2 characters longer than the size given because
          * we need to put in 2 end-of-buffer characters.
          */
-        b->yy_ch_buf = (char *) cmDependsFortran_yyalloc(b->yy_buf_size + 2  );
+        b->yy_ch_buf = (char *) cmDependsFortran_yyalloc(b->yy_buf_size + 2 ,yyscanner );
         if ( ! b->yy_ch_buf )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_create_buffer()" );
 
@@ -1678,15 +1736,15 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
                 YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;
 
         if ( b->yy_is_our_buffer )
-                cmDependsFortran_yyfree((void *) b->yy_ch_buf );
+                cmDependsFortran_yyfree((void *) b->yy_ch_buf ,yyscanner );
 
-        cmDependsFortran_yyfree((void *) b  );
+        cmDependsFortran_yyfree((void *) b ,yyscanner );
 }
 
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-    
+
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmDependsFortran_yyrestart() or at EOF.
@@ -1712,7 +1770,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-    
+
         errno = oerrno;
 }
 
@@ -1803,7 +1861,7 @@ void cmDependsFortran_yypop_buffer_state (yyscan_t yyscanner)
  */
 static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
 {
-        int num_to_alloc;
+        int nuto_alloc;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         if (!yyg->yy_buffer_stack) {
@@ -1812,14 +1870,15 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                  * scanner will even need a stack. We use 2 instead of 1 to avoid an
                  * immediate realloc on the next call.
          */
-                num_to_alloc = 1;
+                nuto_alloc = 1;
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyalloc
-                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
-                                                                );
+                                                                (nuto_alloc * sizeof(struct yy_buffer_state*)
+                                                                , yyscanner);
                 
-                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
+                memset(yyg->yy_buffer_stack, 0, 
+                       nuto_alloc * sizeof(struct yy_buffer_state*));
                                 
-                yyg->yy_buffer_stack_max = num_to_alloc;
+                yyg->yy_buffer_stack_max = nuto_alloc;
                 yyg->yy_buffer_stack_top = 0;
                 return;
         }
@@ -1829,35 +1888,35 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                 /* Increase the buffer to prepare for a possible push. */
                 int grow_size = 8 /* arbitrary grow size */;
 
-                num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
+                nuto_alloc = yyg->yy_buffer_stack_max + grow_size;
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyrealloc
                                                                 (yyg->yy_buffer_stack,
-                                                                num_to_alloc * sizeof(struct yy_buffer_state*)
-                                                                );
+                                                                nuto_alloc * sizeof(struct yy_buffer_state*)
+                                                                , yyscanner);
 
                 /* zero only the new slots.*/
                 memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
-                yyg->yy_buffer_stack_max = num_to_alloc;
+                yyg->yy_buffer_stack_max = nuto_alloc;
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
                 /* They forgot to leave room for the EOB's. */
                 return 0;
 
-        b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state )  );
+        b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_scan_buffer()" );
 
@@ -1879,15 +1938,14 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer  (char * base, yy_size_t  size ,
 /** Setup the input buffer state to scan a string. The next call to cmDependsFortran_yylex() will
  * scan from a @e copy of @a str.
  * @param str a NUL-terminated string to scan
- * @param yy_str a NUL-terminated string to scan
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  * @note If you want to scan bytes that may contain NUL values, then use
  *       cmDependsFortran_yy_scan_bytes() instead.
  */
 YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
 {
-    
+
         return cmDependsFortran_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
 }
 
@@ -1904,10 +1962,10 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * bytes, int  len
         char *buf;
         yy_size_t n;
         int i;
-    
+
         /* Get memory for full buffer, including space for trailing EOB's. */
         n = len + 2;
-        buf = (char *) cmDependsFortran_yyalloc(n  );
+        buf = (char *) cmDependsFortran_yyalloc(n ,yyscanner );
         if ( ! buf )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_scan_bytes()" );
 
@@ -1932,7 +1990,7 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * bytes, int  len
 #define YY_EXIT_FAILURE 2
 #endif
 
-static void yy_fatal_error (yyconst char* msg )
+static void yy_fatal_error (yyconst char* msg , yyscan_t)
 {
         (void) fprintf( stderr, "%s\n", msg );
         exit( YY_EXIT_FAILURE );
@@ -1972,10 +2030,10 @@ YY_EXTRA_TYPE cmDependsFortran_yyget_extra  (yyscan_t yyscanner)
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
 
@@ -1985,10 +2043,10 @@ int cmDependsFortran_yyget_lineno  (yyscan_t yyscanner)
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
 
@@ -2049,8 +2107,8 @@ void cmDependsFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" ); 
-    
+           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner);
+
     yylineno = line_number;
 }
 
@@ -2064,8 +2122,8 @@ void cmDependsFortran_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" ); 
-    
+           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner);
+
     yycolumn = column_no;
 }
 
@@ -2147,7 +2205,7 @@ int cmDependsFortran_yylex_init(yyscan_t* ptr_yy_globals)
         return 1;
     }
 
-    *ptr_yy_globals = (yyscan_t) cmDependsFortran_yyalloc ( sizeof( struct yyguts_t ) );
+    *ptr_yy_globals = (yyscan_t) cmDependsFortran_yyalloc ( sizeof( struct yyguts_t ), NULL );
 
     if (*ptr_yy_globals == NULL){
         errno = ENOMEM;
@@ -2172,15 +2230,15 @@ int cmDependsFortran_yylex_destroy  (yyscan_t yyscanner)
         }
 
         /* Destroy the stack itself. */
-        cmDependsFortran_yyfree(yyg->yy_buffer_stack );
+        cmDependsFortran_yyfree(yyg->yy_buffer_stack ,yyscanner);
         yyg->yy_buffer_stack = NULL;
 
     /* Destroy the start condition stack. */
-        cmDependsFortran_yyfree(yyg->yy_start_stack  );
+        cmDependsFortran_yyfree(yyg->yy_start_stack ,yyscanner );
         yyg->yy_start_stack = NULL;
 
     /* Destroy the main struct (reentrant only). */
-    cmDependsFortran_yyfree ( yyscanner  );
+    cmDependsFortran_yyfree ( yyscanner , yyscanner );
     return 0;
 }
 
@@ -2210,12 +2268,12 @@ static int yy_flex_strlen (yyconst char * s , yyscan_t yyscanner)
 }
 #endif
 
-void *cmDependsFortran_yyalloc (yy_size_t  size )
+void *cmDependsFortran_yyalloc (yy_size_t  size , yyscan_t)
 {
         return (void *) malloc( size );
 }
 
-void *cmDependsFortran_yyrealloc  (void * ptr, yy_size_t  size )
+void *cmDependsFortran_yyrealloc  (void * ptr, yy_size_t  size , yyscan_t)
 {
         /* The cast to (char *) in the following accommodates both
          * implementations that use char* generic pointers, and those
@@ -2227,7 +2285,7 @@ void *cmDependsFortran_yyrealloc  (void * ptr, yy_size_t  size )
         return (void *) realloc( (char *) ptr, size );
 }
 
-void cmDependsFortran_yyfree (void * ptr )
+void cmDependsFortran_yyfree (void * ptr , yyscan_t)
 {
         free( (char *) ptr );   /* see cmDependsFortran_yyrealloc() for (char *) cast */
 }
@@ -2246,6 +2304,7 @@ void cmDependsFortran_yyfree (void * ptr )
 #undef YY_DECL_IS_OURS
 #undef YY_DECL
 #endif
+#line 194 "cmDependsFortranLexer.in.l"
 
 
 
@@ -2256,4 +2315,3 @@ YY_BUFFER_STATE cmDependsFortranLexer_GetCurrentBuffer(yyscan_t yyscanner)
   struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
   return YY_CURRENT_BUFFER;
 }
-