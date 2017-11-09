int get_common_dir(struct strbuf *sb, const char *gitdir)
{
	const char *git_env_common_dir = getenv(GIT_COMMON_DIR_ENVIRONMENT);
	if (git_env_common_dir) {
		strbuf_addstr(sb, git_env_common_dir);
		return 1;
	} else {
		return get_common_dir_noenv(sb, gitdir);
	}
}