void read_early_config(config_fn_t cb, void *data)
{
	struct config_options opts = {0};
	struct strbuf commondir = STRBUF_INIT;
	struct strbuf gitdir = STRBUF_INIT;

	opts.respect_includes = 1;

	if (have_git_dir()) {
		opts.commondir = get_git_common_dir();
		opts.git_dir = get_git_dir();
	/*
	 * When setup_git_directory() was not yet asked to discover the
	 * GIT_DIR, we ask discover_git_directory() to figure out whether there
	 * is any repository config we should use (but unlike
	 * setup_git_directory_gently(), no global state is changed, most
	 * notably, the current working directory is still the same after the
	 * call).
	 */
	} else if (!discover_git_directory(&commondir, &gitdir)) {
		opts.commondir = commondir.buf;
		opts.git_dir = gitdir.buf;
	}

	config_with_options(cb, data, NULL, &opts);

	strbuf_release(&commondir);
	strbuf_release(&gitdir);
}