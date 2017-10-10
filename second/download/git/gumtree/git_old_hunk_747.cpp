	if (!error_flag)
		return error(_("invalid value for %s: %s"), key, value);

	return 0;
}

static int read_populate_opts(struct replay_opts *opts)
{
	if (is_rebase_i(opts)) {
		struct strbuf buf = STRBUF_INIT;

		if (read_oneliner(&buf, rebase_path_gpg_sign_opt(), 1)) {
