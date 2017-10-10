	if (!bases) {
		base_sha1 = null_sha1;
		base_tree_sha1 = EMPTY_TREE_SHA1_BIN;
		if (o->verbosity >= 4)
			printf("No merge base found; doing history-less merge\n");
	} else if (!bases->next) {
		base_sha1 = bases->item->object.sha1;
		base_tree_sha1 = bases->item->tree->object.sha1;
		if (o->verbosity >= 4)
			printf("One merge base found (%.7s)\n",
				sha1_to_hex(base_sha1));
	} else {
		/* TODO: How to handle multiple merge-bases? */
		base_sha1 = bases->item->object.sha1;
		base_tree_sha1 = bases->item->tree->object.sha1;
		if (o->verbosity >= 3)
			printf("Multiple merge bases found. Using the first "
				"(%.7s)\n", sha1_to_hex(base_sha1));
	}

	if (o->verbosity >= 4)
		printf("Merging remote commit %.7s into local commit %.7s with "
			"merge-base %.7s\n", sha1_to_hex(remote->object.sha1),
			sha1_to_hex(local->object.sha1),
			sha1_to_hex(base_sha1));

	if (!hashcmp(remote->object.sha1, base_sha1)) {
		/* Already merged; result == local commit */
		if (o->verbosity >= 2)
			printf("Already up-to-date!\n");
		hashcpy(result_sha1, local->object.sha1);
		goto found_result;
	}
	if (!hashcmp(local->object.sha1, base_sha1)) {
		/* Fast-forward; result == remote commit */
		if (o->verbosity >= 2)
			printf("Fast-forward\n");
		hashcpy(result_sha1, remote->object.sha1);
		goto found_result;
	}

	result = merge_from_diffs(o, base_tree_sha1, local->tree->object.sha1,
				  remote->tree->object.sha1, local_tree);

	if (result != 0) { /* non-trivial merge (with or without conflicts) */
		/* Commit (partial) result */
		struct commit_list *parents = NULL;
		commit_list_insert(remote, &parents); /* LIFO order */
		commit_list_insert(local, &parents);
