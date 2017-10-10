	if (path)
		repo = xstrdup(absolute_path(repo_name));
	else if (!strchr(repo_name, ':'))
		die(_("repository '%s' does not exist"), repo_name);
	else
		repo = repo_name;

	/* no need to be strict, transport_set_option() will validate it again */
	if (option_depth && atoi(option_depth) < 1)
		die(_("depth %s is not a positive number"), option_depth);

	if (argc == 2)
