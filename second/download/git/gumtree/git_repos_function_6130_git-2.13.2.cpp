static int count_unmerged_entries(void)
{
	int i, ret = 0;

	for (i = 0; i < active_nr; i++)
		if (ce_stage(active_cache[i]))
			ret++;

	return ret;
}