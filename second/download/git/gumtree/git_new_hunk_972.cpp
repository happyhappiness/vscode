						printf("../");
					}
				}
				putchar('\n');
				continue;
			}
			if (!strcmp(arg, "--git-dir") ||
			    !strcmp(arg, "--absolute-git-dir")) {
				const char *gitdir = getenv(GIT_DIR_ENVIRONMENT);
				char *cwd;
				int len;
				if (arg[2] == 'g') {	/* --git-dir */
					if (gitdir) {
						puts(gitdir);
						continue;
					}
					if (!prefix) {
						puts(".git");
						continue;
					}
				} else {		/* --absolute-git-dir */
					if (!gitdir && !prefix)
						gitdir = ".git";
					if (gitdir) {
						puts(real_path(gitdir));
						continue;
					}
				}
				cwd = xgetcwd();
				len = strlen(cwd);
				printf("%s%s.git\n", cwd, len && cwd[len-1] != '/' ? "/" : "");
				free(cwd);
				continue;
			}
			if (!strcmp(arg, "--git-common-dir")) {
				strbuf_reset(&buf);
				puts(relative_path(get_git_common_dir(),
						   prefix, &buf));
				continue;
			}
			if (!strcmp(arg, "--is-inside-git-dir")) {
				printf("%s\n", is_inside_git_dir() ? "true"
						: "false");
				continue;
