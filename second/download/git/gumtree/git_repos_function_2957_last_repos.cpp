int sequencer_remove_state(struct replay_opts *opts)
{
	struct strbuf dir = STRBUF_INIT;
	int i;

	free(opts->gpg_sign);
	free(opts->strategy);
	for (i = 0; i < opts->xopts_nr; i++)
		free(opts->xopts[i]);
	free(opts->xopts);

	strbuf_addf(&dir, "%s", get_dir(opts));
	remove_dir_recursively(&dir, 0);
	strbuf_release(&dir);

	return 0;
}