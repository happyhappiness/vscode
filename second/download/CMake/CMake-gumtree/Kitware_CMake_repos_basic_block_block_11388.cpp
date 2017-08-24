{
	struct lzx_dec *ds = strm->ds;
	struct lzx_br *br = &(ds->br);
	int i;

	if (ds->loop == 0)
		memset(ds->pt.freq, 0, sizeof(ds->pt.freq));
	for (i = ds->loop; i < ds->pt.len_size; i++) {
		if (!lzx_br_read_ahead(strm, br, 4)) {
			ds->loop = i;
			return (0);
		}
		ds->pt.bitlen[i] = lzx_br_bits(br, 4);
		ds->pt.freq[ds->pt.bitlen[i]]++;
		lzx_br_consume(br, 4);
	}
	ds->loop = i;
	return (1);
}