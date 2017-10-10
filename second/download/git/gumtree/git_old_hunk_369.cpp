	strbuf_addstr(&path, "/info");
	safe_create_dir(path.buf, 1);

	strbuf_release(&path);
}

int set_git_dir_init(const char *git_dir, const char *real_git_dir,
		     int exist_ok)
{
	if (real_git_dir) {
		struct stat st;

		if (!exist_ok && !stat(git_dir, &st))
			die(_("%s already exists"), git_dir);

		if (!exist_ok && !stat(real_git_dir, &st))
			die(_("%s already exists"), real_git_dir);

		/*
		 * make sure symlinks are resolved because we'll be
		 * moving the target repo later on in separate_git_dir()
		 */
		git_link = xstrdup(real_path(git_dir));
		set_git_dir(real_path(real_git_dir));
	}
	else {
		set_git_dir(real_path(git_dir));
		git_link = NULL;
	}
	startup_info->have_repository = 1;
	return 0;
}

static void separate_git_dir(const char *git_dir)
{
	struct stat st;

	if (!stat(git_link, &st)) {
		const char *src;

