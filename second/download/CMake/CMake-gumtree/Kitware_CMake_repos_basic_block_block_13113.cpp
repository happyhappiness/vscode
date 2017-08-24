{
		r = rd_contents_init(a, xar->entry_encoding,
		    xar->entry_a_sum.alg, xar->entry_e_sum.alg);
		if (r != ARCHIVE_OK) {
			xar->entry_remaining = 0;
			return (r);
		}
		xar->entry_init = 0;
	}