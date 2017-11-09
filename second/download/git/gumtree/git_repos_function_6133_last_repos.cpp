static void run_pager(struct grep_opt *opt, const char *prefix)
{
	struct string_list *path_list = opt->output_priv;
	struct child_process child = CHILD_PROCESS_INIT;
	int i, status;

	for (i = 0; i < path_list->nr; i++)
		argv_array_push(&child.args, path_list->items[i].string);
	child.dir = prefix;
	child.use_shell = 1;

	status = run_command(&child);
	if (status)
		exit(status);
}