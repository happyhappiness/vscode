int bisect_next_all(const char *prefix, int no_checkout)
{
	struct rev_info revs;
	struct commit_list *tried;
	int reaches = 0, all = 0, nr, steps;
	const unsigned char *bisect_rev;
	char steps_msg[32];

	read_bisect_terms(&term_bad, &term_good);
	if (read_bisect_refs())
		die(_("reading bisect refs failed"));

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

		printf(_("%s was both %s and %s\n"),
		       oid_to_hex(current_bad_oid),
		       term_good,
		       term_bad);
		exit(1);
	}

	if (!all) {
		fprintf(stderr, _("No testable commit found.\n"
			"Maybe you started with bad path parameters?\n"));
		exit(4);
	}

	bisect_rev = revs.commits->item->object.oid.hash;

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
	xsnprintf(steps_msg, sizeof(steps_msg),
		  Q_("(roughly %d step)", "(roughly %d steps)", steps),
		  steps);
	/* TRANSLATORS: the last %s will be replaced with
	   "(roughly %d steps)" translation */
	printf(Q_("Bisecting: %d revision left to test after this %s\n",
		  "Bisecting: %d revisions left to test after this %s\n",
		  nr), nr, steps_msg);

	return bisect_checkout(bisect_rev, no_checkout);
}