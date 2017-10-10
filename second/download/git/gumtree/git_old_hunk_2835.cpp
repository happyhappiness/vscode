		return 0;
	return 1;
}

static int create_default_files(const char *template_path)
{
	const char *git_dir = get_git_dir();
	unsigned len = strlen(git_dir);
	static char path[PATH_MAX];
	struct stat st1;
	char repo_version_string[10];
	char junk[2];
	int reinit;
	int filemode;

	if (len > sizeof(path)-50)
		die(_("insane git directory %s"), git_dir);
	memcpy(path, git_dir, len);

	if (len && path[len-1] != '/')
		path[len++] = '/';

	/*
	 * Create .git/refs/{heads,tags}
	 */
	safe_create_dir(git_path("refs"), 1);
	safe_create_dir(git_path("refs/heads"), 1);
	safe_create_dir(git_path("refs/tags"), 1);

	/* Just look for `init.templatedir` */
	git_config(git_init_db_config, NULL);

	/* First copy the templates -- we might have the default
	 * config file there, in which case we would want to read
