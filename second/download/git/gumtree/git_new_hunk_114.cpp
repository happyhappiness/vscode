	parse_commit(commit);

	if (commit->date < cutoff)
		return;

	if (deref) {
		tip_name = xstrfmt("%s^0", tip_name);

		if (generation)
			die("generation: %d, but deref?", generation);
	}

	if (name == NULL) {
