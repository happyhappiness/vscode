			die_errno(_("cannot chdir to %s"), argv[0]);
		}
	} else if (0 < argc) {
		usage(init_db_usage[0]);
	}
	if (is_bare_repository_cfg == 1) {
		char *cwd = xgetcwd();
		setenv(GIT_DIR_ENVIRONMENT, cwd, argc > 0);
		free(cwd);
	}

	if (init_shared_repository != -1)
		shared_repository = init_shared_repository;

	/*
