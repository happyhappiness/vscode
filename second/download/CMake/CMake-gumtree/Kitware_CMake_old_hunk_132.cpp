#endif
	}

	/* Check if an error happend in decompression process. */
	if (uncompressed_size < 0) {
		archive_set_error(&(self->archive->archive),
		    ARCHIVE_ERRNO_MISC, "lz4 decompression failed");
