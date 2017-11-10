static void save_opts(struct replay_opts *opts)
{
	const char *opts_file = git_path_opts_file();

	if (opts->no_commit)
		git_config_set_in_file(opts_file, "options.no-commit", "true");
	if (opts->edit)
		git_config_set_in_file(opts_file, "options.edit", "true");
	if (opts->signoff)
		git_config_set_in_file(opts_file, "options.signoff", "true");
	if (opts->record_origin)
		git_config_set_in_file(opts_file, "options.record-origin", "true");
	if (opts->allow_ff)
		git_config_set_in_file(opts_file, "options.allow-ff", "true");
	if (opts->mainline) {
		struct strbuf buf = STRBUF_INIT;
		strbuf_addf(&buf, "%d", opts->mainline);
		git_config_set_in_file(opts_file, "options.mainline", buf.buf);
		strbuf_release(&buf);
	}
	if (opts->strategy)
		git_config_set_in_file(opts_file, "options.strategy", opts->strategy);
	if (opts->gpg_sign)
		git_config_set_in_file(opts_file, "options.gpg-sign", opts->gpg_sign);
	if (opts->xopts) {
		int i;
		for (i = 0; i < opts->xopts_nr; i++)
			git_config_set_multivar_in_file(opts_file,
							"options.strategy-option",
							opts->xopts[i], "^$", 0);
	}
}