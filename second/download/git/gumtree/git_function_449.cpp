int cmd_notes(int argc, const char **argv, const char *prefix)
{
	int result;
	const char *override_notes_ref = NULL;
	struct option options[] = {
		OPT_STRING(0, "ref", &override_notes_ref, N_("notes-ref"),
			   N_("use notes from <notes-ref>")),
		OPT_END()
	};

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, options, git_notes_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	if (override_notes_ref) {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addstr(&sb, override_notes_ref);
		expand_notes_ref(&sb);
		setenv("GIT_NOTES_REF", sb.buf, 1);
		strbuf_release(&sb);
	}

	if (argc < 1 || !strcmp(argv[0], "list"))
		result = list(argc, argv, prefix);
	else if (!strcmp(argv[0], "add"))
		result = add(argc, argv, prefix);
	else if (!strcmp(argv[0], "copy"))
		result = copy(argc, argv, prefix);
	else if (!strcmp(argv[0], "append") || !strcmp(argv[0], "edit"))
		result = append_edit(argc, argv, prefix);
	else if (!strcmp(argv[0], "show"))
		result = show(argc, argv, prefix);
	else if (!strcmp(argv[0], "merge"))
		result = merge(argc, argv, prefix);
	else if (!strcmp(argv[0], "remove"))
		result = remove_cmd(argc, argv, prefix);
	else if (!strcmp(argv[0], "prune"))
		result = prune(argc, argv, prefix);
	else if (!strcmp(argv[0], "get-ref"))
		result = get_ref(argc, argv, prefix);
	else {
		result = error(_("Unknown subcommand: %s"), argv[0]);
		usage_with_options(git_notes_usage, options);
	}

	return result ? 1 : 0;
}