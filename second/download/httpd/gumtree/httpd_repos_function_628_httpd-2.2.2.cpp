void yy_delete_buffer( YY_BUFFER_STATE b )
#else
void yy_delete_buffer( b )
YY_BUFFER_STATE b;
#endif
        {
        if ( ! b )
                return;

        if ( b == yy_current_buffer )
                yy_current_buffer = (YY_BUFFER_STATE) 0;

        if ( b->yy_is_our_buffer )
                yy_flex_free( (void *) b->yy_ch_buf );

        yy_flex_free( (void *) b );
        }