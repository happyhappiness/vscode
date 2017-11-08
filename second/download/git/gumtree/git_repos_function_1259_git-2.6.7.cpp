static void update_common_dir(struct strbuf *buf, int git_dir_len, const char *common_dir)
{
	char *base = buf->buf + git_dir_len;
	const char **p;

	if (is_dir_file(base, "logs", "HEAD") ||
	    is_dir_file(base, "info", "sparse-checkout"))
		return;	/* keep this in $GIT_DIR */
	for (p = common_list; *p; p++) {
		const char *path = *p;
		int is_dir = 0;
		if (*path == '!')
			path++;
		if (*path == '/') {
			path++;
			is_dir = 1;
		}

		if (!common_dir)
			common_dir = get_git_common_dir();

		if (is_dir && dir_prefix(base, path)) {
			replace_dir(buf, git_dir_len, common_dir);
			return;
		}
		if (!is_dir && !strcmp(base, path)) {
			replace_dir(buf, git_dir_len, common_dir);
			return;
		}
	}
}