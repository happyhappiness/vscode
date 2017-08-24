        /* yy_ch_buf has to be 2 characters longer than the size given because
         * we need to put in 2 end-of-buffer characters.
         */
        b->yy_ch_buf = (char *) cmDependsFortran_yyalloc(b->yy_buf_size + 2 ,yyscanner );
        if ( ! b->yy_ch_buf )
                YY_FATAL_ERROR( "out of dynamic memory in cmDependsFortran_yy_create_buffer()" );

