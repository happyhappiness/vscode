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
			if (!strcmp(arg, "--resolve-git-dir")) {
				const char *gitdir = argv[++i];
				if (!gitdir)
					die("--resolve-git-dir requires an argument");
