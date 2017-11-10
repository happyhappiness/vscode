static int show_bisect_vars(struct rev_list_info *info, int reaches, int all)
{
	int cnt, flags = info->flags;
	char hex[GIT_MAX_HEXSZ + 1] = "";
	struct commit_list *tried;
	struct rev_info *revs = info->revs;

	if (!revs->commits)
		return 1;

	revs->commits = filter_skipped(revs->commits, &tried,
				       flags & BISECT_SHOW_ALL,
				       NULL, NULL);

	/*
	 * revs->commits can reach "reaches" commits among
	 * "all" commits.  If it is good, then there are
	 * (all-reaches) commits left to be bisected.
	 * On the other hand, if it is bad, then the set
	 * to bisect is "reaches".
	 * A bisect set of size N has (N-1) commits further
	 * to test, as we already know one bad one.
	 */
	cnt = all - reaches;
	if (cnt < reaches)
		cnt = reaches;

	if (revs->commits)
		oid_to_hex_r(hex, &revs->commits->item->object.oid);

	if (flags & BISECT_SHOW_ALL) {
		traverse_commit_list(revs, show_commit, show_object, info);
		printf("------\n");
	}

	print_var_str("bisect_rev", hex);
	print_var_int("bisect_nr", cnt - 1);
	print_var_int("bisect_good", all - reaches - 1);
	print_var_int("bisect_bad", reaches - 1);
	print_var_int("bisect_all", all);
	print_var_int("bisect_steps", estimate_bisect_steps(all));

	return 0;
}