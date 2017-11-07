static int get_url(int argc, const char **argv)
{
	int i, push_mode = 0, all_mode = 0;
	const char *remotename = NULL;
	struct remote *remote;
	const char **url;
	int url_nr;
	struct option options[] = {
		OPT_BOOL('\0', "push", &push_mode,
			 N_("query push URLs rather than fetch URLs")),
		OPT_BOOL('\0', "all", &all_mode,
			 N_("return all URLs")),
		OPT_END()
	};
	argc = parse_options(argc, argv, NULL, options, builtin_remote_geturl_usage, 0);

	if (argc != 1)
		usage_with_options(builtin_remote_geturl_usage, options);

	remotename = argv[0];

	if (!remote_is_configured(remotename))
		die(_("No such remote '%s'"), remotename);
	remote = remote_get(remotename);

	url_nr = 0;
	if (push_mode) {
		url = remote->pushurl;
		url_nr = remote->pushurl_nr;
	}
	/* else fetch mode */

	/* Use the fetch URL when no push URLs were found or requested. */
	if (!url_nr) {
		url = remote->url;
		url_nr = remote->url_nr;
	}

	if (!url_nr)
		die(_("no URLs configured for remote '%s'"), remotename);

	if (all_mode) {
		for (i = 0; i < url_nr; i++)
			printf_ln("%s", url[i]);
	} else {
		printf_ln("%s", *url);
	}

	return 0;
}