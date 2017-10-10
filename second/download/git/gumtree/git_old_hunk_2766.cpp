	if (!all) {
		fprintf(stderr, "No testable commit found.\n"
			"Maybe you started with bad path parameters?\n");
		exit(4);
	}

	bisect_rev = revs.commits->item->object.sha1;

	if (!hashcmp(bisect_rev, current_bad_oid->hash)) {
		exit_if_skipped_commits(tried, current_bad_oid);
		printf("%s is the first %s commit\n", sha1_to_hex(bisect_rev),
			term_bad);
		show_diff_tree(prefix, revs.commits->item);
