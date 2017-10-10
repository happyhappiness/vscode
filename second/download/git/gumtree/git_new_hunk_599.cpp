
	if (patch_interactive)
		interactive = 1;

	if (also + only + all + interactive > 1)
		die(_("Only one of --include/--only/--all/--interactive/--patch can be used."));
	if (argc == 0 && (also || (only && !amend && !allow_empty)))
		die(_("No paths with --include/--only does not make sense."));
	if (argc > 0 && !also && !only)
		only_include_assumed = _("Explicit paths specified without -i or -o; assuming --only paths...");
	if (!cleanup_arg || !strcmp(cleanup_arg, "default"))
		cleanup_mode = use_editor ? CLEANUP_ALL : CLEANUP_SPACE;
	else if (!strcmp(cleanup_arg, "verbatim"))
		cleanup_mode = CLEANUP_NONE;
