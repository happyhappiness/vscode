(r != LZMA_OK) {
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "lzma_properties_size failed");
		return (ARCHIVE_FATAL);
	}