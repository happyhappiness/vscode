						printf("../");
					}
				}
				putchar('\n');
				continue;
			}
			if (!strcmp(arg, "--git-dir")) {
				const char *gitdir = getenv(GIT_DIR_ENVIRONMENT);
				char *cwd;
				int len;
				if (gitdir) {
					puts(gitdir);
					continue;
				}
				if (!prefix) {
					puts(".git");
					continue;
				}
				cwd = xgetcwd();
				len = strlen(cwd);
				printf("%s%s.git\n", cwd, len && cwd[len-1] != '/' ? "/" : "");
				free(cwd);
				continue;
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
