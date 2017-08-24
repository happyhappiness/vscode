(zisofs->uncompressed_buffer_size < xsize) {
			if (zisofs->uncompressed_buffer != NULL)
				free(zisofs->uncompressed_buffer);
			zisofs->uncompressed_buffer = malloc(xsize);
			if (zisofs->uncompressed_buffer == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for zisofs decompression");
				return (ARCHIVE_FATAL);
			}
		}