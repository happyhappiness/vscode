{
	static const lzma_stream lzma_init_data = LZMA_STREAM_INIT;
	lzma_stream *strm;
	lzma_filter *lzmafilters;
	lzma_options_lzma lzma_opt;
	int r;

	if (lastrm->valid)
		compression_end(a, lastrm);
	strm = calloc(1, sizeof(*strm) + sizeof(*lzmafilters) * 2);
	if (strm == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for lzma stream");
		return (ARCHIVE_FATAL);
	}
	lzmafilters = (lzma_filter *)(strm+1);
	if (level > 6)
		level = 6;
	if (lzma_lzma_preset(&lzma_opt, level)) {
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ENOMEM,
		    "Internal error initializing compression library");
		return (ARCHIVE_FATAL);
	}
	lzmafilters[0].id = filter_id;
	lzmafilters[0].options = &lzma_opt;
	lzmafilters[1].id = LZMA_VLI_UNKNOWN;/* Terminate */

	r = lzma_properties_size(&(lastrm->prop_size), lzmafilters);
	if (r != LZMA_OK) {
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "lzma_properties_size failed");
		return (ARCHIVE_FATAL);
	}
	if (lastrm->prop_size) {
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

	*strm = lzma_init_data;
	r = lzma_raw_encoder(strm, lzmafilters);
	switch (r) {
	case LZMA_OK:
		lastrm->real_stream = strm;
		lastrm->valid = 1;
		lastrm->code = compression_code_lzma;
		lastrm->end = compression_end_lzma;
		r = ARCHIVE_OK;
		break;
	case LZMA_MEM_ERROR:
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ENOMEM,
		    "Internal error initializing compression library: "
		    "Cannot allocate memory");
		r =  ARCHIVE_FATAL;
		break;
        default:
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "It's a bug in liblzma");
		r =  ARCHIVE_FATAL;
		break;
	}
	return (r);
}