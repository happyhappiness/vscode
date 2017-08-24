{
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