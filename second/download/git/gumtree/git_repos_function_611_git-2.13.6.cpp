void read_early_config(config_fn_t cb, void *data)
{
	struct config_options opts = {0};
	struct strbuf buf = STRBUF_INIT;

	opts.respect_includes = 1;

	if (have_git_dir())
		opts.git_dir = get_git_dir();
	/*
	 * When setup_git_directory() was not yet asked to discover the
	 * GIT_DIR, we ask discover_git_directory() to figure out whether there
	 * is any repository config we should use (but unlike
	 * setup_git_directory_gently(), no global state is changed, most
	 * notably, the current working directory is still the same after the
	 * call).
	 */
	else if (discover_git_directory(&buf))
		opts.git_dir = buf.buf;

	git_config_with_options(cb, data, NULL, &opts);

	strbuf_release(&buf);
}