			}
			if (!strcmp(arg, "--git-common-dir")) {
				const char *pfx = prefix ? prefix : "";
				puts(prefix_filename(pfx, strlen(pfx), get_git_common_dir()));
				continue;
			}
			if (!strcmp(arg, "--is-inside-git-dir")) {
				printf("%s\n", is_inside_git_dir() ? "true"
						: "false");
				continue;
			}
			if (!strcmp(arg, "--is-inside-work-tree")) {
