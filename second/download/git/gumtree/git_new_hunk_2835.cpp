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
