static int exclude_per_directory_cb(const struct option *opt, const char *arg,
				    int unset)
{
	struct dir_struct *dir;
	struct unpack_trees_options *opts;

	opts = (struct unpack_trees_options *)opt->value;

	if (opts->dir)
		die("more than one --exclude-per-directory given.");

	dir = xcalloc(1, sizeof(*opts->dir));
	dir->flags |= DIR_SHOW_IGNORED;
	dir->exclude_per_dir = arg;
	opts->dir = dir;
	/* We do not need to nor want to do read-directory
	 * here; we are merely interested in reusing the
	 * per directory ignore stack mechanism.
	 */
	return 0;
}