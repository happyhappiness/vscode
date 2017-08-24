{
	struct ppmd_stream *strm;
	uint8_t *props;
	int r;

	if (lastrm->valid)
		compression_end(a, lastrm);
	strm = calloc(1, sizeof(*strm));
	if (strm == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for PPMd");
		return (ARCHIVE_FATAL);
	}
	strm->buff = malloc(32);
	if (strm->buff == NULL) {
		free(strm);
		archive_set_error(a, ENOMEM,
		    "Can't allocate memory for PPMd");
		return (ARCHIVE_FATAL);
	}
	strm->buff_ptr = strm->buff;
	strm->buff_end = strm->buff + 32;

	props = malloc(1+4);
	if (props == NULL) {
		free(strm->buff);
		free(strm);
		archive_set_error(a, ENOMEM,
		    "Coludn't allocate memory for PPMd");
		return (ARCHIVE_FATAL);
	}
	props[0] = maxOrder;
	archive_le32enc(props+1, msize);
	__archive_ppmd7_functions.Ppmd7_Construct(&strm->ppmd7_context);
	r = __archive_ppmd7_functions.Ppmd7_Alloc(
		&strm->ppmd7_context, msize, &g_szalloc);
	if (r == 0) {
		free(strm->buff);
		free(strm);
		free(props);
		archive_set_error(a, ENOMEM,
		    "Coludn't allocate memory for PPMd");
		return (ARCHIVE_FATAL);
	}
	__archive_ppmd7_functions.Ppmd7_Init(&(strm->ppmd7_context), maxOrder);
	strm->byteout.a = (struct archive_write *)a;
	strm->byteout.Write = ppmd_write;
	strm->range_enc.Stream = &(strm->byteout);
	__archive_ppmd7_functions.Ppmd7z_RangeEnc_Init(&(strm->range_enc));
	strm->stat = 0;

	lastrm->real_stream = strm;
	lastrm->valid = 1;
	lastrm->code = compression_code_ppmd;
	lastrm->end = compression_end_ppmd;
	lastrm->prop_size = 5;
	lastrm->props = props;
	return (ARCHIVE_OK);
}