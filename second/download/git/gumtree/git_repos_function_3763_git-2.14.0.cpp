int submodule_to_gitdir(struct strbuf *buf, const char *submodule)
{
	const struct submodule *sub;
	const char *git_dir;
	int ret = 0;

	strbuf_reset(buf);
	strbuf_addstr(buf, submodule);
	strbuf_complete(buf, '/');
	strbuf_addstr(buf, ".git");

	git_dir = read_gitfile(buf->buf);
	if (git_dir) {
		strbuf_reset(buf);
		strbuf_addstr(buf, git_dir);
	}
	if (!is_git_directory(buf->buf)) {
		gitmodules_config();
		sub = submodule_from_path(null_sha1, submodule);
		if (!sub) {
			ret = -1;
			goto cleanup;
		}
		strbuf_reset(buf);
		strbuf_git_path(buf, "%s/%s", "modules", sub->name);
	}

cleanup:
	return ret;
}