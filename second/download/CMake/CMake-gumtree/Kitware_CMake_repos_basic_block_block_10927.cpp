{
		ssize_t skipped;

		if (zip->uncompressed_buffer_bytes_remaining == 0) {
			if (zip->pack_stream_inbytes_remaining > 0) {
				r = extract_pack_stream(a, 0);
				if (r < 0)
					return (r);
			} else if (zip->folder_outbytes_remaining > 0) {
				/* Extract a remaining pack stream. */
				r = extract_pack_stream(a, 0);
				if (r < 0)
					return (r);
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Truncated 7-Zip file body");
				return (ARCHIVE_FATAL);
			}
		}
		skipped = get_uncompressed_data(
			a, buff, (size_t)skip_bytes, 0);
		if (skipped < 0)
			return (skipped);
		skip_bytes -= skipped;
		if (zip->pack_stream_bytes_unconsumed)
			read_consume(a);
	}