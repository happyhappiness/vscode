(f->numBindPairs > 0) {
		f->bindPairs =
			calloc((size_t)f->numBindPairs, sizeof(*f->bindPairs));
		if (f->bindPairs == NULL)
			return (-1);
	} else
		f->bindPairs = NULL