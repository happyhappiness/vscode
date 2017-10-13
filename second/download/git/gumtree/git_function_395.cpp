int cmd_fetch(int argc, const char **argv, const char *prefix)
{
	int i;
	struct string_list list = STRING_LIST_INIT_DUP;
	struct remote *remote;
	int result = 0;
	struct argv_array argv_gc_auto = ARGV_ARRAY_INIT;

	packet_trace_identity("fetch");

	/* Record the command line for the reflog */
	strbuf_addstr(&default_rla, "fetch");
	for (i = 1; i < argc; i++)
		strbuf_addf(&default_rla, " %s", argv[i]);

	git_config(git_fetch_config, NULL);

	argc = parse_options(argc, argv, prefix,
			     builtin_fetch_options, builtin_fetch_usage, 0);

	if (deepen_relative) {
		if (deepen_relative < 0)
			die(_("Negative depth in --deepen is not supported"));
		if (depth)
			die(_("--deepen and --depth are mutually exclusive"));
		depth = xstrfmt("%d", deepen_relative);
	}
	if (unshallow) {
		if (depth)
			die(_("--depth and --unshallow cannot be used together"));
		else if (!is_repository_shallow())
			die(_("--unshallow on a complete repository does not make sense"));
		else
			depth = xstrfmt("%d", INFINITE_DEPTH);
	}

	/* no need to be strict, transport_set_option() will validate it again */
	if (depth && atoi(depth) < 1)
		die(_("depth %s is not a positive number"), depth);
	if (depth || deepen_since || deepen_not.nr)
		deepen = 1;

	if (recurse_submodules != RECURSE_SUBMODULES_OFF) {
		if (recurse_submodules_default) {
			int arg = parse_fetch_recurse_submodules_arg("--recurse-submodules-default", recurse_submodules_default);
			set_config_fetch_recurse_submodules(arg);
		}
		gitmodules_config();
		git_config(submodule_config, NULL);
	}

	if (all) {
		if (argc == 1)
			die(_("fetch --all does not take a repository argument"));
		else if (argc > 1)
			die(_("fetch --all does not make sense with refspecs"));
		(void) for_each_remote(get_one_remote_for_fetch, &list);
		result = fetch_multiple(&list);
	} else if (argc == 0) {
		/* No arguments -- use default remote */
		remote = remote_get(NULL);
		result = fetch_one(remote, argc, argv);
	} else if (multiple) {
		/* All arguments are assumed to be remotes or groups */
		for (i = 0; i < argc; i++)
			if (!add_remote_or_group(argv[i], &list))
				die(_("No such remote or remote group: %s"), argv[i]);
		result = fetch_multiple(&list);
	} else {
		/* Single remote or group */
		(void) add_remote_or_group(argv[0], &list);
		if (list.nr > 1) {
			/* More than one remote */
			if (argc > 1)
				die(_("Fetching a group and specifying refspecs does not make sense"));
			result = fetch_multiple(&list);
		} else {
			/* Zero or one remotes */
			remote = remote_get(argv[0]);
			result = fetch_one(remote, argc-1, argv+1);
		}
	}

	if (!result && (recurse_submodules != RECURSE_SUBMODULES_OFF)) {
		struct argv_array options = ARGV_ARRAY_INIT;

		add_options_to_argv(&options);
		result = fetch_populated_submodules(&options,
						    submodule_prefix,
						    recurse_submodules,
						    verbosity < 0,
						    max_children);
		argv_array_clear(&options);
	}

	string_list_clear(&list, 0);

	close_all_packs();

	argv_array_pushl(&argv_gc_auto, "gc", "--auto", NULL);
	if (verbosity < 0)
		argv_array_push(&argv_gc_auto, "--quiet");
	run_command_v_opt(argv_gc_auto.argv, RUN_GIT_CMD);
	argv_array_clear(&argv_gc_auto);

	return result;
}