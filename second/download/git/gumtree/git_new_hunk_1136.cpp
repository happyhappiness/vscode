		int generation, int distance,
		int deref)
{
	struct rev_name *name = (struct rev_name *)commit->util;
	struct commit_list *parents;
	int parent_number = 1;
	char *to_free = NULL;

	parse_commit(commit);

	if (commit->date < cutoff)
		return;

	if (deref) {
		tip_name = to_free = xstrfmt("%s^0", tip_name);

		if (generation)
			die("generation: %d, but deref?", generation);
	}

	if (name == NULL) {
