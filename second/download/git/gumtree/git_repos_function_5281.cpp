static const char *get_repo_path_1(struct strbuf *path, int *is_bundle)
{
	static char *suffix[] = { "/.git", "", ".git/.git", ".git" };
	static char *bundle_suffix[] = { ".bundle", "" };
	size_t baselen = path->len;
	struct stat st;
	int i;

	for (i = 0; i < ARRAY_SIZE(suffix); i++) {
		strbuf_setlen(path, baselen);
		strbuf_addstr(path, suffix[i]);
		if (stat(path->buf, &st))
			continue;
		if (S_ISDIR(st.st_mode) && is_git_directory(path->buf)) {
			*is_bundle = 0;
			return path->buf;
		} else if (S_ISREG(st.st_mode) && st.st_size > 8) {
			/* Is it a "gitfile"? */
			char signature[8];
			const char *dst;
			int len, fd = open(path->buf, O_RDONLY);
			if (fd < 0)
				continue;
			len = read_in_full(fd, signature, 8);
			close(fd);
			if (len != 8 || strncmp(signature, "gitdir: ", 8))
				continue;
			dst = read_gitfile(path->buf);
			if (dst) {
				*is_bundle = 0;
				return dst;
			}
		}
	}

	for (i = 0; i < ARRAY_SIZE(bundle_suffix); i++) {
		strbuf_setlen(path, baselen);
		strbuf_addstr(path, bundle_suffix[i]);
		if (!stat(path->buf, &st) && S_ISREG(st.st_mode)) {
			*is_bundle = 1;
			return path->buf;
		}
	}

	return NULL;
}