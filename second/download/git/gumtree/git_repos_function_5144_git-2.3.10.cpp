static void run_pager(struct grep_opt *opt, const char *prefix)
{
	struct string_list *path_list = opt->output_priv;
	const char **argv = xmalloc(sizeof(const char *) * (path_list->nr + 1));
	int i, status;

	for (i = 0; i < path_list->nr; i++)
		argv[i] = path_list->items[i].string;
	argv[path_list->nr] = NULL;

	status = run_command_v_opt_cd_env(argv, RUN_USING_SHELL, prefix, NULL);
	if (status)
		exit(status);
	free(argv);
}