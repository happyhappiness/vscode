{
		int i;

		/* Do not copy out the BCJ remaining bytes when the output
		 * buffer size is less than five bytes. */
		if (o_avail_in != 0 && t_avail_out < 5 && zip->odd_bcj_size) {
			*used = 0;
			*outbytes = 0;
			return (ret);
		}
		for (i = 0; zip->odd_bcj_size > 0 && t_avail_out; i++) {
			*t_next_out++ = zip->odd_bcj[i];
			t_avail_out--;
			zip->odd_bcj_size--;
		}
		if (o_avail_in == 0 || t_avail_out == 0) {
			*used = o_avail_in - t_avail_in;
			*outbytes = o_avail_out - t_avail_out;
			if (o_avail_in == 0)
				ret = ARCHIVE_EOF;
			return (ret);
		}
	}