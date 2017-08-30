	if (zip->entry_compression == COMPRESSION_DEFLATE) {

		for (;;) {

			size_t remainder;

			ret = deflate(&zip->stream, Z_FINISH);

			if (ret == Z_STREAM_ERROR)

				return (ARCHIVE_FATAL);

			remainder = zip->len_buf - zip->stream.avail_out;

			ret = __archive_write_output(a, zip->buf, remainder);

			if (ret != ARCHIVE_OK)

				return (ret);

