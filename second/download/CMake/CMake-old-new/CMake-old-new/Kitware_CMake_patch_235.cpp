@@ -1,6 +1,6 @@
 /*============================================================================
   CMake - Cross Platform Makefile Generator
-  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
+  Copyright 2000-2015 Kitware, Inc., Insight Software Consortium
 
   Distributed under the OSI-approved BSD License (the "License");
   see accompanying file Copyright.txt for details.
@@ -20,7 +20,7 @@
 #define FLEX_SCANNER
 #define YY_FLEX_MAJOR_VERSION 2
 #define YY_FLEX_MINOR_VERSION 5
-#define YY_FLEX_SUBMINOR_VERSION 35
+#define YY_FLEX_SUBMINOR_VERSION 39
 #if YY_FLEX_SUBMINOR_VERSION > 0
 #define FLEX_BETA
 #endif
@@ -190,11 +190,17 @@ typedef void* yyscan_t;
 typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #endif
 
+#ifndef YY_TYPEDEF_YY_SIZE_T
+#define YY_TYPEDEF_YY_SIZE_T
+typedef size_t yy_size_t;
+#endif
+
 #define EOB_ACT_CONTINUE_SCAN 0
 #define EOB_ACT_END_OF_FILE 1
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
+    #define YY_LINENO_REWIND_TO(ptr)
 
 /* Return all but the first "n" matched characters back to the input stream. */
 #define yyless(n) \
@@ -212,11 +218,6 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 
 #define unput(c) yyunput( c, yyg->yytext_ptr , yyscanner )
 
-#ifndef YY_TYPEDEF_YY_SIZE_T
-#define YY_TYPEDEF_YY_SIZE_T
-typedef size_t yy_size_t;
-#endif
-
 #ifndef YY_STRUCT_YY_BUFFER_STATE
 #define YY_STRUCT_YY_BUFFER_STATE
 struct yy_buffer_state
@@ -234,7 +235,7 @@ struct yy_buffer_state
         /* Number of characters read into yy_ch_buf, not including EOB
          * characters.
          */
-        int yy_n_chars;
+        yy_size_t yy_n_chars;
 
         /* Whether we "own" the buffer - i.e., we know we created it,
          * and can realloc() it to grow it, and should free() it to
@@ -313,7 +314,7 @@ static void cmFortran_yy_init_buffer (YY_BUFFER_STATE b,FILE *file ,yyscan_t yys
 
 YY_BUFFER_STATE cmFortran_yy_scan_buffer (char *base,yy_size_t size ,yyscan_t yyscanner );
 YY_BUFFER_STATE cmFortran_yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
-YY_BUFFER_STATE cmFortran_yy_scan_bytes (yyconst char *bytes,int len ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmFortran_yy_scan_bytes (yyconst char *bytes,yy_size_t len ,yyscan_t yyscanner );
 
 void *cmFortran_yyalloc (yy_size_t ,yyscan_t yyscanner );
 void *cmFortran_yyrealloc (void *,yy_size_t ,yyscan_t yyscanner );
@@ -345,7 +346,7 @@ void cmFortran_yyfree (void * ,yyscan_t yyscanner );
 
 /* Begin user sect3 */
 
-#define cmFortran_yywrap(n) 1
+#define cmFortran_yywrap(yyscanner) 1
 #define YY_SKIP_YYWRAP
 
 typedef unsigned char YY_CHAR;
@@ -369,35 +370,36 @@ static void yy_fatal_error (yyconst char msg[] ,yyscan_t yyscanner );
         *yy_cp = '\0'; \
         yyg->yy_c_buf_p = yy_cp;
 
-#define YY_NUM_RULES 44
-#define YY_END_OF_BUFFER 45
+#define YY_NUM_RULES 45
+#define YY_END_OF_BUFFER 46
 /* This struct is not used in this scanner,
    but its presence is necessary. */
 struct yy_trans_info
         {
         flex_int32_t yy_verify;
         flex_int32_t yy_nxt;
         };
-static yyconst flex_int16_t yy_accept[165] =
+static yyconst flex_int16_t yy_accept[173] =
     {   0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-       45,   39,   41,   40,   43,    1,   39,   32,    2,   34,
-       39,   40,   37,   39,   38,   39,   38,   41,   39,   40,
-       39,   38,    9,    8,    9,    4,    3,   39,    0,   10,
-        0,    0,    0,    0,    0,   32,   32,   33,   35,   37,
-       39,   38,    0,   42,   38,    0,    0,    0,    0,    0,
-        0,    0,    0,   39,    0,   11,   38,    0,    0,    5,
-        0,    0,    0,   28,    0,    0,   32,   32,   32,   32,
-        0,    0,    0,    0,    0,   22,    0,    0,    0,    0,
-        0,    6,    0,    0,    0,    0,    0,    0,    0,    0,
+       46,   40,   42,   41,   44,    1,   40,   33,    2,   35,
+       40,   41,   38,   40,   39,   40,   39,   42,   40,   41,
+       40,   39,    9,    8,    9,    4,    3,   40,    0,   10,
+        0,    0,    0,    0,    0,   33,   33,   34,   36,   38,
+       40,   39,    0,   43,   39,    0,    0,    0,   12,    0,
+        0,    0,    0,    0,    0,   40,    0,   11,   39,    0,
+        0,    5,    0,    0,    0,   29,    0,    0,   33,   33,
+       33,   33,    0,    0,   12,   12,    0,    0,    0,   23,
+        0,    0,    0,    0,    0,    0,    6,    0,    0,    0,
 
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-        0,    0,   29,   30,    0,    0,    0,    0,    0,    0,
-        0,   23,   24,    0,    0,    0,    0,    0,    0,    0,
-        0,   31,   26,    0,    0,   19,    0,    0,   25,   20,
-        0,    0,   18,    0,    0,   17,   27,    0,    0,   16,
-       21,    0,    7,   36,    7,   14,    0,   13,   15,    0,
-        0,    0,   12,    0
+        0,    0,    0,    0,    0,    0,    0,    0,   30,   31,
+        0,    0,    0,    0,    0,    0,    0,   24,   25,    0,
+        0,    0,    0,    0,    0,    0,    0,    0,   32,   27,
+        0,    0,   20,    0,    0,   26,   21,    0,    0,    0,
+       19,    0,    0,   18,   28,    0,    0,   17,   22,    0,
+        7,   37,    7,   15,    0,   14,   16,    0,    0,    0,
+       13,    0
     } ;
 
 static yyconst flex_int32_t yy_ec[256] =
@@ -441,178 +443,186 @@ static yyconst flex_int32_t yy_meta[42] =
         7
     } ;
 
-static yyconst flex_int16_t yy_base[174] =
+static yyconst flex_int16_t yy_base[182] =
     {   0,
-        0,   40,    0,   41,  188,   48,   44,   54,   56,   65,
-      186,    0,  505,  505,  171,  505,   81,   74,  505,  505,
-      158,  505,  151,  137,    0,   85,  122,   87,  153,  145,
-      194,  226,  505,  143,   91,  505,  505,    0,  142,  505,
-      266,   34,   70,   74,   34,  122,  141,  505,    0,  505,
-      112,    0,   98,  505,    0,  154,  306,    0,   43,  133,
-      139,   46,  130,  347,  130,  505,    0,  121,  163,  179,
-      104,  156,  129,  176,  147,  178,  214,  267,  273,  292,
-      279,  179,  249,  280,  257,  265,  288,  289,  116,  107,
-      317,  505,  287,  289,  291,  302,  307,  310,  307,  311,
-
-      316,  326,  329,  333,  332,  336,  347,  345,  349,  101,
-       86,  346,  505,  505,  350,  351,  353,  350,  357,  362,
-      362,  505,  505,  367,  369,  371,  366,  372,   56,   47,
-      374,  505,  505,  374,  379,  505,  374,  387,  505,  505,
-      387,  391,  505,  117,    0,  505,  505,  392,  394,  505,
-      505,  394,  505,  505,  505,  505,  395,  419,  505,  429,
-        0,   25,  505,  505,  446,  453,  459,  462,  469,  476,
-      483,  490,  497
+        0,   40,    0,   41,  220,   48,   44,   54,   56,   65,
+      220,    0,  535,  535,  216,  535,   81,   74,  535,  535,
+      186,  535,  153,  145,    0,   85,  122,   87,  154,  155,
+      195,  227,  535,  147,   91,  535,  535,    0,  147,  535,
+      267,   34,   70,   74,   34,  122,  141,  535,    0,  535,
+      112,    0,   98,  535,    0,  156,  307,    0,  143,   43,
+      155,  151,   48,  101,  130,  348,  130,  535,    0,  121,
+      197,  165,  172,  244,  182,  183,  191,  248,  273,  293,
+      308,  314,  321,  246,  275,  216,  269,  299,  304,  327,
+      307,  304,  312,  116,  107,  367,  535,  327,  334,  347,
+
+      347,  350,  352,  349,  354,  359,  357,  363,  366,  365,
+      369,  372,  369,  373,  374,  101,   86,  372,  535,  535,
+      378,  380,  386,  382,  388,  388,  389,  535,  535,  393,
+      394,  396,  392,  430,  400,   56,   47,  403,  535,  535,
+      409,  414,  535,  409,  416,  535,  535,  416,  419,  441,
+      535,  117,    0,  535,  535,  423,  426,  535,  535,  430,
+      535,  535,  535,  535,  432,  457,  535,  459,    0,   25,
+      535,  535,  476,  483,  489,  492,  499,  506,  513,  520,
+      527
     } ;
 
-static yyconst flex_int16_t yy_def[174] =
+static yyconst flex_int16_t yy_def[182] =
     {   0,
-      164,    1,    1,    1,    1,    1,  165,  165,  165,  165,
-      164,  166,  164,  164,  167,  164,  166,  164,  164,  164,
-      166,  164,  164,  166,  168,  166,  168,  164,  166,  164,
-      169,  164,  164,  164,  164,  164,  164,  166,  167,  164,
-      164,  164,  164,  164,  164,  164,  170,  164,  166,  164,
-      166,  168,  164,  164,   27,  164,  164,   57,  164,  164,
-      164,  164,  164,  169,  169,  164,   32,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  170,  170,  170,  170,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  171,  172,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      173,  173,  164,    0,  164,  164,  164,  164,  164,  164,
-      164,  164,  164
+      172,    1,    1,    1,    1,    1,  173,  173,  173,  173,
+      172,  174,  172,  172,  175,  172,  174,  172,  172,  172,
+      174,  172,  172,  174,  176,  174,  176,  172,  172,  172,
+      177,  172,  172,  172,  172,  172,  172,  174,  175,  172,
+      172,  172,  172,  172,  172,  172,  178,  172,  174,  172,
+      174,  176,  172,  172,   27,  172,  172,   57,  174,  172,
+      172,  172,  172,  172,  172,  177,  177,  172,   32,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  178,  178,
+      178,  178,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  179,  180,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  181,  181,
+      172,    0,  172,  172,  172,  172,  172,  172,  172,  172,
+      172
     } ;
 
-static yyconst flex_int16_t yy_nxt[547] =
+static yyconst flex_int16_t yy_nxt[577] =
     {   0,
        12,   13,   14,   13,   13,   15,   16,   12,   17,   18,
        19,   12,   20,   12,   21,   22,   12,   23,   12,   24,
        25,   25,   25,   25,   25,   25,   25,   25,   25,   25,
        26,   27,   25,   25,   25,   25,   25,   25,   25,   25,
-       25,   28,   28,  163,   28,   28,   34,   29,   29,   28,
-       30,  145,   28,   35,   36,   29,   34,   71,   34,   31,
-      144,   76,   37,   35,   36,   35,   83,   34,   71,   32,
-       32,   37,   76,   88,   35,   46,   46,   83,   46,   47,
-       32,   32,   41,   48,   88,   41,   53,   54,   56,   53,
-      130,   56,   69,   70,   57,   69,   72,   73,   74,   53,
-
-       54,   75,   53,   42,   43,  129,   44,   72,   73,   74,
-       45,  111,   75,   81,   42,   43,   81,   44,  154,  154,
-      110,   45,   38,   46,   46,   90,   46,   47,   93,   38,
-       38,   48,   66,   38,   89,   55,   38,   82,   38,   93,
-       38,   38,   78,   46,   40,   78,   79,   68,   82,   63,
-       80,   96,   38,   55,   58,   56,   51,   58,   56,   84,
-       85,   57,   96,   86,   69,   70,   87,   69,   99,   50,
-       84,   85,   49,   40,   86,   59,   60,   87,   61,   99,
-       91,   94,   62,   91,   95,  164,   59,   60,   92,   61,
-       30,  164,   94,   62,   64,   95,   66,  164,   97,  164,
-
-      100,   64,   64,   98,  164,   64,  101,   64,   64,   97,
-       64,  100,   64,   64,   98,   78,   46,  101,   78,   79,
-      164,  164,  164,   80,   64,   64,   65,   65,   66,   65,
-       65,   65,   65,   65,   65,   65,   65,   65,   65,   67,
-       65,   65,   65,   65,   65,   65,   67,   67,   67,   67,
-       67,   67,   67,   67,   67,   67,   65,   67,   67,   67,
-       67,   67,   67,   67,   67,   67,   67,   41,   78,   46,
-       41,   78,   79,  102,   78,   46,   80,   78,   79,  105,
-       81,  164,   80,   81,  102,  164,  164,  106,   42,   43,
-      105,   44,  107,   78,   46,   45,   78,   79,  106,   42,
-
-       43,   80,   44,  107,   82,  103,   45,   58,  104,  108,
-       58,  109,  112,  113,  114,   82,  103,  164,   91,  104,
-      108,   91,  109,  112,  113,  114,   92,  115,   59,   60,
-      116,   61,  117,  118,  119,   62,  164,  120,  115,   59,
-       60,  116,   61,  117,  118,  119,   62,   64,  120,   66,
-      164,  121,  164,  122,   64,   64,  123,  124,   64,  125,
-       64,   64,  121,   64,  122,   64,   64,  123,  124,  126,
-      125,  127,  128,  131,  132,  133,  134,   64,   64,  135,
-      126,  136,  127,  128,  131,  132,  133,  134,  137,  138,
-      135,  139,  136,  140,  141,  142,  143,  146,  147,  137,
-
-      138,  148,  139,  149,  140,  141,  142,  143,  146,  147,
-      150,  151,  148,  152,  149,  156,  157,  158,  159,  164,
-      160,  150,  151,  160,  152,  164,  156,  157,  158,  159,
-      160,  164,  164,  160,  164,  161,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  161,   33,   33,   33,   33,
-       33,   33,   33,   38,  164,  164,  164,   38,   38,   39,
-       39,   39,   39,   39,   39,   39,   52,  164,   52,   65,
-       65,   65,   65,   65,   65,   65,   77,   77,   77,   77,
-       77,   77,   77,  153,  153,  153,  164,  153,  153,  153,
-      155,  164,  155,  164,  155,  155,  155,  162,  162,  162,
-
-      162,  162,  164,  162,   11,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164
+       25,   28,   28,  171,   28,   28,   34,   29,   29,   28,
+       30,  153,   28,   35,   36,   29,   34,   73,   34,   31,
+      152,   78,   37,   35,   36,   35,   87,   34,   73,   32,
+       32,   37,   78,   92,   35,   46,   46,   87,   46,   47,
+       32,   32,   41,   48,   92,   41,   53,   54,   56,   53,
+      137,   56,   71,   72,   57,   71,   74,   75,   76,   53,
+
+       54,   77,   53,   42,   43,  136,   44,   74,   75,   76,
+       45,  117,   77,   83,   42,   43,   83,   44,  162,  162,
+      116,   45,   38,   46,   46,   95,   46,   47,   93,   38,
+       38,   48,   68,   38,   94,   55,   38,   84,   38,   93,
+       38,   38,   80,   46,   86,   80,   81,   86,   84,   40,
+       82,   70,   38,   55,   38,   58,   59,   56,   58,   65,
+       56,   38,   38,   57,   51,   38,   96,   59,   38,   96,
+       38,   50,   38,   38,   97,   90,   60,   61,   91,   62,
+       63,   88,   89,   64,   38,   38,   90,   60,   61,   91,
+       62,   63,   88,   89,   64,   66,   98,   68,   71,   72,
+
+       49,   71,   66,   66,  101,  102,   66,   98,   66,   66,
+      103,   66,  104,   66,   66,  101,  102,   86,   40,  172,
+       86,  103,   30,  104,  172,   66,   66,   67,   67,   68,
+       67,   67,   67,   67,   67,   67,   67,   67,   67,   67,
+       69,   67,   67,   67,   67,   67,   67,   69,   69,   69,
+       69,   69,   69,   69,   69,   69,   69,   67,   69,   69,
+       69,   69,   69,   69,   69,   69,   69,   69,   41,   99,
+      105,   41,  100,  106,   80,   46,   86,   80,   81,   86,
+       99,  105,   82,  100,  106,  172,  172,  172,   85,   42,
+       43,  172,   44,  107,   80,   46,   45,   80,   81,  172,
+
+       42,   43,   82,   44,  107,  172,  172,   45,   58,   80,
+       46,   58,   80,   81,  172,   80,   46,   82,   80,   81,
+       85,  172,   83,   82,  108,   83,  110,  109,  113,   60,
+       61,  114,   62,   63,  115,  108,   64,  110,  109,  113,
+       60,   61,  114,   62,   63,  115,   84,   64,   66,  111,
+       68,  172,  118,  172,  112,   66,   66,   84,  119,   66,
+      111,   66,   66,  118,   66,  112,   66,   66,   96,  119,
+      120,   96,  121,  122,  123,  124,   97,  125,   66,   66,
+      126,  120,  127,  121,  122,  123,  124,  128,  125,  129,
+      130,  126,  131,  127,  132,  133,  134,  135,  128,  138,
+
+      129,  130,  139,  131,  140,  132,  133,  134,  135,  141,
+      138,  142,  143,  139,  144,  140,  145,  146,  147,  148,
+      141,  149,  142,  143,  151,  144,  154,  145,  146,  147,
+      148,  150,  149,  155,  150,  151,  156,  154,  157,  158,
+      159,  160,  150,   85,  155,  150,  164,  156,  165,  157,
+      158,  159,  160,  166,   85,  167,  172,  164,  168,  165,
+      168,  168,  172,  168,  166,  172,  167,  172,  172,  172,
+      172,  172,  172,  169,  172,  169,   33,   33,   33,   33,
+       33,   33,   33,   38,  172,  172,  172,   38,   38,   39,
+       39,   39,   39,   39,   39,   39,   52,  172,   52,   67,
+
+       67,   67,   67,   67,   67,   67,   79,   79,   79,   79,
+       79,   79,   79,  161,  161,  161,  172,  161,  161,  161,
+      163,  172,  163,  172,  163,  163,  163,  170,  170,  170,
+      170,  170,  172,  170,   11,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172
     } ;
 
-static yyconst flex_int16_t yy_chk[547] =
+static yyconst flex_int16_t yy_chk[577] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
-        1,    2,    4,  162,    2,    4,    7,    2,    4,    6,
-        6,  130,    6,    7,    7,    6,    8,   42,    9,    6,
-      129,   45,    9,    8,    8,    9,   59,   10,   42,    6,
-        6,   10,   45,   62,   10,   18,   18,   59,   18,   18,
-        6,    6,   17,   18,   62,   17,   26,   26,   28,   26,
-      111,   28,   35,   35,   28,   35,   43,   43,   44,   53,
-
-       53,   44,   53,   17,   17,  110,   17,   43,   43,   44,
-       17,   90,   44,   51,   17,   17,   51,   17,  144,  144,
-       89,   17,   27,   46,   46,   68,   46,   46,   71,   27,
-       27,   46,   65,   27,   63,   27,   27,   51,   27,   71,
-       27,   27,   47,   47,   39,   47,   47,   34,   51,   30,
-       47,   73,   27,   27,   29,   56,   24,   29,   56,   60,
-       60,   56,   73,   61,   69,   69,   61,   69,   75,   23,
-       60,   60,   21,   15,   61,   29,   29,   61,   29,   75,
-       70,   72,   29,   70,   72,   11,   29,   29,   70,   29,
-        5,    0,   72,   29,   31,   72,   31,    0,   74,    0,
-
-       76,   31,   31,   74,    0,   31,   82,   31,   31,   74,
-       31,   76,   31,   31,   74,   77,   77,   82,   77,   77,
-        0,    0,    0,   77,   31,   31,   32,   32,   32,   32,
+        1,    2,    4,  170,    2,    4,    7,    2,    4,    6,
+        6,  137,    6,    7,    7,    6,    8,   42,    9,    6,
+      136,   45,    9,    8,    8,    9,   60,   10,   42,    6,
+        6,   10,   45,   63,   10,   18,   18,   60,   18,   18,
+        6,    6,   17,   18,   63,   17,   26,   26,   28,   26,
+      117,   28,   35,   35,   28,   35,   43,   43,   44,   53,
+
+       53,   44,   53,   17,   17,  116,   17,   43,   43,   44,
+       17,   95,   44,   51,   17,   17,   51,   17,  152,  152,
+       94,   17,   27,   46,   46,   70,   46,   46,   64,   27,
+       27,   46,   67,   27,   65,   27,   27,   51,   27,   64,
+       27,   27,   47,   47,   59,   47,   47,   59,   51,   39,
+       47,   34,   27,   27,   29,   29,   59,   56,   29,   30,
+       56,   29,   29,   56,   24,   29,   72,   29,   29,   72,
+       29,   23,   29,   29,   72,   62,   29,   29,   62,   29,
+       29,   61,   61,   29,   29,   29,   62,   29,   29,   62,
+       29,   29,   61,   61,   29,   31,   73,   31,   71,   71,
+
+       21,   71,   31,   31,   75,   76,   31,   73,   31,   31,
+       76,   31,   77,   31,   31,   75,   76,   86,   15,   11,
+       86,   76,    5,   77,    0,   31,   31,   32,   32,   32,
        32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
        32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
        32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
-       32,   32,   32,   32,   32,   32,   32,   41,   78,   78,
-       41,   78,   78,   83,   79,   79,   78,   79,   79,   85,
-       81,    0,   79,   81,   83,    0,    0,   86,   41,   41,
-       85,   41,   86,   80,   80,   41,   80,   80,   86,   41,
-
-       41,   80,   41,   86,   81,   84,   41,   57,   84,   87,
-       57,   88,   93,   94,   95,   81,   84,    0,   91,   84,
-       87,   91,   88,   93,   94,   95,   91,   96,   57,   57,
-       97,   57,   98,   99,  100,   57,    0,  101,   96,   57,
-       57,   97,   57,   98,   99,  100,   57,   64,  101,   64,
-        0,  102,    0,  103,   64,   64,  104,  105,   64,  106,
-       64,   64,  102,   64,  103,   64,   64,  104,  105,  107,
-      106,  108,  109,  112,  115,  116,  117,   64,   64,  118,
-      107,  119,  108,  109,  112,  115,  116,  117,  120,  121,
-      118,  124,  119,  125,  126,  127,  128,  131,  134,  120,
-
-      121,  135,  124,  137,  125,  126,  127,  128,  131,  134,
-      138,  141,  135,  142,  137,  148,  149,  152,  157,    0,
-      158,  138,  141,  158,  142,    0,  148,  149,  152,  157,
-      160,    0,    0,  160,    0,  158,    0,    0,    0,    0,
-        0,    0,    0,    0,    0,  160,  165,  165,  165,  165,
-      165,  165,  165,  166,    0,    0,    0,  166,  166,  167,
-      167,  167,  167,  167,  167,  167,  168,    0,  168,  169,
-      169,  169,  169,  169,  169,  169,  170,  170,  170,  170,
-      170,  170,  170,  171,  171,  171,    0,  171,  171,  171,
-      172,    0,  172,    0,  172,  172,  172,  173,  173,  173,
-
-      173,  173,    0,  173,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164,  164,  164,  164,  164,
-      164,  164,  164,  164,  164,  164
+       32,   32,   32,   32,   32,   32,   32,   32,   41,   74,
+       78,   41,   74,   84,   79,   79,   85,   79,   79,   85,
+       74,   78,   79,   74,   84,    0,    0,    0,   85,   41,
+       41,    0,   41,   87,   80,   80,   41,   80,   80,    0,
+
+       41,   41,   80,   41,   87,    0,    0,   41,   57,   81,
+       81,   57,   81,   81,    0,   82,   82,   81,   82,   82,
+       57,    0,   83,   82,   88,   83,   89,   88,   91,   57,
+       57,   92,   57,   57,   93,   88,   57,   89,   88,   91,
+       57,   57,   92,   57,   57,   93,   83,   57,   66,   90,
+       66,    0,   98,    0,   90,   66,   66,   83,   99,   66,
+       90,   66,   66,   98,   66,   90,   66,   66,   96,   99,
+      100,   96,  101,  102,  103,  104,   96,  105,   66,   66,
+      106,  100,  107,  101,  102,  103,  104,  108,  105,  109,
+      110,  106,  111,  107,  112,  113,  114,  115,  108,  118,
+
+      109,  110,  121,  111,  122,  112,  113,  114,  115,  123,
+      118,  124,  125,  121,  126,  122,  127,  130,  131,  132,
+      123,  133,  124,  125,  135,  126,  138,  127,  130,  131,
+      132,  134,  133,  141,  134,  135,  142,  138,  144,  145,
+      148,  149,  150,  134,  141,  150,  156,  142,  157,  144,
+      145,  148,  149,  160,  150,  165,    0,  156,  166,  157,
+      168,  166,    0,  168,  160,    0,  165,    0,    0,    0,
+        0,    0,    0,  166,    0,  168,  173,  173,  173,  173,
+      173,  173,  173,  174,    0,    0,    0,  174,  174,  175,
+      175,  175,  175,  175,  175,  175,  176,    0,  176,  177,
+
+      177,  177,  177,  177,  177,  177,  178,  178,  178,  178,
+      178,  178,  178,  179,  179,  179,    0,  179,  179,  179,
+      180,    0,  180,    0,  180,  180,  180,  181,  181,  181,
+      181,  181,    0,  181,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172,  172,  172,  172,  172,
+      172,  172,  172,  172,  172,  172
     } ;
 
 /* The intent behind this definition is that it'll catch
@@ -655,6 +665,7 @@ Run flex like this:
 
 Modify cmFortranLexer.cxx:
   - remove TABs
+  - remove use of the 'register' storage class specifier
   - remove "yyscanner" argument from these methods:
       yy_fatal_error, cmFortran_yyalloc, cmFortran_yyrealloc, cmFortran_yyfree
   - remove "yyscanner = NULL" from end of cmFortran_yylex_destroy
@@ -685,7 +696,7 @@ Modify cmFortranLexer.h:
 /*--------------------------------------------------------------------------*/
 
 
-#line 678 "cmFortranLexer.cxx"
+#line 689 "cmFortranLexer.cxx"
 
 #define INITIAL 0
 #define free_fmt 1
@@ -718,8 +729,8 @@ struct yyguts_t
     size_t yy_buffer_stack_max; /**< capacity of stack. */
     YY_BUFFER_STATE * yy_buffer_stack; /**< Stack as an array. */
     char yy_hold_char;
-    int yy_n_chars;
-    int yyleng_r;
+    yy_size_t yy_n_chars;
+    yy_size_t yyleng_r;
     char *yy_c_buf_p;
     int yy_init;
     int yy_start;
@@ -766,14 +777,18 @@ FILE *cmFortran_yyget_out (yyscan_t yyscanner );
 
 void cmFortran_yyset_out  (FILE * out_str ,yyscan_t yyscanner );
 
-int cmFortran_yyget_leng (yyscan_t yyscanner );
+yy_size_t cmFortran_yyget_leng (yyscan_t yyscanner );
 
 char *cmFortran_yyget_text (yyscan_t yyscanner );
 
 int cmFortran_yyget_lineno (yyscan_t yyscanner );
 
 void cmFortran_yyset_lineno (int line_number ,yyscan_t yyscanner );
 
+int cmFortran_yyget_column  (yyscan_t yyscanner );
+
+void cmFortran_yyset_column (int column_no ,yyscan_t yyscanner );
+
 /* Macros after this point can all be overridden by user definitions in
  * section 1.
  */
@@ -918,11 +933,6 @@ YY_DECL
         int yy_act;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-#line 71 "cmFortranLexer.in.l"
-
-
-#line 914 "cmFortranLexer.cxx"
-
         if ( !yyg->yy_init )
                 {
                 yyg->yy_init = 1;
@@ -949,6 +959,12 @@ YY_DECL
                 cmFortran_yy_load_buffer_state(yyscanner );
                 }
 
+        {
+#line 72 "cmFortranLexer.in.l"
+
+
+#line 956 "cmFortranLexer.cxx"
+
         for(;;)             /* loops until end-of-file is reached */
                 {
                 yy_cp = yyg->yy_c_buf_p;
@@ -966,7 +982,7 @@ YY_DECL
 yy_match:
                 do
                         {
-                        YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)];
+                        YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
                         if ( yy_accept[yy_current_state] )
                                 {
                                 yyg->yy_last_accepting_state = yy_current_state;
@@ -975,13 +991,13 @@ YY_DECL
                         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                                 {
                                 yy_current_state = (int) yy_def[yy_current_state];
-                                if ( yy_current_state >= 165 )
+                                if ( yy_current_state >= 173 )
                                         yy_c = yy_meta[(unsigned int) yy_c];
                                 }
                         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
                         ++yy_cp;
                         }
-                while ( yy_base[yy_current_state] != 505 );
+                while ( yy_base[yy_current_state] != 535 );
 
 yy_find_action:
                 yy_act = yy_accept[yy_current_state];
@@ -1007,7 +1023,7 @@ YY_DECL
 
 case 1:
 YY_RULE_SETUP
-#line 73 "cmFortranLexer.in.l"
+#line 74 "cmFortranLexer.in.l"
 {
   cmFortranParser_StringStart(yyextra);
   cmFortranParser_SetOldStartcond(yyextra, YY_START);
@@ -1016,36 +1032,36 @@ YY_RULE_SETUP
         YY_BREAK
 case 2:
 YY_RULE_SETUP
-#line 79 "cmFortranLexer.in.l"
+#line 80 "cmFortranLexer.in.l"
 {
   cmFortranParser_StringStart(yyextra);
   cmFortranParser_SetOldStartcond(yyextra, YY_START);
   BEGIN(str_sq);
 }
         YY_BREAK
 case 3:
-#line 86 "cmFortranLexer.in.l"
+#line 87 "cmFortranLexer.in.l"
 case 4:
 YY_RULE_SETUP
-#line 86 "cmFortranLexer.in.l"
+#line 87 "cmFortranLexer.in.l"
 {
   BEGIN(cmFortranParser_GetOldStartcond(yyextra) );
   yylvalp->string = strdup(cmFortranParser_StringEnd(yyextra));
   return STRING;
 }
 case 5:
 /* rule 5 can match eol */
-#line 93 "cmFortranLexer.in.l"
+#line 94 "cmFortranLexer.in.l"
 case 6:
 /* rule 6 can match eol */
 YY_RULE_SETUP
-#line 93 "cmFortranLexer.in.l"
+#line 94 "cmFortranLexer.in.l"
 /* Ignore (continued strings, free fmt) */
         YY_BREAK
 case 7:
 /* rule 7 can match eol */
 YY_RULE_SETUP
-#line 95 "cmFortranLexer.in.l"
+#line 96 "cmFortranLexer.in.l"
 {
   if (cmFortranParser_GetOldStartcond(yyextra) == fixed_fmt)
     ; /* Ignore (cont. strings, fixed fmt) */
@@ -1058,194 +1074,198 @@ YY_RULE_SETUP
 case 8:
 /* rule 8 can match eol */
 YY_RULE_SETUP
-#line 105 "cmFortranLexer.in.l"
+#line 106 "cmFortranLexer.in.l"
 {
   unput ('\n');
   BEGIN(INITIAL);
   return UNTERMINATED_STRING;
 }
 case 9:
 YY_RULE_SETUP
-#line 111 "cmFortranLexer.in.l"
+#line 112 "cmFortranLexer.in.l"
 {
   cmFortranParser_StringAppend(yyextra, yytext[0]);
 }
         YY_BREAK
 case 10:
 /* rule 10 can match eol */
 YY_RULE_SETUP
-#line 115 "cmFortranLexer.in.l"
+#line 116 "cmFortranLexer.in.l"
 { return EOSTMT; } /* Treat comments like */
 case 11:
 /* rule 11 can match eol */
 YY_RULE_SETUP
-#line 116 "cmFortranLexer.in.l"
+#line 117 "cmFortranLexer.in.l"
 { return EOSTMT; } /* empty lines */
 case 12:
-/* rule 12 can match eol */
 YY_RULE_SETUP
-#line 118 "cmFortranLexer.in.l"
+#line 119 "cmFortranLexer.in.l"
+{ return CPP_LINE_DIRECTIVE; }
+case 13:
+/* rule 13 can match eol */
+YY_RULE_SETUP
+#line 120 "cmFortranLexer.in.l"
 {
   yytext[yyleng-1] = 0;
   yylvalp->string = strdup(strchr(yytext, '<')+1);
   return CPP_INCLUDE_ANGLE;
 }
-case 13:
-YY_RULE_SETUP
-#line 123 "cmFortranLexer.in.l"
-{ return CPP_INCLUDE; }
 case 14:
 YY_RULE_SETUP
-#line 124 "cmFortranLexer.in.l"
-{ return F90PPR_INCLUDE; }
+#line 125 "cmFortranLexer.in.l"
+{ return CPP_INCLUDE; }
 case 15:
 YY_RULE_SETUP
-#line 125 "cmFortranLexer.in.l"
-{ return COCO_INCLUDE; }
+#line 126 "cmFortranLexer.in.l"
+{ return F90PPR_INCLUDE; }
 case 16:
 YY_RULE_SETUP
 #line 127 "cmFortranLexer.in.l"
-{ return CPP_DEFINE; }
+{ return COCO_INCLUDE; }
 case 17:
 YY_RULE_SETUP
-#line 128 "cmFortranLexer.in.l"
-{ return F90PPR_DEFINE; }
+#line 129 "cmFortranLexer.in.l"
+{ return CPP_DEFINE; }
 case 18:
 YY_RULE_SETUP
 #line 130 "cmFortranLexer.in.l"
-{ return CPP_UNDEF; }
+{ return F90PPR_DEFINE; }
 case 19:
 YY_RULE_SETUP
-#line 131 "cmFortranLexer.in.l"
-{ return F90PPR_UNDEF; }
+#line 132 "cmFortranLexer.in.l"
+{ return CPP_UNDEF; }
 case 20:
 YY_RULE_SETUP
 #line 133 "cmFortranLexer.in.l"
-{ return CPP_IFDEF; }
+{ return F90PPR_UNDEF; }
 case 21:
 YY_RULE_SETUP
-#line 134 "cmFortranLexer.in.l"
-{ return CPP_IFNDEF; }
+#line 135 "cmFortranLexer.in.l"
+{ return CPP_IFDEF; }
 case 22:
 YY_RULE_SETUP
-#line 135 "cmFortranLexer.in.l"
-{ return CPP_IF; }
+#line 136 "cmFortranLexer.in.l"
+{ return CPP_IFNDEF; }
 case 23:
 YY_RULE_SETUP
-#line 136 "cmFortranLexer.in.l"
-{ return CPP_ELIF; }
+#line 137 "cmFortranLexer.in.l"
+{ return CPP_IF; }
 case 24:
 YY_RULE_SETUP
-#line 137 "cmFortranLexer.in.l"
-{ return CPP_ELSE; }
+#line 138 "cmFortranLexer.in.l"
+{ return CPP_ELIF; }
 case 25:
 YY_RULE_SETUP
-#line 138 "cmFortranLexer.in.l"
-{ return CPP_ENDIF; }
+#line 139 "cmFortranLexer.in.l"
+{ return CPP_ELSE; }
 case 26:
 YY_RULE_SETUP
 #line 140 "cmFortranLexer.in.l"
-{ return F90PPR_IFDEF; }
+{ return CPP_ENDIF; }
 case 27:
 YY_RULE_SETUP
-#line 141 "cmFortranLexer.in.l"
-{ return F90PPR_IFNDEF; }
+#line 142 "cmFortranLexer.in.l"
+{ return F90PPR_IFDEF; }
 case 28:
 YY_RULE_SETUP
-#line 142 "cmFortranLexer.in.l"
-{ return F90PPR_IF; }
+#line 143 "cmFortranLexer.in.l"
+{ return F90PPR_IFNDEF; }
 case 29:
 YY_RULE_SETUP
-#line 143 "cmFortranLexer.in.l"
-{ return F90PPR_ELIF; }
+#line 144 "cmFortranLexer.in.l"
+{ return F90PPR_IF; }
 case 30:
 YY_RULE_SETUP
-#line 144 "cmFortranLexer.in.l"
-{ return F90PPR_ELSE; }
+#line 145 "cmFortranLexer.in.l"
+{ return F90PPR_ELIF; }
 case 31:
 YY_RULE_SETUP
-#line 145 "cmFortranLexer.in.l"
-{ return F90PPR_ENDIF; }
-/* Line continuations, possible involving comments.  */
+#line 146 "cmFortranLexer.in.l"
+{ return F90PPR_ELSE; }
 case 32:
-/* rule 32 can match eol */
 YY_RULE_SETUP
-#line 148 "cmFortranLexer.in.l"
-
-        YY_BREAK
+#line 147 "cmFortranLexer.in.l"
+{ return F90PPR_ENDIF; }
+/* Line continuations, possible involving comments.  */
 case 33:
 /* rule 33 can match eol */
 YY_RULE_SETUP
-#line 149 "cmFortranLexer.in.l"
+#line 150 "cmFortranLexer.in.l"
 
         YY_BREAK
 case 34:
+/* rule 34 can match eol */
 YY_RULE_SETUP
 #line 151 "cmFortranLexer.in.l"
-{ return COMMA; }
+
+        YY_BREAK
 case 35:
 YY_RULE_SETUP
 #line 153 "cmFortranLexer.in.l"
-{ return DCOLON; }
+{ return COMMA; }
 case 36:
-/* rule 36 can match eol */
 YY_RULE_SETUP
 #line 155 "cmFortranLexer.in.l"
-{ return GARBAGE; }
+{ return DCOLON; }
 case 37:
+/* rule 37 can match eol */
 YY_RULE_SETUP
 #line 157 "cmFortranLexer.in.l"
-{ return ASSIGNMENT_OP; }
+{ return GARBAGE; }
 case 38:
 YY_RULE_SETUP
 #line 159 "cmFortranLexer.in.l"
+{ return ASSIGNMENT_OP; }
+case 39:
+YY_RULE_SETUP
+#line 161 "cmFortranLexer.in.l"
 {
   yylvalp->string = strdup(yytext);
   return WORD;
 }
-case 39:
-YY_RULE_SETUP
-#line 164 "cmFortranLexer.in.l"
-{ return GARBAGE; }
 case 40:
-/* rule 40 can match eol */
 YY_RULE_SETUP
 #line 166 "cmFortranLexer.in.l"
-{ return EOSTMT; }
+{ return GARBAGE; }
 case 41:
+/* rule 41 can match eol */
 YY_RULE_SETUP
-#line 169 "cmFortranLexer.in.l"
-/* Ignore */
-        YY_BREAK
+#line 168 "cmFortranLexer.in.l"
+{ return EOSTMT; }
 case 42:
-/* rule 42 can match eol */
 YY_RULE_SETUP
-#line 170 "cmFortranLexer.in.l"
-/* Ignore line-endings preceeded by \ */
+#line 171 "cmFortranLexer.in.l"
+/* Ignore */
         YY_BREAK
 case 43:
+/* rule 43 can match eol */
 YY_RULE_SETUP
 #line 172 "cmFortranLexer.in.l"
+/* Ignore line-endings preceeded by \ */
+        YY_BREAK
+case 44:
+YY_RULE_SETUP
+#line 174 "cmFortranLexer.in.l"
 { return *yytext; }
 case YY_STATE_EOF(INITIAL):
 case YY_STATE_EOF(free_fmt):
 case YY_STATE_EOF(fixed_fmt):
 case YY_STATE_EOF(str_sq):
 case YY_STATE_EOF(str_dq):
-#line 174 "cmFortranLexer.in.l"
+#line 176 "cmFortranLexer.in.l"
 {
   if(!cmFortranParser_FilePop(yyextra) )
     {
     return YY_NULL;
     }
 }
         YY_BREAK
-case 44:
+case 45:
 YY_RULE_SETUP
-#line 181 "cmFortranLexer.in.l"
+#line 183 "cmFortranLexer.in.l"
 ECHO;
         YY_BREAK
-#line 1270 "cmFortranLexer.cxx"
+#line 1291 "cmFortranLexer.cxx"
 
         case YY_END_OF_BUFFER:
                 {
@@ -1374,6 +1394,7 @@ ECHO;
                         "fatal flex scanner internal error--no action found" );
         } /* end of action switch */
                 } /* end of scanning one token */
+        } /* end of user's declarations */
 } /* end of cmFortran_yylex */
 
 /* yy_get_next_buffer - try to read in a new buffer
@@ -1430,21 +1451,21 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
         else
                 {
-                        int num_to_read =
+                        yy_size_t num_to_read =
                         YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
 
                 while ( num_to_read <= 0 )
                         { /* Not enough room in the buffer - grow it. */
 
                         /* just a shorter name for the current buffer */
-                        YY_BUFFER_STATE b = YY_CURRENT_BUFFER;
+                        YY_BUFFER_STATE b = YY_CURRENT_BUFFER_LVALUE;
 
                         int yy_c_buf_p_offset =
                                 (int) (yyg->yy_c_buf_p - b->yy_ch_buf);
 
                         if ( b->yy_is_our_buffer )
                                 {
-                                int new_size = b->yy_buf_size * 2;
+                                yy_size_t new_size = b->yy_buf_size * 2;
 
                                 if ( new_size <= 0 )
                                         b->yy_buf_size += b->yy_buf_size / 8;
@@ -1475,7 +1496,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                 /* Read in more data. */
                 YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
-                        yyg->yy_n_chars, (size_t) num_to_read );
+                        yyg->yy_n_chars, num_to_read );
 
                 YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
                 }
@@ -1538,7 +1559,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                 while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                         {
                         yy_current_state = (int) yy_def[yy_current_state];
-                        if ( yy_current_state >= 165 )
+                        if ( yy_current_state >= 173 )
                                 yy_c = yy_meta[(unsigned int) yy_c];
                         }
                 yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
@@ -1567,12 +1588,13 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                 {
                 yy_current_state = (int) yy_def[yy_current_state];
-                if ( yy_current_state >= 165 )
+                if ( yy_current_state >= 173 )
                         yy_c = yy_meta[(unsigned int) yy_c];
                 }
         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-        yy_is_jam = (yy_current_state == 164);
+        yy_is_jam = (yy_current_state == 172);
 
+        (void)yyg;
         return yy_is_jam ? 0 : yy_current_state;
 }
 
@@ -1589,7 +1611,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
                 { /* need to shift things up to make room */
                 /* +2 for EOB chars. */
-                int number_to_move = yyg->yy_n_chars + 2;
+                yy_size_t number_to_move = yyg->yy_n_chars + 2;
                 char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
                                         YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
                 char *source =
@@ -1639,7 +1661,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 
                 else
                         { /* need more input */
-                        int offset = yyg->yy_c_buf_p - yyg->yytext_ptr;
+                        yy_size_t offset = yyg->yy_c_buf_p - yyg->yytext_ptr;
                         ++yyg->yy_c_buf_p;
 
                         switch ( yy_get_next_buffer( yyscanner ) )
@@ -1805,10 +1827,6 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
         cmFortran_yyfree((void *) b ,yyscanner );
 }
 
-#ifndef __cplusplus
-extern int isatty (int );
-#endif /* __cplusplus */
-
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmFortran_yyrestart() or at EOF.
@@ -1925,7 +1943,7 @@ void cmFortran_yypop_buffer_state (yyscan_t yyscanner)
  */
 static void cmFortran_yyensure_buffer_stack (yyscan_t yyscanner)
 {
-        int num_to_alloc;
+        yy_size_t num_to_alloc;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         if (!yyg->yy_buffer_stack) {
@@ -2023,12 +2041,12 @@ YY_BUFFER_STATE cmFortran_yy_scan_string (yyconst char * yystr , yyscan_t yyscan
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  */
-YY_BUFFER_STATE cmFortran_yy_scan_bytes  (yyconst char * yybytes, int  _yybytes_len , yyscan_t yyscanner)
+YY_BUFFER_STATE cmFortran_yy_scan_bytes  (yyconst char * yybytes, yy_size_t  _yybytes_len , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
         char *buf;
         yy_size_t n;
-        int i;
+        yy_size_t i;
 
         /* Get memory for full buffer, including space for trailing EOB's. */
         n = _yybytes_len + 2;
@@ -2138,7 +2156,7 @@ FILE *cmFortran_yyget_out  (yyscan_t yyscanner)
 /** Get the length of the current token.
  * @param yyscanner The scanner object.
  */
-int cmFortran_yyget_leng  (yyscan_t yyscanner)
+yy_size_t cmFortran_yyget_leng  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyleng;
@@ -2165,7 +2183,7 @@ void cmFortran_yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscanner)
 }
 
 /** Set the current line number.
- * @param line_number The line number to set.
+ * @param line_number
  * @param yyscanner The scanner object.
  */
 void cmFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
@@ -2174,13 +2192,13 @@ void cmFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmFortran_yyset_lineno called with no buffer" , yyscanner);
+           YY_FATAL_ERROR( "cmFortran_yyset_lineno called with no buffer" );
 
     yylineno = line_number;
 }
 
 /** Set the current column.
- * @param column_no The column number to set.
+ * @param line_number
  * @param yyscanner The scanner object.
  */
 void cmFortran_yyset_column (int  column_no , yyscan_t yyscanner)
@@ -2189,7 +2207,7 @@ void cmFortran_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmFortran_yyset_column called with no buffer" , yyscanner);
+           YY_FATAL_ERROR( "cmFortran_yyset_column called with no buffer" );
 
     yycolumn = column_no;
 }
@@ -2400,7 +2418,7 @@ void cmFortran_yyfree (void * ptr , yyscan_t)
 
 #define YYTABLES_NAME "yytables"
 
-#line 181 "cmFortranLexer.in.l"
+#line 182 "cmFortranLexer.in.l"
 
 
 