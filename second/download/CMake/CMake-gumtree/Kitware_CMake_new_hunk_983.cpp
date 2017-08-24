
	/* If the buffer hasn't been allocated, allocate it now. */
	if (zip->uncompressed_buffer == NULL) {
		zip->uncompressed_buffer_size = UBUFF_SIZE;
		if (zip->uncompressed_buffer_size < minimum) {
			zip->uncompressed_buffer_size = minimum + 1023;
			zip->uncompressed_buffer_size &= ~0x3ff;
		}
		zip->uncompressed_buffer =
		    malloc(zip->uncompressed_buffer_size);
		if (zip->uncompressed_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for 7-Zip decompression");
			return (ARCHIVE_FATAL);
		}
		zip->uncompressed_buffer_bytes_remaining = 0;
	} else if (zip->uncompressed_buffer_size < minimum ||
	    zip->uncompressed_buffer_bytes_remaining < minimum) {
		/*
		 * Make sure the uncompressed buffer can have bytes
		 * at least `minimum' bytes.
		 * NOTE: This case happen when reading the header.
		 */
		size_t used;
		if (zip->uncompressed_buffer_pointer != 0)
			used = zip->uncompressed_buffer_pointer -
				zip->uncompressed_buffer;
		else
			used = 0;
		if (zip->uncompressed_buffer_size < minimum) {
			/*
			 * Expand the uncompressed buffer up to
			 * the minimum size.
			 */
			zip->uncompressed_buffer_size = minimum + 1023;
			zip->uncompressed_buffer_size &= ~0x3ff;
			zip->uncompressed_buffer =
			    realloc(zip->uncompressed_buffer,
				zip->uncompressed_buffer_size);
			if (zip->uncompressed_buffer == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}
		}
		/*
		 * Move unconsumed bytes to the head.
		 */
		if (used) {
			memmove(zip->uncompressed_buffer,
				zip->uncompressed_buffer + used,
				zip->uncompressed_buffer_bytes_remaining);
		}
	} else
		zip->uncompressed_buffer_bytes_remaining = 0;
	zip->uncompressed_buffer_pointer = NULL;
	for (;;) {
		size_t bytes_in, bytes_out;
