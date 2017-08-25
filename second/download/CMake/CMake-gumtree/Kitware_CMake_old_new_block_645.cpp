(zip->uncompressed_buffer == NULL) {
		zip->uncompressed_buffer_size = 64 * 1024;
		zip->uncompressed_buffer =
		    malloc(zip->uncompressed_buffer_size);
		if (zip->uncompressed_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for 7-Zip decompression");
			return (ARCHIVE_FATAL);
		}
	}