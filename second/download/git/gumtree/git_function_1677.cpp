int bisect_next_all(const char *prefix, int no_checkout)
{
	struct rev_info revs;
	struct commit_list *tried;
	int reaches = 0, all = 0, nr, steps;
	const unsigned char *bisect_rev;

	read_bisect_terms(&term_bad, &term_good);
	if (read_bisect_refs())
		die("reading bisect refs failed");

	check_good_are_ancestors_of_bad(prefix, no_checkout);

	bisect_rev_setup(&revs, prefix, "%s", "^%s", 1);
	revs.limited = 1;

	bisect_common(&revs);

	revs.commits = find_bisection(revs.commits, &reaches, &all,
				       !!skipped_revs.nr);
	revs.commits = managed_skipped(revs.commits, &tried);

	if (!revs.commits) {
		/*
		 * We should exit here only if the "bad"
		 * commit is also a "skip" commit.
		 */
		exit_if_skipped_commits(tried, NULL);

		printf("%s was both %s and %s\n",
		       oid_to_hex(current_bad_oid),
		       term_good,
		       term_bad);
		exit(1);
	}

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
		/* This means the bisection process succeeded. */
		exit(10);
	}

	nr = all - reaches - 1;
	steps = estimate_bisect_steps(all);
	printf("Bisecting: %d revision%s left to test after this "
	       "(roughly %d step%s)\n", nr, (nr == 1 ? "" : "s"),
	       steps, (steps == 1 ? "" : "s"));

	return bisect_checkout(bisect_rev, no_checkout);
}