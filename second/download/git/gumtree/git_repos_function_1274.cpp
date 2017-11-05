const char *enter_repo(const char *path, int strict)
{
	static char used_path[PATH_MAX];
	static char validated_path[PATH_MAX];

	if (!path)
		return NULL;

	if (!strict) {
		static const char *suffix[] = {
			"/.git", "", ".git/.git", ".git", NULL,
		};
		const char *gitfile;
		int len = strlen(path);
		int i;
		while ((1 < len) && (path[len-1] == '/'))
			len--;

		if (PATH_MAX <= len)
			return NULL;
		strncpy(used_path, path, len); used_path[len] = 0 ;
		strcpy(validated_path, used_path);

		if (used_path[0] == '~') {
			char *newpath = expand_user_path(used_path);
			if (!newpath || (PATH_MAX - 10 < strlen(newpath))) {
				free(newpath);
				return NULL;
			}
			/*
			 * Copy back into the static buffer. A pity
			 * since newpath was not bounded, but other
			 * branches of the if are limited by PATH_MAX
			 * anyway.
			 */
			strcpy(used_path, newpath); free(newpath);
		}
		else if (PATH_MAX - 10 < len)
			return NULL;
		len = strlen(used_path);
		for (i = 0; suffix[i]; i++) {
			struct stat st;
			strcpy(used_path + len, suffix[i]);
			if (!stat(used_path, &st) &&
			    (S_ISREG(st.st_mode) ||
			    (S_ISDIR(st.st_mode) && is_git_directory(used_path)))) {
				strcat(validated_path, suffix[i]);
				break;
			}
		}
		if (!suffix[i])
			return NULL;
		gitfile = read_gitfile(used_path);
		if (gitfile)
			strcpy(used_path, gitfile);
		if (chdir(used_path))
			return NULL;
		path = validated_path;
	}
	else {
		const char *gitfile = read_gitfile(path);
		if (gitfile)
			path = gitfile;
		if (chdir(path))
			return NULL;
	}

	if (is_git_directory(".")) {
		set_git_dir(".");
		check_repository_format();
		return path;
	}

	return NULL;
}