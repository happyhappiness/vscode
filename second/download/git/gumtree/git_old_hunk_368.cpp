	if (skip_prefix(git_dir, work_tree, &git_dir) &&
	    !strcmp(git_dir, "/.git"))
		return 0;
	return 1;
}

static int create_default_files(const char *template_path)
{
	struct stat st1;
	struct strbuf buf = STRBUF_INIT;
	char *path;
	char repo_version_string[10];
	char junk[2];
	int reinit;
	int filemode;

	/*
	 * Create .git/refs/{heads,tags}
	 */
	safe_create_dir(git_path_buf(&buf, "refs"), 1);
	safe_create_dir(git_path_buf(&buf, "refs/heads"), 1);
	safe_create_dir(git_path_buf(&buf, "refs/tags"), 1);

	/* Just look for `init.templatedir` */
	git_config(git_init_db_config, NULL);

	/* First copy the templates -- we might have the default
	 * config file there, in which case we would want to read
	 * from it after installing.
	 */
	copy_templates(template_path);

	git_config(git_default_config, NULL);
	is_bare_repository_cfg = init_is_bare_repository;

	/* reading existing config may have overwrote it */
	if (init_shared_repository != -1)
		set_shared_repository(init_shared_repository);

	/*
	 * We would have created the above under user's umask -- under
	 * shared-repository settings, we would need to fix them up.
	 */
	if (get_shared_repository()) {
		adjust_shared_perm(get_git_dir());
		adjust_shared_perm(git_path_buf(&buf, "refs"));
		adjust_shared_perm(git_path_buf(&buf, "refs/heads"));
		adjust_shared_perm(git_path_buf(&buf, "refs/tags"));
	}

	/*
	 * Create the default symlink from ".git/HEAD" to the "master"
	 * branch, if it does not exist yet.
	 */
	path = git_path_buf(&buf, "HEAD");
	reinit = (!access(path, R_OK)
		  || readlink(path, junk, sizeof(junk)-1) != -1);
