int fetch_populated_submodules(const struct argv_array *options,
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

	argv_array_push(&argv, "fetch");
	for (i = 0; i < options->argc; i++)
		argv_array_push(&argv, options->argv[i]);
	argv_array_push(&argv, "--recurse-submodules-default");
	/* default value, "--submodule-prefix" and its value are added later */

	cp.env = local_repo_env;
	cp.git_cmd = 1;
	cp.no_stdin = 1;

	calculate_changed_submodule_paths();

	for (i = 0; i < active_nr; i++) {
		struct strbuf submodule_path = STRBUF_INIT;
		struct strbuf submodule_git_dir = STRBUF_INIT;
		struct strbuf submodule_prefix = STRBUF_INIT;
		const struct cache_entry *ce = active_cache[i];
		const char *git_dir, *name, *default_argv;

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		name = ce->name;
		name_for_path = unsorted_string_list_lookup(&config_name_for_path, ce->name);
		if (name_for_path)
			name = name_for_path->util;

		default_argv = "yes";
		if (command_line_option == RECURSE_SUBMODULES_DEFAULT) {
			struct string_list_item *fetch_recurse_submodules_option;
			fetch_recurse_submodules_option = unsorted_string_list_lookup(&config_fetch_recurse_submodules_for_name, name);
			if (fetch_recurse_submodules_option) {
				if ((intptr_t)fetch_recurse_submodules_option->util == RECURSE_SUBMODULES_OFF)
					continue;
				if ((intptr_t)fetch_recurse_submodules_option->util == RECURSE_SUBMODULES_ON_DEMAND) {
					if (!unsorted_string_list_lookup(&changed_submodule_paths, ce->name))
						continue;
					default_argv = "on-demand";
				}
			} else {
				if ((config_fetch_recurse_submodules == RECURSE_SUBMODULES_OFF) ||
				    gitmodules_is_unmerged)
					continue;
				if (config_fetch_recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND) {
					if (!unsorted_string_list_lookup(&changed_submodule_paths, ce->name))
						continue;
					default_argv = "on-demand";
				}
			}
		} else if (command_line_option == RECURSE_SUBMODULES_ON_DEMAND) {
			if (!unsorted_string_list_lookup(&changed_submodule_paths, ce->name))
				continue;
			default_argv = "on-demand";
		}

		strbuf_addf(&submodule_path, "%s/%s", work_tree, ce->name);
		strbuf_addf(&submodule_git_dir, "%s/.git", submodule_path.buf);
		strbuf_addf(&submodule_prefix, "%s%s/", prefix, ce->name);
		git_dir = read_gitfile(submodule_git_dir.buf);
		if (!git_dir)
			git_dir = submodule_git_dir.buf;
		if (is_directory(git_dir)) {
			if (!quiet)
				printf("Fetching submodule %s%s\n", prefix, ce->name);
			cp.dir = submodule_path.buf;
			argv_array_push(&argv, default_argv);
			argv_array_push(&argv, "--submodule-prefix");
			argv_array_push(&argv, submodule_prefix.buf);
			cp.argv = argv.argv;
			if (run_command(&cp))
				result = 1;
			argv_array_pop(&argv);
			argv_array_pop(&argv);
			argv_array_pop(&argv);
		}
		strbuf_release(&submodule_path);
		strbuf_release(&submodule_git_dir);
		strbuf_release(&submodule_prefix);
	}
	argv_array_clear(&argv);
out:
	string_list_clear(&changed_submodule_paths, 1);
	return result;
}