			die_errno(_("could not create work tree dir '%s'"),
				  work_tree);
		junk_work_tree = work_tree;
		set_git_work_tree(work_tree);
	}

	junk_git_dir = real_git_dir ? real_git_dir : git_dir;
	if (safe_create_leading_directories_const(git_dir) < 0)
		die(_("could not create leading directories of '%s'"), git_dir);

	if (0 <= option_verbosity) {
		if (option_bare)
			fprintf(stderr, _("Cloning into bare repository '%s'...\n"), dir);
		else
			fprintf(stderr, _("Cloning into '%s'...\n"), dir);
	}

	if (option_recursive) {
		if (option_required_reference.nr &&
		    option_optional_reference.nr)
			die(_("clone --recursive is not compatible with "
			      "both --reference and --reference-if-able"));
		else if (option_required_reference.nr) {
			string_list_append(&option_config,
				"submodule.alternateLocation=superproject");
			string_list_append(&option_config,
				"submodule.alternateErrorStrategy=die");
		} else if (option_optional_reference.nr) {
			string_list_append(&option_config,
				"submodule.alternateLocation=superproject");
			string_list_append(&option_config,
				"submodule.alternateErrorStrategy=info");
		}
	}

	init_db(git_dir, real_git_dir, option_template, INIT_DB_QUIET);

	if (real_git_dir)
		git_dir = real_git_dir;

	write_config(&option_config);

	git_config(git_default_config, NULL);

	if (option_bare) {
		if (option_mirror)
