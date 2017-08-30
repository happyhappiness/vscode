void cmCommandArgument_yypop_buffer_state (yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

  if (!YY_CURRENT_BUFFER)

    return;



  cmCommandArgument_yy_delete_buffer(YY_CURRENT_BUFFER ,yyscanner);

  YY_CURRENT_BUFFER_LVALUE = NULL;

  if (yyg->yy_buffer_stack_top > 0)

    --yyg->yy_buffer_stack_top;



  if (YY_CURRENT_BUFFER) {

    cmCommandArgument_yy_load_buffer_state(yyscanner );

    yyg->yy_did_buffer_switch_on_eof = 1;

  }

}



/* Allocates the stack if it does not exist.

 *  Guarantees space for at least one push.

 */

static void cmCommandArgument_yyensure_buffer_stack (yyscan_t yyscanner)

{

  int nuto_alloc;

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;



  if (!yyg->yy_buffer_stack) {



    /* First allocation is just for 2 elements, since we don't know if this

     * scanner will even need a stack. We use 2 instead of 1 to avoid an

     * immediate realloc on the next call.

         */

    nuto_alloc = 1;

    yyg->yy_buffer_stack = (struct yy_buffer_state**)cmCommandArgument_yyalloc

                (nuto_alloc * sizeof(struct yy_buffer_state*)

                , yyscanner);

    

    memset(yyg->yy_buffer_stack, 0, nuto_alloc * sizeof(struct yy_buffer_state*));

        

    yyg->yy_buffer_stack_max = nuto_alloc;

    yyg->yy_buffer_stack_top = 0;

    return;

  }



  if (yyg->yy_buffer_stack_top >= (yyg->yy_buffer_stack_max) - 1){



    /* Increase the buffer to prepare for a possible push. */

    int grow_size = 8 /* arbitrary grow size */;



    nuto_alloc = yyg->yy_buffer_stack_max + grow_size;

    yyg->yy_buffer_stack = (struct yy_buffer_state**)cmCommandArgument_yyrealloc

                (yyg->yy_buffer_stack,

                nuto_alloc * sizeof(struct yy_buffer_state*)

                , yyscanner);



    /* zero only the new slots.*/

    memset(yyg->yy_buffer_stack + yyg->yy_buffer_stack_max, 0, grow_size * sizeof(struct yy_buffer_state*));

    yyg->yy_buffer_stack_max = nuto_alloc;

  }

}



/** Setup the input buffer state to scan directly from a user-specified

 * character buffer.  @param base the character buffer @param size the size

 * in bytes of the character buffer @param yyscanner The scanner object.

 * @return the newly allocated buffer state object.

 */

YY_BUFFER_STATE cmCommandArgument_yy_scan_buffer  (char * base, yy_size_t  size , yyscan_t yyscanner)

{

  YY_BUFFER_STATE b;

    

  if ( size < 2 ||

       base[size-2] != YY_END_OF_BUFFER_CHAR ||

       base[size-1] != YY_END_OF_BUFFER_CHAR )

    /* They forgot to leave room for the EOB's. */

    return 0;



  b = (YY_BUFFER_STATE) cmCommandArgument_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );

  if ( ! b )

    YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yy_scan_buffer()" );



  b->yy_buf_size = size - 2;  /* "- 2" to take care of EOB's */

  b->yy_buf_pos = b->yy_ch_buf = base;

  b->yy_is_our_buffer = 0;

  b->yy_input_file = 0;

  b->yy_n_chars = b->yy_buf_size;

  b->yy_is_interactive = 0;

  b->yy_at_bol = 1;

  b->yy_fill_buffer = 0;

  b->yy_buffer_status = YY_BUFFER_NEW;



  cmCommandArgument_yy_switch_to_buffer(b ,yyscanner );



  return b;

}



/** Setup the input buffer state to scan a string. The next call to

 * cmCommandArgument_yylex() will scan from a @e copy of @a str.  @param str

 * a NUL-terminated string to scan @param yyscanner The scanner object.

 * @return the newly allocated buffer state object.  @note If you want to

 * scan bytes that may contain NUL values, then use

 * cmCommandArgument_yy_scan_bytes() instead.

 */

YY_BUFFER_STATE cmCommandArgument_yy_scan_string (yyconst char * yy_str , yyscan_t yyscanner)

{

    

  return cmCommandArgument_yy_scan_bytes(yy_str,strlen(yy_str) ,yyscanner);

}



/** Setup the input buffer state to scan the given bytes. The next call to

 * cmCommandArgument_yylex() will scan from a @e copy of @a bytes.  @param

 * bytes the byte buffer to scan @param len the number of bytes in the buffer

 * pointed to by @a bytes.  @param yyscanner The scanner object.  @return the

 * newly allocated buffer state object.

 */

YY_BUFFER_STATE cmCommandArgument_yy_scan_bytes  (yyconst char * bytes, int  len , yyscan_t yyscanner)

{

  YY_BUFFER_STATE b;

  char *buf;

  yy_size_t n;

  int i;

    

  /* Get memory for full buffer, including space for trailing EOB's. */

  n = len + 2;

  buf = (char *) cmCommandArgument_yyalloc(n ,yyscanner );

  if ( ! buf )

    YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yy_scan_bytes()" );



  for ( i = 0; i < len; ++i )

    buf[i] = bytes[i];



  buf[len] = buf[len+1] = YY_END_OF_BUFFER_CHAR;



  b = cmCommandArgument_yy_scan_buffer(buf,n ,yyscanner);

  if ( ! b )

    YY_FATAL_ERROR( "bad buffer in cmCommandArgument_yy_scan_bytes()" );



  /* It's okay to grow etc. this buffer, and we should throw it

   * away when we're done.

   */

  b->yy_is_our_buffer = 1;



  return b;

}



#ifndef YY_EXIT_FAILURE

