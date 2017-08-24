(cab->entry_cfdata == NULL) {
		r = cab_next_cfdata(a);
		if (r < 0)
			return (r);
	}