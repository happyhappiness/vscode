
	for (i = 0; i < 3; i++)
		free(mmfs[i].ptr);

	if (ret >= 0) {
		const char *filename = argv[0];
		const char *fpath = prefix_filename(prefix, prefixlen, argv[0]);
		FILE *f = to_stdout ? stdout : fopen(fpath, "wb");

		if (!f)
			ret = error("Could not open %s for writing", filename);
		else if (result.size &&
			 fwrite(result.ptr, result.size, 1, f) != 1)
			ret = error("Could not write to %s", filename);
