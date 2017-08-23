static int
compression_code_bzip2(struct archive *a,
    struct la_zstream *lastrm, enum la_zaction action)
{
	bz_stream *strm;
	int r;

	strm = (bz_stream *)lastrm->real_stream;
	/* bzlib.h is not const-correct, so we need this one bit
	 * of ugly hackery to convert a const * pointer to
	 * a non-const pointer. */
	strm->next_in = (char *)(uintptr_t)(const void *)lastrm->next_in;
	strm->avail_in = lastrm->avail_in;
	strm->total_in_lo32 = (uint32_t)(lastrm->total_in & 0xffffffff);
	strm->total_in_hi32 = (uint32_t)(lastrm->total_in >> 32);
	strm->next_out = (char *)lastrm->next_out;
	strm->avail_out = lastrm->avail_out;
	strm->total_out_lo32 = (uint32_t)(lastrm->total_out & 0xffffffff);
	strm->total_out_hi32 = (uint32_t)(lastrm->total_out >> 32);
	r = BZ2_bzCompress(strm,
	    (action == ARCHIVE_Z_FINISH)? BZ_FINISH: BZ_RUN);
	lastrm->next_in = (const unsigned char *)strm->next_in;
	lastrm->avail_in = strm->avail_in;
	lastrm->total_in =
	    (((uint64_t)(uint32_t)strm->total_in_hi32) << 32)
	    + (uint64_t)(uint32_t)strm->total_in_lo32;
	lastrm->next_out = (unsigned char *)strm->next_out;
	lastrm->avail_out = strm->avail_out;
	lastrm->total_out =
	    (((uint64_t)(uint32_t)strm->total_out_hi32) << 32)
	    + (uint64_t)(uint32_t)strm->total_out_lo32;
	switch (r) {
	case BZ_RUN_OK:     /* Non-finishing */
	case BZ_FINISH_OK:  /* Finishing: There's more work to do */
		return (ARCHIVE_OK);
	case BZ_STREAM_END: /* Finishing: all done */
		/* Only occurs in finishing case */
		return (ARCHIVE_EOF);
	default:
		/* Any other return value indicates an error */
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Bzip2 compression failed:"
		    " BZ2_bzCompress() call returned status %d", r);
		return (ARCHIVE_FATAL);
	}
}