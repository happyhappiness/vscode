 * not, since the config can only be read _after_ this function was called.
 */
static const char *setup_git_directory_gently_1(int *nongit_ok)
{
	const char *env_ceiling_dirs = getenv(CEILING_DIRECTORIES_ENVIRONMENT);
	struct string_list ceiling_dirs = STRING_LIST_INIT_DUP;
	static struct strbuf cwd = STRBUF_INIT;
	const char *gitdirenv, *ret;
	char *gitfile;
	int offset, offset_parent, ceil_offset = -1;
	dev_t current_device = 0;
	int one_filesystem = 1;

	/*
	 * We may have read an incomplete configuration before
	 * setting-up the git directory. If so, clear the cache so
	 * that the next queries to the configuration reload complete
	 * configuration (including the per-repo config file that we
	 * ignored previously).
	 */
	git_config_clear();

	/*
	 * Let's assume that we are in a git repository.
	 * If it turns out later that we are somewhere else, the value will be
	 * updated accordingly.
	 */
	if (nongit_ok)
		*nongit_ok = 0;

	if (strbuf_getcwd(&cwd))
		die_errno("Unable to read current working directory");
	offset = cwd.len;

	/*
	 * If GIT_DIR is set explicitly, we're not going
	 * to do any discovery, but we still do repository
	 * validation.
	 */
	gitdirenv = getenv(GIT_DIR_ENVIRONMENT);
	if (gitdirenv)
		return setup_explicit_git_dir(gitdirenv, &cwd, nongit_ok);

	if (env_ceiling_dirs) {
		int empty_entry_found = 0;

		string_list_split(&ceiling_dirs, env_ceiling_dirs, PATH_SEP, -1);
		filter_string_list(&ceiling_dirs, 0,
				   canonicalize_ceiling_entry, &empty_entry_found);
		ceil_offset = longest_ancestor_length(cwd.buf, &ceiling_dirs);
		string_list_clear(&ceiling_dirs, 0);
	}

	if (ceil_offset < 0 && has_dos_drive_prefix(cwd.buf))
		ceil_offset = 1;

	/*
	 * Test in the following order (relative to the cwd):
	 * - .git (file containing "gitdir: <path>")
	 * - .git/
