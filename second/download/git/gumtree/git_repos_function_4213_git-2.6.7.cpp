static int run_fetch(const char *repo, const char **refspecs)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	int ret;

	argv_array_pushl(&args, "fetch", "--update-head-ok", NULL);

	/* Shared options */
	argv_push_verbosity(&args);
	if (opt_progress)
		argv_array_push(&args, opt_progress);

	/* Options passed to git-fetch */
	if (opt_all)
		argv_array_push(&args, opt_all);
	if (opt_append)
		argv_array_push(&args, opt_append);
	if (opt_upload_pack)
		argv_array_push(&args, opt_upload_pack);
	argv_push_force(&args);
	if (opt_tags)
		argv_array_push(&args, opt_tags);
	if (opt_prune)
		argv_array_push(&args, opt_prune);
	if (opt_recurse_submodules)
		argv_array_push(&args, opt_recurse_submodules);
	if (opt_dry_run)
		argv_array_push(&args, "--dry-run");
	if (opt_keep)
		argv_array_push(&args, opt_keep);
	if (opt_depth)
		argv_array_push(&args, opt_depth);
	if (opt_unshallow)
		argv_array_push(&args, opt_unshallow);
	if (opt_update_shallow)
		argv_array_push(&args, opt_update_shallow);
	if (opt_refmap)
		argv_array_push(&args, opt_refmap);

	if (repo) {
		argv_array_push(&args, repo);
		argv_array_pushv(&args, refspecs);
	} else if (*refspecs)
		die("BUG: refspecs without repo?");
	ret = run_command_v_opt(args.argv, RUN_GIT_CMD);
	argv_array_clear(&args);
	return ret;
}