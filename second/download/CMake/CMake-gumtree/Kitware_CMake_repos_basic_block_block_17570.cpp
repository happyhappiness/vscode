{
	static const lzma_stream lzma_init_data = LZMA_STREAM_INIT;
	lzma_stream *strm;
	lzma_options_lzma lzma_opt;
	int r;

	if (lastrm->valid)
		compression_end(a, lastrm);
	if (lzma_lzma_preset(&lzma_opt, level)) {
		lastrm->real_stream = NULL;
		archive_set_error(a, ENOMEM,
		    "Internal error initializing compression library");
		return (ARCHIVE_FATAL);
	}
	strm = calloc(1, sizeof(*strm));
	if (strm == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for lzma stream");
		return (ARCHIVE_FATAL);
	}
	*strm = lzma_init_data;
	r = lzma_alone_encoder(strm, &lzma_opt);
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