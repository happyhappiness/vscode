        else

                ret_val = EOB_ACT_CONTINUE_SCAN;



        if ((yy_size_t) (yyg->yy_n_chars + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {

                /* Extend the array by 50%, plus the number we really need. */

                yy_size_t new_size = yyg->yy_n_chars + number_to_move + (yyg->yy_n_chars >> 1);

                YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) cmDependsFortran_yyrealloc((void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf,new_size ,yyscanner );

                if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )

                        YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );

        }



        yyg->yy_n_chars += number_to_move;

        YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars] = YY_END_OF_BUFFER_CHAR;

        YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[yyg->yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;

