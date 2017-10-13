static void fill_line_ends(struct diff_filespec *spec, long *lines,
			   unsigned long **line_ends)
{
	int num = 0, size = 50;
	long cur = 0;
	unsigned long *ends = NULL;
	char *data = NULL;

	if (diff_populate_filespec(spec, 0))
		die("Cannot read blob %s", sha1_to_hex(spec->sha1));

	ALLOC_ARRAY(ends, size);
	ends[cur++] = 0;
	data = spec->data;
	while (num < spec->size) {
		if (data[num] == '\n' || num == spec->size - 1) {
			ALLOC_GROW(ends, (cur + 1), size);
			ends[cur++] = num;
		}
		num++;
	}

	/* shrink the array to fit the elements */
	REALLOC_ARRAY(ends, cur);
	*lines = cur-1;
	*line_ends = ends;
}