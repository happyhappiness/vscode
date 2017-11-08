int cmd_diff_tree(int argc, const char **argv, const char *prefix)
{
	int nr_sha1;
	char line[1000];
	struct object *tree1, *tree2;
	static struct rev_info *opt = &log_tree_opt;
	struct setup_revision_opt s_r_opt;
	int read_stdin = 0;

	init_revisions(opt, prefix);
	gitmodules_config();
	git_config(git_diff_basic_config, NULL); /* no "diff" UI options */
	opt->abbrev = 0;
	opt->diff = 1;
	opt->disable_stdin = 1;
	memset(&s_r_opt, 0, sizeof(s_r_opt));
	s_r_opt.tweak = diff_tree_tweak_rev;

	precompose_argv(argc, argv);
	argc = setup_revisions(argc, argv, opt, &s_r_opt);

	while (--argc > 0) {
		const char *arg = *++argv;

		if (!strcmp(arg, "--stdin")) {
			read_stdin = 1;
			continue;
		}
		usage(diff_tree_usage);
	}

	/*
	 * NOTE! We expect "a ^b" to be equal to "a..b", so we
	 * reverse the order of the objects if the second one
	 * is marked UNINTERESTING.
	 */
	nr_sha1 = opt->pending.nr;
	switch (nr_sha1) {
	case 0:
		if (!read_stdin)
			usage(diff_tree_usage);
		break;
	case 1:
		tree1 = opt->pending.objects[0].item;
		diff_tree_commit_sha1(tree1->oid.hash);
		break;
	case 2:
		tree1 = opt->pending.objects[0].item;
		tree2 = opt->pending.objects[1].item;
		if (tree2->flags & UNINTERESTING) {
			struct object *tmp = tree2;
			tree2 = tree1;
			tree1 = tmp;
		}
		diff_tree_sha1(tree1->oid.hash,
			       tree2->oid.hash,
			       "", &opt->diffopt);
		log_tree_diff_flush(opt);
		break;
	}

	if (read_stdin) {
		int saved_nrl = 0;
		int saved_dcctc = 0;

		if (opt->diffopt.detect_rename)
			opt->diffopt.setup |= (DIFF_SETUP_USE_SIZE_CACHE |
					       DIFF_SETUP_USE_CACHE);
		while (fgets(line, sizeof(line), stdin)) {
			unsigned char sha1[20];

			if (get_sha1_hex(line, sha1)) {
				fputs(line, stdout);
				fflush(stdout);
			}
			else {
				diff_tree_stdin(line);
				if (saved_nrl < opt->diffopt.needed_rename_limit)
					saved_nrl = opt->diffopt.needed_rename_limit;
				if (opt->diffopt.degraded_cc_to_c)
					saved_dcctc = 1;
			}
		}
		opt->diffopt.degraded_cc_to_c = saved_dcctc;
		opt->diffopt.needed_rename_limit = saved_nrl;
	}

	return diff_result_code(&opt->diffopt, 0);
}