static int patience_diff(mmfile_t *file1, mmfile_t *file2,
		xpparam_t const *xpp, xdfenv_t *env,
		int line1, int count1, int line2, int count2)
{
	struct hashmap map;
	struct entry *first;
	int result = 0;

	/* trivial case: one side is empty */
	if (!count1) {
		while(count2--)
			env->xdf2.rchg[line2++ - 1] = 1;
		return 0;
	} else if (!count2) {
		while(count1--)
			env->xdf1.rchg[line1++ - 1] = 1;
		return 0;
	}

	memset(&map, 0, sizeof(map));
	if (fill_hashmap(file1, file2, xpp, env, &map,
			line1, count1, line2, count2))
		return -1;

	/* are there any matching lines at all? */
	if (!map.has_matches) {
		while(count1--)
			env->xdf1.rchg[line1++ - 1] = 1;
		while(count2--)
			env->xdf2.rchg[line2++ - 1] = 1;
		xdl_free(map.entries);
		return 0;
	}

	first = find_longest_common_sequence(&map);
	if (first)
		result = walk_common_sequence(&map, first,
			line1, count1, line2, count2);
	else
		result = fall_back_to_classic_diff(&map,
			line1, count1, line2, count2);

	xdl_free(map.entries);
	return result;
}