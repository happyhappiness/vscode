static struct diff_rename_src *register_rename_src(struct diff_filepair *p)
{
	int first, last;
	struct diff_filespec *one = p->one;
	unsigned short score = p->score;

	first = 0;
	last = rename_src_nr;
	while (last > first) {
		int next = (last + first) >> 1;
		struct diff_rename_src *src = &(rename_src[next]);
		int cmp = strcmp(one->path, src->p->one->path);
		if (!cmp)
			return src;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}

	/* insert to make it at "first" */
	ALLOC_GROW(rename_src, rename_src_nr + 1, rename_src_alloc);
	rename_src_nr++;
	if (first < rename_src_nr)
		memmove(rename_src + first + 1, rename_src + first,
			(rename_src_nr - first - 1) * sizeof(*rename_src));
	rename_src[first].p = p;
	rename_src[first].score = score;
	return &(rename_src[first]);
}