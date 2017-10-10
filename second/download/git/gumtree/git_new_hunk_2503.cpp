{
	struct string_list *exclude_list = opt->value;
	string_list_append(exclude_list, arg);
	return 0;
}

/*
 * Return 1 if the given path is the root of a git repository or
 * submodule else 0. Will not return 1 for bare repositories with the
 * exception of creating a bare repository in "foo/.git" and calling
 * is_git_repository("foo").
 */
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

static int remove_dirs(struct strbuf *path, const char *prefix, int force_flag,
		int dry_run, int quiet, int *dir_gone)
{
	DIR *dir;
	struct strbuf quoted = STRBUF_INIT;
	struct dirent *e;
	int res = 0, ret = 0, gone = 1, original_len = path->len, len;
	struct string_list dels = STRING_LIST_INIT_DUP;

	*dir_gone = 1;

	if ((force_flag & REMOVE_DIR_KEEP_NESTED_GIT) && is_git_repository(path)) {
		if (!quiet) {
			quote_path_relative(path->buf, prefix, &quoted);
			printf(dry_run ?  _(msg_would_skip_git_dir) : _(msg_skip_git_dir),
					quoted.buf);
		}

