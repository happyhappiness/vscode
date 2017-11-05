static int check_one_conflict(int i, int *type)
{
	const struct cache_entry *e = active_cache[i];

	if (!ce_stage(e)) {
		*type = RESOLVED;
		return i + 1;
	}

	*type = PUNTED;
	if (ce_stage(e) == 1) {
		if (active_nr <= ++i)
			return i + 1;
	}

	/* Only handle regular files with both stages #2 and #3 */
	if (i + 1 < active_nr) {
		const struct cache_entry *e2 = active_cache[i];
		const struct cache_entry *e3 = active_cache[i + 1];
		if (ce_stage(e2) == 2 &&
		    ce_stage(e3) == 3 &&
		    ce_same_name(e, e3) &&
		    S_ISREG(e2->ce_mode) &&
		    S_ISREG(e3->ce_mode))
			*type = THREE_STAGED;
	}

	/* Skip the entries with the same name */
	while (i < active_nr && ce_same_name(e, active_cache[i]))
		i++;
	return i;
}