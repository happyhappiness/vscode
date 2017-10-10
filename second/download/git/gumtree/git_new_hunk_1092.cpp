		free(item->string);
		item->string = real_path;
		return 1;
	}
}

enum discovery_result {
	GIT_DIR_NONE = 0,
	GIT_DIR_EXPLICIT,
	GIT_DIR_DISCOVERED,
	GIT_DIR_BARE,
	/* these are errors */
	GIT_DIR_HIT_CEILING = -1,
	GIT_DIR_HIT_MOUNT_POINT = -2,
	GIT_DIR_INVALID_GITFILE = -3
};

/*
 * We cannot decide in this function whether we are in the work tree or
 * not, since the config can only be read _after_ this function was called.
 *
 * Also, we avoid changing any global state (such as the current working
 * directory) to allow early callers.
 *
 * The directory where the search should start needs to be passed in via the
 * `dir` parameter; upon return, the `dir` buffer will contain the path of
 * the directory where the search ended, and `gitdir` will contain the path of
 * the discovered .git/ directory, if any. If `gitdir` is not absolute, it
 * is relative to `dir` (i.e. *not* necessarily the cwd).
 */
static enum discovery_result setup_git_directory_gently_1(struct strbuf *dir,
							  struct strbuf *gitdir,
							  int die_on_error)
{
	const char *env_ceiling_dirs = getenv(CEILING_DIRECTORIES_ENVIRONMENT);
	struct string_list ceiling_dirs = STRING_LIST_INIT_DUP;
	const char *gitdirenv;
	int ceil_offset = -1, min_offset = has_dos_drive_prefix(dir->buf) ? 3 : 1;
	dev_t current_device = 0;
	int one_filesystem = 1;

	/*
	 * If GIT_DIR is set explicitly, we're not going
	 * to do any discovery, but we still do repository
	 * validation.
	 */
	gitdirenv = getenv(GIT_DIR_ENVIRONMENT);
	if (gitdirenv) {
		strbuf_addstr(gitdir, gitdirenv);
		return GIT_DIR_EXPLICIT;
	}

	if (env_ceiling_dirs) {
		int empty_entry_found = 0;

		string_list_split(&ceiling_dirs, env_ceiling_dirs, PATH_SEP, -1);
		filter_string_list(&ceiling_dirs, 0,
				   canonicalize_ceiling_entry, &empty_entry_found);
		ceil_offset = longest_ancestor_length(dir->buf, &ceiling_dirs);
		string_list_clear(&ceiling_dirs, 0);
	}

	if (ceil_offset < 0)
		ceil_offset = min_offset - 2;

	/*
	 * Test in the following order (relative to the dir):
	 * - .git (file containing "gitdir: <path>")
	 * - .git/
	 * - ./ (bare)
	 * - ../.git
	 * - ../.git/
	 * - ../ (bare)
	 * - ../../.git/
	 *   etc.
	 */
	one_filesystem = !git_env_bool("GIT_DISCOVERY_ACROSS_FILESYSTEM", 0);
	if (one_filesystem)
		current_device = get_device_or_die(dir->buf, NULL, 0);
	for (;;) {
		int offset = dir->len, error_code = 0;

		if (offset > min_offset)
			strbuf_addch(dir, '/');
		strbuf_addstr(dir, DEFAULT_GIT_DIR_ENVIRONMENT);
		gitdirenv = read_gitfile_gently(dir->buf, die_on_error ?
						NULL : &error_code);
		if (!gitdirenv) {
			if (die_on_error ||
			    error_code == READ_GITFILE_ERR_NOT_A_FILE) {
				/* NEEDSWORK: fail if .git is not file nor dir */
				if (is_git_directory(dir->buf))
					gitdirenv = DEFAULT_GIT_DIR_ENVIRONMENT;
			} else if (error_code != READ_GITFILE_ERR_STAT_FAILED)
				return GIT_DIR_INVALID_GITFILE;
		}
		strbuf_setlen(dir, offset);
		if (gitdirenv) {
			strbuf_addstr(gitdir, gitdirenv);
			return GIT_DIR_DISCOVERED;
		}

		if (is_git_directory(dir->buf)) {
			strbuf_addstr(gitdir, ".");
			return GIT_DIR_BARE;
		}

		if (offset <= min_offset)
			return GIT_DIR_HIT_CEILING;

		while (--offset > ceil_offset && !is_dir_sep(dir->buf[offset]))
			; /* continue */
		if (offset <= ceil_offset)
			return GIT_DIR_HIT_CEILING;

		strbuf_setlen(dir, offset > min_offset ?  offset : min_offset);
		if (one_filesystem &&
		    current_device != get_device_or_die(dir->buf, NULL, offset))
			return GIT_DIR_HIT_MOUNT_POINT;
	}
}

const char *discover_git_directory(struct strbuf *gitdir)
{
	struct strbuf dir = STRBUF_INIT, err = STRBUF_INIT;
	size_t gitdir_offset = gitdir->len, cwd_len;
	struct repository_format candidate;

	if (strbuf_getcwd(&dir))
		return NULL;

	cwd_len = dir.len;
	if (setup_git_directory_gently_1(&dir, gitdir, 0) <= 0) {
		strbuf_release(&dir);
		return NULL;
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

	strbuf_reset(&dir);
	strbuf_addf(&dir, "%s/config", gitdir->buf + gitdir_offset);
	read_repository_format(&candidate, dir.buf);
	strbuf_release(&dir);

	if (verify_repository_format(&candidate, &err) < 0) {
		warning("ignoring git dir '%s': %s",
			gitdir->buf + gitdir_offset, err.buf);
		strbuf_release(&err);
		return NULL;
	}

	return gitdir->buf + gitdir_offset;
}

const char *setup_git_directory_gently(int *nongit_ok)
{
	static struct strbuf cwd = STRBUF_INIT;
	struct strbuf dir = STRBUF_INIT, gitdir = STRBUF_INIT;
	const char *prefix, *env_prefix;

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
		die_errno(_("Unable to read current working directory"));
	strbuf_addbuf(&dir, &cwd);

	switch (setup_git_directory_gently_1(&dir, &gitdir, 1)) {
	case GIT_DIR_NONE:
		prefix = NULL;
		break;
	case GIT_DIR_EXPLICIT:
		prefix = setup_explicit_git_dir(gitdir.buf, &cwd, nongit_ok);
		break;
	case GIT_DIR_DISCOVERED:
		if (dir.len < cwd.len && chdir(dir.buf))
			die(_("Cannot change to '%s'"), dir.buf);
		prefix = setup_discovered_git_dir(gitdir.buf, &cwd, dir.len,
						  nongit_ok);
		break;
	case GIT_DIR_BARE:
		if (dir.len < cwd.len && chdir(dir.buf))
			die(_("Cannot change to '%s'"), dir.buf);
		prefix = setup_bare_git_dir(&cwd, dir.len, nongit_ok);
		break;
	case GIT_DIR_HIT_CEILING:
		prefix = setup_nongit(cwd.buf, nongit_ok);
		break;
	case GIT_DIR_HIT_MOUNT_POINT:
		if (nongit_ok) {
			*nongit_ok = 1;
			strbuf_release(&cwd);
			strbuf_release(&dir);
			return NULL;
		}
		die(_("Not a git repository (or any parent up to mount point %s)\n"
		      "Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set)."),
		    dir.buf);
	default:
		die("BUG: unhandled setup_git_directory_1() result");
	}

	env_prefix = getenv(GIT_TOPLEVEL_PREFIX_ENVIRONMENT);
	if (env_prefix)
		prefix = env_prefix;

	if (prefix)
		setenv(GIT_PREFIX_ENVIRONMENT, prefix, 1);
	else
		setenv(GIT_PREFIX_ENVIRONMENT, "", 1);

	startup_info->have_repository = !nongit_ok || !*nongit_ok;
	startup_info->prefix = prefix;

	strbuf_release(&dir);
	strbuf_release(&gitdir);

	return prefix;
}

int git_config_perm(const char *var, const char *value)
{
	int i;
