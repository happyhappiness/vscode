static int is_git_repository(struct strbuf *path)
{
	int ret = 0;
	int gitfile_error;
	size_t orig_path_len = path->len;
	assert(orig_path_len != 0);
	if (path->buf[orig_path_len - 1] != '/')
		strbuf_addch(path, '/');
	strbuf_addstr(path, ".git");
	if (read_gitfile_gently(path->buf, &gitfile_error) || is_git_directory(path->buf))
		ret = 1;
	if (gitfile_error == READ_GITFILE_ERR_OPEN_FAILED ||
	    gitfile_error == READ_GITFILE_ERR_READ_FAILED)
		ret = 1;  /* This could be a real .git file, take the
			   * safe option and avoid cleaning */
	strbuf_setlen(path, orig_path_len);
	return ret;
}