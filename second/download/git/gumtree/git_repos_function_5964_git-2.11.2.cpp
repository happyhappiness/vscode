static int get_ours_cache_pos(const char *path, int pos)
{
	int i = -pos - 1;

	while ((i < active_nr) && !strcmp(active_cache[i]->name, path)) {
		if (ce_stage(active_cache[i]) == 2)
			return i;
		i++;
	}
	return -1;
}