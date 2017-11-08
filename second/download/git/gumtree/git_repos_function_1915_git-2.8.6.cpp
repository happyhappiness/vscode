void prepare_attr_stack(const char *path, int dirlen)
{
	struct attr_stack *elem, *info;
	int len;
	const char *cp;

	/*
	 * At the bottom of the attribute stack is the built-in
	 * set of attribute definitions, followed by the contents
	 * of $(prefix)/etc/gitattributes and a file specified by
	 * core.attributesfile.  Then, contents from
	 * .gitattribute files from directories closer to the
	 * root to the ones in deeper directories are pushed
	 * to the stack.  Finally, at the very top of the stack
	 * we always keep the contents of $GIT_DIR/info/attributes.
	 *
	 * When checking, we use entries from near the top of the
	 * stack, preferring $GIT_DIR/info/attributes, then
	 * .gitattributes in deeper directories to shallower ones,
	 * and finally use the built-in set as the default.
	 */
	bootstrap_attr_stack();

	/*
	 * Pop the "info" one that is always at the top of the stack.
	 */
	info = attr_stack;
	attr_stack = info->prev;

	/*
	 * Pop the ones from directories that are not the prefix of
	 * the path we are checking. Break out of the loop when we see
	 * the root one (whose origin is an empty string "") or the builtin
	 * one (whose origin is NULL) without popping it.
	 */
	while (attr_stack->origin) {
		int namelen = strlen(attr_stack->origin);

		elem = attr_stack;
		if (namelen <= dirlen &&
		    !strncmp(elem->origin, path, namelen) &&
		    (!namelen || path[namelen] == '/'))
			break;

		debug_pop(elem);
		attr_stack = elem->prev;
		free_attr_elem(elem);
	}

	/*
	 * Read from parent directories and push them down
	 */
	if (!is_bare_repository() || direction == GIT_ATTR_INDEX) {
		/*
		 * bootstrap_attr_stack() should have added, and the
		 * above loop should have stopped before popping, the
		 * root element whose attr_stack->origin is set to an
		 * empty string.
		 */
		struct strbuf pathbuf = STRBUF_INIT;

		assert(attr_stack->origin);
		while (1) {
			len = strlen(attr_stack->origin);
			if (dirlen <= len)
				break;
			cp = memchr(path + len + 1, '/', dirlen - len - 1);
			if (!cp)
				cp = path + dirlen;
			strbuf_add(&pathbuf, path, cp - path);
			strbuf_addch(&pathbuf, '/');
			strbuf_addstr(&pathbuf, GITATTRIBUTES_FILE);
			elem = read_attr(pathbuf.buf, 0);
			strbuf_setlen(&pathbuf, cp - path);
			elem->origin = strbuf_detach(&pathbuf, &elem->originlen);
			elem->prev = attr_stack;
			attr_stack = elem;
			debug_push(elem);
		}

		strbuf_release(&pathbuf);
	}

	/*
	 * Finally push the "info" one at the top of the stack.
	 */
	info->prev = attr_stack;
	attr_stack = info;
}