	parse_commit(commit);

	if (commit->date < cutoff)
		return;

	if (deref) {
		char *new_name = xmalloc(strlen(tip_name)+3);
		strcpy(new_name, tip_name);
		strcat(new_name, "^0");
		tip_name = new_name;

		if (generation)
			die("generation: %d, but deref?", generation);
	}

	if (name == NULL) {
