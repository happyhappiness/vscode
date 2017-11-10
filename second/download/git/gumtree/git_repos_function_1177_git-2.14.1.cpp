static int find_common_dir(struct strbuf *sb, const char *gitdir, int fromenv)
{
	if (fromenv) {
		const char *value = getenv(GIT_COMMON_DIR_ENVIRONMENT);
		if (value) {
			strbuf_addstr(sb, value);
			return 1;
		}
	}

	return get_common_dir_noenv(sb, gitdir);
}