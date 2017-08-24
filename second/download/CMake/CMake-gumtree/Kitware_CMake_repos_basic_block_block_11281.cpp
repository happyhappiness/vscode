{
	struct lzx_dec *ds;
	int slot, w_size, w_slot;
	int base, footer;
	int base_inc[18];

	if (strm->ds == NULL) {
		strm->ds = calloc(1, sizeof(*strm->ds));
		if (strm->ds == NULL)
			return (ARCHIVE_FATAL);
	}
	ds = strm->ds;
	ds->error = ARCHIVE_FAILED;

	/* Allow bits from 15(32KBi) up to 21(2MBi) */
	if (w_bits < SLOT_BASE || w_bits > SLOT_MAX)
		return (ARCHIVE_FAILED);

	ds->error = ARCHIVE_FATAL;

	/*
	 * Alloc window
	 */
	w_size = ds->w_size;
	w_slot = slots[w_bits - SLOT_BASE];
	ds->w_size = 1U << w_bits;
	ds->w_mask = ds->w_size -1;
	if (ds->w_buff == NULL || w_size != ds->w_size) {
		free(ds->w_buff);
		ds->w_buff = malloc(ds->w_size);
		if (ds->w_buff == NULL)
			return (ARCHIVE_FATAL);
		free(ds->pos_tbl);
		ds->pos_tbl = malloc(sizeof(ds->pos_tbl[0]) * w_slot);
		if (ds->pos_tbl == NULL)
			return (ARCHIVE_FATAL);
		lzx_huffman_free(&(ds->mt));
	}

	for (footer = 0; footer < 18; footer++)
		base_inc[footer] = 1 << footer;
	base = footer = 0;
	for (slot = 0; slot < w_slot; slot++) {
		int n;
		if (footer == 0)
			base = slot;
		else
			base += base_inc[footer];
		if (footer < 17) {
			footer = -2;
			for (n = base; n; n >>= 1)
				footer++;
			if (footer <= 0)
				footer = 0;
		}
		ds->pos_tbl[slot].base = base;
		ds->pos_tbl[slot].footer_bits = footer;
	}

	ds->w_pos = 0;
	ds->state = 0;
	ds->br.cache_buffer = 0;
	ds->br.cache_avail = 0;
	ds->r0 = ds->r1 = ds->r2 = 1;

	/* Initialize aligned offset tree. */
	if (lzx_huffman_init(&(ds->at), 8, 8) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/* Initialize pre-tree. */
	if (lzx_huffman_init(&(ds->pt), 20, 10) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/* Initialize Main tree. */
	if (lzx_huffman_init(&(ds->mt), 256+(w_slot<<3), 16)
	    != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/* Initialize Length tree. */
	if (lzx_huffman_init(&(ds->lt), 249, 16) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	ds->error = 0;

	return (ARCHIVE_OK);
}