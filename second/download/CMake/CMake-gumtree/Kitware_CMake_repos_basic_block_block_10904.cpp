{
		size_t bytes_in, bytes_out;
		const void *buff_in;
		unsigned char *buff_out;
		int end_of_data;

		/*
		 * Note: '1' here is a performance optimization.
		 * Recall that the decompression layer returns a count of
		 * available bytes; asking for more than that forces the
		 * decompressor to combine reads by copying data.
		 */
		buff_in = __archive_read_ahead(a, 1, &bytes_avail);
		if (bytes_avail <= 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated 7-Zip file body");
			return (ARCHIVE_FATAL);
		}

		buff_out = zip->uncompressed_buffer
			+ zip->uncompressed_buffer_bytes_remaining;
		bytes_out = zip->uncompressed_buffer_size
			- zip->uncompressed_buffer_bytes_remaining;
		bytes_in = bytes_avail;
		if (bytes_in > zip->pack_stream_inbytes_remaining)
			bytes_in = (size_t)zip->pack_stream_inbytes_remaining;
		/* Drive decompression. */
		r = decompress(a, zip, buff_out, &bytes_out,
			buff_in, &bytes_in);
		switch (r) {
		case ARCHIVE_OK:
			end_of_data = 0;
			break;
		case ARCHIVE_EOF:
			end_of_data = 1;
			break;
		default:
			return (ARCHIVE_FATAL);
		}
		zip->pack_stream_inbytes_remaining -= bytes_in;
		if (bytes_out > zip->folder_outbytes_remaining)
			bytes_out = (size_t)zip->folder_outbytes_remaining;
		zip->folder_outbytes_remaining -= bytes_out;
		zip->uncompressed_buffer_bytes_remaining += bytes_out;
		zip->pack_stream_bytes_unconsumed = bytes_in;

		/*
		 * Continue decompression until uncompressed_buffer is full.
		 */
		if (zip->uncompressed_buffer_bytes_remaining ==
		    zip->uncompressed_buffer_size)
			break;
		if (zip->codec2 == _7Z_X86 && zip->odd_bcj_size &&
		    zip->uncompressed_buffer_bytes_remaining + 5 >
		    zip->uncompressed_buffer_size)
			break;
		if (zip->pack_stream_inbytes_remaining == 0 &&
		    zip->folder_outbytes_remaining == 0)
			break;
		if (end_of_data || (bytes_in == 0 && bytes_out == 0)) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		read_consume(a);
	}