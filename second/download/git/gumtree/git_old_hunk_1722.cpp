			die_errno(_("cannot chdir to %s"), argv[0]);
		}
	} else if (0 < argc) {
		usage(init_db_usage[0]);
	}
	if (is_bare_repository_cfg == 1) {
		static char git_dir[PATH_MAX+1];

		setenv(GIT_DIR_ENVIRONMENT,
			getcwd(git_dir, sizeof(git_dir)), argc > 0);
	}

	if (init_shared_repository != -1)
		shared_repository = init_shared_repository;

	/*
