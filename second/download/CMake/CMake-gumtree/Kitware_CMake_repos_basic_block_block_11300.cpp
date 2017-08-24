{
	struct lzx_dec *ds = strm->ds;
	int64_t avail_in;
	int r;

	if (ds->error)
		return (ds->error);

	avail_in = strm->avail_in;
	lzx_br_fixup(strm, &(ds->br));
	do {
		if (ds->state < ST_MAIN)
			r = lzx_read_blocks(strm, last);
		else {
			int64_t bytes_written = strm->avail_out;
			r = lzx_decode_blocks(strm, last);
			bytes_written -= strm->avail_out;
			strm->next_out += bytes_written;
			strm->total_out += bytes_written;
		}
	} while (r == 100);
	strm->total_in += avail_in - strm->avail_in;
	return (r);
}