	/* Skip the entries with the same name */
	while (i < active_nr && ce_same_name(e, active_cache[i]))
		i++;
	return i;
}

/*
 * Scan the index and find paths that have conflicts that rerere can
 * handle, i.e. the ones that has both stages #2 and #3.
 *
 * NEEDSWORK: we do not record or replay a previous "resolve by
 * deletion" for a delete-modify conflict, as that is inherently risky
 * without knowing what modification is being discarded.  The only
 * safe case, i.e. both side doing the deletion and modification that
 * are identical to the previous round, might want to be handled,
 * though.
 */
static int find_conflict(struct string_list *conflict)
{
	int i;
	if (read_cache() < 0)
		return error("Could not read index");

