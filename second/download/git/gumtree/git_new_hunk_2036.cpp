	if (help_format == HELP_FORMAT_NONE)
		help_format = parse_help_format(DEFAULT_HELP_FORMAT);

	alias = alias_lookup(argv[0]);
	if (alias && !is_git_command(argv[0])) {
		printf_ln(_("`git %s' is aliased to `%s'"), argv[0], alias);
		free(alias);
		return 0;
	}

	switch (help_format) {
	case HELP_FORMAT_NONE:
	case HELP_FORMAT_MAN:
