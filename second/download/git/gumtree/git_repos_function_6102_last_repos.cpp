int cmd_diff_tree(int argc, const char **argv, const char *prefix)
{
	char line[1000];
	struct object *tree1, *tree2;
	static struct rev_info *opt = &log_tree_opt;
	struct setup_revision_opt s_r_opt;
	int read_stdin = 0;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(diff_tree_usage);

	git_config(git_diff_basic_config, NULL); /* no "diff" UI options */
	init_revisions(opt, prefix);
	gitmodules_config();
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
	 * NOTE!  We expect "a..b" to expand to "^a b" but it is
	 * perfectly valid for revision range parser to yield "b ^a",
	 * which means the same thing. If we get the latter, i.e. the
	 * second one is marked UNINTERESTING, we recover the original
	 * order the user gave, i.e. "a..b", by swapping the trees.
	 */
	switch (opt->pending.nr) {
	case 0:
		if (!read_stdin)
			usage(diff_tree_usage);
		break;
	case 1:
		tree1 = opt->pending.objects[0].item;
		diff_tree_commit_oid(&tree1->oid);
		break;
	case 2:
		tree1 = opt->pending.objects[0].item;
		tree2 = opt->pending.objects[1].item;
		if (tree2->flags & UNINTERESTING) {
			SWAP(tree2, tree1);
		}
		diff_tree_oid(&tree1->oid, &tree2->oid, "", &opt->diffopt);
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
			struct object_id oid;

			if (get_oid_hex(line, &oid)) {
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