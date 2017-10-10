
	return 0;
}

static void read_populate_opts(struct replay_opts **opts_ptr)
{
	const char *opts_file = git_path(SEQ_OPTS_FILE);

	if (!file_exists(opts_file))
		return;
	if (git_config_from_file(populate_opts_cb, opts_file, *opts_ptr) < 0)
		die(_("Malformed options sheet: %s"), opts_file);
}

static void walk_revs_populate_todo(struct commit_list **todo_list,
				struct replay_opts *opts)
{
	struct commit *commit;
