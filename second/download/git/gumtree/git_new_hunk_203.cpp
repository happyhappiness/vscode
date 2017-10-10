}

int try_merge_command(const char *strategy, size_t xopts_nr,
		      const char **xopts, struct commit_list *common,
		      const char *head_arg, struct commit_list *remotes)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	int i, ret;
	struct commit_list *j;

	argv_array_pushf(&args, "merge-%s", strategy);
	for (i = 0; i < xopts_nr; i++)
		argv_array_pushf(&args, "--%s", xopts[i]);
	for (j = common; j; j = j->next)
		argv_array_push(&args, merge_argument(j->item));
	argv_array_push(&args, "--");
	argv_array_push(&args, head_arg);
	for (j = remotes; j; j = j->next)
		argv_array_push(&args, merge_argument(j->item));

	ret = run_command_v_opt(args.argv, RUN_GIT_CMD);
	argv_array_clear(&args);

	discard_cache();
	if (read_cache() < 0)
		die(_("failed to read the cache"));
	resolve_undo_clear();

	return ret;
