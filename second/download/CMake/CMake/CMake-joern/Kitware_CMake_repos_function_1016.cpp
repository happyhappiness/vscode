static int
compression_init_encoder_xz(struct archive *a,
    struct la_zstream *lastrm, int level, int threads)
{
	static const lzma_stream lzma_init_data = LZMA_STREAM_INIT;
	lzma_stream *strm;
	lzma_filter *lzmafilters;
	lzma_options_lzma lzma_opt;
	int r;
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
	lzma_mt mt_options;
#endif

	(void)threads; /* UNUSED (if multi-threaded LZMA library not avail) */

	if (lastrm->valid)
		compression_end(a, lastrm);
	strm = calloc(1, sizeof(*strm) + sizeof(*lzmafilters) * 2);
	if (strm == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for xz stream");
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
	lzmafilters[0].id = LZMA_FILTER_LZMA2;
	lzmafilters[0].options = &lzma_opt;
	lzmafilters[1].id = LZMA_VLI_UNKNOWN;/* Terminate */

	*strm = lzma_init_data;
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
	if (threads > 1) {
		memset(&mt_options, 0, sizeof(mt_options));
		mt_options.threads = threads;
		mt_options.timeout = 300;
		mt_options.filters = lzmafilters;
		mt_options.check = LZMA_CHECK_CRC64;
		r = lzma_stream_encoder_mt(strm, &mt_options);
	} else
#endif
		r = lzma_stream_encoder(strm, lzmafilters, LZMA_CHECK_CRC64);
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