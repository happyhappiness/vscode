(ds->state < ST_GET_LITERAL)
			r = lzh_read_blocks(strm, last);
		else
			r = lzh_decode_blocks(strm, last)