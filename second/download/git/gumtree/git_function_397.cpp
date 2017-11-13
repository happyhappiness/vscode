int cmd_help(int argc, const char **argv, const char *prefix)
{
	int nongit;
	char *alias;
	enum help_format parsed_help_format;

	argc = parse_options(argc, argv, prefix, builtin_help_options,
			builtin_help_usage, 0);
	parsed_help_format = help_format;

	if (show_all) {
		git_config(git_help_config, NULL);
		printf(_("usage: %s%s"), _(git_usage_string), "\n\n");
		load_command_list("git-", &main_cmds, &other_cmds);
		list_commands(colopts, &main_cmds, &other_cmds);
	}

	if (show_guides)
		list_common_guides_help();

	if (show_all || show_guides) {
		printf("%s\n", _(git_more_info_string));
		/*
		* We're done. Ignore any remaining args
		*/
		return 0;
	}

	if (!argv[0]) {
		printf(_("usage: %s%s"), _(git_usage_string), "\n\n");
		list_common_cmds_help();
		printf("\n%s\n", _(git_more_info_string));
		return 0;
	}

	setup_git_directory_gently(&nongit);
	git_config(git_help_config, NULL);

	if (parsed_help_format != HELP_FORMAT_NONE)
		help_format = parsed_help_format;
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
		show_man_page(argv[0]);
		break;
	case HELP_FORMAT_INFO:
		show_info_page(argv[0]);
		break;
	case HELP_FORMAT_WEB:
		show_html_page(argv[0]);
		break;
	}

	return 0;
}