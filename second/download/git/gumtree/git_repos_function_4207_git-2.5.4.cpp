static void name_rev(struct commit *commit,
		const char *tip_name, int generation, int distance,
		int deref)
{
	struct rev_name *name = (struct rev_name *)commit->util;
	struct commit_list *parents;
	int parent_number = 1;

	parse_commit(commit);

	if (commit->date < cutoff)
		return;

	if (deref) {
		tip_name = xstrfmt("%s^0", tip_name);

		if (generation)
			die("generation: %d, but deref?", generation);
	}

	if (name == NULL) {
		name = xmalloc(sizeof(rev_name));
		commit->util = name;
		goto copy_data;
	} else if (name->distance > distance) {
copy_data:
		name->tip_name = tip_name;
		name->generation = generation;
		name->distance = distance;
	} else
		return;

	for (parents = commit->parents;
			parents;
			parents = parents->next, parent_number++) {
		if (parent_number > 1) {
			int len = strlen(tip_name);
			char *new_name = xmalloc(len +
				1 + decimal_length(generation) +  /* ~<n> */
				1 + 2 +				  /* ^NN */
				1);

			if (len > 2 && !strcmp(tip_name + len - 2, "^0"))
				len -= 2;
			if (generation > 0)
				sprintf(new_name, "%.*s~%d^%d", len, tip_name,
						generation, parent_number);
			else
				sprintf(new_name, "%.*s^%d", len, tip_name,
						parent_number);

			name_rev(parents->item, new_name, 0,
				distance + MERGE_TRAVERSAL_WEIGHT, 0);
		} else {
			name_rev(parents->item, tip_name, generation + 1,
				distance + 1, 0);
		}
	}
}