{
	struct ppmd_stream *strm;

	(void)a; /* UNUSED */

	strm = (struct ppmd_stream *)lastrm->real_stream;

	/* Copy encoded data if there are remaining bytes from previous call. */
	if (strm->buff_bytes) {
		uint8_t *p = strm->buff_ptr - strm->buff_bytes;
		while (lastrm->avail_out && strm->buff_bytes) {
			*lastrm->next_out++ = *p++;
			lastrm->avail_out--;
			lastrm->total_out++;
			strm->buff_bytes--;
		}
		if (strm->buff_bytes)
			return (ARCHIVE_OK);
		if (strm->stat == 1)
			return (ARCHIVE_EOF);
		strm->buff_ptr = strm->buff;
	}
	while (lastrm->avail_in && lastrm->avail_out) {
		__archive_ppmd7_functions.Ppmd7_EncodeSymbol(
			&(strm->ppmd7_context), &(strm->range_enc),
			*lastrm->next_in++);
		lastrm->avail_in--;
		lastrm->total_in++;
	}
	if (lastrm->avail_in == 0 && action == ARCHIVE_Z_FINISH) {
		__archive_ppmd7_functions.Ppmd7z_RangeEnc_FlushData(
			&(strm->range_enc));
		strm->stat = 1;
		/* Return EOF if there are no remaining bytes. */
		if (strm->buff_bytes == 0)
			return (ARCHIVE_EOF);
	}
	return (ARCHIVE_OK);
}