		    (intmax_t)rsrc->uncompressed_size);

		return (ARCHIVE_WARN);

	}



	metadata = malloc((size_t)rsrc->uncompressed_size);

	if (metadata == NULL) {

