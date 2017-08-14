static int
compression_code_gzip(struct archive *a,
    struct la_zstream *lastrm, enum la_zaction action)
{
	z_stream *strm;
	int r;

	strm = (z_stream *)lastrm->real_stream;
	/* zlib.h is not const-correct, so we need this one bit
	 * of ugly hackery to convert a const * pointer to
	 * a non-const pointer. */
	strm->next_in = (Bytef *)(uintptr_t)(const void *)lastrm->next_in;
	strm->avail_in = lastrm->avail_in;
	strm->total_in = (uLong)lastrm->total_in;
	strm->next_out = lastrm->next_out;
	strm->avail_out = lastrm->avail_out;
	strm->total_out = (uLong)lastrm->total_out;
	r = deflate(strm,
	    (action == ARCHIVE_Z_FINISH)? Z_FINISH: Z_NO_FLUSH);
	lastrm->next_in = strm->next_in;
	lastrm->avail_in = strm->avail_in;
	lastrm->total_in = strm->total_in;
	lastrm->next_out = strm->next_out;
	lastrm->avail_out = strm->avail_out;
	lastrm->total_out = strm->total_out;
	switch (r) {
	case Z_OK:
		return (ARCHIVE_OK);
	case Z_STREAM_END:
		return (ARCHIVE_EOF);
	default:
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "GZip compression failed:"
		    " deflate() call returned status %d", r);
		return (ARCHIVE_FATAL);
	}
}