
	switch(rsrc->compression) {
	case 0:  /* No compression. */
		if (rsrc->uncompressed_size != rsrc->compressed_size) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Malformed OS X metadata entry: inconsistent size");
			return (ARCHIVE_FATAL);
		}
#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
#endif
