	if (!dir->basebuf.buf)
		strbuf_init(&dir->basebuf, PATH_MAX);

	/* Read from the parent directories and push them down. */
	current = stk ? stk->baselen : -1;
	strbuf_setlen(&dir->basebuf, current < 0 ? 0 : current);
	while (current < baselen) {
		const char *cp;

		stk = xcalloc(1, sizeof(*stk));
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
