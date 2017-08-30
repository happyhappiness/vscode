{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;



        /* TODO. We should be able to replace this entire function body

         * with

         *              cmCommandArgument_yypop_buffer_state();

         *              cmCommandArgument_yypush_buffer_state(new_buffer);

     */

        cmCommandArgument_yyensure_buffer_stack (yyscanner);

        if ( YY_CURRENT_BUFFER == new_buffer )

                return;



        if ( YY_CURRENT_BUFFER )

                {

                /* Flush out information for old buffer. */

                *yyg->yy_c_buf_p = yyg->yy_hold_char;

                YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = yyg->yy_c_buf_p;

                YY_CURRENT_BUFFER_LVALUE->yy_n_chars = yyg->yy_n_chars;

                }



        YY_CURRENT_BUFFER_LVALUE = new_buffer;

        cmCommandArgument_yy_load_buffer_state(yyscanner );



        /* We don't actually know whether we did this switch during

         * EOF (cmCommandArgument_yywrap()) processing, but the only time this flag

         * is looked at is after cmCommandArgument_yywrap() is called, so it's safe

         * to go ahead and always set it.

         */

        yyg->yy_did_buffer_switch_on_eof = 1;

}



static void cmCommandArgument_yy_load_buffer_state  (yyscan_t yyscanner)

{

    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

        yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;

        yyg->yytext_ptr = yyg->yy_c_buf_p = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;

        yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;

        yyg->yy_hold_char = *yyg->yy_c_buf_p;

}



/** Allocate and initialize an input buffer state.

 * @param file A readable stream.

 * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.

 * @param yyscanner The scanner object.

 * @return the allocated buffer state.

 */

    YY_BUFFER_STATE cmCommandArgument_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)

{

        YY_BUFFER_STATE b;

    

        b = (YY_BUFFER_STATE) cmCommandArgument_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );

        if ( ! b )

                YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yy_create_buffer()" );



        b->yy_buf_size = size;



        /* yy_ch_buf has to be 2 characters longer than the size given because

         * we need to put in 2 end-of-buffer characters.

         */

        b->yy_ch_buf = (char *) cmCommandArgument_yyalloc(b->yy_buf_size + 2 ,yyscanner );

        if ( ! b->yy_ch_buf )

                YY_FATAL_ERROR( "out of dynamic memory in cmCommandArgument_yy_create_buffer()" );



        b->yy_is_our_buffer = 1;



        cmCommandArgument_yy_init_buffer(b,file ,yyscanner);



        return b;

}



/** Destroy the buffer.

