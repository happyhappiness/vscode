

	/* If the buffer hasn't been allocated, allocate it now. */

	if (zip->uncompressed_buffer == NULL) {

		zip->uncompressed_buffer_size = 64 * 1024;

		zip->uncompressed_buffer =

		    malloc(zip->uncompressed_buffer_size);

		if (zip->uncompressed_buffer == NULL) {

			archive_set_error(&a->archive, ENOMEM,

			    "No memory for 7-Zip decompression");

			return (ARCHIVE_FATAL);

		}

	}

	zip->uncompressed_buffer_bytes_remaining = 0;

	zip->uncompressed_buffer_pointer = NULL;

	for (;;) {

		size_t bytes_in, bytes_out;

