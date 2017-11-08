void yy_flush_buffer( YY_BUFFER_STATE b )
#else
void yy_flush_buffer( b )
YY_BUFFER_STATE b;
#endif

        {
        if ( ! b )
                return;

        b->yy_n_chars = 0;

        /* We always need two end-of-buffer characters.  The first causes
         * a transition to the end-of-buffer state.  The second causes
         * a jam in that state.
         */
        b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
        b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;

        b->yy_buf_pos = &b->yy_ch_buf[0];

        b->yy_at_bol = 1;
        b->yy_buffer_status = YY_BUFFER_NEW;

        if ( b == yy_current_buffer )
                yy_load_buffer_state();
        }