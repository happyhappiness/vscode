int cmd_verify_tag(int argc, const char **argv, const char *prefix)
{
	int i = 1, verbose = 0, had_error = 0;
	unsigned flags = 0;
	char *fmt_pretty = NULL;
	const struct option verify_tag_options[] = {
		OPT__VERBOSE(&verbose, N_("print tag contents")),
		OPT_BIT(0, "raw", &flags, N_("print raw gpg status output"), GPG_VERIFY_RAW),
		OPT_STRING(  0 , "format", &fmt_pretty, N_("format"), N_("format to use for the output")),
		OPT_END()
	};

	git_config(git_verify_tag_config, NULL);

	argc = parse_options(argc, argv, prefix, verify_tag_options,
			     verify_tag_usage, PARSE_OPT_KEEP_ARGV0);
	if (argc <= i)
		usage_with_options(verify_tag_usage, verify_tag_options);

	if (verbose)
		flags |= GPG_VERIFY_VERBOSE;

	if (fmt_pretty) {
		verify_ref_format(fmt_pretty);
		flags |= GPG_VERIFY_OMIT_STATUS;
	}

	while (i < argc) {
		unsigned char sha1[20];
		const char *name = argv[i++];
		if (get_sha1(name, sha1)) {
			had_error = !!error("tag '%s' not found.", name);
			continue;
		}

		if (gpg_verify_tag(sha1, name, flags)) {
			had_error = 1;
			continue;
		}

		if (fmt_pretty)
			pretty_print_ref(name, sha1, fmt_pretty);
	}
	return had_error;
}