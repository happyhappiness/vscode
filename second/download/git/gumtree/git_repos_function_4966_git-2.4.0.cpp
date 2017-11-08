static char *get_repo_path(const char *repo, int *is_bundle)
{
	static char *suffix[] = { "/.git", "", ".git/.git", ".git" };
	static char *bundle_suffix[] = { ".bundle", "" };
	struct stat st;
	int i;

	for (i = 0; i < ARRAY_SIZE(suffix); i++) {
		const char *path;
		path = mkpath("%s%s", repo, suffix[i]);
		if (stat(path, &st))
			continue;
		if (S_ISDIR(st.st_mode) && is_git_directory(path)) {
			*is_bundle = 0;
			return xstrdup(absolute_path(path));
		} else if (S_ISREG(st.st_mode) && st.st_size > 8) {
			/* Is it a "gitfile"? */
			char signature[8];
			int len, fd = open(path, O_RDONLY);
			if (fd < 0)
				continue;
			len = read_in_full(fd, signature, 8);
			close(fd);
			if (len != 8 || strncmp(signature, "gitdir: ", 8))
				continue;
			path = read_gitfile(path);
			if (path) {
				*is_bundle = 0;
				return xstrdup(absolute_path(path));
			}
		}
	}

	for (i = 0; i < ARRAY_SIZE(bundle_suffix); i++) {
		const char *path;
		path = mkpath("%s%s", repo, bundle_suffix[i]);
		if (!stat(path, &st) && S_ISREG(st.st_mode)) {
			*is_bundle = 1;
			return xstrdup(absolute_path(path));
		}
	}

	return NULL;
}