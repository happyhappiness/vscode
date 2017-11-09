static int read_populate_opts(struct replay_opts *opts)
{
	if (is_rebase_i(opts)) {
		struct strbuf buf = STRBUF_INIT;

		if (read_oneliner(&buf, rebase_path_gpg_sign_opt(), 1)) {
			if (!starts_with(buf.buf, "-S"))
				strbuf_reset(&buf);
			else {
				free(opts->gpg_sign);
				opts->gpg_sign = xstrdup(buf.buf + 2);
			}
			strbuf_reset(&buf);
		}

		if (read_oneliner(&buf, rebase_path_allow_rerere_autoupdate(), 1)) {
			if (!strcmp(buf.buf, "--rerere-autoupdate"))
				opts->allow_rerere_auto = RERERE_AUTOUPDATE;
			else if (!strcmp(buf.buf, "--no-rerere-autoupdate"))
				opts->allow_rerere_auto = RERERE_NOAUTOUPDATE;
			strbuf_reset(&buf);
		}

		if (file_exists(rebase_path_verbose()))
			opts->verbose = 1;

		read_strategy_opts(opts, &buf);
		strbuf_release(&buf);

		return 0;
	}

	if (!file_exists(git_path_opts_file()))
		return 0;
	/*
	 * The function git_parse_source(), called from git_config_from_file(),
	 * may die() in case of a syntactically incorrect file. We do not care
	 * about this case, though, because we wrote that file ourselves, so we
	 * are pretty certain that it is syntactically correct.
	 */
	if (git_config_from_file(populate_opts_cb, git_path_opts_file(), opts) < 0)
		return error(_("malformed options sheet: '%s'"),
			git_path_opts_file());
	return 0;
}