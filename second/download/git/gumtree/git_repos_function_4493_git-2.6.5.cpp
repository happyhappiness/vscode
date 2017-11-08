int cmd_check_ignore(int argc, const char **argv, const char *prefix)
{
	int num_ignored;
	struct dir_struct dir;

	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, check_ignore_options,
			     check_ignore_usage, 0);

	if (stdin_paths) {
		if (argc > 0)
			die(_("cannot specify pathnames with --stdin"));
	} else {
		if (nul_term_line)
			die(_("-z only makes sense with --stdin"));
		if (argc == 0)
			die(_("no path specified"));
	}
	if (quiet) {
		if (argc > 1)
			die(_("--quiet is only valid with a single pathname"));
		if (verbose)
			die(_("cannot have both --quiet and --verbose"));
	}
	if (show_non_matching && !verbose)
		die(_("--non-matching is only valid with --verbose"));

	/* read_cache() is only necessary so we can watch out for submodules. */
	if (!no_index && read_cache() < 0)
		die(_("index file corrupt"));

	memset(&dir, 0, sizeof(dir));
	setup_standard_excludes(&dir);

	if (stdin_paths) {
		num_ignored = check_ignore_stdin_paths(&dir, prefix);
	} else {
		num_ignored = check_ignore(&dir, prefix, argc, argv);
		maybe_flush_or_die(stdout, "ignore to stdout");
	}

	clear_directory(&dir);

	return !num_ignored;
}