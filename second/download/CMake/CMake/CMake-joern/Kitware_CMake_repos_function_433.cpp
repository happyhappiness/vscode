static int
compression_code_lzma(struct archive *a,
    struct la_zstream *lastrm, enum la_zaction action)
{
	lzma_stream *strm;
	int r;

	strm = (lzma_stream *)lastrm->real_stream;
	strm->next_in = lastrm->next_in;
	strm->avail_in = lastrm->avail_in;
	strm->total_in = lastrm->total_in;
	strm->next_out = lastrm->next_out;
	strm->avail_out = lastrm->avail_out;
	strm->total_out = lastrm->total_out;
	r = lzma_code(strm,
	    (action == ARCHIVE_Z_FINISH)? LZMA_FINISH: LZMA_RUN);
	lastrm->next_in = strm->next_in;
	lastrm->avail_in = strm->avail_in;
	lastrm->total_in = strm->total_in;
	lastrm->next_out = strm->next_out;
	lastrm->avail_out = strm->avail_out;
	lastrm->total_out = strm->total_out;
	switch (r) {
	case LZMA_OK:
		/* Non-finishing case */
		return (ARCHIVE_OK);
	case LZMA_STREAM_END:
		/* This return can only occur in finishing case. */
		return (ARCHIVE_EOF);
	case LZMA_MEMLIMIT_ERROR:
		archive_set_error(a, ENOMEM,
		    "lzma compression error:"
		    " %ju MiB would have been needed",
		    (uintmax_t)((lzma_memusage(strm) + 1024 * 1024 -1)
			/ (1024 * 1024)));
		return (ARCHIVE_FATAL);
	default:
		/* Any other return value indicates an error */
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "lzma compression failed:"
		    " lzma_code() call returned status %d", r);
		return (ARCHIVE_FATAL);
	}
}