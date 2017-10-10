		hashcpy(result_sha1, local_sha1);
		goto found_result;
	}
	assert(local && remote);

	/* Find merge bases */
	bases = get_merge_bases(local, remote, 1);
	if (!bases) {
		base_sha1 = null_sha1;
		base_tree_sha1 = EMPTY_TREE_SHA1_BIN;
		if (o->verbosity >= 4)
			printf("No merge base found; doing history-less merge\n");
	} else if (!bases->next) {
