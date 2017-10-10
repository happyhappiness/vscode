	unsigned long *ends = NULL;
	char *data = NULL;

	if (diff_populate_filespec(spec, 0))
		die("Cannot read blob %s", sha1_to_hex(spec->sha1));

	ends = xmalloc(size * sizeof(*ends));
	ends[cur++] = 0;
	data = spec->data;
	while (num < spec->size) {
		if (data[num] == '\n' || num == spec->size - 1) {
			ALLOC_GROW(ends, (cur + 1), size);
			ends[cur++] = num;
