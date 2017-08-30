	ssize_t bytes_avail;

	int r;



	/* If the buffer hasn't been allocated, allocate it now. */

	if (lha->uncompressed_buffer == NULL) {

		lha->uncompressed_buffer_size = 64 * 1024;

		lha->uncompressed_buffer

		    = (unsigned char *)malloc(lha->uncompressed_buffer_size);

		if (lha->uncompressed_buffer == NULL) {

			archive_set_error(&a->archive, ENOMEM,

			    "No memory for lzh decompression");

			return (ARCHIVE_FATAL);

		}

	}



	/* If we haven't yet read any data, initialize the decompressor. */

	if (!lha->decompress_init) {

		r = lzh_decode_init(&(lha->strm), lha->method);

