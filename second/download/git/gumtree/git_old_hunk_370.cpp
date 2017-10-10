			die_errno(_("unable to move %s to %s"), src, git_dir);
	}

	write_file(git_link, "gitdir: %s", git_dir);
}

int init_db(const char *template_dir, unsigned int flags)
{
	int reinit;
	const char *git_dir = get_git_dir();

	if (git_link)
		separate_git_dir(git_dir);

	safe_create_dir(git_dir, 0);

	init_is_bare_repository = is_bare_repository();

	/* Check to see if the repository version is right.
	 * Note that a newly created repository does not have
	 * config file, so this will not fail.  What we are catching
	 * is an attempt to reinitialize new repository with an old tool.
	 */
	check_repository_format();

	reinit = create_default_files(template_dir);

	create_object_directory();

	if (get_shared_repository()) {
		char buf[10];
		/* We do not spell "group" and such, so that
