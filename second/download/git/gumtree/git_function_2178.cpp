int fetch_populated_submodules(const struct argv_array *options,
			       const char *prefix, int command_line_option,
			       int quiet, int max_parallel_jobs)
{
	int i;
	struct submodule_parallel_fetch spf = SPF_INIT;

	spf.work_tree = get_git_work_tree();
	spf.command_line_option = command_line_option;
	spf.quiet = quiet;
	spf.prefix = prefix;

	if (!spf.work_tree)
		goto out;

	if (read_cache() < 0)
		die("index file corrupt");

	argv_array_push(&spf.args, "fetch");
	for (i = 0; i < options->argc; i++)
		argv_array_push(&spf.args, options->argv[i]);
	argv_array_push(&spf.args, "--recurse-submodules-default");
	/* default value, "--submodule-prefix" and its value are added later */

	calculate_changed_submodule_paths();
	run_processes_parallel(max_parallel_jobs,
			       get_next_submodule,
			       fetch_start_failure,
			       fetch_finish,
			       &spf);

	argv_array_clear(&spf.args);
out:
	string_list_clear(&changed_submodule_paths, 1);
	return spf.result;
}