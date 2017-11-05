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
			data.len--;
		data.buf[data.len] = '\0';
		strbuf_reset(&path);
		if (!is_absolute_path(data.buf))
			strbuf_addf(&path, "%s/", gitdir);
		strbuf_addbuf(&path, &data);
		strbuf_addstr(sb, real_path(path.buf));
		ret = 1;
	} else
		strbuf_addstr(sb, gitdir);
	strbuf_release(&data);
	strbuf_release(&path);
	return ret;
}