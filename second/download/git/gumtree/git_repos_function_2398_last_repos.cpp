int discover_git_directory(struct strbuf *commondir,
			   struct strbuf *gitdir)
{
	struct strbuf dir = STRBUF_INIT, err = STRBUF_INIT;
	size_t gitdir_offset = gitdir->len, cwd_len;
	size_t commondir_offset = commondir->len;
	struct repository_format candidate;

	if (strbuf_getcwd(&dir))
		return -1;

	cwd_len = dir.len;
	if (setup_git_directory_gently_1(&dir, gitdir, 0) <= 0) {
		strbuf_release(&dir);
		return -1;
	}

	/*
	 * The returned gitdir is relative to dir, and if dir does not reflect
	 * the current working directory, we simply make the gitdir absolute.
	 */
	if (dir.len < cwd_len && !is_absolute_path(gitdir->buf + gitdir_offset)) {
		/* Avoid a trailing "/." */
		if (!strcmp(".", gitdir->buf + gitdir_offset))
			strbuf_setlen(gitdir, gitdir_offset);
		else
			strbuf_addch(&dir, '/');
		strbuf_insert(gitdir, gitdir_offset, dir.buf, dir.len);
	}

	get_common_dir(commondir, gitdir->buf + gitdir_offset);

	strbuf_reset(&dir);
	strbuf_addf(&dir, "%s/config", commondir->buf + commondir_offset);
	read_repository_format(&candidate, dir.buf);
	strbuf_release(&dir);

	if (verify_repository_format(&candidate, &err) < 0) {
		warning("ignoring git dir '%s': %s",
			gitdir->buf + gitdir_offset, err.buf);
		strbuf_release(&err);
		strbuf_setlen(commondir, commondir_offset);
		strbuf_setlen(gitdir, gitdir_offset);
		return -1;
	}

	return 0;
}