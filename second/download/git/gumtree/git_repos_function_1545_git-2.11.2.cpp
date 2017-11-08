static int do_submodule_path(struct strbuf *buf, const char *path,
			     const char *fmt, va_list args)
{
	const char *git_dir;
	struct strbuf git_submodule_common_dir = STRBUF_INIT;
	struct strbuf git_submodule_dir = STRBUF_INIT;
	const struct submodule *sub;
	int err = 0;

	strbuf_addstr(buf, path);
	strbuf_complete(buf, '/');
	strbuf_addstr(buf, ".git");

	git_dir = read_gitfile(buf->buf);
	if (git_dir) {
		strbuf_reset(buf);
		strbuf_addstr(buf, git_dir);
	}
	if (!is_git_directory(buf->buf)) {
		gitmodules_config();
		sub = submodule_from_path(null_sha1, path);
		if (!sub) {
			err = SUBMODULE_PATH_ERR_NOT_CONFIGURED;
			goto cleanup;
		}
		strbuf_reset(buf);
		strbuf_git_path(buf, "%s/%s", "modules", sub->name);
	}

	strbuf_addch(buf, '/');
	strbuf_addbuf(&git_submodule_dir, buf);

	strbuf_vaddf(buf, fmt, args);

	if (get_common_dir_noenv(&git_submodule_common_dir, git_submodule_dir.buf))
		update_common_dir(buf, git_submodule_dir.len, git_submodule_common_dir.buf);

	strbuf_cleanup_path(buf);

cleanup:
	strbuf_release(&git_submodule_dir);
	strbuf_release(&git_submodule_common_dir);

	return err;
}