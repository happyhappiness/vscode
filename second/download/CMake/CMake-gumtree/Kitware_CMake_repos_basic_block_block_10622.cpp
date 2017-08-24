{
				*used = 0;
				*outbytes = o_avail_out - t_avail_out;
				if (o_avail_in == 0 &&
				    zip->tmp_stream_bytes_remaining)
					ret = ARCHIVE_EOF;
				return (ret);
			}