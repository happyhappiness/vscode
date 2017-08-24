{
			int64_t bytes_written = strm->avail_out;
			r = lzx_decode_blocks(strm, last);
			bytes_written -= strm->avail_out;
			strm->next_out += bytes_written;
			strm->total_out += bytes_written;
		}