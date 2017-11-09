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

	/*
	 * NEEDSWORK: This was a hack in order to get ls-files and grep to have
	 * properly formated output when recursing submodules.  Once ls-files
	 * and grep have been changed to perform this recursing in-process this
	 * needs to be removed.
	 */
	env_prefix = getenv(GIT_TOPLEVEL_PREFIX_ENVIRONMENT);
	if (env_prefix)
		prefix = env_prefix;

	if (prefix)
		setenv(GIT_PREFIX_ENVIRONMENT, prefix, 1);
	else
		setenv(GIT_PREFIX_ENVIRONMENT, "", 1);

	startup_info->have_repository = !nongit_ok || !*nongit_ok;
	startup_info->prefix = prefix;

	/*
	 * Not all paths through the setup code will call 'set_git_dir()' (which
	 * directly sets up the environment) so in order to guarantee that the
	 * environment is in a consistent state after setup, explicitly setup
	 * the environment if we have a repository.
	 *
	 * NEEDSWORK: currently we allow bogus GIT_DIR values to be set in some
	 * code paths so we also need to explicitly setup the environment if
	 * the user has set GIT_DIR.  It may be beneficial to disallow bogus
	 * GIT_DIR values at some point in the future.
	 */
	if (startup_info->have_repository || getenv(GIT_DIR_ENVIRONMENT)) {
		if (!the_repository->gitdir) {
			const char *gitdir = getenv(GIT_DIR_ENVIRONMENT);
			if (!gitdir)
				gitdir = DEFAULT_GIT_DIR_ENVIRONMENT;
			repo_set_gitdir(the_repository, gitdir);
			setup_git_env();
		}
	}

	strbuf_release(&dir);
	strbuf_release(&gitdir);

	return prefix;
}