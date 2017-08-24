(hf->tbl == NULL) {
		if (tbl_bits < HTBL_BITS)
			bits = tbl_bits;
		else
			bits = HTBL_BITS;
		hf->tbl = malloc(((size_t)1 << bits) * sizeof(hf->tbl[0]));
		if (hf->tbl == NULL)
			return (ARCHIVE_FATAL);
	}