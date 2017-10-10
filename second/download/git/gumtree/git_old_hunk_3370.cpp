		OPT__QUIET(&quiet, "Suppress output for cloning a submodule"),
		OPT_END()
	};

	const char *const git_submodule_helper_usage[] = {
		N_("git submodule--helper clone [--prefix=<path>] [--quiet] "
		   "[--reference <repository>] [--name <name>] [--url <url>]"
		   "[--depth <depth>] [--] [<path>...]"),
		NULL
	};

	argc = parse_options(argc, argv, prefix, module_clone_options,
			     git_submodule_helper_usage, 0);

	if (!path || !*path)
		die(_("submodule--helper: unspecified or empty --path"));

	strbuf_addf(&sb, "%s/modules/%s", get_git_dir(), name);
	sm_gitdir = xstrdup(absolute_path(sb.buf));
	strbuf_reset(&sb);

	if (!is_absolute_path(path)) {
