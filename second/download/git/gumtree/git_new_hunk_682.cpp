
int init_db(const char *git_dir, const char *real_git_dir,
	    const char *template_dir, unsigned int flags)
{
	int reinit;
	int exist_ok = flags & INIT_DB_EXIST_OK;
	char *original_git_dir = real_pathdup(git_dir);

	if (real_git_dir) {
		struct stat st;

		if (!exist_ok && !stat(git_dir, &st))
			die(_("%s already exists"), git_dir);
