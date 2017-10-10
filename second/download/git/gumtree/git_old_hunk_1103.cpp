
	new_git_dir = git_path("modules/%s", sub->name);
	if (safe_create_leading_directories_const(new_git_dir) < 0)
		die(_("could not create directory '%s'"), new_git_dir);
	real_new_git_dir = real_pathdup(new_git_dir, 1);

	if (!prefix)
		prefix = get_super_prefix();

	fprintf(stderr, _("Migrating git directory of '%s%s' from\n'%s' to\n'%s'\n"),
		prefix ? prefix : "", path,
		real_old_git_dir, real_new_git_dir);

	relocate_gitdir(path, real_old_git_dir, real_new_git_dir);

	free(old_git_dir);
	free(real_old_git_dir);
