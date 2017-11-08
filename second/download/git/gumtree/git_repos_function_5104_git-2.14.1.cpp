static void name_rev(struct commit *commit,
		const char *tip_name, timestamp_t taggerdate,
		int generation, int distance, int from_tag,
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
		name = xmalloc(sizeof(rev_name));
		commit->util = name;
		goto copy_data;
	} else if (is_better_name(name, tip_name, taggerdate,
				  generation, distance, from_tag)) {
copy_data:
		name->tip_name = tip_name;
		name->taggerdate = taggerdate;
		name->generation = generation;
		name->distance = distance;
		name->from_tag = from_tag;
	} else {
		free(to_free);
		return;
	}

	for (parents = commit->parents;
			parents;
			parents = parents->next, parent_number++) {
		if (parent_number > 1) {
			size_t len;
			char *new_name;

			strip_suffix(tip_name, "^0", &len);
			if (generation > 0)
				new_name = xstrfmt("%.*s~%d^%d", (int)len, tip_name,
						   generation, parent_number);
			else
				new_name = xstrfmt("%.*s^%d", (int)len, tip_name,
						   parent_number);

			name_rev(parents->item, new_name, taggerdate, 0,
				 distance + MERGE_TRAVERSAL_WEIGHT,
				 from_tag, 0);
		} else {
			name_rev(parents->item, tip_name, taggerdate,
				 generation + 1, distance + 1,
				 from_tag, 0);
		}
	}
}