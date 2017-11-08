static int index_name_pos_also_unmerged(struct index_state *istate,
	const char *path, int namelen)
{
	int pos = index_name_pos(istate, path, namelen);
	struct cache_entry *ce;

	if (pos >= 0)
		return pos;

	/* maybe unmerged? */
	pos = -1 - pos;
	if (pos >= istate->cache_nr ||
			compare_name((ce = istate->cache[pos]), path, namelen))
		return -1;

	/* order of preference: stage 2, 1, 3 */
	if (ce_stage(ce) == 1 && pos + 1 < istate->cache_nr &&
			ce_stage((ce = istate->cache[pos + 1])) == 2 &&
			!compare_name(ce, path, namelen))
		pos++;
	return pos;
}