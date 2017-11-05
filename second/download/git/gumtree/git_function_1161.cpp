int setup_revisions(int argc, const char **argv, struct rev_info *revs, struct setup_revision_opt *opt)
{
	int i, flags, left, seen_dashdash, read_from_stdin, got_rev_arg = 0, revarg_opt;
	struct cmdline_pathspec prune_data;
	const char *submodule = NULL;

	memset(&prune_data, 0, sizeof(prune_data));
	if (opt)
		submodule = opt->submodule;

	/* First, search for "--" */
	if (opt && opt->assume_dashdash) {
		seen_dashdash = 1;
	} else {
		seen_dashdash = 0;
		for (i = 1; i < argc; i++) {
			const char *arg = argv[i];
			if (strcmp(arg, "--"))
				continue;
			argv[i] = NULL;
			argc = i;
			if (argv[i + 1])
				append_prune_data(&prune_data, argv + i + 1);
			seen_dashdash = 1;
			break;
		}
	}

	/* Second, deal with arguments and options */
	flags = 0;
	revarg_opt = opt ? opt->revarg_opt : 0;
	if (seen_dashdash)
		revarg_opt |= REVARG_CANNOT_BE_FILENAME;
	read_from_stdin = 0;
	for (left = i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (*arg == '-') {
			int opts;

			opts = handle_revision_pseudo_opt(submodule,
						revs, argc - i, argv + i,
						&flags);
			if (opts > 0) {
				i += opts - 1;
				continue;
			}

			if (!strcmp(arg, "--stdin")) {
				if (revs->disable_stdin) {
					argv[left++] = arg;
					continue;
				}
				if (read_from_stdin++)
					die("--stdin given twice?");
				read_revisions_from_stdin(revs, &prune_data);
				continue;
			}

			opts = handle_revision_opt(revs, argc - i, argv + i, &left, argv);
			if (opts > 0) {
				i += opts - 1;
				continue;
			}
			if (opts < 0)
				exit(128);
			continue;
		}


		if (handle_revision_arg(arg, revs, flags, revarg_opt)) {
			int j;
			if (seen_dashdash || *arg == '^')
				die("bad revision '%s'", arg);

			/* If we didn't have a "--":
			 * (1) all filenames must exist;
			 * (2) all rev-args must not be interpretable
			 *     as a valid filename.
			 * but the latter we have checked in the main loop.
			 */
			for (j = i; j < argc; j++)
				verify_filename(revs->prefix, argv[j], j == i);

			append_prune_data(&prune_data, argv + i);
			break;
		}
		else
			got_rev_arg = 1;
	}

	if (prune_data.nr) {
		/*
		 * If we need to introduce the magic "a lone ':' means no
		 * pathspec whatsoever", here is the place to do so.
		 *
		 * if (prune_data.nr == 1 && !strcmp(prune_data[0], ":")) {
		 *	prune_data.nr = 0;
		 *	prune_data.alloc = 0;
		 *	free(prune_data.path);
		 *	prune_data.path = NULL;
		 * } else {
		 *	terminate prune_data.alloc with NULL and
		 *	call init_pathspec() to set revs->prune_data here.
		 * }
		 */
		ALLOC_GROW(prune_data.path, prune_data.nr + 1, prune_data.alloc);
		prune_data.path[prune_data.nr++] = NULL;
		parse_pathspec(&revs->prune_data, 0, 0,
			       revs->prefix, prune_data.path);
	}

	if (revs->def == NULL)
		revs->def = opt ? opt->def : NULL;
	if (opt && opt->tweak)
		opt->tweak(revs, opt);
	if (revs->show_merge)
		prepare_show_merge(revs);
	if (revs->def && !revs->pending.nr && !revs->rev_input_given && !got_rev_arg) {
		struct object_id oid;
		struct object *object;
		struct object_context oc;
		if (get_sha1_with_context(revs->def, 0, oid.hash, &oc))
			diagnose_missing_default(revs->def);
		object = get_reference(revs, revs->def, &oid, 0);
		add_pending_object_with_mode(revs, object, revs->def, oc.mode);
	}

	/* Did the user ask for any diff output? Run the diff! */
	if (revs->diffopt.output_format & ~DIFF_FORMAT_NO_OUTPUT)
		revs->diff = 1;

	/* Pickaxe, diff-filter and rename following need diffs */
	if (revs->diffopt.pickaxe ||
	    revs->diffopt.filter ||
	    DIFF_OPT_TST(&revs->diffopt, FOLLOW_RENAMES))
		revs->diff = 1;

	if (revs->topo_order)
		revs->limited = 1;

	if (revs->prune_data.nr) {
		copy_pathspec(&revs->pruning.pathspec, &revs->prune_data);
		/* Can't prune commits with rename following: the paths change.. */
		if (!DIFF_OPT_TST(&revs->diffopt, FOLLOW_RENAMES))
			revs->prune = 1;
		if (!revs->full_diff)
			copy_pathspec(&revs->diffopt.pathspec,
				      &revs->prune_data);
	}
	if (revs->combine_merges)
		revs->ignore_merges = 0;
	revs->diffopt.abbrev = revs->abbrev;

	if (revs->line_level_traverse) {
		revs->limited = 1;
		revs->topo_order = 1;
	}

	diff_setup_done(&revs->diffopt);

	grep_commit_pattern_type(GREP_PATTERN_TYPE_UNSPECIFIED,
				 &revs->grep_filter);
	compile_grep_patterns(&revs->grep_filter);

	if (revs->reverse && revs->reflog_info)
		die("cannot combine --reverse with --walk-reflogs");
	if (revs->reflog_info && revs->limited)
		die("cannot combine --walk-reflogs with history-limiting options");
	if (revs->rewrite_parents && revs->children.name)
		die("cannot combine --parents and --children");

	/*
	 * Limitations on the graph functionality
	 */
	if (revs->reverse && revs->graph)
		die("cannot combine --reverse with --graph");

	if (revs->reflog_info && revs->graph)
		die("cannot combine --walk-reflogs with --graph");
	if (revs->no_walk && revs->graph)
		die("cannot combine --no-walk with --graph");
	if (!revs->reflog_info && revs->grep_filter.use_reflog_filter)
		die("cannot use --grep-reflog without --walk-reflogs");

	if (revs->first_parent_only && revs->bisect)
		die(_("--first-parent is incompatible with --bisect"));

	if (revs->expand_tabs_in_log < 0)
		revs->expand_tabs_in_log = revs->expand_tabs_in_log_default;

	return left;
}