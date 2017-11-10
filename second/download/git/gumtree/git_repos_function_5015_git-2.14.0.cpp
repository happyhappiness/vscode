int cmd_check_mailmap(int argc, const char **argv, const char *prefix)
{
	int i;
	struct string_list mailmap = STRING_LIST_INIT_NODUP;

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, check_mailmap_options,
			     check_mailmap_usage, 0);
	if (argc == 0 && !use_stdin)
		die(_("no contacts specified"));

	read_mailmap(&mailmap, NULL);

	for (i = 0; i < argc; ++i)
		check_mailmap(&mailmap, argv[i]);
	maybe_flush_or_die(stdout, "stdout");

	if (use_stdin) {
		struct strbuf buf = STRBUF_INIT;
		while (strbuf_getline_lf(&buf, stdin) != EOF) {
			check_mailmap(&mailmap, buf.buf);
			maybe_flush_or_die(stdout, "stdout");
		}
		strbuf_release(&buf);
	}

	clear_mailmap(&mailmap);
	return 0;
}