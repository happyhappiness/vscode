	struct exclude_list *el;
	struct exclude_stack *stk = NULL;
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
	while (current < baselen) {
		struct exclude_stack *stk = xcalloc(1, sizeof(*stk));
		const char *cp;

		if (current < 0) {
			cp = base;
			current = 0;
		} else {
			cp = strchr(base + current + 1, '/');
			if (!cp)
				die("oops in prep_exclude");
			cp++;
		}
		stk->prev = dir->exclude_stack;
		stk->baselen = cp - base;
		stk->exclude_ix = group->nr;
		el = add_exclude_list(dir, EXC_DIRS, NULL);
		strbuf_add(&dir->basebuf, base + current, stk->baselen - current);
		assert(stk->baselen == dir->basebuf.len);

		/* Abort if the directory is excluded */
		if (stk->baselen) {
			int dt = DT_DIR;
			dir->basebuf.buf[stk->baselen - 1] = 0;
			dir->exclude = last_exclude_matching_from_lists(dir,
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
		if (dir->exclude_per_dir) {
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
			add_excludes_from_file_to_list(el->src, el->src,
						       stk->baselen, el, 1);
		}
		dir->exclude_stack = stk;
		current = stk->baselen;
	}
	strbuf_setlen(&dir->basebuf, baselen);
}

/*
 * Loads the exclude lists for the directory containing pathname, then
 * scans all exclude lists to determine whether pathname is excluded.
 * Returns the exclude_list element which matched, or NULL for
