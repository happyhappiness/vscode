		die(_("no pattern given."));
	if (!opt.fixed && opt.ignore_case)
		opt.regflags |= REG_ICASE;

	compile_grep_patterns(&opt);

	/* Check revs and then paths */
	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		unsigned char sha1[20];
		struct object_context oc;
		/* Is it a rev? */
		if (!get_sha1_with_context(arg, 0, sha1, &oc)) {
			struct object *object = parse_object_or_die(sha1, arg);
			if (!seen_dashdash)
				verify_non_filename(prefix, arg);
			add_object_array_with_path(object, arg, &list, oc.mode, oc.path);
			continue;
		}
		if (!strcmp(arg, "--")) {
			i++;
			seen_dashdash = 1;
		}
		break;
	}

#ifndef NO_PTHREADS
	if (list.nr || cached || show_in_pager)
		num_threads = 0;
	else if (num_threads == 0)
		num_threads = GREP_NUM_THREADS_DEFAULT;
	else if (num_threads < 0)
