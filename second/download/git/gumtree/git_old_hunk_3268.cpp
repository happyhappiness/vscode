				continue;
			}
			if (starts_with(arg, "--exclude=")) {
				add_ref_exclusion(&ref_excludes, arg + 10);
				continue;
			}
			if (!strcmp(arg, "--local-env-vars")) {
				int i;
				for (i = 0; local_repo_env[i]; i++)
					printf("%s\n", local_repo_env[i]);
				continue;
			}
			if (!strcmp(arg, "--show-toplevel")) {
				const char *work_tree = get_git_work_tree();
				if (work_tree)
					puts(work_tree);
				continue;
			}
