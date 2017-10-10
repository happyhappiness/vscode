};

static const char *argv_submodule[] = {
	"submodule", "update", "--init", "--recursive", NULL
};

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

static char *guess_dir_name(const char *repo, int is_bundle, int is_bare)
{
	const char *end = repo + strlen(repo), *start;
	size_t len;
	char *dir;

	/*
	 * Strip trailing spaces, slashes and /.git
	 */
	while (repo < end && (is_dir_sep(end[-1]) || isspace(end[-1])))
		end--;
	if (end - repo > 5 && is_dir_sep(end[-5]) &&
	    !strncmp(end - 4, ".git", 4)) {
		end -= 5;
		while (repo < end && is_dir_sep(end[-1]))
			end--;
	}

	/*
	 * Find last component, but be prepared that repo could have
	 * the form  "remote.example.com:foo.git", i.e. no slash
	 * in the directory part.
	 */
	start = end;
	while (repo < start && !is_dir_sep(start[-1]) && start[-1] != ':')
		start--;

	/*
	 * Strip .{bundle,git}.
	 */
	len = end - start;
	strip_suffix_mem(start, &len, is_bundle ? ".bundle" : ".git");

	if (is_bare)
		dir = xstrfmt("%.*s.git", (int)len, start);
	else
		dir = xstrndup(start, len);
	/*
	 * Replace sequences of 'control' characters and whitespace
