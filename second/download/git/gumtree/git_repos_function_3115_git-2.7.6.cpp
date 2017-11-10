static int was_tracked(const char *path)
{
	int pos = cache_name_pos(path, strlen(path));

	if (pos < 0)
		pos = -1 - pos;
	while (pos < active_nr &&
	       !strcmp(path, active_cache[pos]->name)) {
		/*
		 * If stage #0, it is definitely tracked.
		 * If it has stage #2 then it was tracked
		 * before this merge started.  All other
		 * cases the path was not tracked.
		 */
		switch (ce_stage(active_cache[pos])) {
		case 0:
		case 2:
			return 1;
		}
		pos++;
	}
	return 0;
}