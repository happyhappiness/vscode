 */
YY_BUFFER_STATE cmExpr_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)
{
  YY_BUFFER_STATE b;

  if ( size < 2 ||
       base[size-2] != YY_END_OF_BUFFER_CHAR ||
       base[size-1] != YY_END_OF_BUFFER_CHAR )
    /* They forgot to leave room for the EOB's. */
    return 0;

  b = (YY_BUFFER_STATE) cmExpr_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
  if ( ! b )
    YY_FATAL_ERROR( "out of dynamic memory in cmExpr_yy_scan_buffer()" );

  b->yy_buf_size = size - 2;  /* "- 2" to take care of EOB's */
  b->yy_buf_pos = b->yy_ch_buf = base;
  b->yy_is_our_buffer = 0;
  b->yy_input_file = 0;
  b->yy_n_chars = b->yy_buf_size;
  b->yy_is_interactive = 0;
  b->yy_at_bol = 1;
  b->yy_fill_buffer = 0;
  b->yy_buffer_status = YY_BUFFER_NEW;

  cmExpr_yy_switch_to_buffer(b ,yyscanner );

  return b;
}

/** Setup the input buffer state to scan a string. The next call to cmExpr_yylex() will
 * scan from a @e copy of @a yy_str.
 * @param yy_str a NUL-terminated string to scan
 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 * @note If you want to scan bytes that may contain NUL values, then use
 *       cmExpr_yy_scan_bytes() instead.
 */
YY_BUFFER_STATE cmExpr_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)
{

  return cmExpr_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);
}

/** Setup the input buffer state to scan the given bytes. The next call to cmExpr_yylex() will
 * scan from a @e copy of @a bytes.
 * @param bytes the byte buffer to scan
 * @param len the number of bytes in the buffer pointed to by @a bytes.
 * @param yyscanner The scanner object.
 * @return the newly allocated buffer state object.
 */
YY_BUFFER_STATE cmExpr_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)
{
  YY_BUFFER_STATE b;
  char *buf;
  yy_size_t n;
  int i;

  /* Get memory for full buffer, including space for trailing EOB's. */
  n = len + 2;
  buf = (char *) cmExpr_yyalloc(n ,yyscanner );
  if ( ! buf )
    YY_FATAL_ERROR( "out of dynamic memory in cmExpr_yy_scan_bytes()" );

  for ( i = 0; i < len; ++i )
    buf[i] = bytes[i];

  buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;

  b = cmExpr_yy_scan_buffer(buf,n ,yyscanner);
  if ( ! b )
    YY_FATAL_ERROR( "bad buffer in cmExpr_yy_scan_bytes()" );

  /* It's okay to grow etc. this buffer, and we should throw it
   * away when we're done.
   */
  b->yy_is_our_buffer = 1;

  return b;
}

#ifndef YY_EXIT_FAILURE
#define YY_EXIT_FAILURE 2
#endif

static void yy_fatal_error (yyconst char* msg , yyscan_t)
{
      (void) fprintf( stderr, "%s\n", msg );
  exit( YY_EXIT_FAILURE );
}

/* Redefine yyless() so it works in section 3 code. */

#undef yyless
#define yyless(n) \
  do \
    { \
    /* Undo effects of setting up yytext. */ \
        int yyless_macro_arg = (n); \
        YY_LESS_LINENO(yyless_macro_arg);\
    yytext[yyleng] = yyg->yy_hold_char; \
    yyg->yy_c_buf_p = yytext + yyless_macro_arg; \
    yyg->yy_hold_char = *yyg->yy_c_buf_p; \
    *yyg->yy_c_buf_p = '\0'; \
    yyleng = yyless_macro_arg; \
    } \
  while ( 0 )

/* Accessor  methods (get/set functions) to struct members. */

