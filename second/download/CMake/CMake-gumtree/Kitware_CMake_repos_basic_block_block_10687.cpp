(i = 0; i < f->numBindPairs; i++) {
		if (parse_7zip_uint64(a, &(f->bindPairs[i].inIndex)) < 0)
			return (-1);
		if (UMAX_ENTRY < f->bindPairs[i].inIndex)
			return (-1);
		if (parse_7zip_uint64(a, &(f->bindPairs[i].outIndex)) < 0)
			return (-1);
		if (UMAX_ENTRY < f->bindPairs[i].outIndex)
			return (-1);
	}