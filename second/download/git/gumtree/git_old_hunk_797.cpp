	argv_array_pushl(&reflog, "reflog", "expire", "--all", NULL);
	argv_array_pushl(&repack, "repack", "-d", "-l", NULL);
	argv_array_pushl(&prune, "prune", "--expire", NULL);
	argv_array_pushl(&prune_worktrees, "worktree", "prune", "--expire", NULL);
	argv_array_pushl(&rerere, "rerere", "gc", NULL);

	gc_config();

	if (pack_refs < 0)
		pack_refs = !is_bare_repository();

	argc = parse_options(argc, argv, prefix, builtin_gc_options,
			     builtin_gc_usage, 0);
