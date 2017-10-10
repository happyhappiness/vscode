		free(item->string);
		item->string = real_path;
		return 1;
	}
}

/*
 * We cannot decide in this function whether we are in the work tree or
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
		die_errno(_("Unable to read current working directory"));
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
	 * - ./ (bare)
	 * - ../.git
	 * - ../.git/
	 * - ../ (bare)
	 * - ../../.git/
	 *   etc.
	 */
	one_filesystem = !git_env_bool("GIT_DISCOVERY_ACROSS_FILESYSTEM", 0);
	if (one_filesystem)
		current_device = get_device_or_die(".", NULL, 0);
	for (;;) {
		gitfile = (char*)read_gitfile(DEFAULT_GIT_DIR_ENVIRONMENT);
		if (gitfile)
			gitdirenv = gitfile = xstrdup(gitfile);
		else {
			if (is_git_directory(DEFAULT_GIT_DIR_ENVIRONMENT))
				gitdirenv = DEFAULT_GIT_DIR_ENVIRONMENT;
		}

		if (gitdirenv) {
			ret = setup_discovered_git_dir(gitdirenv,
						       &cwd, offset,
						       nongit_ok);
			free(gitfile);
			return ret;
		}
		free(gitfile);

		if (is_git_directory("."))
			return setup_bare_git_dir(&cwd, offset, nongit_ok);

		offset_parent = offset;
		while (--offset_parent > ceil_offset && cwd.buf[offset_parent] != '/');
		if (offset_parent <= ceil_offset)
			return setup_nongit(cwd.buf, nongit_ok);
		if (one_filesystem) {
			dev_t parent_device = get_device_or_die("..", cwd.buf,
								offset);
			if (parent_device != current_device) {
				if (nongit_ok) {
					if (chdir(cwd.buf))
						die_errno(_("Cannot come back to cwd"));
					*nongit_ok = 1;
					return NULL;
				}
				strbuf_setlen(&cwd, offset);
				die(_("Not a git repository (or any parent up to mount point %s)\n"
				"Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set)."),
				    cwd.buf);
			}
		}
		if (chdir("..")) {
			strbuf_setlen(&cwd, offset);
			die_errno(_("Cannot change to '%s/..'"), cwd.buf);
		}
		offset = offset_parent;
	}
}

const char *setup_git_directory_gently(int *nongit_ok)
{
	const char *prefix;

	prefix = setup_git_directory_gently_1(nongit_ok);
	if (prefix)
		setenv(GIT_PREFIX_ENVIRONMENT, prefix, 1);
	else
		setenv(GIT_PREFIX_ENVIRONMENT, "", 1);

	startup_info->have_repository = !nongit_ok || !*nongit_ok;
	startup_info->prefix = prefix;

	return prefix;
}

int git_config_perm(const char *var, const char *value)
{
	int i;
