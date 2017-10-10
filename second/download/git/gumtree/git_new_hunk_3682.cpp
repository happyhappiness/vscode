{
	struct option options[] = { OPT_END() };
	argc = parse_options(argc, argv, prefix, options,
			     git_notes_get_ref_usage, 0);

	if (argc) {
		error(_("too many parameters"));
		usage_with_options(git_notes_get_ref_usage, options);
	}

	puts(default_notes_ref());
	return 0;
}
