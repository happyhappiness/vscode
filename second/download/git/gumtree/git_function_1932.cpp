static struct untracked_cache_dir *validate_untracked_cache(struct dir_struct *dir,
						      int base_len,
						      const struct pathspec *pathspec)
{
	struct untracked_cache_dir *root;
	int i;

	if (!dir->untracked || getenv("GIT_DISABLE_UNTRACKED_CACHE"))
		return NULL;

	/*
	 * We only support $GIT_DIR/info/exclude and core.excludesfile
	 * as the global ignore rule files. Any other additions
	 * (e.g. from command line) invalidate the cache. This
	 * condition also catches running setup_standard_excludes()
	 * before setting dir->untracked!
	 */
	if (dir->unmanaged_exclude_files)
		return NULL;

	/*
	 * Optimize for the main use case only: whole-tree git
	 * status. More work involved in treat_leading_path() if we
	 * use cache on just a subset of the worktree. pathspec
	 * support could make the matter even worse.
	 */
	if (base_len || (pathspec && pathspec->nr))
		return NULL;

	/* Different set of flags may produce different results */
	if (dir->flags != dir->untracked->dir_flags ||
	    /*
	     * See treat_directory(), case index_nonexistent. Without
	     * this flag, we may need to also cache .git file content
	     * for the resolve_gitlink_ref() call, which we don't.
	     */
	    !(dir->flags & DIR_SHOW_OTHER_DIRECTORIES) ||
	    /* We don't support collecting ignore files */
	    (dir->flags & (DIR_SHOW_IGNORED | DIR_SHOW_IGNORED_TOO |
			   DIR_COLLECT_IGNORED)))
		return NULL;

	/*
	 * If we use .gitignore in the cache and now you change it to
	 * .gitexclude, everything will go wrong.
	 */
	if (dir->exclude_per_dir != dir->untracked->exclude_per_dir &&
	    strcmp(dir->exclude_per_dir, dir->untracked->exclude_per_dir))
		return NULL;

	/*
	 * EXC_CMDL is not considered in the cache. If people set it,
	 * skip the cache.
	 */
	if (dir->exclude_list_group[EXC_CMDL].nr)
		return NULL;

	/*
	 * An optimization in prep_exclude() does not play well with
	 * CE_SKIP_WORKTREE. It's a rare case anyway, if a single
	 * entry has that bit set, disable the whole untracked cache.
	 */
	for (i = 0; i < active_nr; i++)
		if (ce_skip_worktree(active_cache[i]))
			return NULL;

	if (!ident_in_untracked(dir->untracked)) {
		warning(_("Untracked cache is disabled on this system."));
		return NULL;
	}

	if (!dir->untracked->root) {
		const int len = sizeof(*dir->untracked->root);
		dir->untracked->root = xmalloc(len);
		memset(dir->untracked->root, 0, len);
	}

	/* Validate $GIT_DIR/info/exclude and core.excludesfile */
	root = dir->untracked->root;
	if (hashcmp(dir->ss_info_exclude.sha1,
		    dir->untracked->ss_info_exclude.sha1)) {
		invalidate_gitignore(dir->untracked, root);
		dir->untracked->ss_info_exclude = dir->ss_info_exclude;
	}
	if (hashcmp(dir->ss_excludes_file.sha1,
		    dir->untracked->ss_excludes_file.sha1)) {
		invalidate_gitignore(dir->untracked, root);
		dir->untracked->ss_excludes_file = dir->ss_excludes_file;
	}

	/* Make sure this directory is not dropped out at saving phase */
	root->recurse = 1;
	return root;
}