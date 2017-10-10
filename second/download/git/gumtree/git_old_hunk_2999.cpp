	/* Skip the entries with the same name */
	while (i < active_nr && ce_same_name(e, active_cache[i]))
		i++;
	return i;
}

static int find_conflict(struct string_list *conflict)
{
	int i;
	if (read_cache() < 0)
		return error("Could not read index");

