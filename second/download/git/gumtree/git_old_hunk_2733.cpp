	    "Use '--' to separate paths from revisions, like this:\n"
	    "'git <command> [<revision>...] -- [<file>...]'", arg);
}

int get_common_dir(struct strbuf *sb, const char *gitdir)
{
	struct strbuf data = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	const char *git_common_dir = getenv(GIT_COMMON_DIR_ENVIRONMENT);
	int ret = 0;
	if (git_common_dir) {
		strbuf_addstr(sb, git_common_dir);
		return 1;
	}
	strbuf_addf(&path, "%s/commondir", gitdir);
	if (file_exists(path.buf)) {
		if (strbuf_read_file(&data, path.buf, 0) <= 0)
			die_errno(_("failed to read %s"), path.buf);
		while (data.len && (data.buf[data.len - 1] == '\n' ||
				    data.buf[data.len - 1] == '\r'))
