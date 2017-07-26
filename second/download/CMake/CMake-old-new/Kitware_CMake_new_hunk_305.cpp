 */
    YY_BUFFER_STATE cmFortran_yy_create_buffer  (FILE * file, int  size , yyscan_t yyscanner)
{
	YY_BUFFER_STATE b;

	b = (YY_BUFFER_STATE) cmFortran_yyalloc(sizeof( struct yy_buffer_state ) ,yyscanner );
	if ( ! b )
		YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_create_buffer()" );

	b->yy_buf_size = (yy_size_t)size;

	/* yy_ch_buf has to be 2 characters longer than the size given because
	 * we need to put in 2 end-of-buffer characters.
	 */
	b->yy_ch_buf = (char *) cmFortran_yyalloc(b->yy_buf_size + 2 ,yyscanner );
	if ( ! b->yy_ch_buf )
		YY_FATAL_ERROR( "out of dynamic memory in cmFortran_yy_create_buffer()" );

	b->yy_is_our_buffer = 1;

	cmFortran_yy_init_buffer(b,file ,yyscanner);

	return b;
}

/** Destroy the buffer.
