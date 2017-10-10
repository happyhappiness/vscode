	if (skip_prefix(git_dir, work_tree, &git_dir) &&
	    !strcmp(git_dir, "/.git"))
		return 0;
	return 1;
}

static int create_default_files(const char *template_path,
				const char *original_git_dir)
{
	struct stat st1;
	struct strbuf buf = STRBUF_INIT;
	char *path;
	char repo_version_string[10];
	char junk[2];
	int reinit;
	int filemode;
	struct strbuf err = STRBUF_INIT;

	/* Just look for `init.templatedir` */
	git_config(git_init_db_config, NULL);

	/*
	 * First copy the templates -- we might have the default
	 * config file there, in which case we would want to read
	 * from it after installing.
	 *
	 * Before reading that config, we also need to clear out any cached
	 * values (since we've just potentially changed what's available on
	 * disk).
	 */
	copy_templates(template_path);
	git_config_clear();
	reset_shared_repository();
	git_config(git_default_config, NULL);

	/*
	 * We must make sure command-line options continue to override any
	 * values we might have just re-read from the config.
	 */
	is_bare_repository_cfg = init_is_bare_repository;
	if (init_shared_repository != -1)
		set_shared_repository(init_shared_repository);

	/*
	 * We would have created the above under user's umask -- under
	 * shared-repository settings, we would need to fix them up.
	 */
	if (get_shared_repository()) {
		adjust_shared_perm(get_git_dir());
	}

	/*
	 * We need to create a "refs" dir in any case so that older
	 * versions of git can tell that this is a repository.
	 */
	safe_create_dir(git_path("refs"), 1);
	adjust_shared_perm(git_path("refs"));

	if (refs_init_db(&err))
		die("failed to set up refs db: %s", err.buf);

	/*
	 * Create the default symlink from ".git/HEAD" to the "master"
	 * branch, if it does not exist yet.
	 */
	path = git_path_buf(&buf, "HEAD");
	reinit = (!access(path, R_OK)
		  || readlink(path, junk, sizeof(junk)-1) != -1);
