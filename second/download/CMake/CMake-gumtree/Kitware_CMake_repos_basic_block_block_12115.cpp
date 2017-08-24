{
		unsigned htbl_max;
		uint16_t *p;

		diffbits = maxbits - HTBL_BITS;
		for (i = 1; i <= HTBL_BITS; i++) {
			bitptn[i] >>= diffbits;
			weight[i] >>= diffbits;
		}
		htbl_max = bitptn[HTBL_BITS] +
		    weight[HTBL_BITS] * hf->freq[HTBL_BITS];
		p = &(hf->tbl[htbl_max]);
		while (p < &hf->tbl[1U<<HTBL_BITS])
			*p++ = 0;
	}