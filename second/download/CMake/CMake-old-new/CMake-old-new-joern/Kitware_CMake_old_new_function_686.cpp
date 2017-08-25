static void yyunput (int c, register char * yy_bp , yyscan_t yyscanner)
{
        register char *yy_cp;
    struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;

    yy_cp = yyg->yy_c_buf_p;

        /* undo effects of setting up yytext */
        *yy_cp = yyg->yy_hold_char;

        if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
                { /* need to shift things up to make room */
                /* +2 for EOB chars. */
                register int number_to_move = yyg->yy_n_chars + 2;
                register char *dest = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[
                                        YY_CURRENT_BUFFER_LVALUE->yy_buf_size + 2];
                register char *source =
                                &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move];

                while ( source > YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
                        *--dest = *--source;

                yy_cp += (int) (dest - source);
                yy_bp += (int) (dest - source);
                YY_CURRENT_BUFFER_LVALUE->yy_n_chars =
                        yyg->yy_n_chars = YY_CURRENT_BUFFER_LVALUE->yy_buf_size;

                if ( yy_cp < YY_CURRENT_BUFFER_LVALUE->yy_ch_buf + 2 )
                        YY_FATAL_ERROR( "flex scanner push-back overflow" );
                }

        *--yy_cp = (char) c;

        yyg->yytext_ptr = yy_bp;
        yyg->yy_hold_char = *yy_cp;
        yyg->yy_c_buf_p = yy_cp;
}