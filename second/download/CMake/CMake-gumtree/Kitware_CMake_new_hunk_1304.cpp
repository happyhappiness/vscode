                /* They forgot to leave room for the EOB's. */
                return 0;

        b = (YY_BUFFER_STATE) cmListFileLexer_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
        if ( ! b )
                YY_FATAL_ERROR( "out of dynamic memory in cmListFileLexer_yy_scan_buffer()" );

        b->yy_buf_size = size - 2;      /* "- 2" to take care of EOB's */
        b->yy_buf_pos = b->yy_ch_buf = base;
