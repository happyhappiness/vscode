			       const char *prefix, int command_line_option,
			       int quiet)
{
	int i, result = 0;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct argv_array argv = ARGV_ARRAY_INIT;
	struct string_list_item *name_for_path;
	const char *work_tree = get_git_work_tree();
	if (!work_tree)
		goto out;

	if (read_cache() < 0)
		die("index file corrupt");
