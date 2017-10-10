		die(_("no pattern given."));
	if (!opt.fixed && opt.ignore_case)
		opt.regflags |= REG_ICASE;

	compile_grep_patterns(&opt);

	/*
	 * We have to find "--" in a separate pass, because its presence
	 * influences how we will parse arguments that come before it.
	 */
	for (i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "--")) {
			seen_dashdash = 1;
			break;
		}
	}

	/*
	 * Resolve any rev arguments. If we have a dashdash, then everything up
	 * to it must resolve as a rev. If not, then we stop at the first
	 * non-rev and assume everything else is a path.
	 */
	allow_revs = use_index && !untracked;
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		unsigned char sha1[20];
		struct object_context oc;
		struct object *object;

		if (!strcmp(arg, "--")) {
			i++;
			break;
		}

		if (!allow_revs) {
			if (seen_dashdash)
				die(_("--no-index or --untracked cannot be used with revs"));
			break;
		}

		if (get_sha1_with_context(arg, 0, sha1, &oc)) {
			if (seen_dashdash)
				die(_("unable to resolve revision: %s"), arg);
			break;
		}

		object = parse_object_or_die(sha1, arg);
		if (!seen_dashdash)
			verify_non_filename(prefix, arg);
		add_object_array_with_path(object, arg, &list, oc.mode, oc.path);
	}

	/*
	 * Anything left over is presumed to be a path. But in the non-dashdash
	 * "do what I mean" case, we verify and complain when that isn't true.
	 */
	if (!seen_dashdash) {
		int j;
		for (j = i; j < argc; j++)
			verify_filename(prefix, argv[j], j == i && allow_revs);
	}

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD |
		       (opt.max_depth != -1 ? PATHSPEC_MAXDEPTH_VALID : 0),
		       prefix, argv + i);
	pathspec.max_depth = opt.max_depth;
	pathspec.recursive = 1;

#ifndef NO_PTHREADS
	if (list.nr || cached || show_in_pager)
		num_threads = 0;
	else if (num_threads == 0)
		num_threads = GREP_NUM_THREADS_DEFAULT;
	else if (num_threads < 0)
