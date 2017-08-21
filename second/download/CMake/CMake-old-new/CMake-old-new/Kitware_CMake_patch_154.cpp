@@ -1,14 +1,3 @@
-/*============================================================================
-  CMake - Cross Platform Makefile Generator
-  Copyright 2000-2015 Kitware, Inc., Insight Software Consortium
-
-  Distributed under the OSI-approved BSD License (the "License");
-  see accompanying file Copyright.txt for details.
-
-  This software is distributed WITHOUT ANY WARRANTY; without even the
-  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
-  See the License for more information.
-============================================================================*/
 #line 2 "cmFortranLexer.cxx"
 
 #line 4 "cmFortranLexer.cxx"
@@ -19,8 +8,8 @@
 
 #define FLEX_SCANNER
 #define YY_FLEX_MAJOR_VERSION 2
-#define YY_FLEX_MINOR_VERSION 5
-#define YY_FLEX_SUBMINOR_VERSION 39
+#define YY_FLEX_MINOR_VERSION 6
+#define YY_FLEX_SUBMINOR_VERSION 1
 #if YY_FLEX_SUBMINOR_VERSION > 0
 #define FLEX_BETA
 #endif
@@ -99,25 +88,13 @@ typedef unsigned int flex_uint32_t;
 
 #endif /* ! FLEXINT_H */
 
-#ifdef __cplusplus
-
-/* The "const" storage-class-modifier is valid. */
-#define YY_USE_CONST
-
-#else   /* ! __cplusplus */
-
-/* C99 requires __STDC__ to be defined as 1. */
-#if defined (__STDC__)
-
-#define YY_USE_CONST
-
-#endif  /* defined (__STDC__) */
-#endif  /* ! __cplusplus */
-
-#ifdef YY_USE_CONST
+/* TODO: this is always defined, so inline it */
 #define yyconst const
+
+#if defined(__GNUC__) && __GNUC__ >= 3
+#define yynoreturn __attribute__((__noreturn__))
 #else
-#define yyconst
+#define yynoreturn
 #endif
 
 /* Returned upon end-of-file. */
@@ -204,83 +181,83 @@ typedef size_t yy_size_t;
 
 /* Return all but the first "n" matched characters back to the input stream. */
 #define yyless(n) \
-        do \
-                { \
-                /* Undo effects of setting up yytext. */ \
+	do \
+		{ \
+		/* Undo effects of setting up yytext. */ \
         int yyless_macro_arg = (n); \
         YY_LESS_LINENO(yyless_macro_arg);\
-                *yy_cp = yyg->yy_hold_char; \
-                YY_RESTORE_YY_MORE_OFFSET \
-                yyg->yy_c_buf_p = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
-                YY_DO_BEFORE_ACTION; /* set up yytext again */ \
-                } \
-        while ( 0 )
+		*yy_cp = yyg->yy_hold_char; \
+		YY_RESTORE_YY_MORE_OFFSET \
+		yyg->yy_c_buf_p = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
+		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
+		} \
+	while ( 0 )
 
 #define unput(c) yyunput( c, yyg->yytext_ptr , yyscanner )
 
 #ifndef YY_STRUCT_YY_BUFFER_STATE
 #define YY_STRUCT_YY_BUFFER_STATE
 struct yy_buffer_state
-        {
-        FILE *yy_input_file;
-
-        char *yy_ch_buf;                /* input buffer */
-        char *yy_buf_pos;               /* current position in input buffer */
-
-        /* Size of input buffer in bytes, not including room for EOB
-         * characters.
-         */
-        yy_size_t yy_buf_size;
-
-        /* Number of characters read into yy_ch_buf, not including EOB
-         * characters.
-         */
-        yy_size_t yy_n_chars;
-
-        /* Whether we "own" the buffer - i.e., we know we created it,
-         * and can realloc() it to grow it, and should free() it to
-         * delete it.
-         */
-        int yy_is_our_buffer;
-
-        /* Whether this is an "interactive" input source; if so, and
-         * if we're using stdio for input, then we want to use getc()
-         * instead of fread(), to make sure we stop fetching input after
-         * each newline.
-         */
-        int yy_is_interactive;
-
-        /* Whether we're considered to be at the beginning of a line.
-         * If so, '^' rules will be active on the next match, otherwise
-         * not.
-         */
-        int yy_at_bol;
+	{
+	FILE *yy_input_file;
+
+	char *yy_ch_buf;		/* input buffer */
+	char *yy_buf_pos;		/* current position in input buffer */
+
+	/* Size of input buffer in bytes, not including room for EOB
+	 * characters.
+	 */
+	int yy_buf_size;
+
+	/* Number of characters read into yy_ch_buf, not including EOB
+	 * characters.
+	 */
+	int yy_n_chars;
+
+	/* Whether we "own" the buffer - i.e., we know we created it,
+	 * and can realloc() it to grow it, and should free() it to
+	 * delete it.
+	 */
+	int yy_is_our_buffer;
+
+	/* Whether this is an "interactive" input source; if so, and
+	 * if we're using stdio for input, then we want to use getc()
+	 * instead of fread(), to make sure we stop fetching input after
+	 * each newline.
+	 */
+	int yy_is_interactive;
+
+	/* Whether we're considered to be at the beginning of a line.
+	 * If so, '^' rules will be active on the next match, otherwise
+	 * not.
+	 */
+	int yy_at_bol;
 
     int yy_bs_lineno; /**< The line count. */
     int yy_bs_column; /**< The column count. */
 
-        /* Whether to try to fill the input buffer when we reach the
-         * end of it.
-         */
-        int yy_fill_buffer;
+	/* Whether to try to fill the input buffer when we reach the
+	 * end of it.
+	 */
+	int yy_fill_buffer;
 
-        int yy_buffer_status;
+	int yy_buffer_status;
 
 #define YY_BUFFER_NEW 0
 #define YY_BUFFER_NORMAL 1
-        /* When an EOF's been seen but there's still some text to process
-         * then we mark the buffer as YY_EOF_PENDING, to indicate that we
-         * shouldn't try reading from the input source any more.  We might
-         * still have a bunch of tokens to match, though, because of
-         * possible backing-up.
-         *
-         * When we actually see the EOF, we change the status to "new"
-         * (via cmFortran_yyrestart()), so that the user can continue scanning by
-         * just pointing yyin at a new input file.
-         */
+	/* When an EOF's been seen but there's still some text to process
+	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
+	 * shouldn't try reading from the input source any more.  We might
+	 * still have a bunch of tokens to match, though, because of
+	 * possible backing-up.
+	 *
+	 * When we actually see the EOF, we change the status to "new"
+	 * (via cmFortran_yyrestart()), so that the user can continue scanning by
+	 * just pointing yyin at a new input file.
+	 */
 #define YY_BUFFER_EOF_PENDING 2
 
-        };
+	};
 #endif /* !YY_STRUCT_YY_BUFFER_STATE */
 
 /* We provide macros for accessing buffer states in case in the
@@ -314,7 +291,7 @@ static void cmFortran_yy_init_buffer (YY_BUFFER_STATE b,FILE *file ,yyscan_t yys
 
 YY_BUFFER_STATE cmFortran_yy_scan_buffer (char *base,yy_size_t size ,yyscan_t yyscanner );
 YY_BUFFER_STATE cmFortran_yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
-YY_BUFFER_STATE cmFortran_yy_scan_bytes (yyconst char *bytes,yy_size_t len ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmFortran_yy_scan_bytes (yyconst char *bytes,int len ,yyscan_t yyscanner );
 
 void *cmFortran_yyalloc (yy_size_t ,yyscan_t yyscanner );
 void *cmFortran_yyrealloc (void *,yy_size_t ,yyscan_t yyscanner );
@@ -323,30 +300,30 @@ void cmFortran_yyfree (void * ,yyscan_t yyscanner );
 #define yy_new_buffer cmFortran_yy_create_buffer
 
 #define yy_set_interactive(is_interactive) \
-        { \
-        if ( ! YY_CURRENT_BUFFER ){ \
+	{ \
+	if ( ! YY_CURRENT_BUFFER ){ \
         cmFortran_yyensure_buffer_stack (yyscanner); \
-                YY_CURRENT_BUFFER_LVALUE =    \
+		YY_CURRENT_BUFFER_LVALUE =    \
             cmFortran_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
-        } \
-        YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive; \
-        }
+	} \
+	YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive; \
+	}
 
 #define yy_set_bol(at_bol) \
-        { \
-        if ( ! YY_CURRENT_BUFFER ){\
+	{ \
+	if ( ! YY_CURRENT_BUFFER ){\
         cmFortran_yyensure_buffer_stack (yyscanner); \
-                YY_CURRENT_BUFFER_LVALUE =    \
+		YY_CURRENT_BUFFER_LVALUE =    \
             cmFortran_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
-        } \
-        YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
-        }
+	} \
+	YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
+	}
 
 #define YY_AT_BOL() (YY_CURRENT_BUFFER_LVALUE->yy_at_bol)
 
 /* Begin user sect3 */
 
-#define cmFortran_yywrap(yyscanner) 1
+#define cmFortran_yywrap(yyscanner) (/*CONSTCOND*/1)
 #define YY_SKIP_YYWRAP
 
 typedef unsigned char YY_CHAR;
@@ -358,27 +335,27 @@ typedef int yy_state_type;
 static yy_state_type yy_get_previous_state (yyscan_t yyscanner );
 static yy_state_type yy_try_NUL_trans (yy_state_type current_state  ,yyscan_t yyscanner);
 static int yy_get_next_buffer (yyscan_t yyscanner );
-static void yy_fatal_error (yyconst char msg[] ,yyscan_t yyscanner );
+static void yynoreturn yy_fatal_error (yyconst char* msg ,yyscan_t yyscanner );
 
 /* Done after the current pattern has been matched and before the
  * corresponding action - sets up yytext.
  */
 #define YY_DO_BEFORE_ACTION \
-        yyg->yytext_ptr = yy_bp; \
-        yyleng = (size_t) (yy_cp - yy_bp); \
-        yyg->yy_hold_char = *yy_cp; \
-        *yy_cp = '\0'; \
-        yyg->yy_c_buf_p = yy_cp;
+	yyg->yytext_ptr = yy_bp; \
+	yyleng = (int) (yy_cp - yy_bp); \
+	yyg->yy_hold_char = *yy_cp; \
+	*yy_cp = '\0'; \
+	yyg->yy_c_buf_p = yy_cp;
 
 #define YY_NUM_RULES 45
 #define YY_END_OF_BUFFER 46
 /* This struct is not used in this scanner,
    but its presence is necessary. */
 struct yy_trans_info
-        {
-        flex_int32_t yy_verify;
-        flex_int32_t yy_nxt;
-        };
+	{
+	flex_int32_t yy_verify;
+	flex_int32_t yy_nxt;
+	};
 static yyconst flex_int16_t yy_accept[173] =
     {   0,
         0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
@@ -402,7 +379,7 @@ static yyconst flex_int16_t yy_accept[173] =
        13,    0
     } ;
 
-static yyconst flex_int32_t yy_ec[256] =
+static yyconst YY_CHAR yy_ec[256] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
         1,    1,    4,    1,    1,    1,    1,    1,    1,    1,
@@ -434,7 +411,7 @@ static yyconst flex_int32_t yy_ec[256] =
         1,    1,    1,    1,    1
     } ;
 
-static yyconst flex_int32_t yy_meta[42] =
+static yyconst YY_CHAR yy_meta[42] =
     {   0,
         1,    2,    2,    3,    4,    3,    3,    1,    1,    3,
         3,    1,    3,    5,    1,    3,    1,    3,    6,    1,
@@ -443,7 +420,7 @@ static yyconst flex_int32_t yy_meta[42] =
         7
     } ;
 
-static yyconst flex_int16_t yy_base[182] =
+static yyconst flex_uint16_t yy_base[182] =
     {   0,
         0,   40,    0,   41,  220,   48,   44,   54,   56,   65,
       220,    0,  535,  535,  216,  535,   81,   74,  535,  535,
@@ -491,7 +468,7 @@ static yyconst flex_int16_t yy_def[182] =
       172
     } ;
 
-static yyconst flex_int16_t yy_nxt[577] =
+static yyconst flex_uint16_t yy_nxt[577] =
     {   0,
        12,   13,   14,   13,   13,   15,   16,   12,   17,   18,
        19,   12,   20,   12,   21,   22,   12,   23,   12,   24,
@@ -636,7 +613,7 @@ static yyconst flex_int16_t yy_chk[577] =
 #line 2 "cmFortranLexer.in.l"
 /*============================================================================
   CMake - Cross Platform Makefile Generator
-  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
+  Copyright 2000-2015 Kitware, Inc., Insight Software Consortium
 
   Distributed under the OSI-approved BSD License (the "License");
   see accompanying file Copyright.txt for details.
@@ -659,28 +636,21 @@ static yyconst flex_int16_t yy_chk[577] =
 
 This file must be translated to C and modified to build everywhere.
 
-Run flex like this:
+Run flex >= 2.6 like this:
 
   flex -i --prefix=cmFortran_yy --header-file=cmFortranLexer.h -ocmFortranLexer.cxx cmFortranLexer.in.l
 
 Modify cmFortranLexer.cxx:
-  - remove TABs
-  - remove use of the 'register' storage class specifier
-  - remove "yyscanner" argument from these methods:
-      yy_fatal_error, cmFortran_yyalloc, cmFortran_yyrealloc, cmFortran_yyfree
+  - remove trailing whitespace: sed -i 's/\s*$//' cmFortranLexer.h cmFortranLexer.cxx
+  - remove blank lines at end of file
   - remove "yyscanner = NULL" from end of cmFortran_yylex_destroy
   - remove all YY_BREAK lines occurring right after return statements
-  - change while ( 1 ) to for(;;)
-
-Modify cmFortranLexer.h:
-  - remove TABs
-  - remove the yy_init_globals function
-  - remove the block that includes unistd.h
-  - remove #line directives (avoids bogus warning on old Sun)
+  - add cast in cmFortran_yy_scan_bytes for loop condition of _yybytes_len to size_t
 
 */
 
 #include "cmStandardLexer.h"
+#undef YY_NO_UNPUT
 
 #define cmFortranLexer_cxx
 #include "cmFortranParser.h" /* Interface to parser object.  */
@@ -696,7 +666,7 @@ Modify cmFortranLexer.h:
 /*--------------------------------------------------------------------------*/
 
 
-#line 689 "cmFortranLexer.cxx"
+#line 670 "cmFortranLexer.cxx"
 
 #define INITIAL 0
 #define free_fmt 1
@@ -729,8 +699,8 @@ struct yyguts_t
     size_t yy_buffer_stack_max; /**< capacity of stack. */
     YY_BUFFER_STATE * yy_buffer_stack; /**< Stack as an array. */
     char yy_hold_char;
-    yy_size_t yy_n_chars;
-    yy_size_t yyleng_r;
+    int yy_n_chars;
+    int yyleng_r;
     char *yy_c_buf_p;
     int yy_init;
     int yy_start;
@@ -771,23 +741,23 @@ void cmFortran_yyset_extra (YY_EXTRA_TYPE user_defined ,yyscan_t yyscanner );
 
 FILE *cmFortran_yyget_in (yyscan_t yyscanner );
 
-void cmFortran_yyset_in  (FILE * in_str ,yyscan_t yyscanner );
+void cmFortran_yyset_in  (FILE * _in_str ,yyscan_t yyscanner );
 
 FILE *cmFortran_yyget_out (yyscan_t yyscanner );
 
-void cmFortran_yyset_out  (FILE * out_str ,yyscan_t yyscanner );
+void cmFortran_yyset_out  (FILE * _out_str ,yyscan_t yyscanner );
 
-yy_size_t cmFortran_yyget_leng (yyscan_t yyscanner );
+			int cmFortran_yyget_leng (yyscan_t yyscanner );
 
 char *cmFortran_yyget_text (yyscan_t yyscanner );
 
 int cmFortran_yyget_lineno (yyscan_t yyscanner );
 
-void cmFortran_yyset_lineno (int line_number ,yyscan_t yyscanner );
+void cmFortran_yyset_lineno (int _line_number ,yyscan_t yyscanner );
 
 int cmFortran_yyget_column  (yyscan_t yyscanner );
 
-void cmFortran_yyset_column (int column_no ,yyscan_t yyscanner );
+void cmFortran_yyset_column (int _column_no ,yyscan_t yyscanner );
 
 /* Macros after this point can all be overridden by user definitions in
  * section 1.
@@ -801,8 +771,12 @@ extern int cmFortran_yywrap (yyscan_t yyscanner );
 #endif
 #endif
 
+#ifndef YY_NO_UNPUT
+
     static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
 
+#endif
+
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -836,41 +810,41 @@ static int input (yyscan_t yyscanner );
 /* This used to be an fputs(), but since the string might contain NUL's,
  * we now use fwrite().
  */
-#define ECHO do { if (fwrite( yytext, yyleng, 1, yyout )) {} } while (0)
+#define ECHO do { if (fwrite( yytext, (size_t) yyleng, 1, yyout )) {} } while (0)
 #endif
 
 /* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
  * is returned in "result".
  */
 #ifndef YY_INPUT
 #define YY_INPUT(buf,result,max_size) \
-        if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \
-                { \
-                int c = '*'; \
-                size_t n; \
-                for ( n = 0; n < max_size && \
-                             (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
-                        buf[n] = (char) c; \
-                if ( c == '\n' ) \
-                        buf[n++] = (char) c; \
-                if ( c == EOF && ferror( yyin ) ) \
-                        YY_FATAL_ERROR( "input in flex scanner failed" ); \
-                result = n; \
-                } \
-        else \
-                { \
-                errno=0; \
-                while ( (result = fread(buf, 1, max_size, yyin))==0 && ferror(yyin)) \
-                        { \
-                        if( errno != EINTR) \
-                                { \
-                                YY_FATAL_ERROR( "input in flex scanner failed" ); \
-                                break; \
-                                } \
-                        errno=0; \
-                        clearerr(yyin); \
-                        } \
-                }\
+	if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \
+		{ \
+		int c = '*'; \
+		size_t n; \
+		for ( n = 0; n < max_size && \
+			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
+			buf[n] = (char) c; \
+		if ( c == '\n' ) \
+			buf[n++] = (char) c; \
+		if ( c == EOF && ferror( yyin ) ) \
+			YY_FATAL_ERROR( "input in flex scanner failed" ); \
+		result = n; \
+		} \
+	else \
+		{ \
+		errno=0; \
+		while ( (result = (int) fread(buf, 1, max_size, yyin))==0 && ferror(yyin)) \
+			{ \
+			if( errno != EINTR) \
+				{ \
+				YY_FATAL_ERROR( "input in flex scanner failed" ); \
+				break; \
+				} \
+			errno=0; \
+			clearerr(yyin); \
+			} \
+		}\
 \
 
 #endif
@@ -915,153 +889,153 @@ extern int cmFortran_yylex (yyscan_t yyscanner);
 
 /* Code executed at the end of each rule. */
 #ifndef YY_BREAK
-#define YY_BREAK break;
+#define YY_BREAK /*LINTED*/break;
 #endif
 
 #define YY_RULE_SETUP \
-        if ( yyleng > 0 ) \
-                YY_CURRENT_BUFFER_LVALUE->yy_at_bol = \
-                                (yytext[yyleng - 1] == '\n'); \
-        YY_USER_ACTION
+	if ( yyleng > 0 ) \
+		YY_CURRENT_BUFFER_LVALUE->yy_at_bol = \
+				(yytext[yyleng - 1] == '\n'); \
+	YY_USER_ACTION
 
 /** The main scanner function which does all the work.
  */
 YY_DECL
 {
-        yy_state_type yy_current_state;
-        char *yy_cp, *yy_bp;
-        int yy_act;
+	yy_state_type yy_current_state;
+	char *yy_cp, *yy_bp;
+	int yy_act;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        if ( !yyg->yy_init )
-                {
-                yyg->yy_init = 1;
+	if ( !yyg->yy_init )
+		{
+		yyg->yy_init = 1;
 
 #ifdef YY_USER_INIT
-                YY_USER_INIT;
+		YY_USER_INIT;
 #endif
 
-                if ( ! yyg->yy_start )
-                        yyg->yy_start = 1;      /* first start state */
+		if ( ! yyg->yy_start )
+			yyg->yy_start = 1;	/* first start state */
 
-                if ( ! yyin )
-                        yyin = stdin;
+		if ( ! yyin )
+			yyin = stdin;
 
-                if ( ! yyout )
-                        yyout = stdout;
+		if ( ! yyout )
+			yyout = stdout;
 
-                if ( ! YY_CURRENT_BUFFER ) {
-                        cmFortran_yyensure_buffer_stack (yyscanner);
-                        YY_CURRENT_BUFFER_LVALUE =
-                                cmFortran_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
-                }
+		if ( ! YY_CURRENT_BUFFER ) {
+			cmFortran_yyensure_buffer_stack (yyscanner);
+			YY_CURRENT_BUFFER_LVALUE =
+				cmFortran_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
+		}
 
-                cmFortran_yy_load_buffer_state(yyscanner );
-                }
+		cmFortran_yy_load_buffer_state(yyscanner );
+		}
 
-        {
-#line 72 "cmFortranLexer.in.l"
+	{
+#line 65 "cmFortranLexer.in.l"
 
 
-#line 956 "cmFortranLexer.cxx"
+#line 941 "cmFortranLexer.cxx"
 
-        for(;;)             /* loops until end-of-file is reached */
-                {
-                yy_cp = yyg->yy_c_buf_p;
+	while ( /*CONSTCOND*/1 )		/* loops until end-of-file is reached */
+		{
+		yy_cp = yyg->yy_c_buf_p;
 
-                /* Support of yytext. */
-                *yy_cp = yyg->yy_hold_char;
+		/* Support of yytext. */
+		*yy_cp = yyg->yy_hold_char;
 
-                /* yy_bp points to the position in yy_ch_buf of the start of
-                 * the current run.
-                 */
-                yy_bp = yy_cp;
+		/* yy_bp points to the position in yy_ch_buf of the start of
+		 * the current run.
+		 */
+		yy_bp = yy_cp;
 
-                yy_current_state = yyg->yy_start;
-                yy_current_state += YY_AT_BOL();
+		yy_current_state = yyg->yy_start;
+		yy_current_state += YY_AT_BOL();
 yy_match:
-                do
-                        {
-                        YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
-                        if ( yy_accept[yy_current_state] )
-                                {
-                                yyg->yy_last_accepting_state = yy_current_state;
-                                yyg->yy_last_accepting_cpos = yy_cp;
-                                }
-                        while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
-                                {
-                                yy_current_state = (int) yy_def[yy_current_state];
-                                if ( yy_current_state >= 173 )
-                                        yy_c = yy_meta[(unsigned int) yy_c];
-                                }
-                        yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-                        ++yy_cp;
-                        }
-                while ( yy_base[yy_current_state] != 535 );
+		do
+			{
+			YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
+			if ( yy_accept[yy_current_state] )
+				{
+				yyg->yy_last_accepting_state = yy_current_state;
+				yyg->yy_last_accepting_cpos = yy_cp;
+				}
+			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
+				{
+				yy_current_state = (int) yy_def[yy_current_state];
+				if ( yy_current_state >= 173 )
+					yy_c = yy_meta[(unsigned int) yy_c];
+				}
+			yy_current_state = yy_nxt[yy_base[yy_current_state] + (flex_int16_t) yy_c];
+			++yy_cp;
+			}
+		while ( yy_base[yy_current_state] != 535 );
 
 yy_find_action:
-                yy_act = yy_accept[yy_current_state];
-                if ( yy_act == 0 )
-                        { /* have to back up */
-                        yy_cp = yyg->yy_last_accepting_cpos;
-                        yy_current_state = yyg->yy_last_accepting_state;
-                        yy_act = yy_accept[yy_current_state];
-                        }
-
-                YY_DO_BEFORE_ACTION;
-
-do_action:      /* This label is used only to access EOF actions. */
-
-                switch ( yy_act )
-        { /* beginning of action switch */
-                        case 0: /* must back up */
-                        /* undo the effects of YY_DO_BEFORE_ACTION */
-                        *yy_cp = yyg->yy_hold_char;
-                        yy_cp = yyg->yy_last_accepting_cpos;
-                        yy_current_state = yyg->yy_last_accepting_state;
-                        goto yy_find_action;
+		yy_act = yy_accept[yy_current_state];
+		if ( yy_act == 0 )
+			{ /* have to back up */
+			yy_cp = yyg->yy_last_accepting_cpos;
+			yy_current_state = yyg->yy_last_accepting_state;
+			yy_act = yy_accept[yy_current_state];
+			}
+
+		YY_DO_BEFORE_ACTION;
+
+do_action:	/* This label is used only to access EOF actions. */
+
+		switch ( yy_act )
+	{ /* beginning of action switch */
+			case 0: /* must back up */
+			/* undo the effects of YY_DO_BEFORE_ACTION */
+			*yy_cp = yyg->yy_hold_char;
+			yy_cp = yyg->yy_last_accepting_cpos;
+			yy_current_state = yyg->yy_last_accepting_state;
+			goto yy_find_action;
 
 case 1:
 YY_RULE_SETUP
-#line 74 "cmFortranLexer.in.l"
+#line 67 "cmFortranLexer.in.l"
 {
   cmFortranParser_StringStart(yyextra);
   cmFortranParser_SetOldStartcond(yyextra, YY_START);
   BEGIN(str_dq);
 }
-        YY_BREAK
+	YY_BREAK
 case 2:
 YY_RULE_SETUP
-#line 80 "cmFortranLexer.in.l"
+#line 73 "cmFortranLexer.in.l"
 {
   cmFortranParser_StringStart(yyextra);
   cmFortranParser_SetOldStartcond(yyextra, YY_START);
   BEGIN(str_sq);
 }
-        YY_BREAK
+	YY_BREAK
 case 3:
-#line 87 "cmFortranLexer.in.l"
+#line 80 "cmFortranLexer.in.l"
 case 4:
 YY_RULE_SETUP
-#line 87 "cmFortranLexer.in.l"
+#line 80 "cmFortranLexer.in.l"
 {
   BEGIN(cmFortranParser_GetOldStartcond(yyextra) );
   yylvalp->string = strdup(cmFortranParser_StringEnd(yyextra));
   return STRING;
 }
 case 5:
 /* rule 5 can match eol */
-#line 94 "cmFortranLexer.in.l"
+#line 87 "cmFortranLexer.in.l"
 case 6:
 /* rule 6 can match eol */
 YY_RULE_SETUP
-#line 94 "cmFortranLexer.in.l"
+#line 87 "cmFortranLexer.in.l"
 /* Ignore (continued strings, free fmt) */
-        YY_BREAK
+	YY_BREAK
 case 7:
 /* rule 7 can match eol */
 YY_RULE_SETUP
-#line 96 "cmFortranLexer.in.l"
+#line 89 "cmFortranLexer.in.l"
 {
   if (cmFortranParser_GetOldStartcond(yyextra) == fixed_fmt)
     ; /* Ignore (cont. strings, fixed fmt) */
@@ -1070,572 +1044,576 @@ YY_RULE_SETUP
     unput(yytext[strlen(yytext)-1]);
     }
 }
-        YY_BREAK
+	YY_BREAK
 case 8:
 /* rule 8 can match eol */
 YY_RULE_SETUP
-#line 106 "cmFortranLexer.in.l"
+#line 99 "cmFortranLexer.in.l"
 {
   unput ('\n');
   BEGIN(INITIAL);
   return UNTERMINATED_STRING;
 }
 case 9:
 YY_RULE_SETUP
-#line 112 "cmFortranLexer.in.l"
+#line 105 "cmFortranLexer.in.l"
 {
   cmFortranParser_StringAppend(yyextra, yytext[0]);
 }
-        YY_BREAK
+	YY_BREAK
 case 10:
 /* rule 10 can match eol */
 YY_RULE_SETUP
-#line 116 "cmFortranLexer.in.l"
+#line 109 "cmFortranLexer.in.l"
 { return EOSTMT; } /* Treat comments like */
 case 11:
 /* rule 11 can match eol */
 YY_RULE_SETUP
-#line 117 "cmFortranLexer.in.l"
+#line 110 "cmFortranLexer.in.l"
 { return EOSTMT; } /* empty lines */
 case 12:
 YY_RULE_SETUP
-#line 119 "cmFortranLexer.in.l"
+#line 112 "cmFortranLexer.in.l"
 { return CPP_LINE_DIRECTIVE; }
 case 13:
 /* rule 13 can match eol */
 YY_RULE_SETUP
-#line 120 "cmFortranLexer.in.l"
+#line 113 "cmFortranLexer.in.l"
 {
   yytext[yyleng-1] = 0;
   yylvalp->string = strdup(strchr(yytext, '<')+1);
   return CPP_INCLUDE_ANGLE;
 }
 case 14:
 YY_RULE_SETUP
-#line 125 "cmFortranLexer.in.l"
+#line 118 "cmFortranLexer.in.l"
 { return CPP_INCLUDE; }
 case 15:
 YY_RULE_SETUP
-#line 126 "cmFortranLexer.in.l"
+#line 119 "cmFortranLexer.in.l"
 { return F90PPR_INCLUDE; }
 case 16:
 YY_RULE_SETUP
-#line 127 "cmFortranLexer.in.l"
+#line 120 "cmFortranLexer.in.l"
 { return COCO_INCLUDE; }
 case 17:
 YY_RULE_SETUP
-#line 129 "cmFortranLexer.in.l"
+#line 122 "cmFortranLexer.in.l"
 { return CPP_DEFINE; }
 case 18:
 YY_RULE_SETUP
-#line 130 "cmFortranLexer.in.l"
+#line 123 "cmFortranLexer.in.l"
 { return F90PPR_DEFINE; }
 case 19:
 YY_RULE_SETUP
-#line 132 "cmFortranLexer.in.l"
+#line 125 "cmFortranLexer.in.l"
 { return CPP_UNDEF; }
 case 20:
 YY_RULE_SETUP
-#line 133 "cmFortranLexer.in.l"
+#line 126 "cmFortranLexer.in.l"
 { return F90PPR_UNDEF; }
 case 21:
 YY_RULE_SETUP
-#line 135 "cmFortranLexer.in.l"
+#line 128 "cmFortranLexer.in.l"
 { return CPP_IFDEF; }
 case 22:
 YY_RULE_SETUP
-#line 136 "cmFortranLexer.in.l"
+#line 129 "cmFortranLexer.in.l"
 { return CPP_IFNDEF; }
 case 23:
 YY_RULE_SETUP
-#line 137 "cmFortranLexer.in.l"
+#line 130 "cmFortranLexer.in.l"
 { return CPP_IF; }
 case 24:
 YY_RULE_SETUP
-#line 138 "cmFortranLexer.in.l"
+#line 131 "cmFortranLexer.in.l"
 { return CPP_ELIF; }
 case 25:
 YY_RULE_SETUP
-#line 139 "cmFortranLexer.in.l"
+#line 132 "cmFortranLexer.in.l"
 { return CPP_ELSE; }
 case 26:
 YY_RULE_SETUP
-#line 140 "cmFortranLexer.in.l"
+#line 133 "cmFortranLexer.in.l"
 { return CPP_ENDIF; }
 case 27:
 YY_RULE_SETUP
-#line 142 "cmFortranLexer.in.l"
+#line 135 "cmFortranLexer.in.l"
 { return F90PPR_IFDEF; }
 case 28:
 YY_RULE_SETUP
-#line 143 "cmFortranLexer.in.l"
+#line 136 "cmFortranLexer.in.l"
 { return F90PPR_IFNDEF; }
 case 29:
 YY_RULE_SETUP
-#line 144 "cmFortranLexer.in.l"
+#line 137 "cmFortranLexer.in.l"
 { return F90PPR_IF; }
 case 30:
 YY_RULE_SETUP
-#line 145 "cmFortranLexer.in.l"
+#line 138 "cmFortranLexer.in.l"
 { return F90PPR_ELIF; }
 case 31:
 YY_RULE_SETUP
-#line 146 "cmFortranLexer.in.l"
+#line 139 "cmFortranLexer.in.l"
 { return F90PPR_ELSE; }
 case 32:
 YY_RULE_SETUP
-#line 147 "cmFortranLexer.in.l"
+#line 140 "cmFortranLexer.in.l"
 { return F90PPR_ENDIF; }
 /* Line continuations, possible involving comments.  */
 case 33:
 /* rule 33 can match eol */
 YY_RULE_SETUP
-#line 150 "cmFortranLexer.in.l"
+#line 143 "cmFortranLexer.in.l"
 
-        YY_BREAK
+	YY_BREAK
 case 34:
 /* rule 34 can match eol */
 YY_RULE_SETUP
-#line 151 "cmFortranLexer.in.l"
+#line 144 "cmFortranLexer.in.l"
 
-        YY_BREAK
+	YY_BREAK
 case 35:
 YY_RULE_SETUP
-#line 153 "cmFortranLexer.in.l"
+#line 146 "cmFortranLexer.in.l"
 { return COMMA; }
 case 36:
 YY_RULE_SETUP
-#line 155 "cmFortranLexer.in.l"
+#line 148 "cmFortranLexer.in.l"
 { return DCOLON; }
 case 37:
 /* rule 37 can match eol */
 YY_RULE_SETUP
-#line 157 "cmFortranLexer.in.l"
+#line 150 "cmFortranLexer.in.l"
 { return GARBAGE; }
 case 38:
 YY_RULE_SETUP
-#line 159 "cmFortranLexer.in.l"
+#line 152 "cmFortranLexer.in.l"
 { return ASSIGNMENT_OP; }
 case 39:
 YY_RULE_SETUP
-#line 161 "cmFortranLexer.in.l"
+#line 154 "cmFortranLexer.in.l"
 {
   yylvalp->string = strdup(yytext);
   return WORD;
 }
 case 40:
 YY_RULE_SETUP
-#line 166 "cmFortranLexer.in.l"
+#line 159 "cmFortranLexer.in.l"
 { return GARBAGE; }
 case 41:
 /* rule 41 can match eol */
 YY_RULE_SETUP
-#line 168 "cmFortranLexer.in.l"
+#line 161 "cmFortranLexer.in.l"
 { return EOSTMT; }
 case 42:
 YY_RULE_SETUP
-#line 171 "cmFortranLexer.in.l"
+#line 164 "cmFortranLexer.in.l"
 /* Ignore */
-        YY_BREAK
+	YY_BREAK
 case 43:
 /* rule 43 can match eol */
 YY_RULE_SETUP
-#line 172 "cmFortranLexer.in.l"
+#line 165 "cmFortranLexer.in.l"
 /* Ignore line-endings preceded by \ */
-        YY_BREAK
+	YY_BREAK
 case 44:
 YY_RULE_SETUP
-#line 174 "cmFortranLexer.in.l"
+#line 167 "cmFortranLexer.in.l"
 { return *yytext; }
 case YY_STATE_EOF(INITIAL):
 case YY_STATE_EOF(free_fmt):
 case YY_STATE_EOF(fixed_fmt):
 case YY_STATE_EOF(str_sq):
 case YY_STATE_EOF(str_dq):
-#line 176 "cmFortranLexer.in.l"
+#line 169 "cmFortranLexer.in.l"
 {
   if(!cmFortranParser_FilePop(yyextra) )
     {
     return YY_NULL;
     }
 }
-        YY_BREAK
+	YY_BREAK
 case 45:
 YY_RULE_SETUP
-#line 183 "cmFortranLexer.in.l"
+#line 176 "cmFortranLexer.in.l"
 ECHO;
-        YY_BREAK
-#line 1291 "cmFortranLexer.cxx"
-
-        case YY_END_OF_BUFFER:
-                {
-                /* Amount of text matched not including the EOB char. */
-                int yy_amount_of_matched_text = (int) (yy_cp - yyg->yytext_ptr) - 1;
-
-                /* Undo the effects of YY_DO_BEFORE_ACTION. */
-                *yy_cp = yyg->yy_hold_char;
-                YY_RESTORE_YY_MORE_OFFSET
-
-                if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW )
-                        {
-                        /* We're scanning a new file or input source.  It's
-                         * possible that this happened because the user
-                         * just pointed yyin at a new source and called
-                         * cmFortran_yylex().  If so, then we have to assure
-                         * consistency between YY_CURRENT_BUFFER and our
-                         * globals.  Here is the right place to do so, because
-                         * this is the first action (other than possibly a
-                         * back-up) that will match for the new input source.
-                         */
-                        yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
-                        YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
-                        YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
-                        }
-
-                /* Note that here we test for yy_c_buf_p "<=" to the position
-                 * of the first EOB in the buffer, since yy_c_buf_p will
-                 * already have been incremented past the NUL character
-                 * (since all states make transitions on EOB to the
-                 * end-of-buffer state).  Contrast this with the test
-                 * in input().
-                 */
-                if ( yyg->yy_c_buf_p <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
-                        { /* This was really a NUL. */
-                        yy_state_type yy_next_state;
-
-                        yyg->yy_c_buf_p = yyg->yytext_ptr + yy_amount_of_matched_text;
-
-                        yy_current_state = yy_get_previous_state( yyscanner );
-
-                        /* Okay, we're now positioned to make the NUL
-                         * transition.  We couldn't have
-                         * yy_get_previous_state() go ahead and do it
-                         * for us because it doesn't know how to deal
-                         * with the possibility of jamming (and we don't
-                         * want to build jamming into it because then it
-                         * will run more slowly).
-                         */
-
-                        yy_next_state = yy_try_NUL_trans( yy_current_state , yyscanner);
-
-                        yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
-
-                        if ( yy_next_state )
-                                {
-                                /* Consume the NUL. */
-                                yy_cp = ++yyg->yy_c_buf_p;
-                                yy_current_state = yy_next_state;
-                                goto yy_match;
-                                }
-
-                        else
-                                {
-                                yy_cp = yyg->yy_c_buf_p;
-                                goto yy_find_action;
-                                }
-                        }
-
-                else switch ( yy_get_next_buffer( yyscanner ) )
-                        {
-                        case EOB_ACT_END_OF_FILE:
-                                {
-                                yyg->yy_did_buffer_switch_on_eof = 0;
-
-                                if ( cmFortran_yywrap(yyscanner ) )
-                                        {
-                                        /* Note: because we've taken care in
-                                         * yy_get_next_buffer() to have set up
-                                         * yytext, we can now set up
-                                         * yy_c_buf_p so that if some total
-                                         * hoser (like flex itself) wants to
-                                         * call the scanner after we return the
-                                         * YY_NULL, it'll still work - another
-                                         * YY_NULL will get returned.
-                                         */
-                                        yyg->yy_c_buf_p = yyg->yytext_ptr + YY_MORE_ADJ;
-
-                                        yy_act = YY_STATE_EOF(YY_START);
-                                        goto do_action;
-                                        }
-
-                                else
-                                        {
-                                        if ( ! yyg->yy_did_buffer_switch_on_eof )
-                                                YY_NEW_FILE;
-                                        }
-                                break;
-                                }
-
-                        case EOB_ACT_CONTINUE_SCAN:
-                                yyg->yy_c_buf_p =
-                                        yyg->yytext_ptr + yy_amount_of_matched_text;
-
-                                yy_current_state = yy_get_previous_state( yyscanner );
-
-                                yy_cp = yyg->yy_c_buf_p;
-                                yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
-                                goto yy_match;
-
-                        case EOB_ACT_LAST_MATCH:
-                                yyg->yy_c_buf_p =
-                                &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars];
-
-                                yy_current_state = yy_get_previous_state( yyscanner );
-
-                                yy_cp = yyg->yy_c_buf_p;
-                                yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
-                                goto yy_find_action;
-                        }
-                break;
-                }
-
-        default:
-                YY_FATAL_ERROR(
-                        "fatal flex scanner internal error--no action found" );
-        } /* end of action switch */
-                } /* end of scanning one token */
-        } /* end of user's declarations */
+	YY_BREAK
+#line 1276 "cmFortranLexer.cxx"
+
+	case YY_END_OF_BUFFER:
+		{
+		/* Amount of text matched not including the EOB char. */
+		int yy_amount_of_matched_text = (int) (yy_cp - yyg->yytext_ptr) - 1;
+
+		/* Undo the effects of YY_DO_BEFORE_ACTION. */
+		*yy_cp = yyg->yy_hold_char;
+		YY_RESTORE_YY_MORE_OFFSET
+
+		if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW )
+			{
+			/* We're scanning a new file or input source.  It's
+			 * possible that this happened because the user
+			 * just pointed yyin at a new source and called
+			 * cmFortran_yylex().  If so, then we have to assure
+			 * consistency between YY_CURRENT_BUFFER and our
+			 * globals.  Here is the right place to do so, because
+			 * this is the first action (other than possibly a
+			 * back-up) that will match for the new input source.
+			 */
+			yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
+			YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
+			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
+			}
+
+		/* Note that here we test for yy_c_buf_p "<=" to the position
+		 * of the first EOB in the buffer, since yy_c_buf_p will
+		 * already have been incremented past the NUL character
+		 * (since all states make transitions on EOB to the
+		 * end-of-buffer state).  Contrast this with the test
+		 * in input().
+		 */
+		if ( yyg->yy_c_buf_p <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
+			{ /* This was really a NUL. */
+			yy_state_type yy_next_state;
+
+			yyg->yy_c_buf_p = yyg->yytext_ptr + yy_amount_of_matched_text;
+
+			yy_current_state = yy_get_previous_state( yyscanner );
+
+			/* Okay, we're now positioned to make the NUL
+			 * transition.  We couldn't have
+			 * yy_get_previous_state() go ahead and do it
+			 * for us because it doesn't know how to deal
+			 * with the possibility of jamming (and we don't
+			 * want to build jamming into it because then it
+			 * will run more slowly).
+			 */
+
+			yy_next_state = yy_try_NUL_trans( yy_current_state , yyscanner);
+
+			yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
+
+			if ( yy_next_state )
+				{
+				/* Consume the NUL. */
+				yy_cp = ++yyg->yy_c_buf_p;
+				yy_current_state = yy_next_state;
+				goto yy_match;
+				}
+
+			else
+				{
+				yy_cp = yyg->yy_c_buf_p;
+				goto yy_find_action;
+				}
+			}
+
+		else switch ( yy_get_next_buffer( yyscanner ) )
+			{
+			case EOB_ACT_END_OF_FILE:
+				{
+				yyg->yy_did_buffer_switch_on_eof = 0;
+
+				if ( cmFortran_yywrap(yyscanner ) )
+					{
+					/* Note: because we've taken care in
+					 * yy_get_next_buffer() to have set up
+					 * yytext, we can now set up
+					 * yy_c_buf_p so that if some total
+					 * hoser (like flex itself) wants to
+					 * call the scanner after we return the
+					 * YY_NULL, it'll still work - another
+					 * YY_NULL will get returned.
+					 */
+					yyg->yy_c_buf_p = yyg->yytext_ptr + YY_MORE_ADJ;
+
+					yy_act = YY_STATE_EOF(YY_START);
+					goto do_action;
+					}
+
+				else
+					{
+					if ( ! yyg->yy_did_buffer_switch_on_eof )
+						YY_NEW_FILE;
+					}
+				break;
+				}
+
+			case EOB_ACT_CONTINUE_SCAN:
+				yyg->yy_c_buf_p =
+					yyg->yytext_ptr + yy_amount_of_matched_text;
+
+				yy_current_state = yy_get_previous_state( yyscanner );
+
+				yy_cp = yyg->yy_c_buf_p;
+				yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
+				goto yy_match;
+
+			case EOB_ACT_LAST_MATCH:
+				yyg->yy_c_buf_p =
+				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars];
+
+				yy_current_state = yy_get_previous_state( yyscanner );
+
+				yy_cp = yyg->yy_c_buf_p;
+				yy_bp = yyg->yytext_ptr + YY_MORE_ADJ;
+				goto yy_find_action;
+			}
+		break;
+		}
+
+	default:
+		YY_FATAL_ERROR(
+			"fatal flex scanner internal error--no action found" );
+	} /* end of action switch */
+		} /* end of scanning one token */
+	} /* end of user's declarations */
 } /* end of cmFortran_yylex */
 
 /* yy_get_next_buffer - try to read in a new buffer
  *
  * Returns a code representing an action:
- *      EOB_ACT_LAST_MATCH -
- *      EOB_ACT_CONTINUE_SCAN - continue scanning from current position
- *      EOB_ACT_END_OF_FILE - end of file
+ *	EOB_ACT_LAST_MATCH -
+ *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
+ *	EOB_ACT_END_OF_FILE - end of file
  */
 static int yy_get_next_buffer (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
-        char *source = yyg->yytext_ptr;
-        int number_to_move, i;
-        int ret_val;
-
-        if ( yyg->yy_c_buf_p > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] )
-                YY_FATAL_ERROR(
-                "fatal flex scanner internal error--end of buffer missed" );
-
-        if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )
-                { /* Don't try to fill the buffer, so this is an EOF. */
-                if ( yyg->yy_c_buf_p - yyg->yytext_ptr - YY_MORE_ADJ == 1 )
-                        {
-                        /* We matched a single character, the EOB, so
-                         * treat this as a final EOF.
-                         */
-                        return EOB_ACT_END_OF_FILE;
-                        }
-
-                else
-                        {
-                        /* We matched some text prior to the EOB, first
-                         * process it.
-                         */
-                        return EOB_ACT_LAST_MATCH;
-                        }
-                }
-
-        /* Try to read more data. */
-
-        /* First move last chars to start of buffer. */
-        number_to_move = (int) (yyg->yy_c_buf_p - yyg->yytext_ptr) - 1;
-
-        for ( i = 0; i < number_to_move; ++i )
-                *(dest++) = *(source++);
-
-        if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
-                /* don't do the read, it's not guaranteed to return an EOF,
-                 * just force an EOF
-                 */
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars = 0;
-
-        else
-                {
-                        yy_size_t num_to_read =
-                        YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
-
-                while ( num_to_read <= 0 )
-                        { /* Not enough room in the buffer - grow it. */
-
-                        /* just a shorter name for the current buffer */
-                        YY_BUFFER_STATE b = YY_CURRENT_BUFFER_LVALUE;
-
-                        int yy_c_buf_p_offset =
-                                (int) (yyg->yy_c_buf_p - b->yy_ch_buf);
-
-                        if ( b->yy_is_our_buffer )
-                                {
-                                yy_size_t new_size = b->yy_buf_size * 2;
-
-                                if ( new_size <= 0 )
-                                        b->yy_buf_size += b->yy_buf_size / 8;
-                                else
-                                        b->yy_buf_size *= 2;
-
-                                b->yy_ch_buf = (char *)
-                                        /* Include room in for 2 EOB chars. */
-                                        cmFortran_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
-                                }
-                        else
-                                /* Can't grow it, we don't own it. */
-                                b->yy_ch_buf = 0;
-
-                        if ( ! b->yy_ch_buf )
-                                YY_FATAL_ERROR(
-                                "fatal error - scanner input buffer overflow" );
-
-                        yyg->yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];
-
-                        num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
-                                                number_to_move - 1;
-
-                        }
-
-                if ( num_to_read > YY_READ_BUF_SIZE )
-                        num_to_read = YY_READ_BUF_SIZE;
-
-                /* Read in more data. */
-                YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
-                        yyg->yy_n_chars, num_to_read );
-
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
-                }
-
-        if ( yyg->yy_n_chars == 0 )
-                {
-                if ( number_to_move == YY_MORE_ADJ )
-                        {
-                        ret_val = EOB_ACT_END_OF_FILE;
-                        cmFortran_yyrestart(yyin  ,yyscanner);
-                        }
-
-                else
-                        {
-                        ret_val = EOB_ACT_LAST_MATCH;
-                        YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =
-                                YY_BUFFER_EOF_PENDING;
-                        }
-                }
-
-        else
-                ret_val = EOB_ACT_CONTINUE_SCAN;
-
-        if ((yy_size_t) (yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
-                /* Extend the array by 50%, plus the number we really need. */
-                yy_size_t new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);
-                YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmFortran_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );
-                if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
-                        YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
-        }
-
-        yyg->yy_n_chars += number_to_move;
-        YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
-        YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
-
-        yyg->yytext_ptr = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];
+	char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
+	char *source = yyg->yytext_ptr;
+	yy_size_t number_to_move, i;
+	int ret_val;
+
+	if ( yyg->yy_c_buf_p > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] )
+		YY_FATAL_ERROR(
+		"fatal flex scanner internal error--end of buffer missed" );
+
+	if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )
+		{ /* Don't try to fill the buffer, so this is an EOF. */
+		if ( yyg->yy_c_buf_p - yyg->yytext_ptr - YY_MORE_ADJ == 1 )
+			{
+			/* We matched a single character, the EOB, so
+			 * treat this as a final EOF.
+			 */
+			return EOB_ACT_END_OF_FILE;
+			}
+
+		else
+			{
+			/* We matched some text prior to the EOB, first
+			 * process it.
+			 */
+			return EOB_ACT_LAST_MATCH;
+			}
+		}
+
+	/* Try to read more data. */
+
+	/* First move last chars to start of buffer. */
+	number_to_move = (yy_size_t) (yyg->yy_c_buf_p - yyg->yytext_ptr) - 1;
+
+	for ( i = 0; i < number_to_move; ++i )
+		*(dest++) = *(source++);
+
+	if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
+		/* don't do the read, it's not guaranteed to return an EOF,
+		 * just force an EOF
+		 */
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars = 0;
+
+	else
+		{
+			int num_to_read =
+			YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
+
+		while ( num_to_read <= 0 )
+			{ /* Not enough room in the buffer - grow it. */
+
+			/* just a shorter name for the current buffer */
+			YY_BUFFER_STATE b = YY_CURRENT_BUFFER_LVALUE;
+
+			int yy_c_buf_p_offset =
+				(int) (yyg->yy_c_buf_p - b->yy_ch_buf);
+
+			if ( b->yy_is_our_buffer )
+				{
+				int new_size = b->yy_buf_size * 2;
+
+				if ( new_size <= 0 )
+					b->yy_buf_size += b->yy_buf_size / 8;
+				else
+					b->yy_buf_size *= 2;
+
+				b->yy_ch_buf = (char *)
+					/* Include room in for 2 EOB chars. */
+					cmFortran_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
+				}
+			else
+				/* Can't grow it, we don't own it. */
+				b->yy_ch_buf = NULL;
+
+			if ( ! b->yy_ch_buf )
+				YY_FATAL_ERROR(
+				"fatal error - scanner input buffer overflow" );
+
+			yyg->yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];
+
+			num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
+						number_to_move - 1;
+
+			}
+
+		if ( num_to_read > YY_READ_BUF_SIZE )
+			num_to_read = YY_READ_BUF_SIZE;
+
+		/* Read in more data. */
+		YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
+			yyg->yy_n_chars, num_to_read );
+
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
+		}
+
+	if ( yyg->yy_n_chars == 0 )
+		{
+		if ( number_to_move == YY_MORE_ADJ )
+			{
+			ret_val = EOB_ACT_END_OF_FILE;
+			cmFortran_yyrestart(yyin  ,yyscanner);
+			}
+
+		else
+			{
+			ret_val = EOB_ACT_LAST_MATCH;
+			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =
+				YY_BUFFER_EOF_PENDING;
+			}
+		}
+
+	else
+		ret_val = EOB_ACT_CONTINUE_SCAN;
+
+	if ((int) (yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
+		/* Extend the array by 50%, plus the number we really need. */
+		int new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);
+		YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmFortran_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );
+		if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
+			YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
+	}
+
+	yyg->yy_n_chars += number_to_move;
+	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
+	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
+
+	yyg->yytext_ptr = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];
 
-        return ret_val;
+	return ret_val;
 }
 
 /* yy_get_previous_state - get the state just before the EOB char was reached */
 
     static yy_state_type yy_get_previous_state (yyscan_t yyscanner)
 {
-        yy_state_type yy_current_state;
-        char *yy_cp;
+	yy_state_type yy_current_state;
+	char *yy_cp;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        yy_current_state = yyg->yy_start;
-        yy_current_state += YY_AT_BOL();
-
-        for ( yy_cp = yyg->yytext_ptr + YY_MORE_ADJ; yy_cp < yyg->yy_c_buf_p; ++yy_cp )
-                {
-                YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
-                if ( yy_accept[yy_current_state] )
-                        {
-                        yyg->yy_last_accepting_state = yy_current_state;
-                        yyg->yy_last_accepting_cpos = yy_cp;
-                        }
-                while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
-                        {
-                        yy_current_state = (int) yy_def[yy_current_state];
-                        if ( yy_current_state >= 173 )
-                                yy_c = yy_meta[(unsigned int) yy_c];
-                        }
-                yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-                }
-
-        return yy_current_state;
+	yy_current_state = yyg->yy_start;
+	yy_current_state += YY_AT_BOL();
+
+	for ( yy_cp = yyg->yytext_ptr + YY_MORE_ADJ; yy_cp < yyg->yy_c_buf_p; ++yy_cp )
+		{
+		YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
+		if ( yy_accept[yy_current_state] )
+			{
+			yyg->yy_last_accepting_state = yy_current_state;
+			yyg->yy_last_accepting_cpos = yy_cp;
+			}
+		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
+			{
+			yy_current_state = (int) yy_def[yy_current_state];
+			if ( yy_current_state >= 173 )
+				yy_c = yy_meta[(unsigned int) yy_c];
+			}
+		yy_current_state = yy_nxt[yy_base[yy_current_state] + (flex_int16_t) yy_c];
+		}
+
+	return yy_current_state;
 }
 
 /* yy_try_NUL_trans - try to make a transition on the NUL character
  *
  * synopsis
- *      next_state = yy_try_NUL_trans( current_state );
+ *	next_state = yy_try_NUL_trans( current_state );
  */
     static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state , yyscan_t yyscanner)
 {
-        int yy_is_jam;
+	int yy_is_jam;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner; /* This var may be unused depending upon options. */
-        char *yy_cp = yyg->yy_c_buf_p;
-
-        YY_CHAR yy_c = 1;
-        if ( yy_accept[yy_current_state] )
-                {
-                yyg->yy_last_accepting_state = yy_current_state;
-                yyg->yy_last_accepting_cpos = yy_cp;
-                }
-        while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
-                {
-                yy_current_state = (int) yy_def[yy_current_state];
-                if ( yy_current_state >= 173 )
-                        yy_c = yy_meta[(unsigned int) yy_c];
-                }
-        yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-        yy_is_jam = (yy_current_state == 172);
-
-        (void)yyg;
-        return yy_is_jam ? 0 : yy_current_state;
+	char *yy_cp = yyg->yy_c_buf_p;
+
+	YY_CHAR yy_c = 1;
+	if ( yy_accept[yy_current_state] )
+		{
+		yyg->yy_last_accepting_state = yy_current_state;
+		yyg->yy_last_accepting_cpos = yy_cp;
+		}
+	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
+		{
+		yy_current_state = (int) yy_def[yy_current_state];
+		if ( yy_current_state >= 173 )
+			yy_c = yy_meta[(unsigned int) yy_c];
+		}
+	yy_current_state = yy_nxt[yy_base[yy_current_state] + (flex_int16_t) yy_c];
+	yy_is_jam = (yy_current_state == 172);
+
+	(void)yyg;
+	return yy_is_jam ? 0 : yy_current_state;
 }
 
+#ifndef YY_NO_UNPUT
+
     static void yyunput (int c, char * yy_bp , yyscan_t yyscanner)
 {
-        char *yy_cp;
+	char *yy_cp;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
     yy_cp = yyg->yy_c_buf_p;
 
-        /* undo effects of setting up yytext */
-        *yy_cp = yyg->yy_hold_char;
+	/* undo effects of setting up yytext */
+	*yy_cp = yyg->yy_hold_char;
 
-        if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
-                { /* need to shift things up to make room */
-                /* +2 for EOB chars. */
-                yy_size_t number_to_move = yyg->yy_n_chars + 2;
-                char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
-                                        YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
-                char *source =
-                                &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];
+	if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
+		{ /* need to shift things up to make room */
+		/* +2 for EOB chars. */
+		int number_to_move = yyg->yy_n_chars + 2;
+		char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
+					YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
+		char *source =
+				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];
 
-                while ( source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
-                        *--dest = *--source;
+		while ( source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
+			*--dest = *--source;
 
-                yy_cp += (int) (dest - source);
-                yy_bp += (int) (dest - source);
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars =
-                        yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_buf_size;
+		yy_cp += (int) (dest - source);
+		yy_bp += (int) (dest - source);
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars =
+			yyg->yy_n_chars = (int) YY_CURRENT_BUFFER_LVALUE->yy_buf_size;
 
-                if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
-                        YY_FATAL_ERROR( "flex scanner push-back overflow" );
-                }
+		if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
+			YY_FATAL_ERROR( "flex scanner push-back overflow" );
+		}
 
-        *--yy_cp = (char) c;
+	*--yy_cp = (char) c;
 
-        yyg->yytext_ptr = yy_bp;
-        yyg->yy_hold_char = *yy_cp;
-        yyg->yy_c_buf_p = yy_cp;
+	yyg->yytext_ptr = yy_bp;
+	yyg->yy_hold_char = *yy_cp;
+	yyg->yy_c_buf_p = yy_cp;
 }
 
+#endif
+
 #ifndef YY_NO_INPUT
 #ifdef __cplusplus
     static int yyinput (yyscan_t yyscanner)
@@ -1644,74 +1622,74 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 #endif
 
 {
-        int c;
+	int c;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        *yyg->yy_c_buf_p = yyg->yy_hold_char;
-
-        if ( *yyg->yy_c_buf_p == YY_END_OF_BUFFER_CHAR )
-                {
-                /* yy_c_buf_p now points to the character we want to return.
-                 * If this occurs *before* the EOB characters, then it's a
-                 * valid NUL; if not, then we've hit the end of the buffer.
-                 */
-                if ( yyg->yy_c_buf_p < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
-                        /* This was really a NUL. */
-                        *yyg->yy_c_buf_p = '\0';
-
-                else
-                        { /* need more input */
-                        yy_size_t offset = yyg->yy_c_buf_p - yyg->yytext_ptr;
-                        ++yyg->yy_c_buf_p;
-
-                        switch ( yy_get_next_buffer( yyscanner ) )
-                                {
-                                case EOB_ACT_LAST_MATCH:
-                                        /* This happens because yy_g_n_b()
-                                         * sees that we've accumulated a
-                                         * token and flags that we need to
-                                         * try matching the token before
-                                         * proceeding.  But for input(),
-                                         * there's no matching to consider.
-                                         * So convert the EOB_ACT_LAST_MATCH
-                                         * to EOB_ACT_END_OF_FILE.
-                                         */
-
-                                        /* Reset buffer status. */
-                                        cmFortran_yyrestart(yyin ,yyscanner);
-
-                                        /*FALLTHROUGH*/
-
-                                case EOB_ACT_END_OF_FILE:
-                                        {
-                                        if ( cmFortran_yywrap(yyscanner ) )
-                                                return EOF;
-
-                                        if ( ! yyg->yy_did_buffer_switch_on_eof )
-                                                YY_NEW_FILE;
+	*yyg->yy_c_buf_p = yyg->yy_hold_char;
+
+	if ( *yyg->yy_c_buf_p == YY_END_OF_BUFFER_CHAR )
+		{
+		/* yy_c_buf_p now points to the character we want to return.
+		 * If this occurs *before* the EOB characters, then it's a
+		 * valid NUL; if not, then we've hit the end of the buffer.
+		 */
+		if ( yyg->yy_c_buf_p < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] )
+			/* This was really a NUL. */
+			*yyg->yy_c_buf_p = '\0';
+
+		else
+			{ /* need more input */
+			int offset = yyg->yy_c_buf_p - yyg->yytext_ptr;
+			++yyg->yy_c_buf_p;
+
+			switch ( yy_get_next_buffer( yyscanner ) )
+				{
+				case EOB_ACT_LAST_MATCH:
+					/* This happens because yy_g_n_b()
+					 * sees that we've accumulated a
+					 * token and flags that we need to
+					 * try matching the token before
+					 * proceeding.  But for input(),
+					 * there's no matching to consider.
+					 * So convert the EOB_ACT_LAST_MATCH
+					 * to EOB_ACT_END_OF_FILE.
+					 */
+
+					/* Reset buffer status. */
+					cmFortran_yyrestart(yyin ,yyscanner);
+
+					/*FALLTHROUGH*/
+
+				case EOB_ACT_END_OF_FILE:
+					{
+					if ( cmFortran_yywrap(yyscanner ) )
+						return 0;
+
+					if ( ! yyg->yy_did_buffer_switch_on_eof )
+						YY_NEW_FILE;
 #ifdef __cplusplus
-                                        return yyinput(yyscanner);
+					return yyinput(yyscanner);
 #else
-                                        return input(yyscanner);
+					return input(yyscanner);
 #endif
-                                        }
+					}
 
-                                case EOB_ACT_CONTINUE_SCAN:
-                                        yyg->yy_c_buf_p = yyg->yytext_ptr + offset;
-                                        break;
-                                }
-                        }
-                }
+				case EOB_ACT_CONTINUE_SCAN:
+					yyg->yy_c_buf_p = yyg->yytext_ptr + offset;
+					break;
+				}
+			}
+		}
 
-        c = *(unsigned char *) yyg->yy_c_buf_p; /* cast for 8-bit char's */
-        *yyg->yy_c_buf_p = '\0';        /* preserve yytext */
-        yyg->yy_hold_char = *++yyg->yy_c_buf_p;
+	c = *(unsigned char *) yyg->yy_c_buf_p;	/* cast for 8-bit char's */
+	*yyg->yy_c_buf_p = '\0';	/* preserve yytext */
+	yyg->yy_hold_char = *++yyg->yy_c_buf_p;
 
-        YY_CURRENT_BUFFER_LVALUE->yy_at_bol = (c == '\n');
+	YY_CURRENT_BUFFER_LVALUE->yy_at_bol = (c == '\n');
 
-        return c;
+	return c;
 }
-#endif  /* ifndef YY_NO_INPUT */
+#endif	/* ifndef YY_NO_INPUT */
 
 /** Immediately switch to a different input stream.
  * @param input_file A readable stream.
@@ -1722,14 +1700,14 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        if ( ! YY_CURRENT_BUFFER ){
+	if ( ! YY_CURRENT_BUFFER ){
         cmFortran_yyensure_buffer_stack (yyscanner);
-                YY_CURRENT_BUFFER_LVALUE =
+		YY_CURRENT_BUFFER_LVALUE =
             cmFortran_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
-        }
+	}
 
-        cmFortran_yy_init_buffer(YY_CURRENT_BUFFER,input_file ,yyscanner);
-        cmFortran_yy_load_buffer_state(yyscanner );
+	cmFortran_yy_init_buffer(YY_CURRENT_BUFFER,input_file ,yyscanner);
+	cmFortran_yy_load_buffer_state(yyscanner );
 }
 
 /** Switch to a different input buffer.
@@ -1740,41 +1718,41 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        /* TODO. We should be able to replace this entire function body
-         * with
-         *              cmFortran_yypop_buffer_state();
-         *              cmFortran_yypush_buffer_state(new_buffer);
+	/* TODO. We should be able to replace this entire function body
+	 * with
+	 *		cmFortran_yypop_buffer_state();
+	 *		cmFortran_yypush_buffer_state(new_buffer);
      */
-        cmFortran_yyensure_buffer_stack (yyscanner);
-        if ( YY_CURRENT_BUFFER == new_buffer )
-                return;
-
-        if ( YY_CURRENT_BUFFER )
-                {
-                /* Flush out information for old buffer. */
-                *yyg->yy_c_buf_p = yyg->yy_hold_char;
-                YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
-                }
-
-        YY_CURRENT_BUFFER_LVALUE = new_buffer;
-        cmFortran_yy_load_buffer_state(yyscanner );
-
-        /* We don't actually know whether we did this switch during
-         * EOF (cmFortran_yywrap()) processing, but the only time this flag
-         * is looked at is after cmFortran_yywrap() is called, so it's safe
-         * to go ahead and always set it.
-         */
-        yyg->yy_did_buffer_switch_on_eof = 1;
+	cmFortran_yyensure_buffer_stack (yyscanner);
+	if ( YY_CURRENT_BUFFER == new_buffer )
+		return;
+
+	if ( YY_CURRENT_BUFFER )
+		{
+		/* Flush out information for old buffer. */
+		*yyg->yy_c_buf_p = yyg->yy_hold_char;
+		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
+		}
+
+	YY_CURRENT_BUFFER_LVALUE = new_buffer;
+	cmFortran_yy_load_buffer_state(yyscanner );
+
+	/* We don't actually know whether we did this switch during
+	 * EOF (cmFortran_yywrap()) processing, but the only time this flag
+	 * is looked at is after cmFortran_yywrap() is called, so it's safe
+	 * to go ahead and always set it.
+	 */
+	yyg->yy_did_buffer_switch_on_eof = 1;
 }
 
 static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
-        yyg->yytext_ptr = yyg->yy_c_buf_p = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
-        yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
-        yyg->yy_hold_char = *yyg->yy_c_buf_p;
+	yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
+	yyg->yytext_ptr = yyg->yy_c_buf_p = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
+	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
+	yyg->yy_hold_char = *yyg->yy_c_buf_p;
 }
 
 /** Allocate and initialize an input buffer state.
@@ -1785,26 +1763,26 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
  */
     YY_BUFFER_STATE cmFortran_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
-        YY_BUFFER_STATE b;
+	YY_BUFFER_STATE b;
 
-        b = (YY_BUFFER_STATE) cmFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
-        if ( ! b )
-                YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_create_buffer()" );
+	b = (YY_BUFFER_STATE) cmFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
+	if ( ! b )
+		YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_create_buffer()" );
 
-        b->yy_buf_size = size;
+	b->yy_buf_size = (yy_size_t)size;
 
-        /* yy_ch_buf has to be 2 characters longer than the size given because
-         * we need to put in 2 end-of-buffer characters.
-         */
-        b->yy_ch_buf = (char *) cmFortran_yyalloc(b->yy_buf_size + 2 ,yyscanner );
-        if ( ! b->yy_ch_buf )
-                YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_create_buffer()" );
+	/* yy_ch_buf has to be 2 characters longer than the size given because
+	 * we need to put in 2 end-of-buffer characters.
+	 */
+	b->yy_ch_buf = (char *) cmFortran_yyalloc(b->yy_buf_size + 2 ,yyscanner );
+	if ( ! b->yy_ch_buf )
+		YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_create_buffer()" );
 
-        b->yy_is_our_buffer = 1;
+	b->yy_is_our_buffer = 1;
 
-        cmFortran_yy_init_buffer(b,file ,yyscanner);
+	cmFortran_yy_init_buffer(b,file ,yyscanner);
 
-        return b;
+	return b;
 }
 
 /** Destroy the buffer.
@@ -1815,16 +1793,16 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        if ( ! b )
-                return;
+	if ( ! b )
+		return;
 
-        if ( b == YY_CURRENT_BUFFER ) /* Not sure if we should pop here. */
-                YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;
+	if ( b == YY_CURRENT_BUFFER ) /* Not sure if we should pop here. */
+		YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;
 
-        if ( b->yy_is_our_buffer )
-                cmFortran_yyfree((void *) b->yy_ch_buf ,yyscanner );
+	if ( b->yy_is_our_buffer )
+		cmFortran_yyfree((void *) b->yy_ch_buf ,yyscanner );
 
-        cmFortran_yyfree((void *) b ,yyscanner );
+	cmFortran_yyfree((void *) b ,yyscanner );
 }
 
 /* Initializes or reinitializes a buffer.
@@ -1834,13 +1812,13 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
     static void cmFortran_yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file , yyscan_t yyscanner)
 
 {
-        int oerrno = errno;
+	int oerrno = errno;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        cmFortran_yy_flush_buffer(b ,yyscanner);
+	cmFortran_yy_flush_buffer(b ,yyscanner);
 
-        b->yy_input_file = file;
-        b->yy_fill_buffer = 1;
+	b->yy_input_file = file;
+	b->yy_fill_buffer = 1;
 
     /* If b is the current buffer, then cmFortran_yy_init_buffer was _probably_
      * called from cmFortran_yyrestart() or through yy_get_next_buffer.
@@ -1853,7 +1831,7 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
 
-        errno = oerrno;
+	errno = oerrno;
 }
 
 /** Discard all buffered characters. On the next scan, YY_INPUT will be called.
@@ -1863,25 +1841,25 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
     void cmFortran_yy_flush_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        if ( ! b )
-                return;
+	if ( ! b )
+		return;
 
-        b->yy_n_chars = 0;
+	b->yy_n_chars = 0;
 
-        /* We always need two end-of-buffer characters.  The first causes
-         * a transition to the end-of-buffer state.  The second causes
-         * a jam in that state.
-         */
-        b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
-        b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
+	/* We always need two end-of-buffer characters.  The first causes
+	 * a transition to the end-of-buffer state.  The second causes
+	 * a jam in that state.
+	 */
+	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
+	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
 
-        b->yy_buf_pos = &b->yy_ch_buf[0];
+	b->yy_buf_pos = &b->yy_ch_buf[0];
 
-        b->yy_at_bol = 1;
-        b->yy_buffer_status = YY_BUFFER_NEW;
+	b->yy_at_bol = 1;
+	b->yy_buffer_status = YY_BUFFER_NEW;
 
-        if ( b == YY_CURRENT_BUFFER )
-                cmFortran_yy_load_buffer_state(yyscanner );
+	if ( b == YY_CURRENT_BUFFER )
+		cmFortran_yy_load_buffer_state(yyscanner );
 }
 
 /** Pushes the new state onto the stack. The new state becomes
@@ -1893,28 +1871,28 @@ static void cmFortran_yy_load_buffer_state  (yyscan_t yyscanner)
 void cmFortran_yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        if (new_buffer == NULL)
-                return;
-
-        cmFortran_yyensure_buffer_stack(yyscanner);
-
-        /* This block is copied from cmFortran_yy_switch_to_buffer. */
-        if ( YY_CURRENT_BUFFER )
-                {
-                /* Flush out information for old buffer. */
-                *yyg->yy_c_buf_p = yyg->yy_hold_char;
-                YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
-                }
-
-        /* Only push if top exists. Otherwise, replace top. */
-        if (YY_CURRENT_BUFFER)
-                yyg->yy_buffer_stack_top++;
-        YY_CURRENT_BUFFER_LVALUE = new_buffer;
-
-        /* copied from cmFortran_yy_switch_to_buffer. */
-        cmFortran_yy_load_buffer_state(yyscanner );
-        yyg->yy_did_buffer_switch_on_eof = 1;
+	if (new_buffer == NULL)
+		return;
+
+	cmFortran_yyensure_buffer_stack(yyscanner);
+
+	/* This block is copied from cmFortran_yy_switch_to_buffer. */
+	if ( YY_CURRENT_BUFFER )
+		{
+		/* Flush out information for old buffer. */
+		*yyg->yy_c_buf_p = yyg->yy_hold_char;
+		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
+		}
+
+	/* Only push if top exists. Otherwise, replace top. */
+	if (YY_CURRENT_BUFFER)
+		yyg->yy_buffer_stack_top++;
+	YY_CURRENT_BUFFER_LVALUE = new_buffer;
+
+	/* copied from cmFortran_yy_switch_to_buffer. */
+	cmFortran_yy_load_buffer_state(yyscanner );
+	yyg->yy_did_buffer_switch_on_eof = 1;
 }
 
 /** Removes and deletes the top of the stack, if present.
@@ -1924,65 +1902,65 @@ void cmFortran_yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscan
 void cmFortran_yypop_buffer_state (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        if (!YY_CURRENT_BUFFER)
-                return;
-
-        cmFortran_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
-        YY_CURRENT_BUFFER_LVALUE = NULL;
-        if (yyg->yy_buffer_stack_top > 0)
-                --yyg->yy_buffer_stack_top;
-
-        if (YY_CURRENT_BUFFER) {
-                cmFortran_yy_load_buffer_state(yyscanner );
-                yyg->yy_did_buffer_switch_on_eof = 1;
-        }
+	if (!YY_CURRENT_BUFFER)
+		return;
+
+	cmFortran_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
+	YY_CURRENT_BUFFER_LVALUE = NULL;
+	if (yyg->yy_buffer_stack_top > 0)
+		--yyg->yy_buffer_stack_top;
+
+	if (YY_CURRENT_BUFFER) {
+		cmFortran_yy_load_buffer_state(yyscanner );
+		yyg->yy_did_buffer_switch_on_eof = 1;
+	}
 }
 
 /* Allocates the stack if it does not exist.
  *  Guarantees space for at least one push.
  */
 static void cmFortran_yyensure_buffer_stack (yyscan_t yyscanner)
 {
-        yy_size_t num_to_alloc;
+	int num_to_alloc;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        if (!yyg->yy_buffer_stack) {
+	if (!yyg->yy_buffer_stack) {
 
-                /* First allocation is just for 2 elements, since we don't know if this
-                 * scanner will even need a stack. We use 2 instead of 1 to avoid an
-                 * immediate realloc on the next call.
+		/* First allocation is just for 2 elements, since we don't know if this
+		 * scanner will even need a stack. We use 2 instead of 1 to avoid an
+		 * immediate realloc on the next call.
          */
-                num_to_alloc = 1;
-                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmFortran_yyalloc
-                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
-                                                                , yyscanner);
-                if ( ! yyg->yy_buffer_stack )
-                        YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yyensure_buffer_stack()" );
-
-                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
-
-                yyg->yy_buffer_stack_max = num_to_alloc;
-                yyg->yy_buffer_stack_top = 0;
-                return;
-        }
-
-        if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){
-
-                /* Increase the buffer to prepare for a possible push. */
-                int grow_size = 8 /* arbitrary grow size */;
-
-                num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
-                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmFortran_yyrealloc
-                                                                (yyg->yy_buffer_stack,
-                                                                num_to_alloc * sizeof(struct yy_buffer_state*)
-                                                                , yyscanner);
-                if ( ! yyg->yy_buffer_stack )
-                        YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yyensure_buffer_stack()" );
-
-                /* zero only the new slots.*/
-                memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
-                yyg->yy_buffer_stack_max = num_to_alloc;
-        }
+      num_to_alloc = 1; /* After all that talk, this was set to 1 anyways... */
+		yyg->yy_buffer_stack = (struct yy_buffer_state**)cmFortran_yyalloc
+								(num_to_alloc * sizeof(struct yy_buffer_state*)
+								, yyscanner);
+		if ( ! yyg->yy_buffer_stack )
+			YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yyensure_buffer_stack()" );
+
+		memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
+
+		yyg->yy_buffer_stack_max = num_to_alloc;
+		yyg->yy_buffer_stack_top = 0;
+		return;
+	}
+
+	if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){
+
+		/* Increase the buffer to prepare for a possible push. */
+		yy_size_t grow_size = 8 /* arbitrary grow size */;
+
+		num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
+		yyg->yy_buffer_stack = (struct yy_buffer_state**)cmFortran_yyrealloc
+								(yyg->yy_buffer_stack,
+								num_to_alloc * sizeof(struct yy_buffer_state*)
+								, yyscanner);
+		if ( ! yyg->yy_buffer_stack )
+			YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yyensure_buffer_stack()" );
+
+		/* zero only the new slots.*/
+		memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
+		yyg->yy_buffer_stack_max = num_to_alloc;
+	}
 }
 
 /** Setup the input buffer state to scan directly from a user-specified character buffer.
@@ -1993,31 +1971,31 @@ static void cmFortran_yyensure_buffer_stack (yyscan_t yyscanner)
  */
 YY_BUFFER_STATE cmFortran_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
-        YY_BUFFER_STATE b;
-
-        if ( size < 2 ||
-             base[size-2] != YY_END_OF_BUFFER_CHAR ||
-             base[size-1] != YY_END_OF_BUFFER_CHAR )
-                /* They forgot to leave room for the EOB's. */
-                return 0;
-
-        b = (YY_BUFFER_STATE) cmFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
-        if ( ! b )
-                YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_scan_buffer()" );
-
-        b->yy_buf_size = size - 2;      /* "- 2" to take care of EOB's */
-        b->yy_buf_pos = b->yy_ch_buf = base;
-        b->yy_is_our_buffer = 0;
-        b->yy_input_file = 0;
-        b->yy_n_chars = b->yy_buf_size;
-        b->yy_is_interactive = 0;
-        b->yy_at_bol = 1;
-        b->yy_fill_buffer = 0;
-        b->yy_buffer_status = YY_BUFFER_NEW;
-
-        cmFortran_yy_switch_to_buffer(b ,yyscanner );
-
-        return b;
+	YY_BUFFER_STATE b;
+
+	if ( size < 2 ||
+	     base[size-2] != YY_END_OF_BUFFER_CHAR ||
+	     base[size-1] != YY_END_OF_BUFFER_CHAR )
+		/* They forgot to leave room for the EOB's. */
+		return NULL;
+
+	b = (YY_BUFFER_STATE) cmFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
+	if ( ! b )
+		YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_scan_buffer()" );
+
+	b->yy_buf_size = size - 2;	/* "- 2" to take care of EOB's */
+	b->yy_buf_pos = b->yy_ch_buf = base;
+	b->yy_is_our_buffer = 0;
+	b->yy_input_file = NULL;
+	b->yy_n_chars = b->yy_buf_size;
+	b->yy_is_interactive = 0;
+	b->yy_at_bol = 1;
+	b->yy_fill_buffer = 0;
+	b->yy_buffer_status = YY_BUFFER_NEW;
+
+	cmFortran_yy_switch_to_buffer(b ,yyscanner );
+
+	return b;
 }
 
 /** Setup the input buffer state to scan a string. The next call to cmFortran_yylex() will
@@ -2031,7 +2009,7 @@ YY_BUFFER_STATE cmFortran_yy_scan_buffer  (char * base, yy_size_t  size , yyscan
 YY_BUFFER_STATE cmFortran_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)
 {
 
-        return cmFortran_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
+	return cmFortran_yy_scan_bytes(yystr,(int) strlen(yystr) ,yyscanner);
 }
 
 /** Setup the input buffer state to scan the given bytes. The next call to cmFortran_yylex() will
@@ -2041,62 +2019,64 @@ YY_BUFFER_STATE cmFortran_yy_scan_string (yyconst char * yystr , yyscan_t yyscan
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  */
-YY_BUFFER_STATE cmFortran_yy_scan_bytes  (yyconst char * yybytes, yy_size_t  _yybytes_len , yyscan_t yyscanner)
+YY_BUFFER_STATE cmFortran_yy_scan_bytes  (yyconst char * yybytes, int  _yybytes_len , yyscan_t yyscanner)
 {
-        YY_BUFFER_STATE b;
-        char *buf;
-        yy_size_t n;
-        yy_size_t i;
+	YY_BUFFER_STATE b;
+	char *buf;
+	yy_size_t n;
+	yy_size_t i;
 
-        /* Get memory for full buffer, including space for trailing EOB's. */
-        n = _yybytes_len + 2;
-        buf = (char *) cmFortran_yyalloc(n ,yyscanner );
-        if ( ! buf )
-                YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_scan_bytes()" );
+	/* Get memory for full buffer, including space for trailing EOB's. */
+	n = (yy_size_t) _yybytes_len + 2;
+	buf = (char *) cmFortran_yyalloc(n ,yyscanner );
+	if ( ! buf )
+		YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_scan_bytes()" );
 
-        for ( i = 0; i < _yybytes_len; ++i )
-                buf[i] = yybytes[i];
+	for ( i = 0; i < (size_t)_yybytes_len; ++i )
+		buf[i] = yybytes[i];
 
-        buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
+	buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
 
-        b = cmFortran_yy_scan_buffer(buf,n ,yyscanner);
-        if ( ! b )
-                YY_FATAL_ERROR( "bad buffer in cmFortran_yy_scan_bytes()" );
+	b = cmFortran_yy_scan_buffer(buf,n ,yyscanner);
+	if ( ! b )
+		YY_FATAL_ERROR( "bad buffer in cmFortran_yy_scan_bytes()" );
 
-        /* It's okay to grow etc. this buffer, and we should throw it
-         * away when we're done.
-         */
-        b->yy_is_our_buffer = 1;
+	/* It's okay to grow etc. this buffer, and we should throw it
+	 * away when we're done.
+	 */
+	b->yy_is_our_buffer = 1;
 
-        return b;
+	return b;
 }
 
 #ifndef YY_EXIT_FAILURE
 #define YY_EXIT_FAILURE 2
 #endif
 
-static void yy_fatal_error (yyconst char* msg , yyscan_t)
+static void yynoreturn yy_fatal_error (yyconst char* msg , yyscan_t yyscanner)
 {
-        (void) fprintf( stderr, "%s\n", msg );
-        exit( YY_EXIT_FAILURE );
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+	(void) fprintf( stderr, "%s\n", msg );
+	exit( YY_EXIT_FAILURE );
 }
 
 /* Redefine yyless() so it works in section 3 code. */
 
 #undef yyless
 #define yyless(n) \
-        do \
-                { \
-                /* Undo effects of setting up yytext. */ \
+	do \
+		{ \
+		/* Undo effects of setting up yytext. */ \
         int yyless_macro_arg = (n); \
         YY_LESS_LINENO(yyless_macro_arg);\
-                yytext[yyleng] = yyg->yy_hold_char; \
-                yyg->yy_c_buf_p = yytext + yyless_macro_arg; \
-                yyg->yy_hold_char = *yyg->yy_c_buf_p; \
-                *yyg->yy_c_buf_p = '\0'; \
-                yyleng = yyless_macro_arg; \
-                } \
-        while ( 0 )
+		yytext[yyleng] = yyg->yy_hold_char; \
+		yyg->yy_c_buf_p = yytext + yyless_macro_arg; \
+		yyg->yy_hold_char = *yyg->yy_c_buf_p; \
+		*yyg->yy_c_buf_p = '\0'; \
+		yyleng = yyless_macro_arg; \
+		} \
+	while ( 0 )
 
 /* Accessor  methods (get/set functions) to struct members. */
 
@@ -2156,7 +2136,7 @@ FILE *cmFortran_yyget_out  (yyscan_t yyscanner)
 /** Get the length of the current token.
  * @param yyscanner The scanner object.
  */
-yy_size_t cmFortran_yyget_leng  (yyscan_t yyscanner)
+int cmFortran_yyget_leng  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyleng;
@@ -2183,51 +2163,51 @@ void cmFortran_yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscanner)
 }
 
 /** Set the current line number.
- * @param line_number The line number to set.
+ * @param _line_number line number
  * @param yyscanner The scanner object.
  */
-void cmFortran_yyset_lineno (int  line_number , yyscan_t yyscanner)
+void cmFortran_yyset_lineno (int  _line_number , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
            YY_FATAL_ERROR( "cmFortran_yyset_lineno called with no buffer" );
 
-    yylineno = line_number;
+    yylineno = _line_number;
 }
 
 /** Set the current column.
- * @param column_no The column number to set.
+ * @param _column_no column number
  * @param yyscanner The scanner object.
  */
-void cmFortran_yyset_column (int  column_no , yyscan_t yyscanner)
+void cmFortran_yyset_column (int  _column_no , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
            YY_FATAL_ERROR( "cmFortran_yyset_column called with no buffer" );
 
-    yycolumn = column_no;
+    yycolumn = _column_no;
 }
 
 /** Set the input stream. This does not discard the current
  * input buffer.
- * @param in_str A readable stream.
+ * @param _in_str A readable stream.
  * @param yyscanner The scanner object.
  * @see cmFortran_yy_switch_to_buffer
  */
-void cmFortran_yyset_in (FILE *  in_str , yyscan_t yyscanner)
+void cmFortran_yyset_in (FILE *  _in_str , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    yyin = in_str ;
+    yyin = _in_str ;
 }
 
-void cmFortran_yyset_out (FILE *  out_str , yyscan_t yyscanner)
+void cmFortran_yyset_out (FILE *  _out_str , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    yyout = out_str ;
+    yyout = _out_str ;
 }
 
 int cmFortran_yyget_debug  (yyscan_t yyscanner)
@@ -2236,10 +2216,10 @@ int cmFortran_yyget_debug  (yyscan_t yyscanner)
     return yy_flex_debug;
 }
 
-void cmFortran_yyset_debug (int  bdebug , yyscan_t yyscanner)
+void cmFortran_yyset_debug (int  _bdebug , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    yy_flex_debug = bdebug ;
+    yy_flex_debug = _bdebug ;
 }
 
 /* Accessor methods for yylval and yylloc */
@@ -2315,10 +2295,10 @@ static int yy_init_globals (yyscan_t yyscanner)
      * This function is called from cmFortran_yylex_destroy(), so don't allocate here.
      */
 
-    yyg->yy_buffer_stack = 0;
+    yyg->yy_buffer_stack = NULL;
     yyg->yy_buffer_stack_top = 0;
     yyg->yy_buffer_stack_max = 0;
-    yyg->yy_c_buf_p = (char *) 0;
+    yyg->yy_c_buf_p = NULL;
     yyg->yy_init = 0;
     yyg->yy_start = 0;
 
@@ -2331,8 +2311,8 @@ static int yy_init_globals (yyscan_t yyscanner)
     yyin = stdin;
     yyout = stdout;
 #else
-    yyin = (FILE *) 0;
-    yyout = (FILE *) 0;
+    yyin = NULL;
+    yyout = NULL;
 #endif
 
     /* For future reference: Set errno on error, since we are called by
@@ -2347,15 +2327,15 @@ int cmFortran_yylex_destroy  (yyscan_t yyscanner)
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
     /* Pop the buffer stack, destroying each element. */
-        while(YY_CURRENT_BUFFER){
-                cmFortran_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
-                YY_CURRENT_BUFFER_LVALUE = NULL;
-                cmFortran_yypop_buffer_state(yyscanner);
-        }
+	while(YY_CURRENT_BUFFER){
+		cmFortran_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
+		YY_CURRENT_BUFFER_LVALUE = NULL;
+		cmFortran_yypop_buffer_state(yyscanner);
+	}
 
-        /* Destroy the stack itself. */
-        cmFortran_yyfree(yyg->yy_buffer_stack ,yyscanner);
-        yyg->yy_buffer_stack = NULL;
+	/* Destroy the stack itself. */
+	cmFortran_yyfree(yyg->yy_buffer_stack ,yyscanner);
+	yyg->yy_buffer_stack = NULL;
 
     /* Destroy the start condition stack. */
         cmFortran_yyfree(yyg->yy_start_stack ,yyscanner );
@@ -2377,48 +2357,58 @@ int cmFortran_yylex_destroy  (yyscan_t yyscanner)
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char* s1, yyconst char * s2, int n , yyscan_t yyscanner)
 {
-        int i;
-        for ( i = 0; i < n; ++i )
-                s1[i] = s2[i];
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+
+	int i;
+	for ( i = 0; i < n; ++i )
+		s1[i] = s2[i];
 }
 #endif
 
 #ifdef YY_NEED_STRLEN
 static int yy_flex_strlen (yyconst char * s , yyscan_t yyscanner)
 {
-        int n;
-        for ( n = 0; s[n]; ++n )
-                ;
+	int n;
+	for ( n = 0; s[n]; ++n )
+		;
 
-        return n;
+	return n;
 }
 #endif
 
-void *cmFortran_yyalloc (yy_size_t  size , yyscan_t)
+void *cmFortran_yyalloc (yy_size_t  size , yyscan_t yyscanner)
 {
-        return (void *) malloc( size );
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+	return malloc(size);
 }
 
-void *cmFortran_yyrealloc  (void * ptr, yy_size_t  size , yyscan_t)
+void *cmFortran_yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
 {
-        /* The cast to (char *) in the following accommodates both
-         * implementations that use char* generic pointers, and those
-         * that use void* generic pointers.  It works with the latter
-         * because both ANSI C and C++ allow castless assignment from
-         * any pointer type to void*, and deal with argument conversions
-         * as though doing an assignment.
-         */
-        return (void *) realloc( (char *) ptr, size );
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+
+	/* The cast to (char *) in the following accommodates both
+	 * implementations that use char* generic pointers, and those
+	 * that use void* generic pointers.  It works with the latter
+	 * because both ANSI C and C++ allow castless assignment from
+	 * any pointer type to void*, and deal with argument conversions
+	 * as though doing an assignment.
+	 */
+	return realloc(ptr, size);
 }
 
-void cmFortran_yyfree (void * ptr , yyscan_t)
+void cmFortran_yyfree (void * ptr , yyscan_t yyscanner)
 {
-        free( (char *) ptr );   /* see cmFortran_yyrealloc() for (char *) cast */
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+	free( (char *) ptr );	/* see cmFortran_yyrealloc() for (char *) cast */
 }
 
 #define YYTABLES_NAME "yytables"
 
-#line 182 "cmFortranLexer.in.l"
+#line 176 "cmFortranLexer.in.l"
 
 
 