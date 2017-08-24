{
				int new_size = b->yy_buf_size * 2;

				if ( new_size <= 0 )
					b->yy_buf_size += b->yy_buf_size / 8;
				else
					b->yy_buf_size *= 2;

				b->yy_ch_buf = (char *)
					/* Include room in for 2 EOB chars. */
					cmListFileLexer_yyrealloc((void *) b->yy_ch_buf,b->yy_buf_size + 2 ,yyscanner );
				}