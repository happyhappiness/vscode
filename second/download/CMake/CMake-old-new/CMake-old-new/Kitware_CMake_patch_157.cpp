@@ -8,8 +8,8 @@
 
 #define FLEX_SCANNER
 #define YY_FLEX_MAJOR_VERSION 2
-#define YY_FLEX_MINOR_VERSION 5
-#define YY_FLEX_SUBMINOR_VERSION 35
+#define YY_FLEX_MINOR_VERSION 6
+#define YY_FLEX_SUBMINOR_VERSION 0
 #if YY_FLEX_SUBMINOR_VERSION > 0
 #define FLEX_BETA
 #endif
@@ -93,15 +93,15 @@ typedef unsigned int flex_uint32_t;
 /* The "const" storage-class-modifier is valid. */
 #define YY_USE_CONST
 
-#else   /* ! __cplusplus */
+#else	/* ! __cplusplus */
 
 /* C99 requires __STDC__ to be defined as 1. */
 #if defined (__STDC__)
 
 #define YY_USE_CONST
 
-#endif  /* defined (__STDC__) */
-#endif  /* ! __cplusplus */
+#endif	/* defined (__STDC__) */
+#endif	/* ! __cplusplus */
 
 #ifdef YY_USE_CONST
 #define yyconst const
@@ -179,6 +179,11 @@ typedef void* yyscan_t;
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
@@ -197,89 +202,93 @@ typedef struct yy_buffer_state *YY_BUFFER_STATE;
                     if ( yytext[yyl] == '\n' )\
                         --yylineno;\
             }while(0)
+    #define YY_LINENO_REWIND_TO(dst) \
+            do {\
+                const char *p;\
+                for ( p = yy_cp-1; p >= (dst); --p)\
+                    if ( *p == '\n' )\
+                        --yylineno;\
+            }while(0)
 
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
 
-#ifndef YY_TYPEDEF_YY_SIZE_T
-#define YY_TYPEDEF_YY_SIZE_T
-typedef size_t yy_size_t;
-#endif
+#define unput(c) yyunput( c, yyg->yytext_ptr , yyscanner )
 
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
-        int yy_n_chars;
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
+	yy_size_t yy_buf_size;
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
-         * (via cmListFileLexer_yyrestart()), so that the user can continue scanning by
-         * just pointing yyin at a new input file.
-         */
+	/* When an EOF's been seen but there's still some text to process
+	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
+	 * shouldn't try reading from the input source any more.  We might
+	 * still have a bunch of tokens to match, though, because of
+	 * possible backing-up.
+	 *
+	 * When we actually see the EOF, we change the status to "new"
+	 * (via cmListFileLexer_yyrestart()), so that the user can continue scanning by
+	 * just pointing yyin at a new input file.
+	 */
 #define YY_BUFFER_EOF_PENDING 2
 
-        };
+	};
 #endif /* !YY_STRUCT_YY_BUFFER_STATE */
 
 /* We provide macros for accessing buffer states in case in the
@@ -313,7 +322,7 @@ static void cmListFileLexer_yy_init_buffer (YY_BUFFER_STATE b,FILE *file ,yyscan
 
 YY_BUFFER_STATE cmListFileLexer_yy_scan_buffer (char *base,yy_size_t size ,yyscan_t yyscanner );
 YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char *yy_str ,yyscan_t yyscanner );
-YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes (yyconst char *bytes,int len ,yyscan_t yyscanner );
+YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes (yyconst char *bytes,yy_size_t len ,yyscan_t yyscanner );
 
 void *cmListFileLexer_yyalloc (yy_size_t ,yyscan_t yyscanner );
 void *cmListFileLexer_yyrealloc (void *,yy_size_t ,yyscan_t yyscanner );
@@ -322,30 +331,30 @@ void cmListFileLexer_yyfree (void * ,yyscan_t yyscanner );
 #define yy_new_buffer cmListFileLexer_yy_create_buffer
 
 #define yy_set_interactive(is_interactive) \
-        { \
-        if ( ! YY_CURRENT_BUFFER ){ \
+	{ \
+	if ( ! YY_CURRENT_BUFFER ){ \
         cmListFileLexer_yyensure_buffer_stack (yyscanner); \
-                YY_CURRENT_BUFFER_LVALUE =    \
+		YY_CURRENT_BUFFER_LVALUE =    \
             cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
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
         cmListFileLexer_yyensure_buffer_stack (yyscanner); \
-                YY_CURRENT_BUFFER_LVALUE =    \
+		YY_CURRENT_BUFFER_LVALUE =    \
             cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner); \
-        } \
-        YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
-        }
+	} \
+	YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
+	}
 
 #define YY_AT_BOL() (YY_CURRENT_BUFFER_LVALUE->yy_at_bol)
 
 /* Begin user sect3 */
 
-#define cmListFileLexer_yywrap(n) 1
+#define cmListFileLexer_yywrap(yyscanner) (/*CONSTCOND*/1)
 #define YY_SKIP_YYWRAP
 
 typedef unsigned char YY_CHAR;
@@ -357,27 +366,30 @@ typedef int yy_state_type;
 static yy_state_type yy_get_previous_state (yyscan_t yyscanner );
 static yy_state_type yy_try_NUL_trans (yy_state_type current_state  ,yyscan_t yyscanner);
 static int yy_get_next_buffer (yyscan_t yyscanner );
+#if defined(__GNUC__) && __GNUC__ >= 3
+__attribute__((__noreturn__))
+#endif
 static void yy_fatal_error (yyconst char msg[] ,yyscan_t yyscanner );
 
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
+	yyleng = (size_t) (yy_cp - yy_bp); \
+	yyg->yy_hold_char = *yy_cp; \
+	*yy_cp = '\0'; \
+	yyg->yy_c_buf_p = yy_cp;
 
 #define YY_NUM_RULES 24
 #define YY_END_OF_BUFFER 25
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
 static yyconst flex_int16_t yy_accept[77] =
     {   0,
         0,    0,    0,    0,    0,    0,    0,    0,    4,    4,
@@ -390,7 +402,7 @@ static yyconst flex_int16_t yy_accept[77] =
         0,    0,    0,    0,    0,    0
     } ;
 
-static yyconst flex_int32_t yy_ec[256] =
+static yyconst YY_CHAR yy_ec[256] =
     {   0,
         1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
         1,    1,    4,    1,    1,    1,    1,    1,    1,    1,
@@ -422,13 +434,13 @@ static yyconst flex_int32_t yy_ec[256] =
         1,    1,    1,    1,    1
     } ;
 
-static yyconst flex_int32_t yy_meta[16] =
+static yyconst YY_CHAR yy_meta[16] =
     {   0,
         1,    1,    2,    3,    4,    3,    1,    3,    5,    6,
         1,    6,    1,    1,    7
     } ;
 
-static yyconst flex_int16_t yy_base[95] =
+static yyconst flex_uint16_t yy_base[95] =
     {   0,
         0,    0,   13,   25,   14,   16,   17,   18,   90,   88,
        88,   39,   20,  237,  237,   74,   78,  237,  237,   13,
@@ -458,7 +470,7 @@ static yyconst flex_int16_t yy_def[95] =
 
     } ;
 
-static yyconst flex_int16_t yy_nxt[253] =
+static yyconst flex_uint16_t yy_nxt[253] =
     {   0,
        12,   13,   14,   13,   15,   16,   17,   18,   19,   12,
        12,   20,   21,   22,   12,   24,   28,   25,   28,   28,
@@ -552,19 +564,16 @@ static yyconst flex_int32_t yy_rule_can_match_eol[25] =
 
 This file must be translated to C and modified to build everywhere.
 
-Run flex like this:
+Run flex >= 2.6 like this:
 
   flex --prefix=cmListFileLexer_yy -ocmListFileLexer.c cmListFileLexer.in.l
 
 Modify cmListFileLexer.c:
-  - remove TABs
-  - remove use of the 'register' storage class specifier
-  - remove the yyunput function
-  - add a statement "(void)yyscanner;" to the top of these methods:
-      yy_fatal_error, cmListFileLexer_yyalloc, cmListFileLexer_yyrealloc, cmListFileLexer_yyfree
+  - remove trailing whitespace: sed -i 's/\s*$//' cmListFileLexer.c
+  - remove blank lines at end of file
   - remove statement "yyscanner = NULL;" from cmListFileLexer_yylex_destroy
   - remove all YY_BREAK lines occurring right after return statements
-  - remove the isatty forward declaration
+  - remove unnecessary cast to (int) in yy_get_next_buffer
 
 */
 
@@ -583,7 +592,7 @@ Modify cmListFileLexer.c:
 struct cmListFileLexer_s
 {
   cmListFileLexer_Token token;
-  int bracket;
+  yy_size_t bracket;
   int comment;
   int line;
   int column;
@@ -649,7 +658,7 @@ struct yyguts_t
     YY_BUFFER_STATE * yy_buffer_stack; /**< Stack as an array. */
     char yy_hold_char;
     int yy_n_chars;
-    int yyleng_r;
+    yy_size_t yyleng_r;
     char *yy_c_buf_p;
     int yy_init;
     int yy_start;
@@ -690,23 +699,23 @@ void cmListFileLexer_yyset_extra (YY_EXTRA_TYPE user_defined ,yyscan_t yyscanner
 
 FILE *cmListFileLexer_yyget_in (yyscan_t yyscanner );
 
-void cmListFileLexer_yyset_in  (FILE * in_str ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_in  (FILE * _in_str ,yyscan_t yyscanner );
 
 FILE *cmListFileLexer_yyget_out (yyscan_t yyscanner );
 
-void cmListFileLexer_yyset_out  (FILE * out_str ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_out  (FILE * _out_str ,yyscan_t yyscanner );
 
-int cmListFileLexer_yyget_leng (yyscan_t yyscanner );
+yy_size_t cmListFileLexer_yyget_leng (yyscan_t yyscanner );
 
 char *cmListFileLexer_yyget_text (yyscan_t yyscanner );
 
 int cmListFileLexer_yyget_lineno (yyscan_t yyscanner );
 
-void cmListFileLexer_yyset_lineno (int line_number ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_lineno (int _line_number ,yyscan_t yyscanner );
 
 int cmListFileLexer_yyget_column  (yyscan_t yyscanner );
 
-void cmListFileLexer_yyset_column (int column_no ,yyscan_t yyscanner );
+void cmListFileLexer_yyset_column (int _column_no ,yyscan_t yyscanner );
 
 /* Macros after this point can all be overridden by user definitions in
  * section 1.
@@ -720,6 +729,12 @@ extern int cmListFileLexer_yywrap (yyscan_t yyscanner );
 #endif
 #endif
 
+#ifndef YY_NO_UNPUT
+
+    static void yyunput (int c,char *buf_ptr  ,yyscan_t yyscanner);
+
+#endif
+
 #ifndef yytext_ptr
 static void yy_flex_strncpy (char *,yyconst char *,int ,yyscan_t yyscanner);
 #endif
@@ -761,33 +776,33 @@ static int input (yyscan_t yyscanner );
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
+		while ( (result = fread(buf, 1, max_size, yyin))==0 && ferror(yyin)) \
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
@@ -832,123 +847,124 @@ extern int cmListFileLexer_yylex (yyscan_t yyscanner);
 
 /* Code executed at the end of each rule. */
 #ifndef YY_BREAK
-#define YY_BREAK break;
+#define YY_BREAK /*LINTED*/break;
 #endif
 
 #define YY_RULE_SETUP \
-        YY_USER_ACTION
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
 
-#line 91 "cmListFileLexer.in.l"
+	if ( !yyg->yy_init )
+		{
+		yyg->yy_init = 1;
 
+#ifdef YY_USER_INIT
+		YY_USER_INIT;
+#endif
 
-#line 865 "cmListFileLexer.c"
+		if ( ! yyg->yy_start )
+			yyg->yy_start = 1;	/* first start state */
 
-        if ( !yyg->yy_init )
-                {
-                yyg->yy_init = 1;
+		if ( ! yyin )
+			yyin = stdin;
 
-#ifdef YY_USER_INIT
-                YY_USER_INIT;
-#endif
+		if ( ! yyout )
+			yyout = stdout;
 
-                if ( ! yyg->yy_start )
-                        yyg->yy_start = 1;      /* first start state */
+		if ( ! YY_CURRENT_BUFFER ) {
+			cmListFileLexer_yyensure_buffer_stack (yyscanner);
+			YY_CURRENT_BUFFER_LVALUE =
+				cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
+		}
 
-                if ( ! yyin )
-                        yyin = stdin;
+		cmListFileLexer_yy_load_buffer_state(yyscanner );
+		}
 
-                if ( ! yyout )
-                        yyout = stdout;
+	{
+#line 88 "cmListFileLexer.in.l"
 
-                if ( ! YY_CURRENT_BUFFER ) {
-                        cmListFileLexer_yyensure_buffer_stack (yyscanner);
-                        YY_CURRENT_BUFFER_LVALUE =
-                                cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
-                }
 
-                cmListFileLexer_yy_load_buffer_state(yyscanner );
-                }
+#line 896 "cmListFileLexer.c"
 
-        while ( 1 )             /* loops until end-of-file is reached */
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
+		yy_current_state = yyg->yy_start;
 yy_match:
-                do
-                        {
-                        YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)];
-                        if ( yy_accept[yy_current_state] )
-                                {
-                                yyg->yy_last_accepting_state = yy_current_state;
-                                yyg->yy_last_accepting_cpos = yy_cp;
-                                }
-                        while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
-                                {
-                                yy_current_state = (int) yy_def[yy_current_state];
-                                if ( yy_current_state >= 77 )
-                                        yy_c = yy_meta[(unsigned int) yy_c];
-                                }
-                        yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-                        ++yy_cp;
-                        }
-                while ( yy_base[yy_current_state] != 237 );
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
+				if ( yy_current_state >= 77 )
+					yy_c = yy_meta[(unsigned int) yy_c];
+				}
+			yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
+			++yy_cp;
+			}
+		while ( yy_base[yy_current_state] != 237 );
 
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
-                if ( yy_act != YY_END_OF_BUFFER && yy_rule_can_match_eol[yy_act] )
-                        {
-                        int yyl;
-                        for ( yyl = 0; yyl < yyleng; ++yyl )
-                                if ( yytext[yyl] == '\n' )
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
+		if ( yy_act != YY_END_OF_BUFFER && yy_rule_can_match_eol[yy_act] )
+			{
+			yy_size_t yyl;
+			for ( yyl = 0; yyl < yyleng; ++yyl )
+				if ( yytext[yyl] == '\n' )
 
     do{ yylineno++;
         yycolumn=0;
     }while(0)
 ;
-                        }
+			}
 
-do_action:      /* This label is used only to access EOF actions. */
+do_action:	/* This label is used only to access EOF actions. */
 
-                switch ( yy_act )
-        { /* beginning of action switch */
-                        case 0: /* must back up */
-                        /* undo the effects of YY_DO_BEFORE_ACTION */
-                        *yy_cp = yyg->yy_hold_char;
-                        yy_cp = yyg->yy_last_accepting_cpos;
-                        yy_current_state = yyg->yy_last_accepting_state;
-                        goto yy_find_action;
+		switch ( yy_act )
+	{ /* beginning of action switch */
+			case 0: /* must back up */
+			/* undo the effects of YY_DO_BEFORE_ACTION */
+			*yy_cp = yyg->yy_hold_char;
+			yy_cp = yyg->yy_last_accepting_cpos;
+			yy_current_state = yyg->yy_last_accepting_state;
+			goto yy_find_action;
 
 case 1:
 /* rule 1 can match eol */
 YY_RULE_SETUP
-#line 93 "cmListFileLexer.in.l"
+#line 90 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_Newline;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -960,7 +976,7 @@ YY_RULE_SETUP
 case 2:
 /* rule 2 can match eol */
 YY_RULE_SETUP
-#line 102 "cmListFileLexer.in.l"
+#line 99 "cmListFileLexer.in.l"
 {
   const char* bracket = yytext;
   lexer->comment = yytext[0] == '#';
@@ -974,7 +990,7 @@ YY_RULE_SETUP
     lexer->token.type = cmListFileLexer_Token_ArgumentBracket;
     }
   cmListFileLexerSetToken(lexer, "", 0);
-  lexer->bracket = (int)(strchr(bracket+1, '[') - bracket);
+  lexer->bracket = strchr(bracket+1, '[') - bracket;
   if(yytext[yyleng-1] == '\n')
     {
     ++lexer->line;
@@ -986,25 +1002,25 @@ YY_RULE_SETUP
     }
   BEGIN(BRACKET);
 }
-        YY_BREAK
+	YY_BREAK
 case 3:
 YY_RULE_SETUP
-#line 128 "cmListFileLexer.in.l"
+#line 125 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
   BEGIN(COMMENT);
 }
-        YY_BREAK
+	YY_BREAK
 case 4:
 YY_RULE_SETUP
-#line 133 "cmListFileLexer.in.l"
+#line 130 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
 }
-        YY_BREAK
+	YY_BREAK
 case 5:
 YY_RULE_SETUP
-#line 137 "cmListFileLexer.in.l"
+#line 134 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ParenLeft;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1013,7 +1029,7 @@ YY_RULE_SETUP
 }
 case 6:
 YY_RULE_SETUP
-#line 144 "cmListFileLexer.in.l"
+#line 141 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ParenRight;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1022,7 +1038,7 @@ YY_RULE_SETUP
 }
 case 7:
 YY_RULE_SETUP
-#line 151 "cmListFileLexer.in.l"
+#line 148 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_Identifier;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1031,7 +1047,7 @@ YY_RULE_SETUP
 }
 case 8:
 YY_RULE_SETUP
-#line 158 "cmListFileLexer.in.l"
+#line 155 "cmListFileLexer.in.l"
 {
   /* Handle ]]====]=======]*/
   cmListFileLexerAppend(lexer, yytext, yyleng);
@@ -1041,10 +1057,10 @@ YY_RULE_SETUP
     BEGIN(BRACKETEND);
     }
 }
-        YY_BREAK
+	YY_BREAK
 case 9:
 YY_RULE_SETUP
-#line 168 "cmListFileLexer.in.l"
+#line 165 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
   /* Erase the partial bracket from the token.  */
@@ -1055,43 +1071,43 @@ YY_RULE_SETUP
 }
 case 10:
 YY_RULE_SETUP
-#line 177 "cmListFileLexer.in.l"
+#line 174 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   lexer->column += yyleng;
 }
-        YY_BREAK
+	YY_BREAK
 case 11:
 /* rule 11 can match eol */
 YY_RULE_SETUP
-#line 182 "cmListFileLexer.in.l"
+#line 179 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   ++lexer->line;
   lexer->column = 1;
   BEGIN(BRACKET);
 }
-        YY_BREAK
+	YY_BREAK
 case 12:
 YY_RULE_SETUP
-#line 189 "cmListFileLexer.in.l"
+#line 186 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   lexer->column += yyleng;
   BEGIN(BRACKET);
 }
-        YY_BREAK
+	YY_BREAK
 case YY_STATE_EOF(BRACKET):
 case YY_STATE_EOF(BRACKETEND):
-#line 195 "cmListFileLexer.in.l"
+#line 192 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_BadBracket;
   BEGIN(INITIAL);
   return 1;
 }
 case 13:
 YY_RULE_SETUP
-#line 201 "cmListFileLexer.in.l"
+#line 198 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1100,7 +1116,7 @@ YY_RULE_SETUP
 }
 case 14:
 YY_RULE_SETUP
-#line 208 "cmListFileLexer.in.l"
+#line 205 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1109,7 +1125,7 @@ YY_RULE_SETUP
 }
 case 15:
 YY_RULE_SETUP
-#line 215 "cmListFileLexer.in.l"
+#line 212 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ArgumentUnquoted;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1118,68 +1134,68 @@ YY_RULE_SETUP
 }
 case 16:
 YY_RULE_SETUP
-#line 222 "cmListFileLexer.in.l"
+#line 219 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_ArgumentQuoted;
   cmListFileLexerSetToken(lexer, "", 0);
   lexer->column += yyleng;
   BEGIN(STRING);
 }
-        YY_BREAK
+	YY_BREAK
 case 17:
 YY_RULE_SETUP
-#line 229 "cmListFileLexer.in.l"
+#line 226 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   lexer->column += yyleng;
 }
-        YY_BREAK
+	YY_BREAK
 case 18:
 /* rule 18 can match eol */
 YY_RULE_SETUP
-#line 234 "cmListFileLexer.in.l"
+#line 231 "cmListFileLexer.in.l"
 {
   /* Continuation: text is not part of string */
   ++lexer->line;
   lexer->column = 1;
 }
-        YY_BREAK
+	YY_BREAK
 case 19:
 /* rule 19 can match eol */
 YY_RULE_SETUP
-#line 240 "cmListFileLexer.in.l"
+#line 237 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   ++lexer->line;
   lexer->column = 1;
 }
-        YY_BREAK
+	YY_BREAK
 case 20:
 YY_RULE_SETUP
-#line 246 "cmListFileLexer.in.l"
+#line 243 "cmListFileLexer.in.l"
 {
   lexer->column += yyleng;
   BEGIN(INITIAL);
   return 1;
 }
 case 21:
 YY_RULE_SETUP
-#line 252 "cmListFileLexer.in.l"
+#line 249 "cmListFileLexer.in.l"
 {
   cmListFileLexerAppend(lexer, yytext, yyleng);
   lexer->column += yyleng;
 }
-        YY_BREAK
+	YY_BREAK
 case YY_STATE_EOF(STRING):
-#line 257 "cmListFileLexer.in.l"
+#line 254 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_BadString;
   BEGIN(INITIAL);
   return 1;
 }
 case 22:
 YY_RULE_SETUP
-#line 263 "cmListFileLexer.in.l"
+#line 260 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_Space;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1188,7 +1204,7 @@ YY_RULE_SETUP
 }
 case 23:
 YY_RULE_SETUP
-#line 270 "cmListFileLexer.in.l"
+#line 267 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_BadCharacter;
   cmListFileLexerSetToken(lexer, yytext, yyleng);
@@ -1197,347 +1213,395 @@ YY_RULE_SETUP
 }
 case YY_STATE_EOF(INITIAL):
 case YY_STATE_EOF(COMMENT):
-#line 277 "cmListFileLexer.in.l"
+#line 274 "cmListFileLexer.in.l"
 {
   lexer->token.type = cmListFileLexer_Token_None;
   cmListFileLexerSetToken(lexer, 0, 0);
   return 0;
 }
 case 24:
 YY_RULE_SETUP
-#line 283 "cmListFileLexer.in.l"
+#line 280 "cmListFileLexer.in.l"
 ECHO;
-        YY_BREAK
-#line 1238 "cmListFileLexer.c"
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
-                         * cmListFileLexer_yylex().  If so, then we have to assure
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
-                                if ( cmListFileLexer_yywrap(yyscanner ) )
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
+	YY_BREAK
+#line 1242 "cmListFileLexer.c"
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
+			 * cmListFileLexer_yylex().  If so, then we have to assure
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
+				if ( cmListFileLexer_yywrap(yyscanner ) )
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
 } /* end of cmListFileLexer_yylex */
 
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
-                        int num_to_read =
-                        YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
-
-                while ( num_to_read <= 0 )
-                        { /* Not enough room in the buffer - grow it. */
-
-                        /* just a shorter name for the current buffer */
-                        YY_BUFFER_STATE b = YY_CURRENT_BUFFER;
-
-                        int yy_c_buf_p_offset =
-                                (int) (yyg->yy_c_buf_p - b->yy_ch_buf);
-
-                        if ( b->yy_is_our_buffer )
-                                {
-                                int new_size = b->yy_buf_size * 2;
-
-                                if ( new_size <= 0 )
-                                        b->yy_buf_size += b->yy_buf_size / 8;
-                                else
-                                        b->yy_buf_size *= 2;
-
-                                b->yy_ch_buf = (char *)
-                                        /* Include room in for 2 EOB chars. */
-                                        cmListFileLexer_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
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
-                        yyg->yy_n_chars, (size_t) num_to_read );
-
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
-                }
-
-        if ( yyg->yy_n_chars == 0 )
-                {
-                if ( number_to_move == YY_MORE_ADJ )
-                        {
-                        ret_val = EOB_ACT_END_OF_FILE;
-                        cmListFileLexer_yyrestart(yyin  ,yyscanner);
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
-                YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmListFileLexer_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );
-                if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
-                        YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
-        }
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
+			yy_size_t num_to_read =
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
+				yy_size_t new_size = b->yy_buf_size * 2;
+
+				if ( new_size <= 0 )
+					b->yy_buf_size += b->yy_buf_size / 8;
+				else
+					b->yy_buf_size *= 2;
+
+				b->yy_ch_buf = (char *)
+					/* Include room in for 2 EOB chars. */
+					cmListFileLexer_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
+				}
+			else
+				/* Can't grow it, we don't own it. */
+				b->yy_ch_buf = 0;
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
+			cmListFileLexer_yyrestart(yyin  ,yyscanner);
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
+	if ((yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
+		/* Extend the array by 50%, plus the number we really need. */
+		int new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);
+		YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmListFileLexer_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );
+		if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
+			YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
+	}
 
-        yyg->yy_n_chars += number_to_move;
-        YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
-        YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
+	yyg->yy_n_chars += number_to_move;
+	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;
+	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
 
-        yyg->yytext_ptr = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];
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
+	yy_current_state = yyg->yy_start;
 
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
-                        if ( yy_current_state >= 77 )
-                                yy_c = yy_meta[(unsigned int) yy_c];
-                        }
-                yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-                }
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
+			if ( yy_current_state >= 77 )
+				yy_c = yy_meta[(unsigned int) yy_c];
+			}
+		yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
+		}
 
-        return yy_current_state;
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
-                if ( yy_current_state >= 77 )
-                        yy_c = yy_meta[(unsigned int) yy_c];
-                }
-        yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
-        yy_is_jam = (yy_current_state == 76);
-
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
+		if ( yy_current_state >= 77 )
+			yy_c = yy_meta[(unsigned int) yy_c];
+		}
+	yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
+	yy_is_jam = (yy_current_state == 76);
+
+	(void)yyg;
+	return yy_is_jam ? 0 : yy_current_state;
 }
 
+#ifndef YY_NO_UNPUT
+
+    static void yyunput (int c, char * yy_bp , yyscan_t yyscanner)
+{
+	char *yy_cp;
+    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+
+    yy_cp = yyg->yy_c_buf_p;
+
+	/* undo effects of setting up yytext */
+	*yy_cp = yyg->yy_hold_char;
+
+	if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
+		{ /* need to shift things up to make room */
+		/* +2 for EOB chars. */
+		yy_size_t number_to_move = yyg->yy_n_chars + 2;
+		char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
+					YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
+		char *source =
+				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];
+
+		while ( source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
+			*--dest = *--source;
+
+		yy_cp += (int) (dest - source);
+		yy_bp += (int) (dest - source);
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars =
+			yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_buf_size;
+
+		if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
+			YY_FATAL_ERROR( "flex scanner push-back overflow" );
+		}
+
+	*--yy_cp = (char) c;
+
+    if ( c == '\n' ){
+        --yylineno;
+    }
+
+	yyg->yytext_ptr = yy_bp;
+	yyg->yy_hold_char = *yy_cp;
+	yyg->yy_c_buf_p = yy_cp;
+}
+
+#endif
+
 #ifndef YY_NO_INPUT
 #ifdef __cplusplus
     static int yyinput (yyscan_t yyscanner)
@@ -1546,79 +1610,79 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
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
-                        int offset = yyg->yy_c_buf_p - yyg->yytext_ptr;
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
-                                        cmListFileLexer_yyrestart(yyin ,yyscanner);
-
-                                        /*FALLTHROUGH*/
-
-                                case EOB_ACT_END_OF_FILE:
-                                        {
-                                        if ( cmListFileLexer_yywrap(yyscanner ) )
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
+			yy_size_t offset = yyg->yy_c_buf_p - yyg->yytext_ptr;
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
+					cmListFileLexer_yyrestart(yyin ,yyscanner);
+
+					/*FALLTHROUGH*/
+
+				case EOB_ACT_END_OF_FILE:
+					{
+					if ( cmListFileLexer_yywrap(yyscanner ) )
+						return EOF;
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
 
-        if ( c == '\n' )
+	if ( c == '\n' )
 
     do{ yylineno++;
         yycolumn=0;
     }while(0)
 ;
 
-        return c;
+	return c;
 }
-#endif  /* ifndef YY_NO_INPUT */
+#endif	/* ifndef YY_NO_INPUT */
 
 /** Immediately switch to a different input stream.
  * @param input_file A readable stream.
@@ -1629,14 +1693,14 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        if ( ! YY_CURRENT_BUFFER ){
+	if ( ! YY_CURRENT_BUFFER ){
         cmListFileLexer_yyensure_buffer_stack (yyscanner);
-                YY_CURRENT_BUFFER_LVALUE =
+		YY_CURRENT_BUFFER_LVALUE =
             cmListFileLexer_yy_create_buffer(yyin,YY_BUF_SIZE ,yyscanner);
-        }
+	}
 
-        cmListFileLexer_yy_init_buffer(YY_CURRENT_BUFFER,input_file ,yyscanner);
-        cmListFileLexer_yy_load_buffer_state(yyscanner );
+	cmListFileLexer_yy_init_buffer(YY_CURRENT_BUFFER,input_file ,yyscanner);
+	cmListFileLexer_yy_load_buffer_state(yyscanner );
 }
 
 /** Switch to a different input buffer.
@@ -1647,41 +1711,41 @@ static int yy_get_next_buffer (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        /* TODO. We should be able to replace this entire function body
-         * with
-         *              cmListFileLexer_yypop_buffer_state();
-         *              cmListFileLexer_yypush_buffer_state(new_buffer);
+	/* TODO. We should be able to replace this entire function body
+	 * with
+	 *		cmListFileLexer_yypop_buffer_state();
+	 *		cmListFileLexer_yypush_buffer_state(new_buffer);
      */
-        cmListFileLexer_yyensure_buffer_stack (yyscanner);
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
-        cmListFileLexer_yy_load_buffer_state(yyscanner );
-
-        /* We don't actually know whether we did this switch during
-         * EOF (cmListFileLexer_yywrap()) processing, but the only time this flag
-         * is looked at is after cmListFileLexer_yywrap() is called, so it's safe
-         * to go ahead and always set it.
-         */
-        yyg->yy_did_buffer_switch_on_eof = 1;
+	cmListFileLexer_yyensure_buffer_stack (yyscanner);
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
+	cmListFileLexer_yy_load_buffer_state(yyscanner );
+
+	/* We don't actually know whether we did this switch during
+	 * EOF (cmListFileLexer_yywrap()) processing, but the only time this flag
+	 * is looked at is after cmListFileLexer_yywrap() is called, so it's safe
+	 * to go ahead and always set it.
+	 */
+	yyg->yy_did_buffer_switch_on_eof = 1;
 }
 
 static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
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
@@ -1692,26 +1756,26 @@ static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
  */
     YY_BUFFER_STATE cmListFileLexer_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
 {
-        YY_BUFFER_STATE b;
+	YY_BUFFER_STATE b;
 
-        b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
-        if ( ! b )
-                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_create_buffer()" );
+	b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
+	if ( ! b )
+		YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_create_buffer()" );
 
-        b->yy_buf_size = size;
+	b->yy_buf_size = (yy_size_t)size;
 
-        /* yy_ch_buf has to be 2 characters longer than the size given because
-         * we need to put in 2 end-of-buffer characters.
-         */
-        b->yy_ch_buf = (char *) cmListFileLexer_yyalloc(b->yy_buf_size + 2 ,yyscanner );
-        if ( ! b->yy_ch_buf )
-                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_create_buffer()" );
+	/* yy_ch_buf has to be 2 characters longer than the size given because
+	 * we need to put in 2 end-of-buffer characters.
+	 */
+	b->yy_ch_buf = (char *) cmListFileLexer_yyalloc(b->yy_buf_size + 2 ,yyscanner );
+	if ( ! b->yy_ch_buf )
+		YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_create_buffer()" );
 
-        b->yy_is_our_buffer = 1;
+	b->yy_is_our_buffer = 1;
 
-        cmListFileLexer_yy_init_buffer(b,file ,yyscanner);
+	cmListFileLexer_yy_init_buffer(b,file ,yyscanner);
 
-        return b;
+	return b;
 }
 
 /** Destroy the buffer.
@@ -1722,16 +1786,16 @@ static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
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
-                cmListFileLexer_yyfree((void *) b->yy_ch_buf ,yyscanner );
+	if ( b->yy_is_our_buffer )
+		cmListFileLexer_yyfree((void *) b->yy_ch_buf ,yyscanner );
 
-        cmListFileLexer_yyfree((void *) b ,yyscanner );
+	cmListFileLexer_yyfree((void *) b ,yyscanner );
 }
 
 /* Initializes or reinitializes a buffer.
@@ -1741,13 +1805,13 @@ static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
     static void cmListFileLexer_yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file , yyscan_t yyscanner)
 
 {
-        int oerrno = errno;
+	int oerrno = errno;
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
-        cmListFileLexer_yy_flush_buffer(b ,yyscanner);
+	cmListFileLexer_yy_flush_buffer(b ,yyscanner);
 
-        b->yy_input_file = file;
-        b->yy_fill_buffer = 1;
+	b->yy_input_file = file;
+	b->yy_fill_buffer = 1;
 
     /* If b is the current buffer, then cmListFileLexer_yy_init_buffer was _probably_
      * called from cmListFileLexer_yyrestart() or through yy_get_next_buffer.
@@ -1760,7 +1824,7 @@ static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
 
         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
 
-        errno = oerrno;
+	errno = oerrno;
 }
 
 /** Discard all buffered characters. On the next scan, YY_INPUT will be called.
@@ -1770,25 +1834,25 @@ static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
     void cmListFileLexer_yy_flush_buffer (YY_BUFFER_STATE  b , yyscan_t yyscanner)
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
-                cmListFileLexer_yy_load_buffer_state(yyscanner );
+	if ( b == YY_CURRENT_BUFFER )
+		cmListFileLexer_yy_load_buffer_state(yyscanner );
 }
 
 /** Pushes the new state onto the stack. The new state becomes
@@ -1800,28 +1864,28 @@ static void cmListFileLexer_yy_load_buffer_state  (yyscan_t yyscanner)
 void cmListFileLexer_yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        if (new_buffer == NULL)
-                return;
+	if (new_buffer == NULL)
+		return;
 
-        cmListFileLexer_yyensure_buffer_stack(yyscanner);
+	cmListFileLexer_yyensure_buffer_stack(yyscanner);
 
-        /* This block is copied from cmListFileLexer_yy_switch_to_buffer. */
-        if ( YY_CURRENT_BUFFER )
-                {
-                /* Flush out information for old buffer. */
-                *yyg->yy_c_buf_p = yyg->yy_hold_char;
-                YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
-                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
-                }
+	/* This block is copied from cmListFileLexer_yy_switch_to_buffer. */
+	if ( YY_CURRENT_BUFFER )
+		{
+		/* Flush out information for old buffer. */
+		*yyg->yy_c_buf_p = yyg->yy_hold_char;
+		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;
+		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;
+		}
 
-        /* Only push if top exists. Otherwise, replace top. */
-        if (YY_CURRENT_BUFFER)
-                yyg->yy_buffer_stack_top++;
-        YY_CURRENT_BUFFER_LVALUE = new_buffer;
+	/* Only push if top exists. Otherwise, replace top. */
+	if (YY_CURRENT_BUFFER)
+		yyg->yy_buffer_stack_top++;
+	YY_CURRENT_BUFFER_LVALUE = new_buffer;
 
-        /* copied from cmListFileLexer_yy_switch_to_buffer. */
-        cmListFileLexer_yy_load_buffer_state(yyscanner );
-        yyg->yy_did_buffer_switch_on_eof = 1;
+	/* copied from cmListFileLexer_yy_switch_to_buffer. */
+	cmListFileLexer_yy_load_buffer_state(yyscanner );
+	yyg->yy_did_buffer_switch_on_eof = 1;
 }
 
 /** Removes and deletes the top of the stack, if present.
@@ -1831,65 +1895,65 @@ void cmListFileLexer_yypush_buffer_state (YY_BUFFER_STATE new_buffer , yyscan_t
 void cmListFileLexer_yypop_buffer_state (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-        if (!YY_CURRENT_BUFFER)
-                return;
+	if (!YY_CURRENT_BUFFER)
+		return;
 
-        cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
-        YY_CURRENT_BUFFER_LVALUE = NULL;
-        if (yyg->yy_buffer_stack_top > 0)
-                --yyg->yy_buffer_stack_top;
+	cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);
+	YY_CURRENT_BUFFER_LVALUE = NULL;
+	if (yyg->yy_buffer_stack_top > 0)
+		--yyg->yy_buffer_stack_top;
 
-        if (YY_CURRENT_BUFFER) {
-                cmListFileLexer_yy_load_buffer_state(yyscanner );
-                yyg->yy_did_buffer_switch_on_eof = 1;
-        }
+	if (YY_CURRENT_BUFFER) {
+		cmListFileLexer_yy_load_buffer_state(yyscanner );
+		yyg->yy_did_buffer_switch_on_eof = 1;
+	}
 }
 
 /* Allocates the stack if it does not exist.
  *  Guarantees space for at least one push.
  */
 static void cmListFileLexer_yyensure_buffer_stack (yyscan_t yyscanner)
 {
-        int num_to_alloc;
+	yy_size_t num_to_alloc;
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
-                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyalloc
-                                                                (num_to_alloc * sizeof(struct yy_buffer_state*)
-                                                                , yyscanner);
-                if ( ! yyg->yy_buffer_stack )
-                        YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );
-
-                memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
-
-                yyg->yy_buffer_stack_max = num_to_alloc;
-                yyg->yy_buffer_stack_top = 0;
-                return;
-        }
+		num_to_alloc = 1; /* After all that talk, this was set to 1 anyways... */
+		yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyalloc
+								(num_to_alloc * sizeof(struct yy_buffer_state*)
+								, yyscanner);
+		if ( ! yyg->yy_buffer_stack )
+			YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );
 
-        if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){
+		memset(yyg->yy_buffer_stack, 0, num_to_alloc * sizeof(struct yy_buffer_state*));
 
-                /* Increase the buffer to prepare for a possible push. */
-                int grow_size = 8 /* arbitrary grow size */;
+		yyg->yy_buffer_stack_max = num_to_alloc;
+		yyg->yy_buffer_stack_top = 0;
+		return;
+	}
 
-                num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
-                yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyrealloc
-                                                                (yyg->yy_buffer_stack,
-                                                                num_to_alloc * sizeof(struct yy_buffer_state*)
-                                                                , yyscanner);
-                if ( ! yyg->yy_buffer_stack )
-                        YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );
+	if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){
 
-                /* zero only the new slots.*/
-                memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
-                yyg->yy_buffer_stack_max = num_to_alloc;
-        }
+		/* Increase the buffer to prepare for a possible push. */
+		yy_size_t grow_size = 8 /* arbitrary grow size */;
+
+		num_to_alloc = yyg->yy_buffer_stack_max + grow_size;
+		yyg->yy_buffer_stack = (struct yy_buffer_state**)cmListFileLexer_yyrealloc
+								(yyg->yy_buffer_stack,
+								num_to_alloc * sizeof(struct yy_buffer_state*)
+								, yyscanner);
+		if ( ! yyg->yy_buffer_stack )
+			YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yyensure_buffer_stack()" );
+
+		/* zero only the new slots.*/
+		memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));
+		yyg->yy_buffer_stack_max = num_to_alloc;
+	}
 }
 
 /** Setup the input buffer state to scan directly from a user-specified character buffer.
@@ -1900,31 +1964,31 @@ static void cmListFileLexer_yyensure_buffer_stack (yyscan_t yyscanner)
  */
 YY_BUFFER_STATE cmListFileLexer_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
 {
-        YY_BUFFER_STATE b;
+	YY_BUFFER_STATE b;
 
-        if ( size < 2 ||
-             base[size-2] != YY_END_OF_BUFFER_CHAR ||
-             base[size-1] != YY_END_OF_BUFFER_CHAR )
-                /* They forgot to leave room for the EOB's. */
-                return 0;
+	if ( size < 2 ||
+	     base[size-2] != YY_END_OF_BUFFER_CHAR ||
+	     base[size-1] != YY_END_OF_BUFFER_CHAR )
+		/* They forgot to leave room for the EOB's. */
+		return 0;
 
-        b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
-        if ( ! b )
-                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_buffer()" );
+	b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
+	if ( ! b )
+		YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_buffer()" );
 
-        b->yy_buf_size = size - 2;      /* "- 2" to take care of EOB's */
-        b->yy_buf_pos = b->yy_ch_buf = base;
-        b->yy_is_our_buffer = 0;
-        b->yy_input_file = 0;
-        b->yy_n_chars = b->yy_buf_size;
-        b->yy_is_interactive = 0;
-        b->yy_at_bol = 1;
-        b->yy_fill_buffer = 0;
-        b->yy_buffer_status = YY_BUFFER_NEW;
+	b->yy_buf_size = size - 2;	/* "- 2" to take care of EOB's */
+	b->yy_buf_pos = b->yy_ch_buf = base;
+	b->yy_is_our_buffer = 0;
+	b->yy_input_file = 0;
+	b->yy_n_chars = b->yy_buf_size;
+	b->yy_is_interactive = 0;
+	b->yy_at_bol = 1;
+	b->yy_fill_buffer = 0;
+	b->yy_buffer_status = YY_BUFFER_NEW;
 
-        cmListFileLexer_yy_switch_to_buffer(b ,yyscanner );
+	cmListFileLexer_yy_switch_to_buffer(b ,yyscanner );
 
-        return b;
+	return b;
 }
 
 /** Setup the input buffer state to scan a string. The next call to cmListFileLexer_yylex() will
@@ -1938,7 +2002,7 @@ YY_BUFFER_STATE cmListFileLexer_yy_scan_buffer  (char * base, yy_size_t  size ,
 YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yystr , yyscan_t yyscanner)
 {
 
-        return cmListFileLexer_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
+	return cmListFileLexer_yy_scan_bytes(yystr,strlen(yystr) ,yyscanner);
 }
 
 /** Setup the input buffer state to scan the given bytes. The next call to cmListFileLexer_yylex() will
@@ -1948,34 +2012,34 @@ YY_BUFFER_STATE cmListFileLexer_yy_scan_string (yyconst char * yystr , yyscan_t
  * @param yyscanner The scanner object.
  * @return the newly allocated buffer state object.
  */
-YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * yybytes, int  _yybytes_len , yyscan_t yyscanner)
+YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * yybytes, yy_size_t  _yybytes_len , yyscan_t yyscanner)
 {
-        YY_BUFFER_STATE b;
-        char *buf;
-        yy_size_t n;
-        int i;
+	YY_BUFFER_STATE b;
+	char *buf;
+	yy_size_t n;
+	yy_size_t i;
 
-        /* Get memory for full buffer, including space for trailing EOB's. */
-        n = _yybytes_len + 2;
-        buf = (char *) cmListFileLexer_yyalloc(n ,yyscanner );
-        if ( ! buf )
-                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_bytes()" );
+	/* Get memory for full buffer, including space for trailing EOB's. */
+	n = _yybytes_len + 2;
+	buf = (char *) cmListFileLexer_yyalloc(n ,yyscanner );
+	if ( ! buf )
+		YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_bytes()" );
 
-        for ( i = 0; i < _yybytes_len; ++i )
-                buf[i] = yybytes[i];
+	for ( i = 0; i < _yybytes_len; ++i )
+		buf[i] = yybytes[i];
 
-        buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
+	buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
 
-        b = cmListFileLexer_yy_scan_buffer(buf,n ,yyscanner);
-        if ( ! b )
-                YY_FATAL_ERROR( "bad buffer in cmListFileLexer_yy_scan_bytes()" );
+	b = cmListFileLexer_yy_scan_buffer(buf,n ,yyscanner);
+	if ( ! b )
+		YY_FATAL_ERROR( "bad buffer in cmListFileLexer_yy_scan_bytes()" );
 
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
@@ -1984,27 +2048,28 @@ YY_BUFFER_STATE cmListFileLexer_yy_scan_bytes  (yyconst char * yybytes, int  _yy
 
 static void yy_fatal_error (yyconst char* msg , yyscan_t yyscanner)
 {
-        (void)yyscanner;
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
 
@@ -2064,7 +2129,7 @@ FILE *cmListFileLexer_yyget_out  (yyscan_t yyscanner)
 /** Get the length of the current token.
  * @param yyscanner The scanner object.
  */
-int cmListFileLexer_yyget_leng  (yyscan_t yyscanner)
+yy_size_t cmListFileLexer_yyget_leng  (yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
     return yyleng;
@@ -2091,51 +2156,51 @@ void cmListFileLexer_yyset_extra (YY_EXTRA_TYPE  user_defined , yyscan_t yyscann
 }
 
 /** Set the current line number.
- * @param line_number
+ * @param _line_number line number
  * @param yyscanner The scanner object.
  */
-void cmListFileLexer_yyset_lineno (int  line_number , yyscan_t yyscanner)
+void cmListFileLexer_yyset_lineno (int  _line_number , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* lineno is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmListFileLexer_yyset_lineno called with no buffer" , yyscanner);
+           YY_FATAL_ERROR( "cmListFileLexer_yyset_lineno called with no buffer" );
 
-    yylineno = line_number;
+    yylineno = _line_number;
 }
 
 /** Set the current column.
- * @param line_number
+ * @param _column_no column number
  * @param yyscanner The scanner object.
  */
-void cmListFileLexer_yyset_column (int  column_no , yyscan_t yyscanner)
+void cmListFileLexer_yyset_column (int  _column_no , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
         /* column is only valid if an input buffer exists. */
         if (! YY_CURRENT_BUFFER )
-           yy_fatal_error( "cmListFileLexer_yyset_column called with no buffer" , yyscanner);
+           YY_FATAL_ERROR( "cmListFileLexer_yyset_column called with no buffer" );
 
-    yycolumn = column_no;
+    yycolumn = _column_no;
 }
 
 /** Set the input stream. This does not discard the current
  * input buffer.
- * @param in_str A readable stream.
+ * @param _in_str A readable stream.
  * @param yyscanner The scanner object.
  * @see cmListFileLexer_yy_switch_to_buffer
  */
-void cmListFileLexer_yyset_in (FILE *  in_str , yyscan_t yyscanner)
+void cmListFileLexer_yyset_in (FILE *  _in_str , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    yyin = in_str ;
+    yyin = _in_str ;
 }
 
-void cmListFileLexer_yyset_out (FILE *  out_str , yyscan_t yyscanner)
+void cmListFileLexer_yyset_out (FILE *  _out_str , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    yyout = out_str ;
+    yyout = _out_str ;
 }
 
 int cmListFileLexer_yyget_debug  (yyscan_t yyscanner)
@@ -2144,10 +2209,10 @@ int cmListFileLexer_yyget_debug  (yyscan_t yyscanner)
     return yy_flex_debug;
 }
 
-void cmListFileLexer_yyset_debug (int  bdebug , yyscan_t yyscanner)
+void cmListFileLexer_yyset_debug (int  _bdebug , yyscan_t yyscanner)
 {
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
-    yy_flex_debug = bdebug ;
+    yy_flex_debug = _bdebug ;
 }
 
 /* Accessor methods for yylval and yylloc */
@@ -2255,15 +2320,15 @@ int cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
     struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
 
     /* Pop the buffer stack, destroying each element. */
-        while(YY_CURRENT_BUFFER){
-                cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
-                YY_CURRENT_BUFFER_LVALUE = NULL;
-                cmListFileLexer_yypop_buffer_state(yyscanner);
-        }
+	while(YY_CURRENT_BUFFER){
+		cmListFileLexer_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner );
+		YY_CURRENT_BUFFER_LVALUE = NULL;
+		cmListFileLexer_yypop_buffer_state(yyscanner);
+	}
 
-        /* Destroy the stack itself. */
-        cmListFileLexer_yyfree(yyg->yy_buffer_stack ,yyscanner);
-        yyg->yy_buffer_stack = NULL;
+	/* Destroy the stack itself. */
+	cmListFileLexer_yyfree(yyg->yy_buffer_stack ,yyscanner);
+	yyg->yy_buffer_stack = NULL;
 
     /* Destroy the start condition stack. */
         cmListFileLexer_yyfree(yyg->yy_start_stack ,yyscanner );
@@ -2285,51 +2350,58 @@ int cmListFileLexer_yylex_destroy  (yyscan_t yyscanner)
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
 
 void *cmListFileLexer_yyalloc (yy_size_t  size , yyscan_t yyscanner)
 {
-        (void)yyscanner;
-        return (void *) malloc( size );
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+	return (void *) malloc( size );
 }
 
 void *cmListFileLexer_yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
 {
-        /* The cast to (char *) in the following accommodates both
-         * implementations that use char* generic pointers, and those
-         * that use void* generic pointers.  It works with the latter
-         * because both ANSI C and C++ allow castless assignment from
-         * any pointer type to void*, and deal with argument conversions
-         * as though doing an assignment.
-         */
-        (void)yyscanner;
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
+	return (void *) realloc( (char *) ptr, size );
 }
 
 void cmListFileLexer_yyfree (void * ptr , yyscan_t yyscanner)
 {
-        (void)yyscanner;
-        free( (char *) ptr );   /* see cmListFileLexer_yyrealloc() for (char *) cast */
+	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
+	(void)yyg;
+	free( (char *) ptr );	/* see cmListFileLexer_yyrealloc() for (char *) cast */
 }
 
 #define YYTABLES_NAME "yytables"
 
-#line 282 "cmListFileLexer.in.l"
+#line 280 "cmListFileLexer.in.l"
 
 
 