static void prep_exclude(struct dir_struct *dir,
			 struct index_state *istate,
			 const char *base, int baselen)
{
	struct exclude_list_group *group;
	struct exclude_list *el;
	struct exclude_stack *stk = NULL;
	struct untracked_cache_dir *untracked;
	int current;

	group = &dir->exclude_list_group[EXC_DIRS];

	/*
	 * Pop the exclude lists from the EXCL_DIRS exclude_list_group
	 * which originate from directories not in the prefix of the
	 * path being checked.
	 */
	while ((stk = dir->exclude_stack) != NULL) {
		if (stk->baselen <= baselen &&
		    !strncmp(dir->basebuf.buf, base, stk->baselen))
			break;
		el = &group->el[dir->exclude_stack->exclude_ix];
		dir->exclude_stack = stk->prev;
		dir->exclude = NULL;
		free((char *)el->src); /* see strbuf_detach() below */
		clear_exclude_list(el);
		free(stk);
		group->nr--;
	}

	/* Skip traversing into sub directories if the parent is excluded */
	if (dir->exclude)
		return;

	/*
	 * Lazy initialization. All call sites currently just
	 * memset(dir, 0, sizeof(*dir)) before use. Changing all of
	 * them seems lots of work for little benefit.
	 */
	if (!dir->basebuf.buf)
		strbuf_init(&dir->basebuf, PATH_MAX);

	/* Read from the parent directories and push them down. */
	current = stk ? stk->baselen : -1;
	strbuf_setlen(&dir->basebuf, current < 0 ? 0 : current);
	if (dir->untracked)
		untracked = stk ? stk->ucd : dir->untracked->root;
	else
		untracked = NULL;

	while (current < baselen) {
		const char *cp;
		struct sha1_stat sha1_stat;

		stk = xcalloc(1, sizeof(*stk));
		if (current < 0) {
			cp = base;
			current = 0;
		} else {
			cp = strchr(base + current + 1, '/');
			if (!cp)
				die("oops in prep_exclude");
			cp++;
			untracked =
				lookup_untracked(dir->untracked, untracked,
						 base + current,
						 cp - base - current);
		}
		stk->prev = dir->exclude_stack;
		stk->baselen = cp - base;
		stk->exclude_ix = group->nr;
		stk->ucd = untracked;
		el = add_exclude_list(dir, EXC_DIRS, NULL);
		strbuf_add(&dir->basebuf, base + current, stk->baselen - current);
		assert(stk->baselen == dir->basebuf.len);

		/* Abort if the directory is excluded */
		if (stk->baselen) {
			int dt = DT_DIR;
			dir->basebuf.buf[stk->baselen - 1] = 0;
			dir->exclude = last_exclude_matching_from_lists(dir,
									istate,
				dir->basebuf.buf, stk->baselen - 1,
				dir->basebuf.buf + current, &dt);
			dir->basebuf.buf[stk->baselen - 1] = '/';
			if (dir->exclude &&
			    dir->exclude->flags & EXC_FLAG_NEGATIVE)
				dir->exclude = NULL;
			if (dir->exclude) {
				dir->exclude_stack = stk;
				return;
			}
		}

		/* Try to read per-directory file */
		hashclr(sha1_stat.sha1);
		sha1_stat.valid = 0;
		if (dir->exclude_per_dir &&
		    /*
		     * If we know that no files have been added in
		     * this directory (i.e. valid_cached_dir() has
		     * been executed and set untracked->valid) ..
		     */
		    (!untracked || !untracked->valid ||
		     /*
		      * .. and .gitignore does not exist before
		      * (i.e. null exclude_sha1). Then we can skip
		      * loading .gitignore, which would result in
		      * ENOENT anyway.
		      */
		     !is_null_sha1(untracked->exclude_sha1))) {
			/*
			 * dir->basebuf gets reused by the traversal, but we
			 * need fname to remain unchanged to ensure the src
			 * member of each struct exclude correctly
			 * back-references its source file.  Other invocations
			 * of add_exclude_list provide stable strings, so we
			 * strbuf_detach() and free() here in the caller.
			 */
			struct strbuf sb = STRBUF_INIT;
			strbuf_addbuf(&sb, &dir->basebuf);
			strbuf_addstr(&sb, dir->exclude_per_dir);
			el->src = strbuf_detach(&sb, NULL);
			add_excludes(el->src, el->src, stk->baselen, el, istate,
				     untracked ? &sha1_stat : NULL);
		}
		/*
		 * NEEDSWORK: when untracked cache is enabled, prep_exclude()
		 * will first be called in valid_cached_dir() then maybe many
		 * times more in last_exclude_matching(). When the cache is
		 * used, last_exclude_matching() will not be called and
		 * reading .gitignore content will be a waste.
		 *
		 * So when it's called by valid_cached_dir() and we can get
		 * .gitignore SHA-1 from the index (i.e. .gitignore is not
		 * modified on work tree), we could delay reading the
		 * .gitignore content until we absolutely need it in
		 * last_exclude_matching(). Be careful about ignore rule
		 * order, though, if you do that.
		 */
		if (untracked &&
		    hashcmp(sha1_stat.sha1, untracked->exclude_sha1)) {
			invalidate_gitignore(dir->untracked, untracked);
			hashcpy(untracked->exclude_sha1, sha1_stat.sha1);
		}
		dir->exclude_stack = stk;
		current = stk->baselen;
	}
	strbuf_setlen(&dir->basebuf, baselen);
}