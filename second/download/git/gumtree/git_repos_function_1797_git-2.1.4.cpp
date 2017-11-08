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

		dir = path;
		path = slash + 1;
		size = strlen(path) + 1;
		if (size > sizeof(sa->sun_path)) {
			errno = ENAMETOOLONG;
			return -1;
		}

		if (!getcwd(ctx->orig_dir, sizeof(ctx->orig_dir))) {
			errno = ENAMETOOLONG;
			return -1;
		}
		if (chdir_len(dir, slash - dir) < 0)
			return -1;
	}

	memset(sa, 0, sizeof(*sa));
	sa->sun_family = AF_UNIX;
	memcpy(sa->sun_path, path, size);
	return 0;
}