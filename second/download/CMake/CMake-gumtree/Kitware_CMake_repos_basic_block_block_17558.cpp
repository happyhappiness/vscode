{
	z_stream *strm;

	if (lastrm->valid)
		compression_end(a, lastrm);
	strm = calloc(1, sizeof(*strm));
	if (strm == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for gzip stream");
		return (ARCHIVE_FATAL);
	}
	/* zlib.h is not const-correct, so we need this one bit
	 * of ugly hackery to convert a const * pointer to
	 * a non-const pointer. */
	strm->next_in = (Bytef *)(uintptr_t)(const void *)lastrm->next_in;
	strm->avail_in = lastrm->avail_in;
	strm->total_in = (uLong)lastrm->total_in;
	strm->next_out = lastrm->next_out;
	strm->avail_out = lastrm->avail_out;
	strm->total_out = (uLong)lastrm->total_out;
	if (deflateInit2(strm, level, Z_DEFLATED,
	    (withheader)?15:-15,
	    8, Z_DEFAULT_STRATEGY) != Z_OK) {
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library");
		return (ARCHIVE_FATAL);
	}
	lastrm->real_stream = strm;
	lastrm->valid = 1;
	lastrm->code = compression_code_gzip;
	lastrm->end = compression_end_gzip;
	return (ARCHIVE_OK);
}