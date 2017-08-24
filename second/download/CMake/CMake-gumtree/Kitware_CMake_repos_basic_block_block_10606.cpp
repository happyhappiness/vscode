{
		ssize_t bytes;

		zip->tmp_stream_bytes_avail =
		    zip->tmp_stream_buff_size - t_avail_out;
		if (zip->tmp_stream_bytes_avail >
		      zip->main_stream_bytes_remaining)
			zip->tmp_stream_bytes_avail =
			    zip->main_stream_bytes_remaining;
		zip->tmp_stream_bytes_remaining = zip->tmp_stream_bytes_avail;
		bytes = Bcj2_Decode(zip, bcj2_next_out, bcj2_avail_out);
		if (bytes < 0) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "BCJ2 conversion Failed");
			return (ARCHIVE_FAILED);
		}
		zip->main_stream_bytes_remaining -=
		    zip->tmp_stream_bytes_avail
		      - zip->tmp_stream_bytes_remaining;
		bcj2_avail_out -= bytes;
		*outbytes = o_avail_out - bcj2_avail_out;
	}