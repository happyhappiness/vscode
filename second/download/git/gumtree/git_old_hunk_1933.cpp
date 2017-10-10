	int r = chdir(path);
	free(path);
	return r;
}

struct unix_sockaddr_context {
	char orig_dir[PATH_MAX];
};

static void unix_sockaddr_cleanup(struct unix_sockaddr_context *ctx)
{
	if (!ctx->orig_dir[0])
		return;
	/*
	 * If we fail, we can't just return an error, since we have
	 * moved the cwd of the whole process, which could confuse calling
	 * code.  We are better off to just die.
	 */
	if (chdir(ctx->orig_dir) < 0)
		die("unable to restore original working directory");
}

static int unix_sockaddr_init(struct sockaddr_un *sa, const char *path,
			      struct unix_sockaddr_context *ctx)
{
	int size = strlen(path) + 1;

	ctx->orig_dir[0] = '\0';
	if (size > sizeof(sa->sun_path)) {
		const char *slash = find_last_dir_sep(path);
		const char *dir;

		if (!slash) {
			errno = ENAMETOOLONG;
			return -1;
		}

