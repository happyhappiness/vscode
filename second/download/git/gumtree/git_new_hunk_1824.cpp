			(*argc)--;
		} else if (skip_prefix(cmd, "--work-tree=", &cmd)) {
			setenv(GIT_WORK_TREE_ENVIRONMENT, cmd, 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "--bare")) {
			char *cwd = xgetcwd();
			is_bare_repository_cfg = 1;
			setenv(GIT_DIR_ENVIRONMENT, cwd, 0);
			free(cwd);
			setenv(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, "0", 1);
			if (envchanged)
				*envchanged = 1;
		} else if (!strcmp(cmd, "-c")) {
			if (*argc < 2) {
				fprintf(stderr, "-c expects a configuration string\n" );
