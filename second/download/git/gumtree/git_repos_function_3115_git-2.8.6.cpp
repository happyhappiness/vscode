static int get_next_submodule(struct child_process *cp,
			      struct strbuf *err, void *data, void **task_cb)
{
	int ret = 0;
	struct submodule_parallel_fetch *spf = data;

	for (; spf->count < active_nr; spf->count++) {
		struct strbuf submodule_path = STRBUF_INIT;
		struct strbuf submodule_git_dir = STRBUF_INIT;
		struct strbuf submodule_prefix = STRBUF_INIT;
		const struct cache_entry *ce = active_cache[spf->count];
		const char *git_dir, *default_argv;
		const struct submodule *submodule;

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		submodule = submodule_from_path(null_sha1, ce->name);
		if (!submodule)
			submodule = submodule_from_name(null_sha1, ce->name);

		default_argv = "yes";
		if (spf->command_line_option == RECURSE_SUBMODULES_DEFAULT) {
			if (submodule &&
			    submodule->fetch_recurse !=
						RECURSE_SUBMODULES_NONE) {
				if (submodule->fetch_recurse ==
						RECURSE_SUBMODULES_OFF)
					continue;
				if (submodule->fetch_recurse ==
						RECURSE_SUBMODULES_ON_DEMAND) {
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
		} else if (spf->command_line_option == RECURSE_SUBMODULES_ON_DEMAND) {
			if (!unsorted_string_list_lookup(&changed_submodule_paths, ce->name))
				continue;
			default_argv = "on-demand";
		}

		strbuf_addf(&submodule_path, "%s/%s", spf->work_tree, ce->name);
		strbuf_addf(&submodule_git_dir, "%s/.git", submodule_path.buf);
		strbuf_addf(&submodule_prefix, "%s%s/", spf->prefix, ce->name);
		git_dir = read_gitfile(submodule_git_dir.buf);
		if (!git_dir)
			git_dir = submodule_git_dir.buf;
		if (is_directory(git_dir)) {
			child_process_init(cp);
			cp->dir = strbuf_detach(&submodule_path, NULL);
			cp->env = local_repo_env;
			cp->git_cmd = 1;
			if (!spf->quiet)
				strbuf_addf(err, "Fetching submodule %s%s\n",
					    spf->prefix, ce->name);
			argv_array_init(&cp->args);
			argv_array_pushv(&cp->args, spf->args.argv);
			argv_array_push(&cp->args, default_argv);
			argv_array_push(&cp->args, "--submodule-prefix");
			argv_array_push(&cp->args, submodule_prefix.buf);
			ret = 1;
		}
		strbuf_release(&submodule_path);
		strbuf_release(&submodule_git_dir);
		strbuf_release(&submodule_prefix);
		if (ret) {
			spf->count++;
			return 1;
		}
	}
	return 0;
}