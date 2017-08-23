static int
compression_init_encoder_bzip2(struct archive *a,
    struct la_zstream *lastrm, int level)
{
	bz_stream *strm;

	if (lastrm->valid)
		compression_end(a, lastrm);
	strm = calloc(1, sizeof(*strm));
	if (strm == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for bzip2 stream");
		return (ARCHIVE_FATAL);
	}
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
	if (BZ2_bzCompressInit(strm, level, 0, 30) != BZ_OK) {
		free(strm);
		lastrm->real_stream = NULL;
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library");
		return (ARCHIVE_FATAL);
	}
	lastrm->real_stream = strm;
	lastrm->valid = 1;
	lastrm->code = compression_code_bzip2;
	lastrm->end = compression_end_bzip2;
	return (ARCHIVE_OK);
}