static int was_tracked(const char *path)
{
	int pos = cache_name_pos(path, strlen(path));

	if (0 <= pos)
		/* we have been tracking this path */
		return 1;

	/*
	 * Look for an unmerged entry for the path,
	 * specifically stage #2, which would indicate
	 * that "our" side before the merge started
	 * had the path tracked (and resulted in a conflict).
	 */
	for (pos = -1 - pos;
	     pos < active_nr && !strcmp(path, active_cache[pos]->name);
	     pos++)
		if (ce_stage(active_cache[pos]) == 2)
			return 1;
	return 0;
}