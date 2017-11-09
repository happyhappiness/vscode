static int set_url(int argc, const char **argv)
{
	int i, push_mode = 0, add_mode = 0, delete_mode = 0;
	int matches = 0, negative_matches = 0;
	const char *remotename = NULL;
	const char *newurl = NULL;
	const char *oldurl = NULL;
	struct remote *remote;
	regex_t old_regex;
	const char **urlset;
	int urlset_nr;
	struct strbuf name_buf = STRBUF_INIT;
	struct option options[] = {
		OPT_BOOL('\0', "push", &push_mode,
			 N_("manipulate push URLs")),
		OPT_BOOL('\0', "add", &add_mode,
			 N_("add URL")),
		OPT_BOOL('\0', "delete", &delete_mode,
			    N_("delete URLs")),
		OPT_END()
	};
	argc = parse_options(argc, argv, NULL, options, builtin_remote_seturl_usage,
			     PARSE_OPT_KEEP_ARGV0);

	if (add_mode && delete_mode)
		die(_("--add --delete doesn't make sense"));

	if (argc < 3 || argc > 4 || ((add_mode || delete_mode) && argc != 3))
		usage_with_options(builtin_remote_seturl_usage, options);

	remotename = argv[1];
	newurl = argv[2];
	if (argc > 3)
		oldurl = argv[3];

	if (delete_mode)
		oldurl = newurl;

	remote = remote_get(remotename);
	if (!remote_is_configured(remote, 1))
		die(_("No such remote '%s'"), remotename);

	if (push_mode) {
		strbuf_addf(&name_buf, "remote.%s.pushurl", remotename);
		urlset = remote->pushurl;
		urlset_nr = remote->pushurl_nr;
	} else {
		strbuf_addf(&name_buf, "remote.%s.url", remotename);
		urlset = remote->url;
		urlset_nr = remote->url_nr;
	}

	/* Special cases that add new entry. */
	if ((!oldurl && !delete_mode) || add_mode) {
		if (add_mode)
			git_config_set_multivar(name_buf.buf, newurl,
						       "^$", 0);
		else
			git_config_set(name_buf.buf, newurl);
		strbuf_release(&name_buf);

		return 0;
	}

	/* Old URL specified. Demand that one matches. */
	if (regcomp(&old_regex, oldurl, REG_EXTENDED))
		die(_("Invalid old URL pattern: %s"), oldurl);

	for (i = 0; i < urlset_nr; i++)
		if (!regexec(&old_regex, urlset[i], 0, NULL, 0))
			matches++;
		else
			negative_matches++;
	if (!delete_mode && !matches)
		die(_("No such URL found: %s"), oldurl);
	if (delete_mode && !negative_matches && !push_mode)
		die(_("Will not delete all non-push URLs"));

	regfree(&old_regex);

	if (!delete_mode)
		git_config_set_multivar(name_buf.buf, newurl, oldurl, 0);
	else
		git_config_set_multivar(name_buf.buf, NULL, oldurl, 1);
	return 0;
}