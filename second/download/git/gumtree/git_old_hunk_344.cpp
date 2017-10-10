			die_errno(_("could not create work tree dir '%s'"),
				  work_tree);
		junk_work_tree = work_tree;
		set_git_work_tree(work_tree);
	}

	junk_git_dir = git_dir;
	if (safe_create_leading_directories_const(git_dir) < 0)
		die(_("could not create leading directories of '%s'"), git_dir);

	set_git_dir_init(git_dir, real_git_dir, 0);
	if (real_git_dir) {
		git_dir = real_git_dir;
		junk_git_dir = real_git_dir;
	}

	if (0 <= option_verbosity) {
		if (option_bare)
			fprintf(stderr, _("Cloning into bare repository '%s'...\n"), dir);
		else
			fprintf(stderr, _("Cloning into '%s'...\n"), dir);
	}
	init_db(option_template, INIT_DB_QUIET);
	write_config(&option_config);

	git_config(git_default_config, NULL);

	if (option_bare) {
		if (option_mirror)
