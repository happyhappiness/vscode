@@ -1,3 +1,19 @@
+/*=========================================================================
+
+  Program:   CMake - Cross-Platform Makefile Generator
+  Module:    $RCSfile$
+  Language:  C++
+  Date:      $Date$
+  Version:   $Revision$
+
+  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
+  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
+
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
+     PURPOSE.  See the above copyright notices for more information.
+
+=========================================================================*/
 #line 2 "cmDependsFortranLexer.cxx"
 
 #line 4 "cmDependsFortranLexer.cxx"
@@ -9,7 +25,7 @@
 #define FLEX_SCANNER
 #define YY_FLEX_MAJOR_VERSION 2
 #define YY_FLEX_MINOR_VERSION 5
-#define YY_FLEX_SUBMINOR_VERSION 33
+#define YY_FLEX_SUBMINOR_VERSION 34
 #if YY_FLEX_SUBMINOR_VERSION > 0
 #define FLEX_BETA
 #endif
@@ -31,10 +47,10 @@
 
 /* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */
 
-#if __STDC_VERSION__ >= 199901L
+#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
 
 /* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
- * if you want the limit (max/min) macros for int types. 
+ * if you want the limit (max/min) macros for int types.
  */
 #ifndef __STDC_LIMIT_MACROS
 #define __STDC_LIMIT_MACROS 1
@@ -51,7 +67,7 @@ typedef uint32_t flex_uint32_t;
 typedef signed char flex_int8_t;
 typedef short int flex_int16_t;
 typedef int flex_int32_t;
-typedef unsigned char flex_uint8_t; 
+typedef unsigned char flex_uint8_t;
 typedef unsigned short int flex_uint16_t;
 typedef unsigned int flex_uint32_t;
 #endif /* ! C99 */
@@ -94,11 +110,12 @@ typedef unsigned int flex_uint32_t;
 
 #else   /* ! __cplusplus */
 
-#if __STDC__
+/* C99 requires __STDC__ to be defined as 1. */
+#if defined (__STDC__)
 
 #define YY_USE_CONST
 
-#endif  /* __STDC__ */
+#endif  /* defined (__STDC__) */
 #endif  /* ! __cplusplus */
 
 #ifdef YY_USE_CONST
@@ -134,8 +151,6 @@ typedef void* yyscan_t;
 #define yycolumn (YY_CURRENT_BUFFER_LVALUE->yy_bs_column)
 #define yy_flex_debug yyg->yy_flex_debug_r
 
-int cmDependsFortran_yylex_init (yyscan_t* scanner);
-
 /* Enter a start condition.  This macro really ought to take a parameter,
  * but we do it the disgusting crufty way forced on us by the ()-less
  * definition of BEGIN.
@@ -176,7 +191,7 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 #define EOB_ACT_LAST_MATCH 2
 
     #define YY_LESS_LINENO(n)
-    
+
 /* Return all but the first "n" matched characters back to the input stream. */
 #define yyless(n) \
         do \
@@ -196,11 +211,13 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
 /* The following is because we cannot portably get our hands on size_t
  * (without autoconf's help, which isn't available because we want
  * flex-generated scanners to compile on their own).
+ * Given that the standard has decreed that size_t exists since 1989,
+ * I guess we can afford to depend on it. Manoj.
  */
 
 #ifndef YY_TYPEDEF_YY_SIZE_T
 #define YY_TYPEDEF_YY_SIZE_T
-typedef unsigned int yy_size_t;
+typedef size_t yy_size_t;
 #endif
 
 #ifndef YY_STRUCT_YY_BUFFER_STATE
@@ -243,7 +260,7 @@ struct yy_buffer_state
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
-    
+
         /* Whether to try to fill the input buffer when we reach the
          * end of it.
          */
@@ -364,25 +381,25 @@ struct yy_trans_info
         flex_int32_t yy_verify;
         flex_int32_t yy_nxt;
         };
-static yyconst flex_int16_t yy_accept[155] =
+static yyconst flex_int16_t yy_accept[158] =
     {   0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-       42,   36,   38,   37,   40,    1,   36,   36,   31,    2,
-       37,   34,   36,   35,   36,   35,   37,   36,   35,    9,
-        8,    9,    4,    3,   36,    0,   10,    0,    0,    0,
-        0,    0,    0,    0,    0,    0,    0,   31,   31,   32,
-       34,   36,   35,    0,   39,   35,    0,   36,    0,   11,
-       35,    0,    0,    5,    0,    0,    0,   21,    0,    0,
-        0,    0,    0,    0,   27,    0,   31,   31,   31,   31,
-        0,    0,    0,    0,    0,    6,    0,    0,    0,    0,
+       42,   36,   38,   37,   40,    1,   36,   31,    2,   37,
+       34,   36,   35,   36,   35,   38,   36,   37,   36,   35,
+        9,    8,    9,    4,    3,   36,    0,   10,    0,    0,
+        0,    0,    0,   31,   31,   32,   34,   36,   35,    0,
+       39,   35,    0,    0,    0,    0,    0,    0,    0,    0,
+       36,    0,   11,   35,    0,    0,    5,    0,    0,    0,
+       27,    0,    0,   31,   31,   31,   31,    0,    0,    0,
+        0,    0,   21,    0,    0,    0,    0,    0,    6,    0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 
-        0,    0,    0,    0,    0,    0,   22,   23,    0,    0,
-        0,    0,    0,    0,    0,   28,   29,    0,    0,    0,
-        0,    0,    0,    0,    0,   24,   19,    0,    0,   17,
-        0,   18,   30,   25,    0,    0,    0,    0,    0,   15,
-       20,    0,   16,   26,    0,    0,    7,   33,    7,   12,
-       13,    0,   14,    0
+        0,    0,    0,    0,    0,    0,    0,    0,    0,   28,
+       29,    0,    0,    0,    0,    0,    0,    0,   22,   23,
+        0,    0,    0,    0,    0,    0,    0,    0,   30,   25,
+        0,    0,   18,    0,    0,   24,   19,    0,    0,   17,
+        0,    0,   16,   26,    0,    0,   15,   20,    0,    7,
+       33,    7,   13,    0,   12,   14,    0
     } ;
 
 static yyconst flex_int32_t yy_ec[256] =
@@ -394,12 +411,12 @@ static yyconst flex_int32_t yy_ec[256] =
         1,   12,    1,    4,    1,    1,    1,   13,   13,   13,
        13,   13,   13,   13,   13,   13,   13,    1,   14,    1,
        15,   16,   17,    1,   18,   18,   19,   20,   21,   22,
-       18,   18,   23,   18,   18,   18,   18,   24,   18,   18,
-       18,   18,   18,   18,   25,   18,   18,   18,   18,   18,
-        1,   26,    1,    1,   27,    1,   18,   18,   28,   29,
+       18,   18,   23,   18,   18,   24,   18,   25,   18,   18,
+       18,   18,   26,   18,   27,   18,   18,   18,   18,   18,
+        1,   28,    1,    1,   29,    1,   18,   18,   30,   31,
 
-       30,   31,   18,   18,   32,   18,   18,   33,   18,   34,
-       18,   18,   18,   18,   35,   18,   36,   18,   18,   18,
+       32,   33,   18,   18,   34,   18,   18,   35,   18,   36,
+       18,   18,   18,   18,   37,   18,   38,   18,   18,   18,
        18,   18,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
@@ -417,152 +434,180 @@ static yyconst flex_int32_t yy_ec[256] =
         1,    1,    1,    1,    1
     } ;
 
-static yyconst flex_int32_t yy_meta[37] =
+static yyconst flex_int32_t yy_meta[39] =
     {   0,
         1,    2,    2,    3,    4,    3,    3,    1,    1,    3,
         3,    1,    5,    3,    3,    1,    1,    6,    6,    6,
-        6,    6,    6,    6,    6,    1,    5,    6,    6,    6,
-        6,    6,    6,    6,    6,    6
+        6,    6,    6,    6,    6,    6,    6,    1,    5,    6,
+        6,    6,    6,    6,    6,    6,    6,    6
     } ;
 
-static yyconst flex_int16_t yy_base[163] =
+static yyconst flex_int16_t yy_base[166] =
     {   0,
-        0,    0,    0,    0,  276,   34,   37,   39,   48,   49,
-      277,    0,  356,  356,  273,  356,   62,   97,   63,  356,
-      356,  259,  257,    0,   36,  129,  267,  156,  183,  356,
-      266,   69,  356,  356,    0,  267,  356,  218,  239,   10,
-       26,  234,  253,  246,  242,   42,   46,   76,   98,  356,
-      356,   82,    0,  104,  356,    0,  260,  285,  261,  356,
-        0,  258,  108,   83,  231,   80,  232,   61,  232,  230,
-      235,  236,   84,  224,   89,  224,  129,  148,  219,  225,
-      131,  217,  244,  241,  138,  356,  213,  213,  213,  210,
-      211,  211,  206,  208,  214,  215,  203,  203,  200,  196,
-
-      152,  147,  151,  173,  172,  142,  356,  356,  144,  143,
-      141,  134,  136,  142,  140,  356,  356,  130,  129,  122,
-      113,  114,  139,  123,   96,  356,  356,   94,   95,  356,
-      100,  356,  356,  356,   89,   76,   53,   94,    0,  356,
-      356,   53,  356,  356,   40,   32,  356,  356,  356,  356,
-      356,   15,  356,  356,  312,  318,  323,  325,  331,  337,
-      343,  349
+        0,   37,    0,   38,  176,   45,   41,   51,   53,   63,
+      161,    0,  492,  492,  150,  492,   76,   77,  492,  492,
+      118,  116,    0,   66,  114,   93,  143,  123,  181,  210,
+      492,  115,  114,  492,  492,    0,  110,  492,  247,   70,
+      100,   96,   75,  144,  197,  492,  492,  135,    0,  136,
+      492,    0,  104,  284,    0,  136,  226,  140,  142,   89,
+      322,   87,  492,    0,   81,  183,  253,  158,  243,  175,
+      240,  234,  252,  285,  291,  307,  338,  298,  248,  286,
+      319,  306,  327,  327,  329,   69,   67,  357,  492,  331,
+      333,  340,  341,  347,  349,  346,  350,  354,  351,  354,
+
+      356,  355,  362,  366,  366,  370,   62,   50,  367,  492,
+      492,  371,  373,  375,  371,  377,  376,  380,  492,  492,
+      386,  390,  392,  387,  393,   44,   36,  396,  492,  492,
+      396,  400,  492,  394,  401,  492,  492,  405,  410,  492,
+       56,    0,  492,  492,  413,  415,  492,  492,  415,  492,
+      492,  492,  492,  416,  492,  492,  492,  448,  454,  459,
+      461,  467,  473,  479,  485
     } ;
 
-static yyconst flex_int16_t yy_def[163] =
+static yyconst flex_int16_t yy_def[166] =
     {   0,
-      154,    1,    1,    1,    1,    1,  155,  155,  155,  155,
-      154,  156,  154,  154,  157,  154,  156,  156,  154,  154,
-      154,  154,  156,  158,  156,  158,  154,  159,  154,  154,
-      154,  154,  154,  154,  156,  157,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  160,  154,
-      154,  156,  158,  154,  154,   26,  154,  159,  159,  154,
-       29,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  160,  160,  160,  160,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  161,  162,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,    0,  154,  154,  154,  154,  154,  154,
-      154,  154
+      157,    1,    1,    1,    1,    1,  158,  158,  158,  158,
+      157,  159,  157,  157,  160,  157,  157,  157,  157,  157,
+      157,  159,  161,  159,  161,  157,  157,  157,  162,  157,
+      157,  157,  157,  157,  157,  159,  160,  157,  157,  157,
+      157,  157,  157,  157,  163,  157,  157,  159,  161,  157,
+      157,   25,  157,  157,   54,  157,  157,  157,  157,  157,
+      162,  162,  157,   30,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  163,  163,  163,  163,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      164,  165,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,    0,  157,  157,  157,
+      157,  157,  157,  157,  157
     } ;
 
-static yyconst flex_int16_t yy_nxt[393] =
+static yyconst flex_int16_t yy_nxt[531] =
     {   0,
-       12,   13,   14,   13,   13,   15,   16,   17,   18,   19,
-       20,   12,   12,   21,   22,   12,   23,   24,   24,   24,
-       24,   24,   24,   24,   24,   25,   26,   24,   24,   24,
-       24,   24,   24,   24,   24,   24,   27,   54,   55,   31,
-       54,   31,   66,   67,  153,   28,   32,   33,   32,   33,
-       31,   31,   29,   29,   34,   34,   68,   32,   32,   69,
-      152,   29,   29,   38,   48,   48,   38,   48,   49,  151,
-       63,   64,   50,   63,   73,   74,   75,   48,   48,   76,
-       48,   49,  150,   81,   85,   50,   81,   85,  146,   91,
-       39,   40,   86,   41,   92,  148,  148,   42,   43,   78,
-
-       48,   43,   78,   79,  145,   54,   55,   80,   54,   63,
-       64,   88,   63,   82,   89,   97,   44,  100,   98,  144,
-      143,   45,  101,  142,  141,  140,   46,  139,   47,   35,
-       78,   48,   81,   78,   79,   81,   35,   35,   80,   85,
-       35,   56,   85,  138,   35,   35,  137,   86,  136,   78,
-       48,  135,   78,   79,   35,   56,   58,   80,   60,  134,
-      133,  132,   82,   58,   58,  131,  130,   58,   58,  129,
-      128,   58,   58,  127,  126,  125,  124,  123,  122,  121,
-      120,   58,   58,   59,   59,   60,   59,   59,   59,   59,
-       59,   59,   59,   59,   59,   61,   59,   59,   59,   59,
-
-       61,   61,   61,   61,   61,   61,   61,   61,   59,   61,
-       61,   61,   61,   61,   61,   61,   61,   61,   61,   38,
-       78,   48,   38,   78,   79,  119,   78,   48,   80,   78,
-       79,  118,  117,  116,   80,  115,  114,  113,  112,  111,
-      110,  109,  108,  107,  106,  105,   39,   40,  104,   41,
-      103,  102,   99,   42,   43,   96,   95,   43,   94,   93,
-       90,   87,   84,   60,   83,   72,   71,   70,   65,   37,
-       62,   57,   44,   52,   51,   37,  154,   45,   27,  154,
-      154,  154,   46,  154,   47,   58,  154,   60,  154,  154,
-      154,  154,   58,   58,  154,  154,   58,   58,  154,  154,
-
-       58,   58,  154,  154,  154,  154,  154,  154,  154,  154,
-       58,   58,   30,   30,   30,   30,   30,   30,   35,  154,
-      154,  154,   35,   36,   36,   36,   36,   36,   36,   53,
-       53,   59,   59,   59,   59,   59,   59,   77,   77,   77,
-       77,   77,   77,  147,  147,  147,  154,  147,  147,  149,
-      154,  149,  154,  149,  149,   11,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154
-
+       12,   13,   14,   13,   13,   15,   16,   12,   17,   18,
+       19,   12,   12,   20,   21,   12,   22,   23,   23,   23,
+       23,   23,   23,   23,   23,   23,   23,   24,   25,   23,
+       23,   23,   23,   23,   23,   23,   23,   23,   26,   26,
+      142,   26,   26,   32,   27,   27,   26,   28,  141,   26,
+       33,   34,   27,   32,  127,   32,   29,  151,  151,   35,
+       33,   34,   33,   30,   30,   32,  126,   50,   51,   35,
+       50,  108,   33,  107,   30,   30,   36,   39,   44,   44,
+       39,   44,   45,   36,   36,   87,   46,   36,   36,   63,
+       68,   36,   36,   86,   53,   40,   41,   53,   42,   73,
+
+       54,   68,   43,   36,   36,   53,   40,   41,   53,   42,
+       73,   54,   38,   43,   36,   66,   67,   71,   66,   65,
+       72,   36,   36,   69,   70,   36,   52,   60,   71,   36,
+       36,   72,   48,   47,   69,   70,   78,   50,   51,   78,
+       50,   36,   52,   36,   55,   44,   44,   55,   44,   45,
+       36,   36,   38,   46,   36,   36,   80,   79,   36,   36,
+      157,   83,   56,   57,   84,   58,   85,   80,   79,   59,
+       36,   36,   83,   56,   57,   84,   58,   85,   28,   90,
+       59,   61,  157,   63,   66,   67,  157,   66,   61,   61,
+       90,  157,   61,   61,   93,  157,   61,   61,   75,   44,
+
+      157,   75,   76,  157,  157,   93,   77,  157,   61,   61,
+       62,   62,   63,   62,   62,   62,   62,   62,   62,   62,
+       62,   62,   64,   62,   62,   62,   62,   64,   64,   64,
+       64,   64,   64,   64,   64,   64,   64,   62,   64,   64,
+       64,   64,   64,   64,   64,   64,   64,   64,   39,   81,
+       82,   39,   96,  157,   88,  157,  157,   88,  157,   94,
+       81,   82,   89,   96,   95,   91,   40,   41,   92,   42,
+       94,   97,   98,   43,  157,   95,   91,   40,   41,   92,
+       42,  157,   97,   98,   43,   55,   75,   44,   55,   75,
+       76,  157,   75,   44,   77,   75,   76,  157,  157,   78,
+
+       77,  157,   78,   56,   57,  157,   58,   99,   75,   44,
+       59,   75,   76,  157,   56,   57,   77,   58,   99,  157,
+       79,   59,   61,  157,   63,  102,  157,  157,  157,   61,
+       61,   79,  157,   61,   61,  157,  102,   61,   61,   75,
+       44,  100,   75,   76,  101,  105,  103,   77,  106,   61,
+       61,  104,  100,  109,  110,  101,  105,  103,   88,  106,
+      111,   88,  104,  112,  109,  110,   89,  113,  114,  115,
+      116,  111,  117,  118,  112,  119,  120,  121,  113,  114,
+      115,  116,  122,  117,  118,  123,  119,  120,  121,  124,
+      125,  128,  129,  122,  130,  131,  123,  132,  133,  134,
+
+      124,  125,  128,  129,  135,  130,  131,  136,  132,  133,
+      134,  137,  138,  139,  140,  135,  143,  144,  136,  145,
+      146,  147,  137,  138,  139,  140,  148,  143,  144,  149,
+      145,  146,  147,  153,  154,  155,  156,  148,  157,  157,
+      149,  157,  157,  157,  153,  154,  155,  156,   31,   31,
+       31,   31,   31,   31,   36,  157,  157,  157,   36,   37,
+       37,   37,   37,   37,   37,   49,   49,   62,   62,   62,
+       62,   62,   62,   74,   74,   74,   74,   74,   74,  150,
+      150,  150,  157,  150,  150,  152,  157,  152,  157,  152,
+      152,   11,  157,  157,  157,  157,  157,  157,  157,  157,
+
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157
     } ;
 
-static yyconst flex_int16_t yy_chk[393] =
+static yyconst flex_int16_t yy_chk[531] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
-        1,    1,    1,    1,    1,    1,    6,   25,   25,    7,
-       25,    8,   40,   40,  152,    6,    7,    7,    8,    8,
-        9,   10,    6,    6,    9,   10,   41,    9,   10,   41,
-      146,    6,    6,   17,   19,   19,   17,   19,   19,  145,
-       32,   32,   19,   32,   46,   46,   47,   48,   48,   47,
-       48,   48,  142,   52,   64,   48,   52,   64,  137,   68,
-       17,   17,   64,   17,   68,  138,  138,   17,   18,   49,
-
-       49,   18,   49,   49,  136,   54,   54,   49,   54,   63,
-       63,   66,   63,   52,   66,   73,   18,   75,   73,  135,
-      131,   18,   75,  129,  128,  125,   18,  124,   18,   26,
-       77,   77,   81,   77,   77,   81,   26,   26,   77,   85,
-       26,   26,   85,  123,   26,   26,  122,   85,  121,   78,
-       78,  120,   78,   78,   26,   26,   28,   78,   28,  119,
-      118,  115,   81,   28,   28,  114,  113,   28,   28,  112,
-      111,   28,   28,  110,  109,  106,  105,  104,  103,  102,
-      101,   28,   28,   29,   29,   29,   29,   29,   29,   29,
-       29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
-
-       29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
-       29,   29,   29,   29,   29,   29,   29,   29,   29,   38,
-       79,   79,   38,   79,   79,  100,   80,   80,   79,   80,
-       80,   99,   98,   97,   80,   96,   95,   94,   93,   92,
-       91,   90,   89,   88,   87,   84,   38,   38,   83,   38,
-       82,   76,   74,   38,   43,   72,   71,   43,   70,   69,
-       67,   65,   62,   59,   57,   45,   44,   42,   39,   36,
-       31,   27,   43,   23,   22,   15,   11,   43,    5,    0,
-        0,    0,   43,    0,   43,   58,    0,   58,    0,    0,
-        0,    0,   58,   58,    0,    0,   58,   58,    0,    0,
-
-       58,   58,    0,    0,    0,    0,    0,    0,    0,    0,
-       58,   58,  155,  155,  155,  155,  155,  155,  156,    0,
-        0,    0,  156,  157,  157,  157,  157,  157,  157,  158,
-      158,  159,  159,  159,  159,  159,  159,  160,  160,  160,
-      160,  160,  160,  161,  161,  161,    0,  161,  161,  162,
-        0,  162,    0,  162,  162,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154,  154,  154,  154,  154,  154,  154,  154,  154,
-      154,  154
-
+        1,    1,    1,    1,    1,    1,    1,    1,    2,    4,
+      127,    2,    4,    7,    2,    4,    6,    6,  126,    6,
+        7,    7,    6,    8,  108,    9,    6,  141,  141,    9,
+        8,    8,    9,    6,    6,   10,  107,   24,   24,   10,
+       24,   87,   10,   86,    6,    6,   17,   17,   18,   18,
+       17,   18,   18,   17,   17,   65,   18,   17,   17,   62,
+       40,   17,   17,   60,   26,   17,   17,   26,   17,   43,
+
+       26,   40,   17,   17,   17,   53,   17,   17,   53,   17,
+       43,   53,   37,   17,   25,   33,   33,   42,   33,   32,
+       42,   25,   25,   41,   41,   25,   25,   28,   42,   25,
+       25,   42,   22,   21,   41,   41,   48,   50,   50,   48,
+       50,   25,   25,   27,   27,   44,   44,   27,   44,   44,
+       27,   27,   15,   44,   27,   27,   56,   48,   27,   27,
+       11,   58,   27,   27,   58,   27,   59,   56,   48,   27,
+       27,   27,   58,   27,   27,   58,   27,   59,    5,   68,
+       27,   29,    0,   29,   66,   66,    0,   66,   29,   29,
+       68,    0,   29,   29,   70,    0,   29,   29,   45,   45,
+
+        0,   45,   45,    0,    0,   70,   45,    0,   29,   29,
+       30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
+       30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
+       30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
+       30,   30,   30,   30,   30,   30,   30,   30,   39,   57,
+       57,   39,   72,    0,   67,    0,    0,   67,    0,   71,
+       57,   57,   67,   72,   71,   69,   39,   39,   69,   39,
+       71,   73,   79,   39,    0,   71,   69,   39,   39,   69,
+       39,    0,   73,   79,   39,   54,   74,   74,   54,   74,
+       74,    0,   75,   75,   74,   75,   75,    0,    0,   78,
+
+       75,    0,   78,   54,   54,    0,   54,   80,   76,   76,
+       54,   76,   76,    0,   54,   54,   76,   54,   80,    0,
+       78,   54,   61,    0,   61,   82,    0,    0,    0,   61,
+       61,   78,    0,   61,   61,    0,   82,   61,   61,   77,
+       77,   81,   77,   77,   81,   84,   83,   77,   85,   61,
+       61,   83,   81,   90,   91,   81,   84,   83,   88,   85,
+       92,   88,   83,   93,   90,   91,   88,   94,   95,   96,
+       97,   92,   98,   99,   93,  100,  101,  102,   94,   95,
+       96,   97,  103,   98,   99,  104,  100,  101,  102,  105,
+      106,  109,  112,  103,  113,  114,  104,  115,  116,  117,
+
+      105,  106,  109,  112,  118,  113,  114,  121,  115,  116,
+      117,  122,  123,  124,  125,  118,  128,  131,  121,  132,
+      134,  135,  122,  123,  124,  125,  138,  128,  131,  139,
+      132,  134,  135,  145,  146,  149,  154,  138,    0,    0,
+      139,    0,    0,    0,  145,  146,  149,  154,  158,  158,
+      158,  158,  158,  158,  159,    0,    0,    0,  159,  160,
+      160,  160,  160,  160,  160,  161,  161,  162,  162,  162,
+      162,  162,  162,  163,  163,  163,  163,  163,  163,  164,
+      164,  164,    0,  164,  164,  165,    0,  165,    0,  165,
+      165,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157,
+      157,  157,  157,  157,  157,  157,  157,  157,  157,  157
     } ;
 
 /* The intent behind this definition is that it'll catch
@@ -639,7 +684,7 @@ Modify cmDependsFortranLexer.h:
 /*--------------------------------------------------------------------------*/
 
 
-#line 643 "cmDependsFortranLexer.cxx"
+#line 672 "cmDependsFortranLexer.cxx"
 
 #define INITIAL 0
 #define free_fmt 1
@@ -695,6 +740,10 @@ struct yyguts_t
 
 static int yy_init_globals (yyscan_t yyscanner );
 
+int cmDependsFortran_yylex_init (yyscan_t* scanner);
+
+int cmDependsFortran_yylex_init_extra (YY_EXTRA_TYPE user_defined,yyscan_t* scanner);
+
 /* Accessor methods to globals.
    These are made visible to non-reentrant scanners for convenience. */
 
@@ -737,7 +786,7 @@ extern int cmDependsFortran_yywrap (yyscan_t yyscanner );
 #endif
 
     static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
-    
+
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -766,7 +815,7 @@ static int input (yyscan_t yyscanner );
 /* This used to be an fputs(), but since the string might contain NUL's,
  * we now use fwrite().
  */
-#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
+#define ECHO fwrite( yytext, yyleng, 1, yyout )
 #endif
 
 /* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
@@ -777,7 +826,7 @@ static int input (yyscan_t yyscanner );
         if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \
                 { \
                 int c = '*'; \
-                size_t n; \
+                int n; \
                 for ( n = 0; n < max_size && \
                              (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
                         buf[n] = (char) c; \
@@ -866,7 +915,7 @@ YY_DECL
 #line 75 "cmDependsFortranLexer.in.l"
 
 
-#line 870 "cmDependsFortranLexer.cxx"
+#line 903 "cmDependsFortranLexer.cxx"
 
         if ( !yyg->yy_init )
                 {
@@ -920,13 +969,13 @@ YY_DECL
                         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                                 {
                                 yy_current_state = (int) yy_def[yy_current_state];
-                                if ( yy_current_state >= 155 )
+                                if ( yy_current_state >= 158 )
                                         yy_c = yy_meta[(unsigned int) yy_c];
                                 }
                         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
                         ++yy_cp;
                         }
-                while ( yy_base[yy_current_state] != 356 );
+                while ( yy_base[yy_current_state] != 492 );
 
 yy_find_action:
                 yy_act = yy_accept[yy_current_state];
@@ -1173,7 +1222,7 @@ YY_RULE_SETUP
 #line 176 "cmDependsFortranLexer.in.l"
 ECHO;
         YY_BREAK
-#line 1206 "cmDependsFortranLexer.cxx"
+#line 1239 "cmDependsFortranLexer.cxx"
 
         case YY_END_OF_BUFFER:
                 {
@@ -1427,6 +1476,14 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         else
                 ret_val = EOB_ACT_CONTINUE_SCAN;
 
+        if ((yy_size_t) (yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
+                /* Extend the array by 50%, plus the number we really need. */
+                yy_size_t new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);
+                YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmDependsFortran_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );
+                if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
+                        YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
+        }
+
         yyg->yy_n_chars += number_to_move;
         YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
         YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
@@ -1458,7 +1515,7 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
                 while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                         {
                         yy_current_state = (int) yy_def[yy_current_state];
-                        if ( yy_current_state >= 155 )
+                        if ( yy_current_state >= 158 )
                                 yy_c = yy_meta[(unsigned int) yy_c];
                         }
                 yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
@@ -1487,11 +1544,11 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
         while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
                 {
                 yy_current_state = (int) yy_def[yy_current_state];
-                if ( yy_current_state >= 155 )
+                if ( yy_current_state >= 158 )
                         yy_c = yy_meta[(unsigned int) yy_c];
                 }
         yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-        yy_is_jam = (yy_current_state == 154);
+        yy_is_jam = (yy_current_state == 157);
 
         return yy_is_jam ? 0 : yy_current_state;
 }
@@ -1684,7 +1741,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
     YY_BUFFER_STATE cmDependsFortran_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
         YY_BUFFER_STATE b;
-    
+
         b = (YY_BUFFER_STATE) cmDependsFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
         if ( ! b )
                 YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_create_buffer()" );
@@ -1728,7 +1785,7 @@ static void cmDependsFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 #ifndef __cplusplus
 extern int isatty (int );
 #endif /* __cplusplus */
-    
+
 /* Initializes or reinitializes a buffer.
  * This function is sometimes called more than once on the same buffer,
  * such as during a cmDependsFortran_yyrestart() or at EOF.
@@ -1754,7 +1811,7 @@ extern int isatty (int );
     }
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
-    
+
         errno = oerrno;
 }
 
@@ -1858,9 +1915,11 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                 yyg->yy_buffer_stack = (struct yy_buffer_state**)cmDependsFortran_yyalloc
                                                                 (num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
-                
+                if ( ! yyg->yy_buffer_stack )
+                        YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yyensure_buffer_stack()" );
+
                 memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
-                                
+
                 yyg->yy_buffer_stack_max = num_to_alloc;
                 yyg->yy_buffer_stack_top = 0;
                 return;
@@ -1876,6 +1935,8 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
                                                                 (yyg->yy_buffer_stack,
                                                                 num_to_alloc * sizeof(struct yy_buffer_state*)
                                                                 , yyscanner);
+                if ( ! yyg->yy_buffer_stack )
+                        YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yyensure_buffer_stack()" );
 
                 /* zero only the new slots.*/
                 memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
@@ -1887,12 +1948,12 @@ static void cmDependsFortran_yyensure_buffer_stack (yyscan_t yyscanner)
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
@@ -1928,7 +1989,7 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_buffer  (char * base, yy_size_t  size ,
  */
 YY_BUFFER_STATE cmDependsFortran_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)
 {
-    
+
         return cmDependsFortran_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
 }
 
@@ -1945,7 +2006,7 @@ YY_BUFFER_STATE cmDependsFortran_yy_scan_bytes  (yyconst char * yybytes, int  _y
         char *buf;
         yy_size_t n;
         int i;
-    
+
         /* Get memory for full buffer, including space for trailing EOB's. */
         n = _yybytes_len + 2;
         buf = (char *) cmDependsFortran_yyalloc(n ,yyscanner );
@@ -2013,10 +2074,10 @@ YY_EXTRA_TYPE cmDependsFortran_yyget_extra  (yyscan_t yyscanner)
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
 
@@ -2026,10 +2087,10 @@ int cmDependsFortran_yyget_lineno  (yyscan_t yyscanner)
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
 
@@ -2090,8 +2151,8 @@ void cmDependsFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmDependsFortran_yyset_lineno called with no buffer" , yyscanner);
+
     yylineno = line_number;
 }
 
@@ -2105,8 +2166,8 @@ void cmDependsFortran_yyset_column (int  column_no , yyscan_t yyscanner)
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner); 
-    
+           yy_fatal_error( "cmDependsFortran_yyset_column called with no buffer" , yyscanner);
+
     yycolumn = column_no;
 }
 
@@ -2170,6 +2231,42 @@ int cmDependsFortran_yylex_init(yyscan_t* ptr_yy_globals)
     return yy_init_globals ( *ptr_yy_globals );
 }
 
+/* cmDependsFortran_yylex_init_extra has the same functionality as cmDependsFortran_yylex_init, but follows the
+ * convention of taking the scanner as the last argument. Note however, that
+ * this is a *pointer* to a scanner, as it will be allocated by this call (and
+ * is the reason, too, why this function also must handle its own declaration).
+ * The user defined value in the first argument will be available to cmDependsFortran_yyalloc in
+ * the yyextra field.
+ */
+
+int cmDependsFortran_yylex_init_extra(YY_EXTRA_TYPE yy_user_defined,yyscan_t* ptr_yy_globals )
+
+{
+    struct yyguts_t dummy_yyguts;
+
+    cmDependsFortran_yyset_extra (yy_user_defined, &dummy_yyguts);
+
+    if (ptr_yy_globals == NULL){
+        errno = EINVAL;
+        return 1;
+    }
+
+    *ptr_yy_globals = (yyscan_t) cmDependsFortran_yyalloc ( sizeof( struct yyguts_t ), &dummy_yyguts );
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
+    cmDependsFortran_yyset_extra (yy_user_defined, *ptr_yy_globals);
+
+    return yy_init_globals ( *ptr_yy_globals );
+}
+
 static int yy_init_globals (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;