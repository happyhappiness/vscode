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
		 * the configuration can be read by older version
		 * of git. Note, we use octal numbers for new share modes,
		 * and compatibility values for PERM_GROUP and
		 * PERM_EVERYBODY.
		 */
		if (get_shared_repository() < 0)
			/* force to the mode value */
			xsnprintf(buf, sizeof(buf), "0%o", -get_shared_repository());
		else if (get_shared_repository() == PERM_GROUP)
			xsnprintf(buf, sizeof(buf), "%d", OLD_PERM_GROUP);
		else if (get_shared_repository() == PERM_EVERYBODY)
			xsnprintf(buf, sizeof(buf), "%d", OLD_PERM_EVERYBODY);
		else
			die("BUG: invalid value for shared_repository");
		git_config_set("core.sharedrepository", buf);
		git_config_set("receive.denyNonFastforwards", "true");
	}

	if (!(flags & INIT_DB_QUIET)) {
		int len = strlen(git_dir);

		/* TRANSLATORS: The first '%s' is either "Reinitialized
		   existing" or "Initialized empty", the second " shared" or
		   "", and the last '%s%s' is the verbatim directory name. */
		printf(_("%s%s Git repository in %s%s\n"),
		       reinit ? _("Reinitialized existing") : _("Initialized empty"),
		       get_shared_repository() ? _(" shared") : "",
		       git_dir, len && git_dir[len-1] != '/' ? "/" : "");
	}

	return 0;
}