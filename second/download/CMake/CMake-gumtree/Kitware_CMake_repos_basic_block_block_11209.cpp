(!cab->entry_cffolder->decompress_init) {
		cab->stream.next_in = NULL;
		cab->stream.avail_in = 0;
		cab->stream.total_in = 0;
		cab->stream.next_out = NULL;
		cab->stream.avail_out = 0;
		cab->stream.total_out = 0;
		if (cab->stream_valid)
			r = inflateReset(&cab->stream);
		else
			r = inflateInit2(&cab->stream,
			    -15 /* Don't check for zlib header */);
		if (r != Z_OK) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Can't initialize deflate decompression.");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
		/* Stream structure has been set up. */
		cab->stream_valid = 1;
		/* We've initialized decompression for this stream. */
		cab->entry_cffolder->decompress_init = 1;
	}