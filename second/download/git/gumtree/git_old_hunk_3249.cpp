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

unsigned is_submodule_modified(const char *path, int ignore_untracked)
{
	ssize_t len;
	struct child_process cp = CHILD_PROCESS_INIT;
