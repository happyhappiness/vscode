{
			ssize_t bytes;
			size_t remaining = zip->tmp_stream_bytes_remaining;
			bytes = Bcj2_Decode(zip, t_next_out, t_avail_out);
			if (bytes < 0) {
				archive_set_error(&(a->archive),
				    ARCHIVE_ERRNO_MISC,
				    "BCJ2 conversion Failed");
				return (ARCHIVE_FAILED);
			}
			zip->main_stream_bytes_remaining -=
			    remaining - zip->tmp_stream_bytes_remaining;
			t_avail_out -= bytes;
			if (o_avail_in == 0 || t_avail_out == 0) {
				*used = 0;
				*outbytes = o_avail_out - t_avail_out;
				if (o_avail_in == 0 &&
				    zip->tmp_stream_bytes_remaining)
					ret = ARCHIVE_EOF;
				return (ret);
			}
			t_next_out += bytes;
			bcj2_next_out = t_next_out;
			bcj2_avail_out = t_avail_out;
		}