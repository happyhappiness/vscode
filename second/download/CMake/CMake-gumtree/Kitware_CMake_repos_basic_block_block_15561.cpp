(lastrm->prop_size) {
		lastrm->props = malloc(lastrm->prop_size);
		if (lastrm->props == NULL) {
			free(strm);
			lastrm->real_stream = NULL;
			archive_set_error(a, ENOMEM,
			    "Cannot allocate memory");
			return (ARCHIVE_FATAL);
		}
		r = lzma_properties_encode(lzmafilters,  lastrm->props);
		if (r != LZMA_OK) {
			free(strm);
			lastrm->real_stream = NULL;
			archive_set_error(a, ARCHIVE_ERRNO_MISC,
			    "lzma_properties_encode failed");
			return (ARCHIVE_FATAL);
		}
	}