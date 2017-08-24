(i = 0; i < pi->numPackStreams; i++) {
		if (parse_7zip_uint64(a, &(pi->sizes[i])) < 0)
			return (-1);
	}