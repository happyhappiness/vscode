	args->worktree_attributes = worktree_attributes;

	return argc;
}

int write_archive(int argc, const char **argv, const char *prefix,
		  int setup_prefix, const char *name_hint, int remote)
{
	int nongit = 0;
	const struct archiver *ar = NULL;
	struct archiver_args args;

	if (setup_prefix && prefix == NULL)
		prefix = setup_git_directory_gently(&nongit);

	git_config_get_bool("uploadarchive.allowunreachable", &remote_allow_unreachable);
	git_config(git_default_config, NULL);

	init_tar_archiver();
	init_zip_archiver();

	argc = parse_archive_args(argc, argv, &ar, &args, name_hint, remote);
	if (nongit) {
		/*
		 * We know this will die() with an error, so we could just
		 * die ourselves; but its error message will be more specific
		 * than what we could write here.
		 */
		setup_git_directory();
