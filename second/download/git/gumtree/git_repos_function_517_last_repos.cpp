static int add_rename_dst(struct diff_filespec *two)
{
	int first = find_rename_dst(two);

	if (first >= 0)
		return -1;
	first = -first - 1;

	/* insert to make it at "first" */
	ALLOC_GROW(rename_dst, rename_dst_nr + 1, rename_dst_alloc);
	rename_dst_nr++;
	if (first < rename_dst_nr)
		memmove(rename_dst + first + 1, rename_dst + first,
			(rename_dst_nr - first - 1) * sizeof(*rename_dst));
	rename_dst[first].two = alloc_filespec(two->path);
	fill_filespec(rename_dst[first].two, &two->oid, two->oid_valid,
		      two->mode);
	rename_dst[first].pair = NULL;
	return 0;
}