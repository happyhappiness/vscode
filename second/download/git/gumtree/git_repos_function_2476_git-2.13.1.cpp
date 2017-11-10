static int unix_sockaddr_init(struct sockaddr_un *sa, const char *path,
			      struct unix_sockaddr_context *ctx)
{
	int size = strlen(path) + 1;

	ctx->orig_dir = NULL;
	if (size > sizeof(sa->sun_path)) {
		const char *slash = find_last_dir_sep(path);
		const char *dir;
		struct strbuf cwd = STRBUF_INIT;

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
		if (strbuf_getcwd(&cwd))
			return -1;
		ctx->orig_dir = strbuf_detach(&cwd, NULL);
		if (chdir_len(dir, slash - dir) < 0)
			return -1;
	}

	memset(sa, 0, sizeof(*sa));
	sa->sun_family = AF_UNIX;
	memcpy(sa->sun_path, path, size);
	return 0;
}