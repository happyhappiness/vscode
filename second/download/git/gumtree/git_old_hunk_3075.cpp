				len = strlen(cwd);
				printf("%s%s.git\n", cwd, len && cwd[len-1] != '/' ? "/" : "");
				free(cwd);
				continue;
			}
			if (!strcmp(arg, "--git-common-dir")) {
				puts(get_git_common_dir());
				continue;
			}
			if (!strcmp(arg, "--resolve-git-dir")) {
				const char *gitdir = argv[++i];
				if (!gitdir)
					die("--resolve-git-dir requires an argument");
