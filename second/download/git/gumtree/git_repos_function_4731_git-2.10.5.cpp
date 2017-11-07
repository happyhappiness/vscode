static char *git_header_name(struct apply_state *state,
			     const char *line,
			     int llen)
{
	const char *name;
	const char *second = NULL;
	size_t len, line_len;

	line += strlen("diff --git ");
	llen -= strlen("diff --git ");

	if (*line == '"') {
		const char *cp;
		struct strbuf first = STRBUF_INIT;
		struct strbuf sp = STRBUF_INIT;

		if (unquote_c_style(&first, line, &second))
			goto free_and_fail1;

		/* strip the a/b prefix including trailing slash */
		cp = skip_tree_prefix(state, first.buf, first.len);
		if (!cp)
			goto free_and_fail1;
		strbuf_remove(&first, 0, cp - first.buf);

		/*
		 * second points at one past closing dq of name.
		 * find the second name.
		 */
		while ((second < line + llen) && isspace(*second))
			second++;

		if (line + llen <= second)
			goto free_and_fail1;
		if (*second == '"') {
			if (unquote_c_style(&sp, second, NULL))
				goto free_and_fail1;
			cp = skip_tree_prefix(state, sp.buf, sp.len);
			if (!cp)
				goto free_and_fail1;
			/* They must match, otherwise ignore */
			if (strcmp(cp, first.buf))
				goto free_and_fail1;
			strbuf_release(&sp);
			return strbuf_detach(&first, NULL);
		}

		/* unquoted second */
		cp = skip_tree_prefix(state, second, line + llen - second);
		if (!cp)
			goto free_and_fail1;
		if (line + llen - cp != first.len ||
		    memcmp(first.buf, cp, first.len))
			goto free_and_fail1;
		return strbuf_detach(&first, NULL);

	free_and_fail1:
		strbuf_release(&first);
		strbuf_release(&sp);
		return NULL;
	}

	/* unquoted first name */
	name = skip_tree_prefix(state, line, llen);
	if (!name)
		return NULL;

	/*
	 * since the first name is unquoted, a dq if exists must be
	 * the beginning of the second name.
	 */
	for (second = name; second < line + llen; second++) {
		if (*second == '"') {
			struct strbuf sp = STRBUF_INIT;
			const char *np;

			if (unquote_c_style(&sp, second, NULL))
				goto free_and_fail2;

			np = skip_tree_prefix(state, sp.buf, sp.len);
			if (!np)
				goto free_and_fail2;

			len = sp.buf + sp.len - np;
			if (len < second - name &&
			    !strncmp(np, name, len) &&
			    isspace(name[len])) {
				/* Good */
				strbuf_remove(&sp, 0, np - sp.buf);
				return strbuf_detach(&sp, NULL);
			}

		free_and_fail2:
			strbuf_release(&sp);
			return NULL;
		}
	}

	/*
	 * Accept a name only if it shows up twice, exactly the same
	 * form.
	 */
	second = strchr(name, '\n');
	if (!second)
		return NULL;
	line_len = second - name;
	for (len = 0 ; ; len++) {
		switch (name[len]) {
		default:
			continue;
		case '\n':
			return NULL;
		case '\t': case ' ':
			/*
			 * Is this the separator between the preimage
			 * and the postimage pathname?  Again, we are
			 * only interested in the case where there is
			 * no rename, as this is only to set def_name
			 * and a rename patch has the names elsewhere
			 * in an unambiguous form.
			 */
			if (!name[len + 1])
				return NULL; /* no postimage name */
			second = skip_tree_prefix(state, name + len + 1,
						  line_len - (len + 1));
			if (!second)
				return NULL;
			/*
			 * Does len bytes starting at "name" and "second"
			 * (that are separated by one HT or SP we just
			 * found) exactly match?
			 */
			if (second[len] == '\n' && !strncmp(name, second, len))
				return xmemdupz(name, len);
		}
	}
}