(bytes) {
		skipped_bytes = read_stream(a, &p, bytes, 0);
		if (skipped_bytes < 0)
			return (skipped_bytes);
		if (skipped_bytes == 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Truncated 7-Zip file body");
			return (ARCHIVE_FATAL);
		}
		bytes -= (size_t)skipped_bytes;
		if (zip->pack_stream_bytes_unconsumed)
			read_consume(a);
	}